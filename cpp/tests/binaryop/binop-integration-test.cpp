/*
 * Copyright (c) 2019-2020, NVIDIA CORPORATION.
 *
 * Copyright 2018-2019 BlazingDB, Inc.
 *     Copyright 2018 Christian Noboa Mardini <christian@blazingdb.com>
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

#include <tests/binaryop/assert-binops.h>
#include <cudf/binaryop.hpp>
#include <tests/binaryop/binop-fixture.hpp>

namespace cudf {
namespace test {
namespace binop {
struct BinaryOperationIntegrationTest : public BinaryOperationTest {
};

TEST_F(BinaryOperationIntegrationTest, Add_Scalar_Vector_SI32_FP32_SI64)
{
  using TypeOut = int32_t;
  using TypeLhs = float;
  using TypeRhs = int64_t;

  using ADD = cudf::library::operation::Add<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ADD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ADD());
}

TEST_F(BinaryOperationIntegrationTest, Add_Vector_Vector_SI32_FP32_FP32)
{
  using TypeOut = int32_t;
  using TypeLhs = float;
  using TypeRhs = float;

  using ADD = cudf::library::operation::Add<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10000);
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ADD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ADD());
}

TEST_F(BinaryOperationIntegrationTest, Sub_Scalar_Vector_SI32_FP32_FP32)
{
  using TypeOut = int32_t;
  using TypeLhs = float;
  using TypeRhs = int64_t;

  using SUB = cudf::library::operation::Sub<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SUB,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SUB());
}

TEST_F(BinaryOperationIntegrationTest, Add_Vector_Scalar_SI08_SI16_SI32)
{
  using TypeOut = int8_t;
  using TypeLhs = int16_t;
  using TypeRhs = int32_t;

  using ADD = cudf::library::operation::Add<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_scalar<TypeRhs>();
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ADD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ADD());
}

TEST_F(BinaryOperationIntegrationTest, Add_Vector_Vector_SI32_FP64_SI08)
{
  using TypeOut = int32_t;
  using TypeLhs = double;
  using TypeRhs = int8_t;

  using ADD = cudf::library::operation::Add<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ADD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ADD());
}

TEST_F(BinaryOperationIntegrationTest, Sub_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using SUB = cudf::library::operation::Sub<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SUB,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SUB());
}

TEST_F(BinaryOperationIntegrationTest, Sub_Vector_Scalar_SI64_FP64_SI32)
{
  using TypeOut = int64_t;
  using TypeLhs = double;
  using TypeRhs = int32_t;

  using SUB = cudf::library::operation::Sub<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10000);
  auto rhs = make_random_wrapped_scalar<TypeRhs>();

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SUB,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SUB());
}

TEST_F(BinaryOperationIntegrationTest, Mul_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using MUL = cudf::library::operation::Mul<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MUL,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MUL());
}

TEST_F(BinaryOperationIntegrationTest, Mul_Vector_Vector_SI64_FP32_FP32)
{
  using TypeOut = int64_t;
  using TypeLhs = float;
  using TypeRhs = float;

  using MUL = cudf::library::operation::Mul<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MUL,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MUL());
}

TEST_F(BinaryOperationIntegrationTest, Div_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using DIV = cudf::library::operation::Div<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::DIV,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, DIV());
}

TEST_F(BinaryOperationIntegrationTest, Div_Vector_Vector_SI64_FP32_FP32)
{
  using TypeOut = int64_t;
  using TypeLhs = float;
  using TypeRhs = float;

  using DIV = cudf::library::operation::Div<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::DIV,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, DIV());
}

TEST_F(BinaryOperationIntegrationTest, TrueDiv_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using TRUEDIV = cudf::library::operation::TrueDiv<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::TRUE_DIV,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, TRUEDIV());
}

TEST_F(BinaryOperationIntegrationTest, FloorDiv_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using FLOORDIV = cudf::library::operation::FloorDiv<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::FLOOR_DIV,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, FLOORDIV());
}

TEST_F(BinaryOperationIntegrationTest, FloorDiv_Vector_Vector_SI64_FP32_FP32)
{
  using TypeOut = int64_t;
  using TypeLhs = float;
  using TypeRhs = float;

  using FLOORDIV = cudf::library::operation::FloorDiv<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::FLOOR_DIV,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, FLOORDIV());
}

TEST_F(BinaryOperationIntegrationTest, Mod_Vector_Vector_SI64)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using MOD = cudf::library::operation::Mod<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MOD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MOD());
}

TEST_F(BinaryOperationIntegrationTest, Mod_Vector_Vector_FP32)
{
  using TypeOut = float;
  using TypeLhs = float;
  using TypeRhs = float;

  using MOD = cudf::library::operation::Mod<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MOD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MOD());
}

TEST_F(BinaryOperationIntegrationTest, Mod_Vector_Vector_SI64_FP32_FP32)
{
  using TypeOut = int64_t;
  using TypeLhs = float;
  using TypeRhs = float;

  using MOD = cudf::library::operation::Mod<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MOD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MOD());
}

TEST_F(BinaryOperationIntegrationTest, Mod_Vector_Vector_FP64)
{
  using TypeOut = double;
  using TypeLhs = double;
  using TypeRhs = double;

  using MOD = cudf::library::operation::Mod<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::MOD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, MOD());
}

TEST_F(BinaryOperationIntegrationTest, Pow_Vector_Vector_FP64_SI64_SI64)
{
  using TypeOut = double;
  using TypeLhs = int64_t;
  using TypeRhs = int64_t;

  using POW = cudf::library::operation::Pow<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::POW,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  /**
   * According to CUDA Programming Guide, 'E.1. Standard Functions', 'Table 7 - Double-Precision
   * Mathematical Standard Library Functions with Maximum ULP Error'
   * The pow function has 2 (full range) maximum ulp error.
   */
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, POW(), NearEqualComparator<TypeOut>{2});
}

