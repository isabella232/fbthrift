/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <type_traits>

#if (!defined(_MSC_VER) && __has_include(<optional>)) ||        \
    (defined(_MSC_VER) && (__cplusplus >= 201703L || _MSVC_LANG >= 201703L))
#include <optional>
// Technically it should be 201606 but std::optional is present with 201603.
#if __cpp_lib_optional >= 201603 || _LIBCPP_STD_VER > 14
#define THRIFT_HAS_OPTIONAL
#endif
#endif

#include <assert.h>
#include <limits.h>
#include <folly/CPortability.h>
#include <folly/CppAttributes.h>
#include <folly/Portability.h>
#include <folly/Traits.h>
#include <folly/synchronization/AtomicUtil.h>
#include <thrift/lib/cpp2/BoxedValuePtr.h>
#include <thrift/lib/cpp2/Thrift.h>

namespace apache {
namespace thrift {
namespace detail {

template <typename T>
using is_set_t =
    std::conditional_t<std::is_const<T>::value, const uint8_t, uint8_t>;

[[noreturn]] void throw_on_bad_field_access();

struct ensure_isset_unsafe_fn;
struct unset_unsafe_fn;
struct alias_isset_fn;

// IntWrapper is a wrapper of integer that's always copy/move assignable
// even if integer is atomic
template <typename T>
struct IntWrapper {
  IntWrapper() = default;
  explicit IntWrapper(T t) : value(t) {}

  T value{0};
};

template <typename U>
struct IntWrapper<std::atomic<U>> {
  IntWrapper() = default;

  IntWrapper(const IntWrapper& other) noexcept : value(other.value.load()) {}
  IntWrapper(IntWrapper&& other) noexcept : value(other.value.load()) {}

  IntWrapper& operator=(const IntWrapper& other) noexcept {
    value = other.value.load();
    return *this;
  }

  IntWrapper& operator=(IntWrapper&& other) noexcept {
    value = other.value.load();
    return *this;
  }

  std::atomic<U> value{0};
};

template <typename T>
class BitSet {
 public:
  BitSet() = default;

  explicit BitSet(T value) : int_(value) {}

  BitSet(const BitSet&) = default;

  class reference {
   public:
    reference(BitSet& bitSet, const uint8_t bit) : bitSet_(bitSet), bit_(bit) {}

    reference& operator=(bool flag) {
      if (flag) {
        bitSet_.set(bit_);
      } else {
        bitSet_.reset(bit_);
      }
      return *this;
    }

    operator bool() const { return bitSet_.get(bit_); }

    reference& operator=(reference& other) { return *this = bool(other); }

   private:
    BitSet& bitSet_;
    const uint8_t bit_;
  };

  bool operator[](const uint8_t bit) const {
    assert(bit < NUM_BITS);
    return get(bit);
  }

  reference operator[](const uint8_t bit) {
    assert(bit < NUM_BITS);
    return reference(*this, bit);
  }

  T& value() { return int_.value; }

  const T& value() const { return int_.value; }

 private:
  template <class U>
  static bool get(U u, std::size_t bit) {
    return u & (U(1) << bit);
  }

  template <class U>
  static void set(U& u, std::size_t bit) {
    u |= (U(1) << bit);
  }

  template <class U>
  static void reset(U& u, std::size_t bit) {
    u &= ~(U(1) << bit);
  }

  template <class U>
  static bool get(const std::atomic<U>& u, std::size_t bit) {
    return u.load(std::memory_order_relaxed) & (U(1) << bit);
  }

  template <class U>
  static void set(std::atomic<U>& u, std::size_t bit) {
    folly::atomic_fetch_set(u, bit, std::memory_order_relaxed);
  }

  template <class U>
  static void reset(std::atomic<U>& u, std::size_t bit) {
    folly::atomic_fetch_reset(u, bit, std::memory_order_relaxed);
  }

  bool get(std::size_t bit) const { return get(int_.value, bit); }
  void set(std::size_t bit) { set(int_.value, bit); }
  void reset(std::size_t bit) { reset(int_.value, bit); }

  IntWrapper<T> int_;

  static constexpr int NUM_BITS = sizeof(T) * CHAR_BIT;
};

template <bool kIsConst>
class BitRef {
  template <bool B>
  friend class BitRef;

 public:
  using Isset = std::conditional_t<kIsConst, const uint8_t, uint8_t>;
  using AtomicIsset = std::
      conditional_t<kIsConst, const std::atomic<uint8_t>, std::atomic<uint8_t>>;

  FOLLY_ERASE BitRef(Isset& isset, uint8_t bit_index)
      : value_(isset), bit_index_(bit_index) {}

  FOLLY_ERASE BitRef(AtomicIsset& isset, uint8_t bit_index)
      : value_(isset), bit_index_(bit_index), is_atomic_(true) {}

  template <bool B>
  explicit BitRef(const BitRef<B>& other)
      : value_(
            other.is_atomic_ ? IssetBitSet(other.value_.atomic.value())
                             : IssetBitSet(other.value_.non_atomic.value())),
        bit_index_(other.bit_index_),
        is_atomic_(other.is_atomic_) {}

#if FOLLY_MOBILE
  // We have this attribute to prevent binary size regression
  // TODO: Remove special attribute for MOBILE
  FOLLY_ERASE
#endif
  void operator=(bool flag) {
    if (is_atomic_) {
      value_.atomic[bit_index_] = flag;
    } else {
      value_.non_atomic[bit_index_] = flag;
    }
  }

  explicit operator bool() const {
    if (is_atomic_) {
      return value_.atomic[bit_index_];
    } else {
      return value_.non_atomic[bit_index_];
    }
  }

