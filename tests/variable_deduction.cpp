//
// Created by alex on 27/08/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "symbolic_integers.h"
using namespace md::sym;

template<typename II, typename CC, typename PP>
struct TypeDefinitions {
    typedef II I;
    typedef CC C;
    typedef PP P;
};
template<typename>
class DeductionTest : public testing::Test {};
typedef TypeDefinitions<std::string, int16_t, uint8_t> Int16;
typedef TypeDefinitions<std::string, int32_t, uint8_t> Int32;
typedef TypeDefinitions<std::string, int64_t, uint8_t> Int64;
typedef testing::Types<Int16, Int32, Int64> Integers;

TYPED_TEST_CASE(DeductionTest, Integers);

TYPED_TEST(DeductionTest, VariableDeduction) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;
    typedef std::unordered_map<typename TypeParam::I, typename TypeParam::C> ValueVec;
    typedef std::vector<std::pair<TestPolynomial, typename TypeParam::C>> ImplicitVec;

    // Base variables
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto c = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("c");
    ImplicitVec implicit_values;

    // Example 1
    auto poly1 = a;
    auto poly2 = a * b * 2 + 1;
    auto poly3 = a*a*b*b*c*c*5 + a*a*b + 3;
    auto a_val = 1;
    auto b_val = 3;
    auto c_val = 7;
    auto val1 = a_val;
    auto val2 = a_val * b_val * 2 + 1;
    auto val3 = 5 * a_val * a_val * b_val * b_val * c_val * c_val + a_val * a_val * b_val + 3;

    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    auto values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example 2
    poly1 = a * b * c + a * c * c * b + 1;
    poly2 = a * a + c * c + 2;
    poly3 = 5 * c;
    a_val = 2;
    b_val = 3;
    c_val = 5;
    val1 = a_val * b_val * c_val + a_val * c_val * c_val * b_val + 1;
    val2 = a_val * a_val + c_val * c_val + 2;
    val3 = 5 * c_val;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example 3
    poly1 = 3 * b * b;
    poly2 = b * b * b + a * a * a - 10;
    poly3 = a * b  + a * c  + b * c + 3;
    a_val = 1;
    b_val = 2;
    c_val = 3;
    val1 = 3 * b_val * b_val;
    val2 = b_val * b_val * b_val + a_val * a_val * a_val - 10;
    val3 = a_val * b_val + a_val * c_val + b_val * c_val + 3;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with floor and min
    poly1 = a;
    poly2 = a * b * 2 + 1;
    poly3 = a*a*b*b*c*c*5 + floor(a*b*b, 2) + min(a*a, b*b) + 3;
    a_val = 1;
    b_val = 3;
    c_val = 7;
    val1 = a_val;
    val2 = a_val * b_val * 2 + 1;
    val3 = 5 * a_val * a_val * b_val * b_val * c_val * c_val + int(floor(float(a_val * b_val * b_val) / 2.0))
           + std::min(a_val*a_val, b_val*b_val) + 3;

    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with ceil and max
    poly1 = a * b * c + a * c * c * b + 1;
    poly2 = a * a + ceil(c * c, 6) + max(c * c, 12) + 2;
    poly3 = 5 * c;
    a_val = 2;
    b_val = 3;
    c_val = 5;
    val1 = a_val * b_val * c_val + a_val * c_val * c_val * b_val + 1;
    val2 = a_val * a_val + int(ceil(float(c_val * c_val) / 6.0))
           + std::max(c_val*c_val, 12) + 2;
    val3 = 5 * c_val;
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Example with both floor, ceil and min, max
    poly1 = 3 * b * b;
    poly2 = floor(b * b * b, 3) + a * a * a - 10 - min(b * b, 17);
    poly3 = ceil(a * b * 7, 5)  + a * c  + b * c + 3 + max(a * b - 5, a + 2*b);
    a_val = 1;
    b_val = 2;
    c_val = 3;
    val1 = 3 * b_val * b_val;
    val2 = int(floor(float(b_val * b_val * b_val) / 3.0)) + a_val * a_val * a_val - 10
           - std::min(b_val * b_val, 17);
    val3 = int(ceil(float(a_val * b_val * 7) / 5.0)) + a_val * c_val + b_val * c_val + 3
           + std::max(a_val * b_val - 5, a_val + 2 * b_val);
    implicit_values = ImplicitVec{{poly1, val1}, {poly2, val2}, {poly3, val3}};
    values = deduce_values(implicit_values);
    // Simple checks
    EXPECT_EQ((a * a).eval(values), a_val * a_val);
    EXPECT_EQ((b * b).eval(values), b_val * b_val);
    EXPECT_EQ((c * c).eval(values), c_val * c_val);
    // Polynomial checks
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);

    // Check for throws when incorrectly specified
    poly1 = a * b * b;
    poly2 = b * 2 + 1;
    poly3 = c * c * a + c * b + 2;
    a_val = 1;
    b_val = 2;
    c_val = 3;
    val1 = a_val * b_val * b_val;
    val2 = b_val * 2 + 1;
    val3 = c_val * c_val * a_val + c_val * b_val + 2;
    implicit_values = {{poly1, val1}, {poly2, val2}, {poly3, val3}};
    EXPECT_THROW(deduce_values(implicit_values), std::runtime_error);

    poly1 = a * b * b;
    poly2 = b * c * 2 + 1;
    poly3 = c * c * a + 2;
    a_val = 1;
    b_val = 2;
    c_val = 3;
    val1 = a_val * b_val * b_val;
    val2 = b_val * c_val *  2 + 1;
    val3 = c_val * c_val * a_val + 2;
    implicit_values = {{poly1, val1}, {poly2, val2}, {poly3, val3}};
    EXPECT_THROW(deduce_values(implicit_values), std::runtime_error);
}