TEST_F(BinaryOperationIntegrationTest, Pow_Vector_Vector_FP32)
{
  using TypeOut = float;
  using TypeLhs = float;
  using TypeRhs = float;

  using POW = cudf::library::operation::Pow<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::POW,
                                                  data_type(experimental::type_to_id<TypeOut>()));
  /**
   * According to CUDA Programming Guide, 'E.1. Standard Functions', 'Table 7 - Double-Precision
   * Mathematical Standard Library Functions with Maximum ULP Error'
   * The pow function has 2 (full range) maximum ulp error.
   */
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, POW(), NearEqualComparator<TypeOut>{2});
}

TEST_F(BinaryOperationIntegrationTest, And_Vector_Vector_SI16_SI64_SI32)
{
  using TypeOut = int16_t;
  using TypeLhs = int64_t;
  using TypeRhs = int32_t;

  using AND = cudf::library::operation::BitwiseAnd<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::BITWISE_AND,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, AND());
}

TEST_F(BinaryOperationIntegrationTest, Or_Vector_Vector_SI64_SI16_SI32)
{
  using TypeOut = int64_t;
  using TypeLhs = int16_t;
  using TypeRhs = int32_t;

  using OR = cudf::library::operation::BitwiseOr<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::BITWISE_OR,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, OR());
}

TEST_F(BinaryOperationIntegrationTest, Xor_Vector_Vector_SI32_SI16_SI64)
{
  using TypeOut = int32_t;
  using TypeLhs = int16_t;
  using TypeRhs = int64_t;

  using XOR = cudf::library::operation::BitwiseXor<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::BITWISE_XOR,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, XOR());
}

TEST_F(BinaryOperationIntegrationTest, Logical_And_Vector_Vector_SI16_FP64_SI8)
{
  using TypeOut = int16_t;
  using TypeLhs = double;
  using TypeRhs = int8_t;

  using AND = cudf::library::operation::LogicalAnd<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LOGICAL_AND,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, AND());
}

TEST_F(BinaryOperationIntegrationTest, Logical_Or_Vector_Vector_B8_SI16_SI64)
{
  using TypeOut = bool;
  using TypeLhs = int16_t;
  using TypeRhs = int64_t;

  using OR = cudf::library::operation::LogicalOr<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LOGICAL_OR,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, OR());
}

TEST_F(BinaryOperationIntegrationTest, Less_Scalar_Vector_B8_TSS_TSS)
{
  using TypeOut = bool;
  using TypeLhs = cudf::timestamp_s;
  using TypeRhs = cudf::timestamp_s;

  using LESS = cudf::library::operation::Less<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  auto rhs = make_random_wrapped_column<TypeRhs>(10);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS());
}

TEST_F(BinaryOperationIntegrationTest, Greater_Scalar_Vector_B8_TSMS_TSS)
{
  using TypeOut = bool;
  using TypeLhs = cudf::timestamp_ms;
  using TypeRhs = cudf::timestamp_s;

  using GREATER = cudf::library::operation::Greater<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::GREATER,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, GREATER());
}

