//
// Created by AK on 13/10/15.
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
class MonomialTest : public testing::Test {};
typedef TypeDefinitions<std::string, int16_t, uint8_t> Int16;
typedef TypeDefinitions<std::string, int32_t, uint8_t> Int32;
typedef TypeDefinitions<std::string, int64_t, uint8_t> Int64;
typedef testing::Types<Int16, Int32, Int64> Integers;

TYPED_TEST_CASE(MonomialTest, Integers);

TYPED_TEST(MonomialTest, Constructor) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto one = TestMonomial(1);
    auto two = TestMonomial(2);

    // Constant monomial 1
    EXPECT_EQ(one.coefficient, 1);
    EXPECT_TRUE(one.is_constant());
    EXPECT_EQ(one.powers.size(), 0);

    // Monomial with 1 variable
    auto a = TestMonomial(TestComposite(Id, "a"));
    EXPECT_EQ(a.coefficient, 1);
    EXPECT_FALSE(a.is_constant());
    EXPECT_THAT(a.powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1}));

    // From constant
    EXPECT_EQ(two.coefficient, 2);
    EXPECT_TRUE(two.is_constant());
    EXPECT_EQ(two.powers.size(), 0);

    // From another
    two.powers.push_back(entry_pair{TestComposite(Id, "a"), 2});
    auto two_x2 = TestMonomial(two);
    EXPECT_EQ(two_x2.coefficient, 2);
    EXPECT_FALSE(two_x2.is_constant());
    EXPECT_THAT(two_x2.powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 2}));
}

TYPED_TEST(MonomialTest, Equality) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto two = TestMonomial(2);
    auto two_2 = TestMonomial(2);
    auto ten_a = TestMonomial(10);
    auto a = TestMonomial(TestComposite(Id, "a"));

    // Equality with integers
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_NE(two, 1);
    EXPECT_NE(1, two);

    // Not equality between 'a' and a constant
    EXPECT_EQ(two, two_2);
    EXPECT_EQ(two_2, two);
    EXPECT_NE(two, a);
    EXPECT_NE(a, two);
    EXPECT_NE(two_2, a);
    EXPECT_NE(a, two_2);

    // Up to coefficient equality for constants
    EXPECT_TRUE(up_to_coefficient(0, two));
    EXPECT_TRUE(up_to_coefficient(0, two_2));
    EXPECT_FALSE(up_to_coefficient(0, a));

    // Up to coefficient equality for 'a' and '10x'
    ten_a.powers.push_back(a.powers[0]);
    EXPECT_TRUE(up_to_coefficient(a, ten_a));
    EXPECT_TRUE(up_to_coefficient(ten_a, a));
}


TYPED_TEST(MonomialTest, Operators) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    // Values
    auto a = TestMonomial(TestComposite(Id, "a"));
    auto b = TestMonomial(TestComposite(Id, "b"));
    auto c = TestMonomial(TestComposite(Id, "c"));
    auto composite = 2 * b * c * a;

    // Verify inner structure (such as ordering)
    EXPECT_EQ(composite.coefficient, 2);
    EXPECT_FALSE(composite.is_constant());
    EXPECT_THAT(composite.powers, testing::ElementsAre(entry_pair{a.powers[0].first, 1},
                                                       entry_pair{b.powers[0].first, 1},
                                                       entry_pair{c.powers[0].first, 1}));

    // Check equality between different forms
    EXPECT_EQ(composite / 2, a * b * c);
    EXPECT_EQ(composite / a, 2 * b * c);
    EXPECT_EQ(composite / b, 2 * a * c);
    EXPECT_EQ(composite / c, 2 * a * b);

    // Check for errors on non integer division
    EXPECT_THROW(composite / 4, std::runtime_error);
    EXPECT_THROW(composite / (a * a), std::runtime_error);
    EXPECT_THROW(composite / (b * b), std::runtime_error);
    EXPECT_THROW(composite / (c * c), std::runtime_error);
    EXPECT_THROW(composite / 0, std::runtime_error);
}

