/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/isset_bitpacking/gen-cpp2/module_metadata.h"

// some of these functions can be so large that the compiler gives up optimizing
// them - and issues a warning which may be treated as an error!
//
// these functions are so rarely called that it is probably okay for them not to
// be optimized in practice
FOLLY_CLANG_DISABLE_WARNING("-Wignored-optimization-argument")

namespace apache {
namespace thrift {
namespace detail {
namespace md {
using ThriftMetadata = ::apache::thrift::metadata::ThriftMetadata;
using ThriftPrimitiveType = ::apache::thrift::metadata::ThriftPrimitiveType;
using ThriftType = ::apache::thrift::metadata::ThriftType;
using ThriftService = ::apache::thrift::metadata::ThriftService;
using ThriftServiceContext = ::apache::thrift::metadata::ThriftServiceContext;
using ThriftFunctionGenerator = void (*)(ThriftMetadata&, ThriftService&);


const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::Default>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.Default", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_Default = res.first->second;
  module_Default.name_ref() = "module.Default";
  module_Default.is_union_ref() = false;
  static const EncodedThriftField
  module_Default_fields[] = {
    {1, "field1", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_Default_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_Default.fields_ref()->push_back(std::move(field));
  }
  module_Default.structured_annotations_ref()->push_back(*cvStruct("cpp.PackIsset", {}).cv_struct_ref());
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::NonAtomic>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.NonAtomic", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_NonAtomic = res.first->second;
  module_NonAtomic.name_ref() = "module.NonAtomic";
  module_NonAtomic.is_union_ref() = false;
  static const EncodedThriftField
  module_NonAtomic_fields[] = {
    {1, "field1", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_NonAtomic_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_NonAtomic.fields_ref()->push_back(std::move(field));
  }
  module_NonAtomic.structured_annotations_ref()->push_back(*cvStruct("cpp.PackIsset", {{"atomic", cvBool(false)}}).cv_struct_ref());
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::Atomic>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.Atomic", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_Atomic = res.first->second;
  module_Atomic.name_ref() = "module.Atomic";
  module_Atomic.is_union_ref() = false;
  static const EncodedThriftField
  module_Atomic_fields[] = {
    {1, "field1", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_Atomic_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_Atomic.fields_ref()->push_back(std::move(field));
  }
  module_Atomic.structured_annotations_ref()->push_back(*cvStruct("cpp.PackIsset", {{"atomic", cvBool(true)}}).cv_struct_ref());
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::AtomicFoo>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.AtomicFoo", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_AtomicFoo = res.first->second;
  module_AtomicFoo.name_ref() = "module.AtomicFoo";
  module_AtomicFoo.is_union_ref() = false;
  static const EncodedThriftField
  module_AtomicFoo_fields[] = {
    {1, "field1", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_AtomicFoo_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_AtomicFoo.fields_ref()->push_back(std::move(field));
  }
  module_AtomicFoo.structured_annotations_ref()->push_back(*cvStruct("cpp.PackIsset", {{"atomic", cvBool(true)}}).cv_struct_ref());
  return res.first->second;
}

} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