TEST_F(BinaryOperationIntegrationTest, Less_Vector_Vector_B8_TSS_TSS)
{
  using TypeOut = bool;
  using TypeLhs = cudf::timestamp_s;
  using TypeRhs = cudf::timestamp_s;

  using LESS = cudf::library::operation::Less<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10);
  auto rhs = make_random_wrapped_column<TypeRhs>(10);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS());
}

TEST_F(BinaryOperationIntegrationTest, Greater_Vector_Vector_B8_TSMS_TSS)
{
  using TypeOut = bool;
  using TypeLhs = cudf::timestamp_ms;
  using TypeRhs = cudf::timestamp_s;

  using GREATER = cudf::library::operation::Greater<TypeOut, TypeLhs, TypeRhs>;

  cudf::test::UniformRandomGenerator<long> rand_gen(1, 10);
  auto itr = cudf::test::make_counting_transform_iterator(
    0, [&rand_gen](auto row) { return rand_gen.generate() * 1000; });

  auto lhs = cudf::test::fixed_width_column_wrapper<TypeLhs>(itr, itr + 100, make_validity_iter());

  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::GREATER,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, GREATER());
}

TEST_F(BinaryOperationIntegrationTest, Less_Scalar_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using LESS = cudf::library::operation::Less<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::string_scalar("eee");
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS());
}

TEST_F(BinaryOperationIntegrationTest, Less_Vector_Scalar_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using LESS = cudf::library::operation::Less<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto rhs = cudf::string_scalar("eee");
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS());
}

TEST_F(BinaryOperationIntegrationTest, Less_Vector_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using LESS = cudf::library::operation::Less<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS());
}

TEST_F(BinaryOperationIntegrationTest, Greater_Vector_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using GREATER = cudf::library::operation::Greater<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::GREATER,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, GREATER());
}

TEST_F(BinaryOperationIntegrationTest, Equal_Vector_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using EQUAL = cudf::library::operation::Equal<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::EQUAL,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, EQUAL());
}

TEST_F(BinaryOperationIntegrationTest, Equal_Vector_Scalar_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using EQUAL = cudf::library::operation::Equal<TypeOut, TypeLhs, TypeRhs>;

  auto rhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto lhs = cudf::string_scalar("");
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::EQUAL,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, EQUAL());
}

TEST_F(BinaryOperationIntegrationTest, LessEqual_Vector_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using LESS_EQUAL = cudf::library::operation::LessEqual<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LESS_EQUAL,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LESS_EQUAL());
}

TEST_F(BinaryOperationIntegrationTest, GreaterEqual_Vector_Vector_B8_STR_STR)
{
  using TypeOut = bool;
  using TypeLhs = std::string;
  using TypeRhs = std::string;

  using GREATER_EQUAL = cudf::library::operation::GreaterEqual<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::test::strings_column_wrapper({"eee", "bb", "<null>", "", "aa", "bbb", "ééé"});
  auto rhs = cudf::test::strings_column_wrapper({"ééé", "bbb", "aa", "", "<null>", "bb", "eee"});
  auto out =
    cudf::experimental::binary_operation(lhs,
                                         rhs,
                                         cudf::experimental::binary_operator::GREATER_EQUAL,
                                         data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, GREATER_EQUAL());
}

TEST_F(BinaryOperationIntegrationTest, ShiftLeft_Vector_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_LEFT = cudf::library::operation::ShiftLeft<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_LEFT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_LEFT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftLeft_Vector_Vector_SI32_SI16_SI64)
{
  using TypeOut = int;
  using TypeLhs = int16_t;
  using TypeRhs = int64_t;

  using SHIFT_LEFT = cudf::library::operation::ShiftLeft<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_LEFT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_LEFT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftLeft_Scalar_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_LEFT = cudf::library::operation::ShiftLeft<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_LEFT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_LEFT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftLeft_Vector_Scalar_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_LEFT = cudf::library::operation::ShiftLeft<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_scalar<TypeRhs>();
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_LEFT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_LEFT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRight_Vector_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT = cudf::library::operation::ShiftRight<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_RIGHT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRight_Vector_Vector_SI32_SI16_SI64)
{
  using TypeOut = int;
  using TypeLhs = int16_t;
  using TypeRhs = int64_t;

  using SHIFT_RIGHT = cudf::library::operation::ShiftRight<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_RIGHT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRight_Scalar_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT = cudf::library::operation::ShiftRight<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_RIGHT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRight_Vector_Scalar_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT = cudf::library::operation::ShiftRight<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_scalar<TypeRhs>();
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::SHIFT_RIGHT,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRightUnsigned_Vector_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT_UNSIGNED =
    cudf::library::operation::ShiftRightUnsigned<TypeOut, TypeLhs, TypeRhs>;

  int num_els = 4;

  TypeLhs lhs[] = {-8, 78, -93, 0, -INT_MAX};
  cudf::test::fixed_width_column_wrapper<TypeLhs> lhs_w(lhs, lhs + num_els);

  TypeRhs shift[] = {1, 1, 3, 2, 16};
  cudf::test::fixed_width_column_wrapper<TypeRhs> shift_w(shift, shift + num_els);

  TypeOut expected[] = {2147483644, 39, 536870900, 0, 32768};
  cudf::test::fixed_width_column_wrapper<TypeOut> expected_w(expected, expected + num_els);

  auto out =
    cudf::experimental::binary_operation(lhs_w,
                                         shift_w,
                                         cudf::experimental::binary_operator::SHIFT_RIGHT_UNSIGNED,
                                         data_type(experimental::type_to_id<TypeOut>()));

  cudf::test::expect_columns_equal(*out, expected_w);
}