 private:
  union IssetBitSet {
    explicit IssetBitSet(Isset& isset) : non_atomic(isset) {}
    explicit IssetBitSet(AtomicIsset& isset) : atomic(isset) {}
    apache::thrift::detail::BitSet<Isset&> non_atomic;
    apache::thrift::detail::BitSet<AtomicIsset&> atomic;
  } value_;

  const uint8_t bit_index_;
  const bool is_atomic_ = false;
};
} // namespace detail

// A reference to an unqualified field of the possibly const-qualified type
// std::remove_reference_t<T> in a Thrift-generated struct.
template <typename T>
class field_ref {
  static_assert(std::is_reference<T>::value, "not a reference");

  template <typename U>
  friend class field_ref;
  friend struct apache::thrift::detail::unset_unsafe_fn;

 public:
  using value_type = std::remove_reference_t<T>;
  using reference_type = T;

 private:
  using BitRef =
      apache::thrift::detail::BitRef<std::is_const<value_type>::value>;

 public:
  FOLLY_ERASE field_ref(
      reference_type value,
      typename BitRef::Isset& is_set,
      const uint8_t bit_index = 0) noexcept
      : value_(value), bitref_(is_set, bit_index) {}

  FOLLY_ERASE field_ref(
      reference_type value,
      typename BitRef::AtomicIsset& is_set,
      const uint8_t bit_index = 0) noexcept
      : value_(value), bitref_(is_set, bit_index) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<
              std::add_const_t<std::remove_reference_t<U>>,
              value_type>{} &&
              !(std::is_rvalue_reference<T>{} && std::is_lvalue_reference<U>{}),
          int> = 0>
  FOLLY_ERASE /* implicit */ field_ref(const field_ref<U>& other) noexcept
      : value_(other.value_), bitref_(other.bitref_) {}

  template <typename U = value_type>
  FOLLY_ERASE
      std::enable_if_t<std::is_assignable<value_type&, U&&>::value, field_ref&>
      operator=(U&& value) noexcept(
          std::is_nothrow_assignable<value_type&, U&&>::value) {
    value_ = static_cast<U&&>(value);
    bitref_ = true;
    return *this;
  }

  // Workaround for https://bugs.llvm.org/show_bug.cgi?id=49442
  FOLLY_ERASE field_ref& operator=(value_type&& value) noexcept(
      std::is_nothrow_move_assignable<value_type>::value) {
    value_ = static_cast<value_type&&>(value);
    bitref_ = true;
    return *this;
    value.~value_type(); // Force emit destructor...
  }

  // Assignment from field_ref is intentionally not provided to prevent
  // potential confusion between two possible behaviors, copying and reference
  // rebinding. The copy_from method is provided instead.
  template <typename U>
  FOLLY_ERASE void copy_from(field_ref<U> other) noexcept(
      std::is_nothrow_assignable<value_type&, U>::value) {
    value_ = other.value();
    bitref_ = other.is_set();
  }

  [[deprecated("Use is_set() method instead")]] FOLLY_ERASE bool has_value()
      const noexcept {
    return bool(bitref_);
  }

  // Returns true iff the field is set. field_ref doesn't provide conversion to
  // bool to avoid confusion between checking if the field is set and getting
  // the field's value, particularly for bool fields.
  FOLLY_ERASE bool is_set() const noexcept { return bool(bitref_); }

  // Returns a reference to the value.
  FOLLY_ERASE reference_type value() const noexcept {
    return static_cast<reference_type>(value_);
  }

  FOLLY_ERASE reference_type operator*() const noexcept {
    return static_cast<reference_type>(value_);
  }

  FOLLY_ERASE value_type* operator->() const noexcept { return &value_; }

  FOLLY_ERASE reference_type ensure() noexcept {
    bitref_ = true;
    return static_cast<reference_type>(value_);
  }

  template <typename Index>
  FOLLY_ERASE auto operator[](const Index& index) const -> decltype(auto) {
    return value_[index];
  }

  template <typename... Args>
  FOLLY_ERASE value_type& emplace(Args&&... args) {
    bitref_ = false; // C++ Standard requires *this to be empty if
                     // `std::optional::emplace(...)` throws
    value_ = value_type(static_cast<Args&&>(args)...);
    bitref_ = true;
    return value_;
  }

  template <class U, class... Args>
  FOLLY_ERASE std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>, Args&&...>::
          value,
      value_type&>
  emplace(std::initializer_list<U> ilist, Args&&... args) {
    bitref_ = false;
    value_ = value_type(ilist, static_cast<Args&&>(args)...);
    bitref_ = true;
    return value_;
  }

 private:
  value_type& value_;
  BitRef bitref_;
};

template <typename T, typename U>
bool operator==(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs == *rhs;
}

template <typename T, typename U>
bool operator!=(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs != *rhs;
}

template <typename T, typename U>
bool operator<(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs < *rhs;
}

template <typename T, typename U>
bool operator>(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs > *rhs;
}

template <typename T, typename U>
bool operator<=(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs <= *rhs;
}

template <typename T, typename U>
bool operator>=(field_ref<T> lhs, field_ref<U> rhs) {
  return *lhs >= *rhs;
}

template <typename T, typename U>
bool operator==(field_ref<T> lhs, const U& rhs) {
  return *lhs == rhs;
}

template <typename T, typename U>
bool operator!=(field_ref<T> lhs, const U& rhs) {
  return *lhs != rhs;
}

template <typename T, typename U>
bool operator<(field_ref<T> lhs, const U& rhs) {
  return *lhs < rhs;
}

template <typename T, typename U>
bool operator>(field_ref<T> lhs, const U& rhs) {
  return *lhs > rhs;
}

template <typename T, typename U>
bool operator<=(field_ref<T> lhs, const U& rhs) {
  return *lhs <= rhs;
}

template <typename T, typename U>
bool operator>=(field_ref<T> lhs, const U& rhs) {
  return *lhs >= rhs;
}

template <typename T, typename U>
bool operator==(const T& lhs, field_ref<U> rhs) {
  return lhs == *rhs;
}

template <typename T, typename U>
bool operator!=(const T& lhs, field_ref<U> rhs) {
  return lhs != *rhs;
}

template <typename T, typename U>
bool operator<(const T& lhs, field_ref<U> rhs) {
  return lhs < *rhs;
}

template <typename T, typename U>
bool operator>(const T& lhs, field_ref<U> rhs) {
  return lhs > *rhs;
}

template <typename T, typename U>
bool operator<=(const T& lhs, field_ref<U> rhs) {
  return lhs <= *rhs;
}

template <typename T, typename U>
bool operator>=(const T& lhs, field_ref<U> rhs) {
  return lhs >= *rhs;
}

// A reference to an optional field of the possibly const-qualified type
// std::remove_reference_t<T> in a Thrift-generated struct.
template <typename T>
class optional_field_ref {
  static_assert(std::is_reference<T>::value, "not a reference");

