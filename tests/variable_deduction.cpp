//
// Created by alex on 27/08/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "symbolic_integers.h"
using namespace md::sym;

template<typename CC, typename II, typename PP>
struct TypeDefinitions {
    typedef CC C;
    typedef II I;
    typedef PP P;
};
template<typename>
class DeductionTest : public testing::Test {};
typedef TypeDefinitions<int16_t, uint16_t, uint8_t> Int16;
typedef TypeDefinitions<int32_t, uint32_t, uint8_t> Int32;
typedef TypeDefinitions<int64_t, uint64_t, uint8_t> Int64;
typedef testing::Types<Int16, Int32, Int64> Integers;

TYPED_TEST_CASE(DeductionTest, Integers);

TYPED_TEST(DeductionTest, VariableDeduction) {
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    typedef std::vector<std::pair<typename TypeParam::I, typename TypeParam::C>> value_vec;
    auto reg = registry<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P>();
    reg->reset();

    // Base variables
    auto x = reg->new_variable();
    auto y = reg->new_variable();
    auto z = reg->new_variable();
    typedef std::vector<std::pair<Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P>, typename TypeParam::C>> ImplicitVec;
    ImplicitVec implicit_values;

    // Example 1
    auto poly1 = x;
    auto poly2 = x * y * 2 + 1;
    auto poly3 = x*x*y*y*z*z*5 + x*x*y + 3;
    auto x_val = 1;
    auto y_val = 3;
    auto z_val = 7;
    auto val1 = x_val;
    auto val2 = x_val * y_val * 2 + 1;
    auto val3 = 5 * x_val * x_val * y_val * y_val * z_val * z_val + x_val * x_val * y_val + 3;

    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    auto values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example 2
    poly1 = x * y * z + x * z * z * y + 1;
    poly2 = x * x + z * z + 2;
    poly3 = 5 * z;
    x_val = 2;
    y_val = 3;
    z_val = 5;
    val1 = x_val * y_val * z_val + x_val * z_val * z_val * y_val + 1;
    val2 = x_val * x_val + z_val * z_val + 2;
    val3 = 5 * z_val;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example 3
    poly1 = 3 * y * y;
    poly2 = y * y * y + x * x * x - 10;
    poly3 = x * y  + x * z  + y * z + 3;
    x_val = 1;
    y_val = 2;
    z_val = 3;
    val1 = 3 * y_val * y_val;
    val2 = y_val * y_val * y_val + x_val * x_val * x_val - 10;
    val3 = x_val * y_val + x_val * z_val + y_val * z_val + 3;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with floor and min
    poly1 = x;
    poly2 = x * y * 2 + 1;
    poly3 = x*x*y*y*z*z*5 + floor(x*y*y, 2) + min(x*x, y*y) + 3;
    x_val = 1;
    y_val = 3;
    z_val = 7;
    val1 = x_val;
    val2 = x_val * y_val * 2 + 1;
    val3 = 5 * x_val * x_val * y_val * y_val * z_val * z_val + int(floor(float(x_val * y_val * y_val) / 2.0))
           + std::min(x_val*x_val, y_val*y_val) + 3;

    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with ceil and max
    poly1 = x * y * z + x * z * z * y + 1;
    poly2 = x * x + ceil(z * z, 6) + max(z * z, 12) + 2;
    poly3 = 5 * z;
    x_val = 2;
    y_val = 3;
    z_val = 5;
    val1 = x_val * y_val * z_val + x_val * z_val * z_val * y_val + 1;
    val2 = x_val * x_val + int(ceil(float(z_val * z_val) / 6.0))
           + std::max(z_val*z_val, 12) + 2;
    val3 = 5 * z_val;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with both floor, ceil and min, max
    poly1 = 3 * y * y;
    poly2 = floor(y * y * y, 3) + x * x * x - 10 - min(y * y, 17);
    poly3 = ceil(x * y * 7, 5)  + x * z  + y * z + 3 + max(x * y - 5, x + 2*y);
    x_val = 1;
    y_val = 2;
    z_val = 3;
    val1 = 3 * y_val * y_val;
    val2 = int(floor(float(y_val * y_val * y_val) / 3.0)) + x_val * x_val * x_val - 10
            - std::min(y_val * y_val, 17);
    val3 = int(ceil(float(x_val * y_val * 7) / 5.0)) + x_val * z_val + y_val * z_val + 3
            + std::max(x_val * y_val - 5, x_val + 2 * y_val);
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = reg->deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Check for throws when incorrectly specified
    poly1 = x * y * y;
    poly2 = y * 2 + 1;
    poly3 = z * z * x + z * y + 2;
    x_val = 1;
    y_val = 2;
    z_val = 3;
    val1 = x_val * y_val * y_val;
    val2 = y_val * 2 + 1;
    val3 = z_val * z_val * x_val + z_val * y_val + 2;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    EXPECT_THROW(reg->deduce_values(implicit_values), std::runtime_error);

    poly1 = x * y * y;
    poly2 = y * z * 2 + 1;
    poly3 = z * z * x + 2;
    x_val = 1;
    y_val = 2;
    z_val = 3;
    val1 = x_val * y_val * y_val;
    val2 = y_val * z_val *  2 + 1;
    val3 = z_val * z_val * x_val + 2;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    EXPECT_THROW(reg->deduce_values(implicit_values), std::runtime_error);
}