TEST_F(BinaryOperationIntegrationTest, ShiftRightUnsigned_Vector_Vector_SI32_SI16_SI64)
{
  using TypeOut = int;
  using TypeLhs = int16_t;
  using TypeRhs = int64_t;

  using SHIFT_RIGHT_UNSIGNED =
    cudf::library::operation::ShiftRightUnsigned<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out =
    cudf::experimental::binary_operation(lhs,
                                         rhs,
                                         cudf::experimental::binary_operator::SHIFT_RIGHT_UNSIGNED,
                                         data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT_UNSIGNED());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRightUnsigned_Scalar_Vector_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT_UNSIGNED =
    cudf::library::operation::ShiftRightUnsigned<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out =
    cudf::experimental::binary_operation(lhs,
                                         rhs,
                                         cudf::experimental::binary_operator::SHIFT_RIGHT_UNSIGNED,
                                         data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT_UNSIGNED());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRightUnsigned_Vector_Scalar_SI32)
{
  using TypeOut = int;
  using TypeLhs = int;
  using TypeRhs = int;

  using SHIFT_RIGHT_UNSIGNED =
    cudf::library::operation::ShiftRightUnsigned<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(100);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_scalar<TypeRhs>();
  auto out =
    cudf::experimental::binary_operation(lhs,
                                         rhs,
                                         cudf::experimental::binary_operator::SHIFT_RIGHT_UNSIGNED,
                                         data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT_UNSIGNED());
}

TEST_F(BinaryOperationIntegrationTest, LogBase_Vector_Scalar_SI32_SI32_float)
{
  using TypeOut = int;      // Cast the result value to int for easy comparison
  using TypeLhs = int32_t;  // All input types get converted into doubles
  using TypeRhs = float;

  using LOG_BASE = cudf::library::operation::LogBase<TypeOut, TypeLhs, TypeRhs>;

  // Make sure there are no zeros. The log value is purposefully cast to int for easy comparison
  auto elements = make_counting_transform_iterator(1, [](auto i) { return i + 10; });
  fixed_width_column_wrapper<TypeLhs> lhs(elements, elements + 100);
  // Find log to the base 10
  auto rhs = numeric_scalar<TypeRhs>(10);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LOG_BASE,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LOG_BASE());
}

TEST_F(BinaryOperationIntegrationTest, LogBase_Scalar_Vector_float_SI32)
{
  using TypeOut = float;
  using TypeLhs = int;
  using TypeRhs = int;  // Integral types promoted to double

  using LOG_BASE = cudf::library::operation::LogBase<TypeOut, TypeLhs, TypeRhs>;

  // Make sure there are no zeros
  auto elements = make_counting_transform_iterator(1, [](auto i) { return i + 30; });
  fixed_width_column_wrapper<TypeRhs> rhs(elements, elements + 100);
  // Find log to the base 2
  auto lhs = numeric_scalar<TypeLhs>(2);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LOG_BASE,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LOG_BASE());
}

