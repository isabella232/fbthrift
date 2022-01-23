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

ast_mutator standard_mutator() {
  ast_mutator mutator;
  // TODO(afuller): Move all mutation logic to here.
  mutator.add_interaction_visitor(&propagate_process_in_event_base_annotation);
  return mutator;
}

} // namespace compiler
} // namespace thrift
} // namespace apache