TYPED_TEST(MonomialTest, FloorCeil) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto five = TestMonomial(5);

    // Values
    auto a = TestMonomial(TestComposite(Id, "a"));
    auto b = TestMonomial(TestComposite(Id, "b"));
    auto composite = five * a * a * b;

    // Testing numerical floor and ceil
    EXPECT_EQ(floor(typename TypeParam::C(1), typename TypeParam::C(2)), 0);
    EXPECT_EQ(floor(typename TypeParam::C(-1), typename TypeParam::C(2)), -1);
    EXPECT_EQ(floor(typename TypeParam::C(1), typename TypeParam::C(-2)), -1);
    EXPECT_EQ(floor(typename TypeParam::C(-1), typename TypeParam::C(-2)), 0);
    EXPECT_EQ(floor(typename TypeParam::C(2), typename TypeParam::C(2)), 1);
    EXPECT_EQ(floor(typename TypeParam::C(-2), typename TypeParam::C(2)), -1);
    EXPECT_EQ(floor(typename TypeParam::C(2), typename TypeParam::C(-2)), -1);
    EXPECT_EQ(floor(typename TypeParam::C(-2), typename TypeParam::C(-2)), 1);
    EXPECT_EQ(floor(typename TypeParam::C(0), typename TypeParam::C(2)), 0);
    EXPECT_EQ(floor(typename TypeParam::C(0), typename TypeParam::C(-2)), 0);
    EXPECT_EQ(ceil(typename TypeParam::C(1), typename TypeParam::C(2)), 1);
    EXPECT_EQ(ceil(typename TypeParam::C(-1), typename TypeParam::C(2)), 0);
    EXPECT_EQ(ceil(typename TypeParam::C(1), typename TypeParam::C(-2)), 0);
    EXPECT_EQ(ceil(typename TypeParam::C(-1), typename TypeParam::C(-2)), 1);
    EXPECT_EQ(ceil(typename TypeParam::C(2), typename TypeParam::C(2)), 1);
    EXPECT_EQ(ceil(typename TypeParam::C(-2), typename TypeParam::C(2)), -1);
    EXPECT_EQ(ceil(typename TypeParam::C(2), typename TypeParam::C(-2)), -1);
    EXPECT_EQ(ceil(typename TypeParam::C(-2), typename TypeParam::C(-2)), 1);
    EXPECT_EQ(ceil(typename TypeParam::C(0), typename TypeParam::C(2)), 0);
    EXPECT_EQ(ceil(typename TypeParam::C(0), typename TypeParam::C(-2)), 0);

    // Constant operations
    EXPECT_EQ(floor(five, 3), 1);
    EXPECT_EQ(floor(3, five), 0);
    EXPECT_EQ(floor(0, five), 0);
    EXPECT_EQ(ceil(2, five), 1);
    EXPECT_EQ(ceil(five, 2), 3);
    EXPECT_EQ(ceil(0, five), 0);


    // Exact floor divisions
    EXPECT_EQ(floor(composite, a * a), five * b);
    EXPECT_EQ(floor(composite, b), five * a * a);
    EXPECT_EQ(floor(composite, 5), a * a * b);
    // Exact ceil divisions
    EXPECT_EQ(ceil(composite, a * a), five * b);
    EXPECT_EQ(ceil(composite, b), five * a * a);
    EXPECT_EQ(ceil(composite, 5), a * a * b);

    // Symbolic floor divisions
    auto floor_3 = floor(composite, 3);
    auto floor_a3 = floor(composite, a * a * a);
    auto floor_b2 = floor(composite, b * b);
    EXPECT_EQ(floor_3.coefficient, 1);
    EXPECT_EQ(floor_3.powers.size(), 1);
    EXPECT_EQ(floor_3.powers[0].second, 1);
    EXPECT_EQ(floor_a3.coefficient, 1);
    EXPECT_EQ(floor_a3.powers.size(), 1);
    EXPECT_EQ(floor_a3.powers[0].second, 1);
    EXPECT_EQ(floor_b2.coefficient, 1);
    EXPECT_EQ(floor_b2.powers.size(), 1);
    EXPECT_EQ(floor_b2.powers[0].second, 1);

    // Symbolic ceil divisions
    auto ceil_3 = ceil(composite, 3);
    auto ceil_x3 = ceil(composite, a * a * a);
    auto ceil_y2 = ceil(composite, b * b);
    EXPECT_EQ(ceil_3.coefficient, 1);
    EXPECT_EQ(ceil_3.powers.size(), 1);
    EXPECT_EQ(ceil_3.powers[0].second, 1);
    EXPECT_EQ(ceil_x3.coefficient, 1);
    EXPECT_EQ(ceil_x3.powers.size(), 1);
    EXPECT_EQ(ceil_x3.powers[0].second, 1);
    EXPECT_EQ(ceil_y2.coefficient, 1);
    EXPECT_EQ(ceil_y2.powers.size(), 1);
    EXPECT_EQ(ceil_y2.powers[0].second, 1);
}

