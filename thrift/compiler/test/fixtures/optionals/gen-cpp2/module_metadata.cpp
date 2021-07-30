/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/optionals/gen-cpp2/module_metadata.h"

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

void EnumMetadata<::cpp2::Animal>::gen(ThriftMetadata& metadata) {
  auto res = metadata.enums_ref()->emplace("module.Animal", ::apache::thrift::metadata::ThriftEnum{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftEnum& enum_metadata = res.first->second;
  enum_metadata.name_ref() = "module.Animal";
  using EnumTraits = TEnumTraits<::cpp2::Animal>;
  for (std::size_t i = 0; i < EnumTraits::size; ++i) {
    enum_metadata.elements_ref()->emplace(static_cast<int32_t>(EnumTraits::values[i]), EnumTraits::names[i].str());
  }
}

const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::Color>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.Color", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_Color = res.first->second;
  module_Color.name_ref() = "module.Color";
  module_Color.is_union_ref() = false;
  static const EncodedThriftField
  module_Color_fields[] = {
    {1, "red", false, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
    {2, "green", false, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "blue", false, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "alpha", false, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_DOUBLE_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_Color_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_Color.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::Vehicle>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.Vehicle", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_Vehicle = res.first->second;
  module_Vehicle.name_ref() = "module.Vehicle";
  module_Vehicle.is_union_ref() = false;
  static const EncodedThriftField
  module_Vehicle_fields[] = {
    {1, "color", false, std::make_unique<Struct< ::cpp2::Color>>("module.Color"), std::vector<ThriftConstStruct>{}},
    {2, "licensePlate", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "description", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "name", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {5, "hasAC", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_BOOL_TYPE), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_Vehicle_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_Vehicle.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}
const ::apache::thrift::metadata::ThriftStruct&
StructMetadata<::cpp2::Person>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.Person", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_Person = res.first->second;
  module_Person.name_ref() = "module.Person";
  module_Person.is_union_ref() = false;
  static const EncodedThriftField
  module_Person_fields[] = {
    {1, "id", false, std::make_unique<Typedef>("module.PersonID", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I64_TYPE)), std::vector<ThriftConstStruct>{}},
    {2, "name", false, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {3, "age", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I16_TYPE), std::vector<ThriftConstStruct>{}},
    {4, "address", true, std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE), std::vector<ThriftConstStruct>{}},
    {5, "favoriteColor", true, std::make_unique<Struct< ::cpp2::Color>>("module.Color"), std::vector<ThriftConstStruct>{}},
    {6, "friends", true, std::make_unique<Set>(std::make_unique<Typedef>("module.PersonID", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I64_TYPE))), std::vector<ThriftConstStruct>{}},
    {7, "bestFriend", true, std::make_unique<Typedef>("module.PersonID", std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I64_TYPE)), std::vector<ThriftConstStruct>{}},
    {8, "petNames", true, std::make_unique<Map>(std::make_unique<Enum< ::cpp2::Animal>>("module.Animal"), std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_STRING_TYPE)), std::vector<ThriftConstStruct>{}},
    {9, "afraidOfAnimal", true, std::make_unique<Enum< ::cpp2::Animal>>("module.Animal"), std::vector<ThriftConstStruct>{}},
    {10, "vehicles", true, std::make_unique<List>(std::make_unique<Struct< ::cpp2::Vehicle>>("module.Vehicle")), std::vector<ThriftConstStruct>{}},
  };
  for (const auto& f : module_Person_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id_ref() = f.id;
    field.name_ref() = f.name;
    field.is_optional_ref() = f.is_optional;
    f.metadata_type_interface->writeAndGenType(*field.type_ref(), metadata);
    field.structured_annotations_ref() = f.structured_annotations;
    module_Person.fields_ref()->push_back(std::move(field));
  }
  return res.first->second;
}

} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