  template <typename U>
  friend class optional_field_ref;
  friend struct apache::thrift::detail::ensure_isset_unsafe_fn;
  friend struct apache::thrift::detail::unset_unsafe_fn;
  friend struct apache::thrift::detail::alias_isset_fn;

 public:
  using value_type = std::remove_reference_t<T>;
  using reference_type = T;

 private:
  using BitRef =
      apache::thrift::detail::BitRef<std::is_const<value_type>::value>;

  // for alias_isset_fn
  FOLLY_ERASE optional_field_ref(reference_type value, BitRef bitref)
      : value_(value), bitref_(bitref) {}

 public:
  FOLLY_ERASE optional_field_ref(
      reference_type value,
      typename BitRef::Isset& is_set,
      const uint8_t bit_index = 0) noexcept
      : value_(value), bitref_(is_set, bit_index) {}

  FOLLY_ERASE optional_field_ref(
      reference_type value,
      typename BitRef::AtomicIsset& is_set,
      const uint8_t bit_index = 0) noexcept
      : value_(value), bitref_(is_set, bit_index) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<
              std::add_const_t<std::remove_reference_t<U>>,
              value_type>{} &&
              !(std::is_rvalue_reference<T>{} && std::is_lvalue_reference<U>{}),
          int> = 0>
  FOLLY_ERASE /* implicit */ optional_field_ref(
      const optional_field_ref<U>& other) noexcept
      : value_(other.value_), bitref_(other.bitref_) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<T, U&&>{} || std::is_same<T, const U&&>{},
          int> = 0>
  FOLLY_ERASE explicit optional_field_ref(
      const optional_field_ref<U&>& other) noexcept
      : value_(other.value_), bitref_(other.bitref_) {}

  template <typename U = value_type>
  FOLLY_ERASE std::enable_if_t<
      std::is_assignable<value_type&, U&&>::value,
      optional_field_ref&>
  operator=(U&& value) noexcept(
      std::is_nothrow_assignable<value_type&, U&&>::value) {
    value_ = static_cast<U&&>(value);
    bitref_ = true;
    return *this;
  }

  // Workaround for https://bugs.llvm.org/show_bug.cgi?id=49442
  FOLLY_ERASE optional_field_ref& operator=(value_type&& value) noexcept(
      std::is_nothrow_move_assignable<value_type>::value) {
    value_ = static_cast<value_type&&>(value);
    bitref_ = true;
    return *this;
    value.~value_type(); // Force emit destructor...
  }

  // Copies the data (the set flag and the value if available) from another
  // optional_field_ref object.
  //
  // Assignment from optional_field_ref is intentionally not provided to prevent
  // potential confusion between two possible behaviors, copying and reference
  // rebinding. This copy_from method is provided instead.
  template <typename U>
  FOLLY_ERASE void copy_from(const optional_field_ref<U>& other) noexcept(
      std::is_nothrow_assignable<value_type&, U>::value) {
    value_ = other.value_unchecked();
    bitref_ = other.has_value();
  }

  template <typename U>
  FOLLY_ERASE void move_from(optional_field_ref<U> other) noexcept(
      std::is_nothrow_assignable<value_type&, std::remove_reference_t<U>&&>::
          value) {
    value_ = static_cast<std::remove_reference_t<U>&&>(other.value_);
    bitref_ = other.has_value();
  }

#ifdef THRIFT_HAS_OPTIONAL
  template <typename U>
  FOLLY_ERASE void from_optional(const std::optional<U>& other) noexcept(
      std::is_nothrow_assignable<value_type&, const U&>::value) {
    // Use if instead of a shorter ternary expression to prevent a potential
    // copy if T and U mismatch.
    if (other) {
      value_ = *other;
    } else {
      value_ = {};
    }
    bitref_ = other.has_value();
  }

  // Moves the value from std::optional. As std::optional's move constructor,
  // move_from doesn't make other empty.
  template <typename U>
  FOLLY_ERASE void from_optional(std::optional<U>&& other) noexcept(
      std::is_nothrow_assignable<value_type&, U&&>::value) {
    // Use if instead of a shorter ternary expression to prevent a potential
    // copy if T and U mismatch.
    if (other) {
      value_ = static_cast<U&&>(*other);
    } else {
      value_ = {};
    }
    bitref_ = other.has_value();
  }

  FOLLY_ERASE std::optional<std::remove_const_t<value_type>> to_optional()
      const {
    using type = std::optional<std::remove_const_t<value_type>>;
    return bitref_ ? type(value_) : type();
  }
#endif

  FOLLY_ERASE bool has_value() const noexcept { return bool(bitref_); }

  FOLLY_ERASE explicit operator bool() const noexcept { return bool(bitref_); }