TYPED_TEST(MonomialTest, MinMax) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto five = TestMonomial(5);

    // Values
    auto a = TestMonomial(TestComposite(Id, "a"));
    auto b = TestMonomial(TestComposite(Id, "b"));
    auto composite = five * a * a * b;

    // Testing numerical min and max
    EXPECT_EQ(min(typename TypeParam::C(1), typename TypeParam::C(2)), 1);
    EXPECT_EQ(min(typename TypeParam::C(2), typename TypeParam::C(1)), 1);
    EXPECT_EQ(min(typename TypeParam::C(2), typename TypeParam::C(2)), 2);
    EXPECT_EQ(max(typename TypeParam::C(1), typename TypeParam::C(2)), 2);
    EXPECT_EQ(max(typename TypeParam::C(2), typename TypeParam::C(1)), 2);
    EXPECT_EQ(max(typename TypeParam::C(2), typename TypeParam::C(2)), 2);

    // Constant expressions
    EXPECT_EQ(min(five, 3), 3);
    EXPECT_EQ(min(3, five), 3);
    EXPECT_EQ(min(five, 8), 5);
    EXPECT_EQ(min(8, five), 5);
    EXPECT_EQ(max(five, 3), 5);
    EXPECT_EQ(max(3, five), 5);
    EXPECT_EQ(max(five, 8), 8);
    EXPECT_EQ(max(8, five), 8);

    // Symbolic min
    auto min_3 = min(composite, 3);
    auto min_a3 = min(composite, a * a * a);
    auto min_b2 = min(composite, b * b);
    EXPECT_EQ(min_3.coefficient, 1);
    EXPECT_EQ(min_3.powers.size(), 1);
    EXPECT_EQ(min_3.powers[0].second, 1);
    EXPECT_EQ(min_a3.coefficient, 1);
    EXPECT_EQ(min_a3.powers.size(), 1);
    EXPECT_EQ(min_a3.powers[0].second, 1);
    EXPECT_EQ(min_b2.coefficient, 1);
    EXPECT_EQ(min_b2.powers.size(), 1);
    EXPECT_EQ(min_b2.powers[0].second, 1);

    // Symbolic max
    auto max_3 = max(composite, 3);
    auto max_a3 = max(composite, a * a * a);
    auto max_b2 = max(composite, b * b);
    EXPECT_EQ(max_3.coefficient, 1);
    EXPECT_EQ(max_3.powers.size(), 1);
    EXPECT_EQ(max_3.powers[0].second, 1);
    EXPECT_EQ(max_a3.coefficient, 1);
    EXPECT_EQ(max_a3.powers.size(), 1);
    EXPECT_EQ(max_a3.powers[0].second, 1);
    EXPECT_EQ(max_b2.coefficient, 1);
    EXPECT_EQ(max_b2.powers.size(), 1);
    EXPECT_EQ(max_b2.powers[0].second, 1);
}


