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

#include <thrift/compiler/sema/standard_mutator.h>

namespace apache {
namespace thrift {
namespace compiler {

// TODO(afuller): Instead of mutating the AST, readers should look for
// the interaction level annotation and the validation logic should be moved to
// a standard validator.
void propagate_process_in_event_base_annotation(
    diagnostic_context& ctx, mutator_context&, t_interaction& node) {
  for (auto* func : node.get_functions()) {
    func->set_is_interaction_member();
    if (func->has_annotation("thread")) {
      ctx.failure(
          "Interaction methods cannot be individually annotated with "
          "thread='eb'. Use process_in_event_base on the interaction instead.");
    }
  }
  if (node.has_annotation("process_in_event_base")) {
    if (node.has_annotation("serial")) {
      ctx.failure("EB interactions are already serial");
    }
    for (auto* func : node.get_functions()) {
      func->set_annotation("thread", "eb");
    }
  }
}

void remove_param_list_field_qualifiers(
    diagnostic_context& ctx, mutator_context&, t_function& node) {
  for (auto& field : node.params().fields()) {
    switch (field.qualifier()) {
      case t_field_qualifier::unspecified:
        continue;
      case t_field_qualifier::required:
        ctx.warning("optional keyword is ignored in argument lists.");
        break;
      case t_field_qualifier::optional:
        ctx.warning("required keyword is ignored in argument lists.");
        break;
    }
    field.set_qualifier(t_field_qualifier::unspecified);
  }
}

void assign_uri(diagnostic_context& ctx, mutator_context&, t_named& node) {
  if (auto* uri = node.find_annotation_or_null("thrift.uri")) {
    // Manually assigned.
    node.set_uri(*uri);
    return;
  }

  auto* program = dynamic_cast<const t_program*>(ctx.root());
  assert(program != nullptr);
  if (program != nullptr && !program->package().empty()) {
    // Derive from package.
    node.set_uri(program->package().get_uri(node.name()));
  }
}

void rectify_returned_interactions(
    diagnostic_context& ctx, mutator_context&, t_function& node) {
  auto check_is_interaction = [&](auto node) {
    const auto* type = node->get_true_type();
    if (!type->is_service() ||
        !static_cast<const t_service*>(type)->is_interaction()) {
      ctx.failure("Only an interaction is allowed in this position");
    }
  };

  if (node.is_interaction_constructor()) {
    // uses old syntax
    return;
  }

  if (const auto& ret = node.returned_interaction()) {
    check_is_interaction(*ret);
  } else if (node.return_type()->is_service()) {
    check_is_interaction(node.return_type());
    node.set_returned_interaction(node.return_type());
    node.set_return_type(t_base_type::t_void());
  } else if (node.return_type()->is_streamresponse()) {
    auto& stream =
        static_cast<const t_stream_response&>(node.return_type().deref());
    if (stream.first_response_type() &&
        stream.first_response_type()->deref().is_service()) {
      check_is_interaction(&stream.first_response_type()->deref());
      node.set_returned_interaction(stream.first_response_type());
      const_cast<t_stream_response&>(stream).set_first_response_type(
          boost::none);
    }
  } else if (node.return_type()->is_sink()) {
    auto& sink = static_cast<const t_sink&>(node.return_type().deref());
    if (sink.first_response_type() &&
        sink.first_response_type()->deref().is_service()) {
      check_is_interaction(&sink.first_response_type()->deref());
      node.set_returned_interaction(sink.first_response_type());
      const_cast<t_sink&>(sink).set_first_response_type(boost::none);
    }
  }
}

ast_mutator standard_mutator() {
  ast_mutator mutator;
  mutator.add_root_definition_visitor(&assign_uri);
  mutator.add_interaction_visitor(&propagate_process_in_event_base_annotation);
  mutator.add_function_visitor(&remove_param_list_field_qualifiers);
  mutator.add_function_visitor(&rectify_returned_interactions);
  return mutator;
}

} // namespace compiler
} // namespace thrift
} // namespace apache
