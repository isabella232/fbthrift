/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/enums/gen-cpp2/module_metadata.h"

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

void EnumMetadata<::cpp2::Metasyntactic>::gen(ThriftMetadata& metadata) {
  auto res = metadata.enums_ref()->emplace("module.Metasyntactic", ::apache::thrift::metadata::ThriftEnum{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftEnum& enum_metadata = res.first->second;
  enum_metadata.name_ref() = "module.Metasyntactic";
  using EnumTraits = TEnumTraits<::cpp2::Metasyntactic>;
  for (std::size_t i = 0; i != EnumTraits::size; ++i) {
    enum_metadata.elements_ref()->emplace(static_cast<int32_t>(EnumTraits::values[i]), EnumTraits::names[i].str());
  }
}

const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::SomeStruct>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.SomeStruct", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_SomeStruct = res.first->second;
  module_SomeStruct.name_ref() = "module.SomeStruct";
  module_SomeStruct.is_union_ref() = false;
  static const EncodedThriftField
  module_SomeStruct_fields[] = {
    {1, "reasonable", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic"), std::vector<ThriftConstStruct>{}},
    {2, "fine", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic"), std::vector<ThriftConstStruct>{}},
    {3, "questionable", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic"), std::vector<ThriftConstStruct>{}},
    {4, "tags", false, std::make_unique<Set>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_SomeStruct_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_SomeStruct.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}

} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