TYPED_TEST(MonomialTest, Eval) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;
    typedef std::unordered_map<typename TypeParam::I, typename TypeParam::C> ValueVec;

    auto two = TestMonomial(2);
    auto five = TestMonomial(5);

    // Values
    const typename TypeParam::C a_val = 3;
    const typename TypeParam::C b_val = 5;
    const typename TypeParam::C c_val = 7;
    auto a = TestMonomial(TestComposite(Id, "a"));
    auto b = TestMonomial(TestComposite(Id, "b"));
    auto c = TestMonomial(TestComposite(Id, "c"));
    const ValueVec values = {{"a", a_val}, {"b", b_val}, {"c", c_val}};

    // Constant
    EXPECT_EQ(two.eval({}), 2);
    EXPECT_EQ(five.eval({}), 5);
    // Simple
    EXPECT_EQ(a.eval(values), a_val);
    EXPECT_EQ(b.eval(values), b_val);
    EXPECT_EQ(c.eval(values), c_val);
    // Using single
    EXPECT_EQ(a.eval(values), a_val);
    EXPECT_EQ(b.eval(values), b_val);
    EXPECT_EQ(c.eval(values), c_val);

    // Complex
    EXPECT_EQ((2 * a * a * b).eval(values), 2 * a_val * a_val * b_val);
    EXPECT_EQ((5 * b * b * c).eval(values), 5 * b_val * b_val * c_val);
    EXPECT_EQ((3 * c * c * a).eval(values), 3 * c_val * c_val * a_val);
    // Using second type of eval
    EXPECT_EQ((2 * a * a * b).eval(values), 2 * a_val * a_val * b_val);
    EXPECT_EQ((5 * b * b * c).eval(values), 5 * b_val * b_val * c_val);
    EXPECT_EQ((3 * c * c * a).eval(values), 3 * c_val * c_val * a_val);

    // Floor and ceil division
    EXPECT_EQ(floor(5 * a * a * b, 2).eval(values), 112);
    EXPECT_EQ(floor(b * b * c, 7).eval(values), 25);
    EXPECT_EQ(floor(2 * a * b * c, 1000).eval(values), 0);
    EXPECT_EQ(ceil(5 * a * a * b, 2).eval(values), 113);
    EXPECT_EQ(ceil(b * b * c, 7).eval(values), 25);
    EXPECT_EQ(ceil(2 * a * b * c, 1000).eval(values), 1);
    // Using second type of eval
    EXPECT_EQ(floor(5 * a * a * b, 2).eval(values), 112);
    EXPECT_EQ(floor(b * b * c, 7).eval(values), 25);
    EXPECT_EQ(floor(two * a * b * c, 1000).eval(values), 0);
    EXPECT_EQ(ceil(5 * a * a * b, 2).eval(values), 113);
    EXPECT_EQ(ceil(b * b * c, 7).eval(values), 25);
    EXPECT_EQ(ceil(two * a * b * c, 1000).eval(values), 1);

    // Exception for zero division on eval
    EXPECT_THROW(floor(5 * a * b, a * a).eval(ValueVec {{"b", b_val}, {"a", 0}}), std::runtime_error);
    EXPECT_THROW(ceil(5 * a * b, a * a).eval(ValueVec {{"b", b_val}, {"a", 0}}), std::runtime_error);
    // Exception for not provided variables
    EXPECT_THROW(floor(5 * a * b, a * a).eval(ValueVec {{"b", b_val}}), std::runtime_error);
    EXPECT_THROW(ceil(5 * a * b, a * a).eval(ValueVec {{"a", a_val}}), std::runtime_error);

    // Min and max
    EXPECT_EQ(min(5 * a * a, b * b * b).eval(values), 45);
    EXPECT_EQ(min(b * b * c, 100).eval(values), 100);
    EXPECT_EQ(min(150, a * b * c).eval(values), 105);
    EXPECT_EQ(max(5 * a * a, b * b * b).eval(values), 125);
    EXPECT_EQ(max(b * b * c, 100).eval(values), 175);
    EXPECT_EQ(max(150, a * b * c).eval(values), 150);
    // Using second type of eval

    // Exception for not provided variables
    EXPECT_THROW(min(5 * a * a, a * b * b).eval(ValueVec {{"b", b_val}}), std::runtime_error);
    EXPECT_THROW(max(5 * a * a, a * b * b).eval(ValueVec {{"a", a_val}}), std::runtime_error);
}