  FOLLY_ERASE void reset() noexcept(
      std::is_nothrow_move_assignable<value_type>::value) {
    value_ = value_type();
    bitref_ = false;
  }

  // Returns a reference to the value if this optional_field_ref has one; throws
  // bad_field_access otherwise.
  FOLLY_ERASE reference_type value() const {
    throw_if_unset();
    return static_cast<reference_type>(value_);
  }

  template <typename U = std::remove_const_t<value_type>>
  FOLLY_ERASE std::remove_const_t<value_type> value_or(
      U&& default_value) const {
    using type = std::remove_const_t<value_type>;
    return bitref_ ? type(static_cast<reference_type>(value_))
                   : type(static_cast<U&&>(default_value));
  }

  // Returns a reference to the value without checking whether it is available.
  FOLLY_ERASE reference_type value_unchecked() const {
    return static_cast<reference_type>(value_);
  }

  FOLLY_ERASE reference_type operator*() const { return value(); }

  FOLLY_ERASE value_type* operator->() const {
    throw_if_unset();
    return &value_;
  }

  FOLLY_ERASE reference_type
  ensure() noexcept(std::is_nothrow_move_assignable<value_type>::value) {
    if (!bitref_) {
      value_ = value_type();
      bitref_ = true;
    }
    return static_cast<reference_type>(value_);
  }

  template <typename... Args>
  FOLLY_ERASE value_type& emplace(Args&&... args) {
    reset(); // C++ Standard requires *this to be empty if
             // `std::optional::emplace(...)` throws
    value_ = value_type(static_cast<Args&&>(args)...);
    bitref_ = true;
    return value_;
  }

  template <class U, class... Args>
  FOLLY_ERASE std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>&, Args&&...>::
          value,
      value_type&>
  emplace(std::initializer_list<U> ilist, Args&&... args) {
    reset();
    value_ = value_type(ilist, static_cast<Args&&>(args)...);
    bitref_ = true;
    return value_;
  }

 private:
  FOLLY_ERASE void throw_if_unset() const {
    if (!bitref_) {
      apache::thrift::detail::throw_on_bad_field_access();
    }
  }

