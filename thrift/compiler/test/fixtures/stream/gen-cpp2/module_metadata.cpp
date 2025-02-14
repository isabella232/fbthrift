/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/stream/gen-cpp2/module_metadata.h"

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
StructMetadata<::cpp2::FooEx>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs_ref()->emplace("module.FooEx", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return res.first->second;
  }
  ::apache::thrift::metadata::ThriftStruct& module_FooEx = res.first->second;
  module_FooEx.name_ref() = "module.FooEx";
  module_FooEx.is_union_ref() = false;
  return res.first->second;
}

void ExceptionMetadata<::cpp2::FooEx>::gen(ThriftMetadata& metadata) {
  auto res = metadata.exceptions_ref()->emplace("module.FooEx", ::apache::thrift::metadata::ThriftException{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftException& module_FooEx = res.first->second;
  module_FooEx.name_ref() = "module.FooEx";
}
void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_returnstream(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name_ref() = "returnstream";
  auto func_ret_type = std::make_unique<Stream>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE));
  func_ret_type->writeAndGenType(*func.return_type_ref(), metadata);
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_returnstream_i32_from_1;
  module_PubSubStreamingService_returnstream_i32_from_1.id_ref() = 1;
  module_PubSubStreamingService_returnstream_i32_from_1.name_ref() = "i32_from";
  module_PubSubStreamingService_returnstream_i32_from_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_returnstream_i32_from_1_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_returnstream_i32_from_1_type->writeAndGenType(*module_PubSubStreamingService_returnstream_i32_from_1.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_returnstream_i32_from_1));
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_returnstream_i32_to_2;
  module_PubSubStreamingService_returnstream_i32_to_2.id_ref() = 2;
  module_PubSubStreamingService_returnstream_i32_to_2.name_ref() = "i32_to";
  module_PubSubStreamingService_returnstream_i32_to_2.is_optional_ref() = false;
  auto module_PubSubStreamingService_returnstream_i32_to_2_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_returnstream_i32_to_2_type->writeAndGenType(*module_PubSubStreamingService_returnstream_i32_to_2.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_returnstream_i32_to_2));
  func.is_oneway_ref() = false;
  service.functions_ref()->push_back(std::move(func));
}
void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_streamthrows(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name_ref() = "streamthrows";
  auto func_ret_type = std::make_unique<Stream>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE));
  func_ret_type->writeAndGenType(*func.return_type_ref(), metadata);
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_streamthrows_foo_1;
  module_PubSubStreamingService_streamthrows_foo_1.id_ref() = 1;
  module_PubSubStreamingService_streamthrows_foo_1.name_ref() = "foo";
  module_PubSubStreamingService_streamthrows_foo_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_streamthrows_foo_1_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_streamthrows_foo_1_type->writeAndGenType(*module_PubSubStreamingService_streamthrows_foo_1.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_streamthrows_foo_1));
  func.is_oneway_ref() = false;
  service.functions_ref()->push_back(std::move(func));
}
void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_boththrows(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name_ref() = "boththrows";
  auto func_ret_type = std::make_unique<Stream>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE));
  func_ret_type->writeAndGenType(*func.return_type_ref(), metadata);
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_boththrows_foo_1;
  module_PubSubStreamingService_boththrows_foo_1.id_ref() = 1;
  module_PubSubStreamingService_boththrows_foo_1.name_ref() = "foo";
  module_PubSubStreamingService_boththrows_foo_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_boththrows_foo_1_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_boththrows_foo_1_type->writeAndGenType(*module_PubSubStreamingService_boththrows_foo_1.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_boththrows_foo_1));
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_boththrows_e_1;
  module_PubSubStreamingService_boththrows_e_1.id_ref() = 1;
  module_PubSubStreamingService_boththrows_e_1.name_ref() = "e";
  module_PubSubStreamingService_boththrows_e_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_boththrows_e_1_type = std::make_unique<Struct< ::cpp2::FooEx>>("module.FooEx");
  module_PubSubStreamingService_boththrows_e_1_type->writeAndGenType(*module_PubSubStreamingService_boththrows_e_1.type_ref(), metadata);
  func.exceptions_ref()->push_back(std::move(module_PubSubStreamingService_boththrows_e_1));
  ExceptionMetadata< ::cpp2::FooEx>::gen(metadata);
  func.is_oneway_ref() = false;
  service.functions_ref()->push_back(std::move(func));
}
void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_responseandstreamthrows(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name_ref() = "responseandstreamthrows";
  auto func_ret_type = std::make_unique<Stream>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE));
  func_ret_type->writeAndGenType(*func.return_type_ref(), metadata);
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_responseandstreamthrows_foo_1;
  module_PubSubStreamingService_responseandstreamthrows_foo_1.id_ref() = 1;
  module_PubSubStreamingService_responseandstreamthrows_foo_1.name_ref() = "foo";
  module_PubSubStreamingService_responseandstreamthrows_foo_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_responseandstreamthrows_foo_1_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_responseandstreamthrows_foo_1_type->writeAndGenType(*module_PubSubStreamingService_responseandstreamthrows_foo_1.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_responseandstreamthrows_foo_1));
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_responseandstreamthrows_e_1;
  module_PubSubStreamingService_responseandstreamthrows_e_1.id_ref() = 1;
  module_PubSubStreamingService_responseandstreamthrows_e_1.name_ref() = "e";
  module_PubSubStreamingService_responseandstreamthrows_e_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_responseandstreamthrows_e_1_type = std::make_unique<Struct< ::cpp2::FooEx>>("module.FooEx");
  module_PubSubStreamingService_responseandstreamthrows_e_1_type->writeAndGenType(*module_PubSubStreamingService_responseandstreamthrows_e_1.type_ref(), metadata);
  func.exceptions_ref()->push_back(std::move(module_PubSubStreamingService_responseandstreamthrows_e_1));
  ExceptionMetadata< ::cpp2::FooEx>::gen(metadata);
  func.is_oneway_ref() = false;
  service.functions_ref()->push_back(std::move(func));
}
void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_returnstreamFast(ThriftMetadata& metadata, ThriftService& service) {
  ::apache::thrift::metadata::ThriftFunction func;
  (void)metadata;
  func.name_ref() = "returnstreamFast";
  auto func_ret_type = std::make_unique<Stream>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE));
  func_ret_type->writeAndGenType(*func.return_type_ref(), metadata);
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_returnstreamFast_i32_from_1;
  module_PubSubStreamingService_returnstreamFast_i32_from_1.id_ref() = 1;
  module_PubSubStreamingService_returnstreamFast_i32_from_1.name_ref() = "i32_from";
  module_PubSubStreamingService_returnstreamFast_i32_from_1.is_optional_ref() = false;
  auto module_PubSubStreamingService_returnstreamFast_i32_from_1_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_returnstreamFast_i32_from_1_type->writeAndGenType(*module_PubSubStreamingService_returnstreamFast_i32_from_1.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_returnstreamFast_i32_from_1));
  ::apache::thrift::metadata::ThriftField module_PubSubStreamingService_returnstreamFast_i32_to_2;
  module_PubSubStreamingService_returnstreamFast_i32_to_2.id_ref() = 2;
  module_PubSubStreamingService_returnstreamFast_i32_to_2.name_ref() = "i32_to";
  module_PubSubStreamingService_returnstreamFast_i32_to_2.is_optional_ref() = false;
  auto module_PubSubStreamingService_returnstreamFast_i32_to_2_type = std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE);
  module_PubSubStreamingService_returnstreamFast_i32_to_2_type->writeAndGenType(*module_PubSubStreamingService_returnstreamFast_i32_to_2.type_ref(), metadata);
  func.arguments_ref()->push_back(std::move(module_PubSubStreamingService_returnstreamFast_i32_to_2));
  func.is_oneway_ref() = false;
  service.functions_ref()->push_back(std::move(func));
}

void ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen(::apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  const ::apache::thrift::metadata::ThriftServiceContextRef* self = genRecurse(*response.metadata_ref(), *response.services_ref());
  DCHECK(self != nullptr);
  // TODO(praihan): Remove ThriftServiceContext from response. But in the meantime, we need to fill the field with the result of looking up in ThriftMetadata.
  ::apache::thrift::metadata::ThriftServiceContext context;
  context.module_ref() = *self->module_ref();
  context.service_info_ref() = response.metadata_ref()->services_ref()->at(*self->service_name_ref());
  response.context_ref() = std::move(context);
}

const ThriftServiceContextRef* ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::genRecurse(ThriftMetadata& metadata, std::vector<ThriftServiceContextRef>& services) {
  (void) metadata;
  ::apache::thrift::metadata::ThriftService module_PubSubStreamingService;
  module_PubSubStreamingService.name_ref() = "module.PubSubStreamingService";
  static const ThriftFunctionGenerator functions[] = {
    ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_returnstream,
    ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_streamthrows,
    ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_boththrows,
    ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_responseandstreamthrows,
    ServiceMetadata<::cpp2::PubSubStreamingServiceSvIf>::gen_returnstreamFast,
  };
  for (auto& function_gen : functions) {
    function_gen(metadata, module_PubSubStreamingService);
  }
  // We need to keep the index around because a reference or iterator could be invalidated.
  auto selfIndex = services.size();
  services.emplace_back();
  ThriftServiceContextRef& context = services[selfIndex];
  metadata.services_ref()->emplace("module.PubSubStreamingService", std::move(module_PubSubStreamingService));
  context.service_name_ref() = "module.PubSubStreamingService";
  ::apache::thrift::metadata::ThriftModuleContext module;
  module.name_ref() = "module";
  context.module_ref() = std::move(module);
  return &context;
}
} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
