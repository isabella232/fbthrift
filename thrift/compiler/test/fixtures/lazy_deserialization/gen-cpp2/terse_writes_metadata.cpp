/**
 * Autogenerated by Thrift for src/terse_writes.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/lazy_deserialization/gen-cpp2/terse_writes_metadata.h"

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
StructMetadata<::apache::thrift::test::TerseFoo>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("terse_writes.TerseFoo", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& terse_writes_TerseFoo = res.first->second;
  terse_writes_TerseFoo.name_ref() = "terse_writes.TerseFoo";
  terse_writes_TerseFoo.is_union_ref() = false;
  static const EncodedThriftField
  terse_writes_TerseFoo_fields[] = {
    {1, "field1", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {2, "field2", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
    {3, "field3", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {4, "field4", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : terse_writes_TerseFoo_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    terse_writes_TerseFoo.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::apache::thrift::test::TerseLazyFoo>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("terse_writes.TerseLazyFoo", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& terse_writes_TerseLazyFoo = res.first->second;
  terse_writes_TerseLazyFoo.name_ref() = "terse_writes.TerseLazyFoo";
  terse_writes_TerseLazyFoo.is_union_ref() = false;
  static const EncodedThriftField
  terse_writes_TerseLazyFoo_fields[] = {
    {1, "field1", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {2, "field2", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
    {3, "field3", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {4, "field4", false, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : terse_writes_TerseLazyFoo_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    terse_writes_TerseLazyFoo.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::apache::thrift::test::TerseOptionalFoo>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("terse_writes.TerseOptionalFoo", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& terse_writes_TerseOptionalFoo = res.first->second;
  terse_writes_TerseOptionalFoo.name_ref() = "terse_writes.TerseOptionalFoo";
  terse_writes_TerseOptionalFoo.is_union_ref() = false;
  static const EncodedThriftField
  terse_writes_TerseOptionalFoo_fields[] = {
    {1, "field1", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : terse_writes_TerseOptionalFoo_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    terse_writes_TerseOptionalFoo.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::apache::thrift::test::TerseOptionalLazyFoo>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("terse_writes.TerseOptionalLazyFoo", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& terse_writes_TerseOptionalLazyFoo = res.first->second;
  terse_writes_TerseOptionalLazyFoo.name_ref() = "terse_writes.TerseOptionalLazyFoo";
  terse_writes_TerseOptionalLazyFoo.is_union_ref() = false;
  static const EncodedThriftField
  terse_writes_TerseOptionalLazyFoo_fields[] = {
    {1, "field1", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {2, "field2", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
    {3, "field3", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE)), std::vector<ThriftConstStruct>{}},
    {4, "field4", true, std::make_unique<List>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE)), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : terse_writes_TerseOptionalLazyFoo_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    terse_writes_TerseOptionalLazyFoo.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}

} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