  value_type& value_;
  BitRef bitref_;
};

template <typename T1, typename T2>
bool operator==(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  return a && b ? *a == *b : a.has_value() == b.has_value();
}

template <typename T1, typename T2>
bool operator!=(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  return !(a == b);
}

template <typename T1, typename T2>
bool operator<(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  if (a.has_value() != b.has_value()) {
    return a.has_value() < b.has_value();
  }
  return a ? *a < *b : false;
}

template <typename T1, typename T2>
bool operator>(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  return b < a;
}

template <typename T1, typename T2>
bool operator<=(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  return !(a > b);
}

template <typename T1, typename T2>
bool operator>=(optional_field_ref<T1> a, optional_field_ref<T2> b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator==(optional_field_ref<T> a, const U& b) {
  return a ? *a == b : false;
}

template <typename T, typename U>
bool operator!=(optional_field_ref<T> a, const U& b) {
  return !(a == b);
}

template <typename T, typename U>
bool operator==(const U& a, optional_field_ref<T> b) {
  return b == a;
}

template <typename T, typename U>
bool operator!=(const U& a, optional_field_ref<T> b) {
  return b != a;
}

template <typename T, typename U>
bool operator<(optional_field_ref<T> a, const U& b) {
  return a ? *a < b : true;
}

template <typename T, typename U>
bool operator>(optional_field_ref<T> a, const U& b) {
  return a ? *a > b : false;
}

template <typename T, typename U>
bool operator<=(optional_field_ref<T> a, const U& b) {
  return !(a > b);
}

template <typename T, typename U>
bool operator>=(optional_field_ref<T> a, const U& b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator<(const U& a, optional_field_ref<T> b) {
  return b > a;
}

template <typename T, typename U>
bool operator<=(const U& a, optional_field_ref<T> b) {
  return b >= a;
}

template <typename T, typename U>
bool operator>(const U& a, optional_field_ref<T> b) {
  return b < a;
}

template <typename T, typename U>
bool operator>=(const U& a, optional_field_ref<T> b) {
  return b <= a;
}

#ifdef THRIFT_HAS_OPTIONAL
template <class T>
bool operator==(const optional_field_ref<T>& a, std::nullopt_t) {
  return !a.has_value();
}
template <class T>
bool operator==(std::nullopt_t, const optional_field_ref<T>& a) {
  return !a.has_value();
}
template <class T>
bool operator!=(const optional_field_ref<T>& a, std::nullopt_t) {
  return a.has_value();
}
template <class T>
bool operator!=(std::nullopt_t, const optional_field_ref<T>& a) {
  return a.has_value();
}
#endif

namespace detail {

template <typename T>
struct is_boxed_value_ptr : std::false_type {};

template <typename T>
struct is_boxed_value_ptr<boxed_value_ptr<T>> : std::true_type {};

template <typename From, typename To>
using copy_reference_t = std::conditional_t<
    std::is_lvalue_reference<From>{},
    std::add_lvalue_reference_t<To>,
    std::add_rvalue_reference_t<To>>;

template <typename From, typename To>
using copy_const_t = std::conditional_t<
    std::is_const<std::remove_reference_t<From>>{},
    std::add_const_t<To>,
    To>;

} // namespace detail

template <typename T>
class optional_boxed_field_ref {
  static_assert(std::is_reference<T>::value, "not a reference");
  static_assert(
      detail::is_boxed_value_ptr<folly::remove_cvref_t<T>>::value,
      "not a boxed_value_ptr");

  using element_type = typename folly::remove_cvref_t<T>::element_type;

  template <typename U>
  friend class optional_boxed_field_ref;

 public:
  using value_type = detail::copy_const_t<T, element_type>;
  using reference_type = detail::copy_reference_t<T, value_type>;

  FOLLY_ERASE explicit optional_boxed_field_ref(T value) noexcept
      : value_(value) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<
              std::add_const_t<std::remove_reference_t<U>>,
              std::remove_reference_t<T>>{} &&
              !(std::is_rvalue_reference<T>{} && std::is_lvalue_reference<U>{}),
          int> = 0>
  FOLLY_ERASE /* implicit */ optional_boxed_field_ref(
      const optional_boxed_field_ref<U>& other) noexcept
      : value_(other.value_) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<T, U&&>{} || std::is_same<T, const U&&>{},
          int> = 0>
  FOLLY_ERASE explicit optional_boxed_field_ref(
      const optional_boxed_field_ref<U&>& other) noexcept
      : value_(other.value_) {}

  template <typename U = value_type>
  FOLLY_ERASE std::enable_if_t<
      std::is_assignable<value_type&, U&&>::value,
      optional_boxed_field_ref&>
  operator=(U&& value) {
    value_ = static_cast<U&&>(value);
    return *this;
  }

  // Copies the data (the set flag and the value if available) from another
  // optional_boxed_field_ref object.
  //
  // Assignment from optional_boxed_field_ref is intentionally not provided to
  // prevent potential confusion between two possible behaviors, copying and
  // reference rebinding. This copy_from method is provided instead.
  template <typename U>
  FOLLY_ERASE void copy_from(const optional_boxed_field_ref<U>& other) {
    value_ = T(other.value_);
  }

  template <typename U>
  FOLLY_ERASE void move_from(optional_boxed_field_ref<U> other) noexcept {
    value_ = static_cast<std::remove_reference_t<U>&&>(other.value_);
  }

#ifdef THRIFT_HAS_OPTIONAL
  template <typename U>
  FOLLY_ERASE void from_optional(const std::optional<U>& other) {
    // Use if instead of a shorter ternary expression to prevent a potential
    // copy if T and U mismatch.
    if (other) {
      value_ = *other;
    } else {
      value_ = {};
    }
  }

  // Moves the value from std::optional. As std::optional's move constructor,
  // move_from doesn't make other empty.
  template <typename U>
  FOLLY_ERASE void from_optional(std::optional<U>&& other) {
    // Use if instead of a shorter ternary expression to prevent a potential
    // copy if T and U mismatch.
    if (other) {
      value_ = static_cast<U&&>(*other);
    } else {
      value_ = {};
    }
  }

  FOLLY_ERASE std::optional<std::remove_const_t<value_type>> to_optional()
      const {
    using type = std::optional<std::remove_const_t<value_type>>;
    return has_value() ? type(*value_) : type();
  }
#endif

  FOLLY_ERASE bool has_value() const noexcept {
    return static_cast<bool>(value_);
  }

  FOLLY_ERASE explicit operator bool() const noexcept { return has_value(); }

  FOLLY_ERASE void reset() noexcept { value_.reset(); }

  // Returns a reference to the value if this optional_boxed_field_ref has one;
  // throws bad_field_access otherwise.
  FOLLY_ERASE reference_type value() const {
    throw_if_unset();
    return static_cast<reference_type>(*value_);
  }

  template <typename U = std::remove_const_t<value_type>>
  FOLLY_ERASE std::remove_const_t<value_type> value_or(
      U&& default_value) const {
    using type = std::remove_const_t<value_type>;
    return has_value() ? type(static_cast<reference_type>(*value_))
                       : type(static_cast<U&&>(default_value));
  }

  FOLLY_ERASE reference_type operator*() const { return value(); }

  FOLLY_ERASE value_type* operator->() const {
    throw_if_unset();
    return &*value_;
  }

  FOLLY_ERASE reference_type ensure() {
    if (!has_value()) {
      emplace();
    }
    return static_cast<reference_type>(*value_);
  }

  template <typename... Args>
  FOLLY_ERASE value_type& emplace(Args&&... args) {
    reset(); // C++ Standard requires *this to be empty if
             // `std::optional::emplace(...)` throws
    value_ = value_type(static_cast<Args&&>(args)...);
    return *value_;
  }

  template <class U, class... Args>
  FOLLY_ERASE std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>&, Args&&...>::
          value,
      value_type&>
  emplace(std::initializer_list<U> ilist, Args&&... args) {
    reset();
    value_ = value_type(ilist, static_cast<Args&&>(args)...);
    return *value_;
  }

 private:
  FOLLY_ERASE void throw_if_unset() const {
    if (!has_value()) {
      apache::thrift::detail::throw_on_bad_field_access();
    }
  }

  std::remove_reference_t<T>& value_;
};

template <typename T1, typename T2>
bool operator==(
    optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  return a && b ? *a == *b : a.has_value() == b.has_value();
}

template <typename T1, typename T2>
bool operator!=(
    optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  return !(a == b);
}

template <typename T1, typename T2>
bool operator<(optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  if (a.has_value() != b.has_value()) {
    return a.has_value() < b.has_value();
  }
  return a ? *a < *b : false;
}

template <typename T1, typename T2>
bool operator>(optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  return b < a;
}

template <typename T1, typename T2>
bool operator<=(
    optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  return !(a > b);
}

template <typename T1, typename T2>
bool operator>=(
    optional_boxed_field_ref<T1> a, optional_boxed_field_ref<T2> b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator==(optional_boxed_field_ref<T> a, const U& b) {
  return a ? *a == b : false;
}

template <typename T, typename U>
bool operator!=(optional_boxed_field_ref<T> a, const U& b) {
  return !(a == b);
}

template <typename T, typename U>
bool operator==(const U& a, optional_boxed_field_ref<T> b) {
  return b == a;
}

template <typename T, typename U>
bool operator!=(const U& a, optional_boxed_field_ref<T> b) {
  return b != a;
}

template <typename T, typename U>
bool operator<(optional_boxed_field_ref<T> a, const U& b) {
  return a ? *a < b : true;
}

template <typename T, typename U>
bool operator>(optional_boxed_field_ref<T> a, const U& b) {
  return a ? *a > b : false;
}

template <typename T, typename U>
bool operator<=(optional_boxed_field_ref<T> a, const U& b) {
  return !(a > b);
}

template <typename T, typename U>
bool operator>=(optional_boxed_field_ref<T> a, const U& b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator<(const U& a, optional_boxed_field_ref<T> b) {
  return b > a;
}

template <typename T, typename U>
bool operator<=(const U& a, optional_boxed_field_ref<T> b) {
  return b >= a;
}

template <typename T, typename U>
bool operator>(const U& a, optional_boxed_field_ref<T> b) {
  return b < a;
}

template <typename T, typename U>
bool operator>=(const U& a, optional_boxed_field_ref<T> b) {
  return b <= a;
}

#ifdef THRIFT_HAS_OPTIONAL
template <class T>
bool operator==(const optional_boxed_field_ref<T>& a, std::nullopt_t) {
  return !a.has_value();
}
template <class T>
bool operator==(std::nullopt_t, const optional_boxed_field_ref<T>& a) {
  return !a.has_value();
}
template <class T>
bool operator!=(const optional_boxed_field_ref<T>& a, std::nullopt_t) {
  return a.has_value();
}
template <class T>
bool operator!=(std::nullopt_t, const optional_boxed_field_ref<T>& a) {
  return a.has_value();
}
#endif

namespace detail {

struct get_pointer_fn {
  template <class T>
  T* operator()(optional_field_ref<T&> field) const {
    return field ? &*field : nullptr;
  }

  template <class T>
  auto* operator()(optional_boxed_field_ref<T&> field) const {
    return field ? &*field : nullptr;
  }
};

struct can_throw_fn {
  template <typename T>
  FOLLY_ERASE T&& operator()(T&& value) const {
    return static_cast<T&&>(value);
  }
};

struct ensure_isset_unsafe_fn {
  template <typename T>
  void operator()(optional_field_ref<T> ref) const noexcept {
    ref.bitref_ = true;
  }
};

struct unset_unsafe_fn {
  template <typename T>
  void operator()(field_ref<T> ref) const noexcept {
    ref.bitref_ = false;
  }

  template <typename T>
  void operator()(optional_field_ref<T> ref) const noexcept {
    ref.bitref_ = false;
  }
};

struct alias_isset_fn {
  template <typename T, typename F>
  auto operator()(optional_field_ref<T> ref, F functor) const
      noexcept(noexcept(functor(ref.value_))) {
    auto&& result = functor(ref.value_);
    return optional_field_ref<decltype(result)>(
        static_cast<decltype(result)>(result), ref.bitref_);
  }
};

template <typename T>
FOLLY_ERASE apache::thrift::optional_field_ref<T&&> make_optional_field_ref(
    T&& ref,
    apache::thrift::detail::is_set_t<std::remove_reference_t<T>>& is_set) {
  return {std::forward<T>(ref), is_set};
}

template <typename T>
FOLLY_ERASE apache::thrift::field_ref<T&&> make_field_ref(
    T&& ref,
    apache::thrift::detail::is_set_t<std::remove_reference_t<T>>& is_set) {
  return {std::forward<T>(ref), is_set};
}

} // namespace detail

constexpr apache::thrift::detail::get_pointer_fn get_pointer;

//  can_throw
//
//  Used to annotate optional field accesses that can throw,
//  suppressing any linter warning about unchecked access.
//
//  Example:
//
//    auto value = apache::thrift::can_throw(*obj.field_ref());
constexpr apache::thrift::detail::can_throw_fn can_throw;

[[deprecated("Use `emplace` or `operator=` to set Thrift fields.")]] //
constexpr apache::thrift::detail::ensure_isset_unsafe_fn ensure_isset_unsafe;

constexpr apache::thrift::detail::ensure_isset_unsafe_fn
    ensure_isset_unsafe_deprecated;

[[deprecated("Use `reset` to clear Thrift fields.")]] //
constexpr apache::thrift::detail::unset_unsafe_fn unset_unsafe;

constexpr apache::thrift::detail::unset_unsafe_fn unset_unsafe_deprecated;

[[deprecated]] //
constexpr apache::thrift::detail::alias_isset_fn alias_isset;

// A reference to an required field of the possibly const-qualified type
// std::remove_reference_t<T> in a Thrift-generated struct.
template <typename T>
class required_field_ref {
  static_assert(std::is_reference<T>::value, "not a reference");

  template <typename U>
  friend class required_field_ref;

 public:
  using value_type = std::remove_reference_t<T>;
  using reference_type = T;

  FOLLY_ERASE explicit required_field_ref(reference_type value) noexcept
      : value_(value) {}

  template <
      typename U,
      std::enable_if_t<
          std::is_same<
              std::add_const_t<std::remove_reference_t<U>>,
              value_type>{} &&
              !(std::is_rvalue_reference<T>{} && std::is_lvalue_reference<U>{}),
          int> = 0>
  FOLLY_ERASE /* implicit */ required_field_ref(
      const required_field_ref<U>& other) noexcept
      : value_(other.value_) {}

  template <typename U = value_type>
  FOLLY_ERASE std::enable_if_t<
      std::is_assignable<value_type&, U&&>::value,
      required_field_ref&>
  operator=(U&& value) noexcept(
      std::is_nothrow_assignable<value_type&, U&&>::value) {
    value_ = static_cast<U&&>(value);
    return *this;
  }

  // Workaround for https://bugs.llvm.org/show_bug.cgi?id=49442
  FOLLY_ERASE required_field_ref& operator=(value_type&& value) noexcept(
      std::is_nothrow_move_assignable<value_type>::value) {
    value_ = static_cast<value_type&&>(value);
    return *this;
    value.~value_type(); // Force emit destructor...
  }

  // Assignment from required_field_ref is intentionally not provided to prevent
  // potential confusion between two possible behaviors, copying and reference
  // rebinding. The copy_from method is provided instead.
  template <typename U>
  FOLLY_ERASE void copy_from(required_field_ref<U> other) noexcept(
      std::is_nothrow_assignable<value_type&, U>::value) {
    value_ = other.value();
  }

  // Returns true iff the field is set. required_field_ref doesn't provide
  // conversion to bool to avoid confusion between checking if the field is set
  // and getting the field's value, particularly for bool fields.
  FOLLY_ERASE bool has_value() const noexcept { return true; }

  // Returns a reference to the value.
  FOLLY_ERASE reference_type value() const noexcept {
    return static_cast<reference_type>(value_);
  }

  FOLLY_ERASE reference_type operator*() const noexcept {
    return static_cast<reference_type>(value_);
  }

  FOLLY_ERASE value_type* operator->() const noexcept { return &value_; }

  FOLLY_ERASE reference_type ensure() noexcept {
    return static_cast<reference_type>(value_);
  }

  template <typename Index>
  FOLLY_ERASE auto operator[](const Index& index) const -> decltype(auto) {
    return value_[index];
  }

  template <typename... Args>
  FOLLY_ERASE value_type& emplace(Args&&... args) {
    return value_ = value_type(static_cast<Args&&>(args)...);
  }

  template <class U, class... Args>
  FOLLY_ERASE std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>, Args&&...>::
          value,
      value_type&>
  emplace(std::initializer_list<U> ilist, Args&&... args) {
    return value_ = value_type(ilist, static_cast<Args&&>(args)...);
  }

 private:
  value_type& value_;
};

template <typename T, typename U>
bool operator==(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs == *rhs;
}

template <typename T, typename U>
bool operator!=(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs != *rhs;
}

template <typename T, typename U>
bool operator<(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs < *rhs;
}

template <typename T, typename U>
bool operator>(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs > *rhs;
}

template <typename T, typename U>
bool operator<=(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs <= *rhs;
}

template <typename T, typename U>
bool operator>=(required_field_ref<T> lhs, required_field_ref<U> rhs) {
  return *lhs >= *rhs;
}

template <typename T, typename U>
bool operator==(required_field_ref<T> lhs, const U& rhs) {
  return *lhs == rhs;
}

template <typename T, typename U>
bool operator!=(required_field_ref<T> lhs, const U& rhs) {
  return *lhs != rhs;
}

template <typename T, typename U>
bool operator<(required_field_ref<T> lhs, const U& rhs) {
  return *lhs < rhs;
}

template <typename T, typename U>
bool operator>(required_field_ref<T> lhs, const U& rhs) {
  return *lhs > rhs;
}

template <typename T, typename U>
bool operator<=(required_field_ref<T> lhs, const U& rhs) {
  return *lhs <= rhs;
}

template <typename T, typename U>
bool operator>=(required_field_ref<T> lhs, const U& rhs) {
  return *lhs >= rhs;
}

template <typename T, typename U>
bool operator==(const T& lhs, required_field_ref<U> rhs) {
  return lhs == *rhs;
}

template <typename T, typename U>
bool operator!=(const T& lhs, required_field_ref<U> rhs) {
  return lhs != *rhs;
}

template <typename T, typename U>
bool operator<(const T& lhs, required_field_ref<U> rhs) {
  return lhs < *rhs;
}

template <typename T, typename U>
bool operator>(const T& lhs, required_field_ref<U> rhs) {
  return lhs > *rhs;
}

template <typename T, typename U>
bool operator<=(const T& lhs, required_field_ref<U> rhs) {
  return lhs <= *rhs;
}

template <typename T, typename U>
bool operator>=(const T& lhs, required_field_ref<U> rhs) {
  return lhs >= *rhs;
}

namespace detail {

struct union_field_ref_owner_vtable {
  using reset_t = void(void*);

  reset_t* reset;
};

struct union_field_ref_owner_vtable_impl {
  template <typename T>
  static void reset(void* obj) {
    apache::thrift::clear(*static_cast<T*>(obj));
  }
};

template <typename T>
FOLLY_INLINE_VARIABLE constexpr union_field_ref_owner_vtable //
    union_field_ref_owner_vtable_for{nullptr};
template <typename T>
FOLLY_INLINE_VARIABLE constexpr union_field_ref_owner_vtable //
    union_field_ref_owner_vtable_for<T&>{
        &union_field_ref_owner_vtable_impl::reset<T>};
template <typename T>
FOLLY_INLINE_VARIABLE constexpr union_field_ref_owner_vtable //
    union_field_ref_owner_vtable_for<T const&>{nullptr};

template <class T, class = void>
struct element_type {
  using type = T;
};

template <class T>
struct element_type<T, folly::void_t<typename T::element_type>> {
  using type = typename T::element_type;
};

template <class T>
using is_boxed = folly::detail::is_instantiation_of<boxed_value_ptr, T>;

} // namespace detail

// A reference to an union field of the possibly const-qualified type
template <typename T>
class union_field_ref {
  static_assert(std::is_reference<T>::value, "not a reference");

  template <typename>
  friend class union_field_ref;

  using element_type =
      typename detail::element_type<folly::remove_cvref_t<T>>::type;
  using is_boxed = detail::is_boxed<folly::remove_cvref_t<T>>;

  using storage_reference_type = T;
  using storage_value_type = std::remove_reference_t<T>;

 public:
  using value_type = detail::copy_const_t<T, element_type>;
  using reference_type = detail::copy_reference_t<T, value_type>;

 private:
  using int_t =
      std::conditional_t<std::is_const<value_type>::value, const int, int>;
  using owner =
      std::conditional_t<std::is_const<value_type>::value, void const*, void*>;
  using vtable = apache::thrift::detail::union_field_ref_owner_vtable;

 public:
  FOLLY_ERASE union_field_ref(
      storage_reference_type storage_value,
      int_t& type,
      int field_type,
      owner ow,
      vtable const& vt) noexcept
      : storage_value_(storage_value),
        type_(type),
        field_type_(field_type),
        owner_(ow),
        vtable_(vt) {}

  template <
      typename U = value_type,
      std::enable_if_t<
          std::is_assignable<reference_type, U&&>::value &&
              std::is_constructible<value_type, U&&>::value,
          int> = 0>
  FOLLY_ERASE union_field_ref& operator=(U&& other) noexcept(
      std::is_nothrow_constructible<value_type, U>::value&&
          std::is_nothrow_assignable<value_type, U>::value) {
    if (has_value()) {
      get_value() = static_cast<U&&>(other);
    } else {
      emplace(static_cast<U&&>(other));
    }
    return *this;
  }

  FOLLY_ERASE bool has_value() const { return type_ == field_type_; }

  FOLLY_ERASE explicit operator bool() const { return has_value(); }

  // Returns a reference to the value if this is union's active field,
  // bad_field_access otherwise.
  FOLLY_ERASE reference_type value() const {
    throw_if_unset();
    return static_cast<reference_type>(get_value());
  }

  FOLLY_ERASE reference_type operator*() const { return value(); }

  FOLLY_ERASE value_type* operator->() const {
    throw_if_unset();
    return &get_value();
  }

  FOLLY_ERASE reference_type ensure() {
    if (!has_value()) {
      emplace();
    }
    return static_cast<reference_type>(get_value());
  }

  template <typename... Args>
  FOLLY_ERASE value_type& emplace(Args&&... args) {
    vtable_.reset(owner_);
    ::new (&storage_value_) storage_value_type(static_cast<Args&&>(args)...);
    type_ = field_type_;
    return get_value();
  }

  template <class U, class... Args>
  FOLLY_ERASE std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>, Args&&...>::
          value,
      value_type&>
  emplace(std::initializer_list<U> ilist, Args&&... args) {
    vtable_.reset(owner_);
    ::new (&storage_value_)
        storage_value_type(ilist, static_cast<Args&&>(args)...);
    type_ = field_type_;
    return get_value();
  }

 private:
  FOLLY_ERASE void throw_if_unset() const {
    if (!has_value()) {
      apache::thrift::detail::throw_on_bad_field_access();
    }
  }

  FOLLY_ERASE value_type& get_value() const { return get_value(is_boxed{}); }
  FOLLY_ERASE value_type& get_value(std::true_type) const {
    return *storage_value_;
  }
  FOLLY_ERASE value_type& get_value(std::false_type) const {
    return storage_value_;
  }

  storage_value_type& storage_value_;
  int_t& type_;
  const int field_type_;
  owner owner_;
  vtable const& vtable_;
};

template <typename T1, typename T2>
bool operator==(union_field_ref<T1> a, union_field_ref<T2> b) {
  return a && b ? *a == *b : a.has_value() == b.has_value();
}

template <typename T1, typename T2>
bool operator!=(union_field_ref<T1> a, union_field_ref<T2> b) {
  return !(a == b);
}

template <typename T1, typename T2>
bool operator<(union_field_ref<T1> a, union_field_ref<T2> b) {
  if (a.has_value() != b.has_value()) {
    return a.has_value() < b.has_value();
  }
  return a ? *a < *b : false;
}

template <typename T1, typename T2>
bool operator>(union_field_ref<T1> a, union_field_ref<T2> b) {
  return b < a;
}

template <typename T1, typename T2>
bool operator<=(union_field_ref<T1> a, union_field_ref<T2> b) {
  return !(a > b);
}

template <typename T1, typename T2>
bool operator>=(union_field_ref<T1> a, union_field_ref<T2> b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator==(union_field_ref<T> a, const U& b) {
  return a ? *a == b : false;
}

template <typename T, typename U>
bool operator!=(union_field_ref<T> a, const U& b) {
  return !(a == b);
}

template <typename T, typename U>
bool operator==(const U& a, union_field_ref<T> b) {
  return b == a;
}

template <typename T, typename U>
bool operator!=(const U& a, union_field_ref<T> b) {
  return b != a;
}

template <typename T, typename U>
bool operator<(union_field_ref<T> a, const U& b) {
  return a ? *a < b : true;
}

template <typename T, typename U>
bool operator>(union_field_ref<T> a, const U& b) {
  return a ? *a > b : false;
}

template <typename T, typename U>
bool operator<=(union_field_ref<T> a, const U& b) {
  return !(a > b);
}

template <typename T, typename U>
bool operator>=(union_field_ref<T> a, const U& b) {
  return !(a < b);
}

template <typename T, typename U>
bool operator<(const U& a, union_field_ref<T> b) {
  return b > a;
}

template <typename T, typename U>
bool operator<=(const U& a, union_field_ref<T> b) {
  return b >= a;
}

template <typename T, typename U>
bool operator>(const U& a, union_field_ref<T> b) {
  return b < a;
}

template <typename T, typename U>
bool operator>=(const U& a, union_field_ref<T> b) {
  return b <= a;
}

} // namespace thrift
} // namespace apache
