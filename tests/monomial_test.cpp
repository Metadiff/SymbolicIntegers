//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "symbolic_integers.h"

template<typename>
class MonomialTest : public testing::Test {
};

typedef testing::Types<unsigned short, unsigned int, unsigned long> Integers;
using namespace md::sym::monomial;

TYPED_TEST_CASE(MonomialTest, Integers);

TYPED_TEST(MonomialTest, Constructor) {
    typedef Monomial<TypeParam, TypeParam> Monomial;
    Monomial::total_ids = 0;
    Monomial::floor_registry.clear();
    Monomial::ceil_registry.clear();

    // Constant monomial 1
    auto one = Monomial(1);
    EXPECT_EQ(one.coefficient, 1);
    EXPECT_TRUE(one.is_constant());
    EXPECT_EQ(one.powers.size(), 0);

    // Monomial with 1 variable
    auto a = Monomial();
    EXPECT_EQ(a.coefficient, 1);
    EXPECT_FALSE(a.is_constant());
    EXPECT_THAT(a.powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 1}));

    // From constant
    auto two = Monomial(2);
    EXPECT_EQ(two.coefficient, 2);
    EXPECT_TRUE(two.is_constant());
    EXPECT_EQ(two.powers.size(), 0);

    two.powers.push_back(std::pair<TypeParam, TypeParam>{0, 2});
    // From another
    auto two_x2 = Monomial(two);
    EXPECT_EQ(two_x2.coefficient, 2);
    EXPECT_FALSE(two_x2.is_constant());
    EXPECT_THAT(two_x2.powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 2}));
}

TYPED_TEST(MonomialTest, Equality) {
    typedef Monomial<TypeParam, TypeParam> Monomial;
    Monomial::total_ids = 0;
    Monomial::floor_registry.clear();
    Monomial::ceil_registry.clear();

    // Equality with integers
    auto two = Monomial(2);
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_NE(two, 1);
    EXPECT_NE(1, two);

    // Not equality between 'x' and a constant
    auto two_2 = Monomial(2);
    auto x = Monomial();
    EXPECT_EQ(two, two_2);
    EXPECT_EQ(two_2, two);
    EXPECT_NE(two, x);
    EXPECT_NE(x, two);
    EXPECT_NE(two_2, x);
    EXPECT_NE(x, two_2);

    // Up to coefficient equality for constants
    EXPECT_TRUE(up_to_coefficient(0, two));
    EXPECT_TRUE(up_to_coefficient(0, two_2));
    EXPECT_FALSE(up_to_coefficient(0, x));

    // Up to coefficient equality for 'x' and '10x'
    auto ten_x = Monomial(10);
    ten_x.powers.push_back(x.powers[0]);
    EXPECT_TRUE(up_to_coefficient(x, ten_x));
    EXPECT_TRUE(up_to_coefficient(ten_x, x));
}


TYPED_TEST(MonomialTest, Operators) {
    typedef Monomial<TypeParam, TypeParam> Monomial;
    Monomial::total_ids = 0;
    Monomial::floor_registry.clear();
    Monomial::ceil_registry.clear();

    auto x = Monomial();
    auto y = Monomial();
    auto z = Monomial();
    auto composite = 2 * y * z * x;

    // Verify inner structure (such as ordering)
    EXPECT_EQ(composite.coefficient, 2);
    EXPECT_FALSE(composite.is_constant());
    EXPECT_THAT(composite.powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{x.powers[0].first, 1},
                                                       std::pair<TypeParam, TypeParam>{y.powers[0].first, 1},
                                                       std::pair<TypeParam, TypeParam>{z.powers[0].first, 1}));

    // Check equality between different forms
    EXPECT_EQ(composite / 2, x * y * z);
    EXPECT_EQ(composite / x, 2 * y * z);
    EXPECT_EQ(composite / y, 2 * x * z);
    EXPECT_EQ(composite / z, 2 * x * y);

    // Check for errors on non integer division
    EXPECT_THROW(composite / 4, md::sym::NonIntegerDivision);
    EXPECT_THROW(composite / (x * x), md::sym::NonIntegerDivision);
    EXPECT_THROW(composite / (y * y), md::sym::NonIntegerDivision);
    EXPECT_THROW(composite / (z * z), md::sym::NonIntegerDivision);
}