TEST_F(BinaryOperationIntegrationTest, LogBase_Vector_Vector_double_SI64_SI32)
{
  using TypeOut = double;
  using TypeLhs = int64_t;
  using TypeRhs = int32_t;  // Integral types promoted to double

  using LOG_BASE = cudf::library::operation::LogBase<TypeOut, TypeLhs, TypeRhs>;

  // Make sure there are no zeros
  auto elements = make_counting_transform_iterator(1, [](auto i) { return std::pow(2, i); });
  fixed_width_column_wrapper<TypeLhs> lhs(elements, elements + 50);

  // Find log to the base 7
  auto rhs_elements = make_counting_transform_iterator(0, [](auto) { return 7; });
  fixed_width_column_wrapper<TypeRhs> rhs(rhs_elements, rhs_elements + 50);
  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::LOG_BASE,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, LOG_BASE());
}

TEST_F(BinaryOperationIntegrationTest, CastAdd_Vector_Vector_SI32_float_float)
{
  using TypeOut = int32_t;
  using TypeLhs = float;
  using TypeRhs = float;  // Integral types promoted to double

  using ADD = cudf::library::operation::Add<TypeOut, TypeLhs, TypeRhs>;

  auto lhs      = cudf::test::fixed_width_column_wrapper<float>{1.3f, 1.6f};
  auto rhs      = cudf::test::fixed_width_column_wrapper<float>{1.3f, 1.6f};
  auto expected = cudf::test::fixed_width_column_wrapper<int>{2, 3};

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ADD,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ADD());
}

TEST_F(BinaryOperationIntegrationTest, ShiftRightUnsigned_Scalar_Vector_SI64_SI64_SI32)
{
  using TypeOut = int64_t;
  using TypeLhs = int64_t;
  using TypeRhs = int32_t;

  using SHIFT_RIGHT_UNSIGNED =
    cudf::library::operation::ShiftRightUnsigned<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = cudf::experimental::scalar_type_t<TypeLhs>(-12);
  // this generates values in the range 1-10 which should be reasonable for the shift
  auto rhs = make_random_wrapped_column<TypeRhs>(100);
  auto out =
    cudf::experimental::binary_operation(lhs,
                                         rhs,
                                         cudf::experimental::binary_operator::SHIFT_RIGHT_UNSIGNED,
                                         data_type(experimental::type_to_id<TypeOut>()));

  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, SHIFT_RIGHT_UNSIGNED());
}

TEST_F(BinaryOperationIntegrationTest, ATan2_Scalar_Vector_FP32)
{
  using TypeOut = float;
  using TypeLhs = float;
  using TypeRhs = float;

  using ATAN2 = cudf::library::operation::ATan2<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_scalar<TypeLhs>();
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ATAN2,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  // atan2 has a max ULP error of 2 per CUDA programming guide
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ATAN2(), NearEqualComparator<TypeOut>{2});
}

TEST_F(BinaryOperationIntegrationTest, ATan2_Vector_Scalar_FP64)
{
  using TypeOut = double;
  using TypeLhs = double;
  using TypeRhs = double;

  using ATAN2 = cudf::library::operation::ATan2<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10000);
  auto rhs = make_random_wrapped_scalar<TypeRhs>();

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ATAN2,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  // atan2 has a max ULP error of 2 per CUDA programming guide
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ATAN2(), NearEqualComparator<TypeOut>{2});
}

TEST_F(BinaryOperationIntegrationTest, ATan2_Vector_Vector_FP64_FP32_FP64)
{
  using TypeOut = double;
  using TypeLhs = float;
  using TypeRhs = double;

  using ATAN2 = cudf::library::operation::ATan2<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10000);
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ATAN2,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  // atan2 has a max ULP error of 2 per CUDA programming guide
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ATAN2(), NearEqualComparator<TypeOut>{2});
}

TEST_F(BinaryOperationIntegrationTest, ATan2_Vector_Vector_FP64_SI32_SI64)
{
  using TypeOut = double;
  using TypeLhs = int32_t;
  using TypeRhs = int64_t;

  using ATAN2 = cudf::library::operation::ATan2<TypeOut, TypeLhs, TypeRhs>;

  auto lhs = make_random_wrapped_column<TypeLhs>(10000);
  auto rhs = make_random_wrapped_column<TypeRhs>(10000);

  auto out = cudf::experimental::binary_operation(lhs,
                                                  rhs,
                                                  cudf::experimental::binary_operator::ATAN2,
                                                  data_type(experimental::type_to_id<TypeOut>()));

  // atan2 has a max ULP error of 2 per CUDA programming guide
  ASSERT_BINOP<TypeOut, TypeLhs, TypeRhs>(*out, lhs, rhs, ATAN2(), NearEqualComparator<TypeOut>{2});
}

}  // namespace binop
}  // namespace test
}  // namespace cudf

CUDF_TEST_PROGRAM_MAIN()
