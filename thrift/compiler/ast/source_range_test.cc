/*
 * Copyright (c) Facebook, Inc. and its affiliates.
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

#include <thrift/compiler/ast/source_range.h>

#include <folly/portability/GTest.h>
#include <thrift/compiler/ast/t_program.h>

namespace apache::thrift::compiler {
namespace {

// Simulates parsing a thrift file, only adding the offsets to the program.
void add_offsets(t_program& program, const std::string& content) {
  size_t offset = 0;
  for (const auto& c : content) {
    offset++;
    if (c == '\n') {
      program.add_line_offset(offset);
    }
  }
}

class SourceLocTest : public ::testing::Test {};
class SourceRangeTest : public ::testing::Test {};

TEST_F(SourceLocTest, Offset) {
  t_program program("");

  add_offsets(
      program,
      "struct A {\n"
      "  1: optional A a (cpp.ref);\n"
      "}\n");

  EXPECT_EQ(source_loc().offset(), t_program::noffset); // unknown loc.
  EXPECT_EQ(
      source_loc(program, 0, 7).offset(),
      t_program::noffset); // unknown line, ignored col.
  EXPECT_EQ(source_loc(program, 1, 0).offset(), 0); // first line, unknown col.

  EXPECT_EQ(source_loc(program, 1, 1).offset(), 0); // struct begin
  EXPECT_EQ(source_loc(program, 3, 2).offset(), 41); // struct end

  EXPECT_EQ(source_loc(program, 2, 3).offset(), 13); // field begin
  EXPECT_EQ(source_loc(program, 2, 29).offset(), 39); // field end

  EXPECT_EQ(source_loc(program, 100, 1).offset(), t_program::noffset);
}

template <typename T>
void TestOrdering(int expected_cmp, const T& lhs, const T& rhs) {
  EXPECT_EQ(lhs == rhs, expected_cmp == 0);
  EXPECT_EQ(lhs != rhs, expected_cmp != 0);
  EXPECT_EQ(lhs < rhs, expected_cmp < 0);
  EXPECT_EQ(lhs <= rhs, expected_cmp <= 0);
  EXPECT_EQ(lhs > rhs, expected_cmp > 0);
  EXPECT_EQ(lhs >= rhs, expected_cmp >= 0);

  EXPECT_EQ(rhs == lhs, 0 == expected_cmp);
  EXPECT_EQ(rhs != lhs, 0 != expected_cmp);
  EXPECT_EQ(rhs < lhs, 0 < expected_cmp);
  EXPECT_EQ(rhs <= lhs, 0 <= expected_cmp);
  EXPECT_EQ(rhs > lhs, 0 > expected_cmp);
  EXPECT_EQ(rhs >= lhs, 0 >= expected_cmp);
}

TEST_F(SourceLocTest, Order) {
  t_program prog1("prog/1/src.thrift");
  t_program prog2("prog/2/src.thrift");
  TestOrdering(0, source_loc(), source_loc());
  TestOrdering(-1, source_loc(), source_loc(prog1, 1, 1));
  TestOrdering(0, source_loc(prog1, 7, 13), source_loc(prog1, 7, 13));
  TestOrdering(-1, source_loc(prog1, 7, 12), source_loc(prog1, 7, 13));
  TestOrdering(1, source_loc(prog1, 7, 12), source_loc(prog1, 6, 13));
  TestOrdering(-1, source_loc(prog1, 7, 12), source_loc(prog2, 6, 13));

  // For stability and consistency with operator==, Pointer address is a tie
  // breaker between same paths.
  t_program prog1b("prog/1/src.thrift");
  TestOrdering(
      &prog1 > &prog1b ? 1 : -1,
      source_loc(prog1, 1, 1),
      source_loc(prog1b, 1, 1));
}

TEST_F(SourceRangeTest, ProgramMismatch) {
  t_program program1("");
  t_program program2("");

  source_loc loc1(program1, 1, 1);
  source_loc loc2(program2, 2, 1);

  EXPECT_THROW(source_range(loc1, loc2), std::invalid_argument);
}

} // namespace
} // namespace apache::thrift::compiler