TYPED_TEST(MonomialTest, FloorCeil) {
    typedef Monomial<TypeParam, TypeParam> Monomial;
    Monomial::total_ids = 0;
    Monomial::floor_registry.clear();
    Monomial::ceil_registry.clear();

    auto x = Monomial();
    auto y = Monomial();
    auto five = Monomial(5);
    auto three = Monomial(3);
    auto two = Monomial(2);
    auto composite = five * x * x * y;

    // Constant expressions
    EXPECT_EQ(floor(five, two), two);
    EXPECT_EQ(ceil(five, two), three);

    // Exact floor divisions
    EXPECT_EQ(floor(composite, x * x), five * y);
    EXPECT_EQ(floor(composite, y), five * x * x);
    EXPECT_EQ(floor(composite, 5), x * x * y);
    // Exact ceil divisions
    EXPECT_EQ(ceil(composite, x * x), five * y);
    EXPECT_EQ(ceil(composite, y), five * x * x);
    EXPECT_EQ(ceil(composite, 5), x * x * y);

    // Partial floor divisions
    auto floor_3 = floor(composite, three);
    auto floor_x3 = floor(composite, x * x * x);
    auto floor_y2 = floor(composite, y * y);
    EXPECT_EQ(floor_3.coefficient, 1);
    EXPECT_EQ(floor_3.powers.size(), 1);
    EXPECT_EQ(floor_3.powers[0].second, 1);
    EXPECT_EQ(floor_x3.coefficient, 1);
    EXPECT_EQ(floor_x3.powers.size(), 1);
    EXPECT_EQ(floor_x3.powers[0].second, 1);
    EXPECT_EQ(floor_y2.coefficient, 1);
    EXPECT_EQ(floor_y2.powers.size(), 1);
    EXPECT_EQ(floor_y2.powers[0].second, 1);

    // Partial ceil divisions
    auto ceil_3 = ceil(composite, three);
    auto ceil_x3 = ceil(composite, x * x * x);
    auto ceil_y2 = ceil(composite, y * y);
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

TYPED_TEST(MonomialTest, Eval) {
    typedef Monomial<TypeParam, TypeParam> Monomial;
    Monomial::total_ids = 0;
    Monomial::floor_registry.clear();
    Monomial::ceil_registry.clear();

    auto two = Monomial(2);
    auto five = Monomial(5);
    auto x = Monomial();
    const long long x_val = 3;
    auto y = Monomial();
    const long long y_val = 5;
    auto z = Monomial();
    const long long z_val = 7;
    std::vector<long long> values{x_val, y_val, z_val};

    // Simple
    EXPECT_EQ(two.eval(), 2);
    EXPECT_EQ(five.eval(), 5);
    EXPECT_EQ(x.eval(values), x_val);
    EXPECT_EQ(y.eval(values), y_val);
    EXPECT_EQ(z.eval(values), z_val);

    // Complex
    EXPECT_EQ((two * x * x * y).eval(values), 2 * x_val * x_val * y_val);
    EXPECT_EQ((five * y * y * z).eval(values), 5 * y_val * y_val * z_val);
    EXPECT_EQ((3 * z * z * x).eval(values), 3 * z_val * z_val * x_val);

    // Floor and ceil division
    EXPECT_EQ(floor(5 * x * x * y, 2).eval(values), (5 * x_val * x_val * y_val) / 2);
    EXPECT_EQ(ceil(5 * x * x * y, 2).eval(values), (5 * x_val * x_val * y_val) / 2 + 1);
    EXPECT_EQ(floor(y * y * z, 7).eval(values), (y_val * y_val * z_val) / 7);
    EXPECT_EQ(ceil(y * y * z, 7).eval(values), (y_val * y_val * z_val) / 7);
    EXPECT_EQ(floor(two * x * y * z, 1000).eval(values), 0);
    EXPECT_EQ(ceil(two * x * y * z, 1000).eval(values), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}