//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "symbolic_integers.h"
using namespace md::sym;

TEST(MonomialTest, Constructor) {
    typedef std::pair<I, P> entry_pair;
    auto reg = registry();
    reg->reset();
    auto one = Monomial(1);
    auto two = Monomial(2);

    // Constant monomial 1
    EXPECT_EQ(one.coefficient, 1);
    EXPECT_TRUE(one.is_constant());
    EXPECT_EQ(one.powers.size(), 0);

    // Monomial with 1 variable
    auto a = reg->new_monomial_variable();
    EXPECT_EQ(a.coefficient, 1);
    EXPECT_FALSE(a.is_constant());
    EXPECT_THAT(a.powers, testing::ElementsAre(entry_pair{0, 1}));

    // From constant
    EXPECT_EQ(two.coefficient, 2);
    EXPECT_TRUE(two.is_constant());
    EXPECT_EQ(two.powers.size(), 0);

    // From another
    two.powers.push_back(entry_pair{0, 2});
    auto two_x2 = Monomial(two);
    EXPECT_EQ(two_x2.coefficient, 2);
    EXPECT_FALSE(two_x2.is_constant());
    EXPECT_THAT(two_x2.powers, testing::ElementsAre(entry_pair{0, 2}));
}

TEST(MonomialTest, Equality) {
    typedef std::pair<I, P> entry_pair;
    auto reg = registry();
    reg->reset();
    auto two = Monomial(2);
    auto two_2 = Monomial(2);
    auto ten_x = Monomial(10);
    auto x = reg->new_monomial_variable();

    // Equality with integers
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_NE(two, 1);
    EXPECT_NE(1, two);

    // Not equality between 'x' and a constant
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
    ten_x.powers.push_back(x.powers[0]);
    EXPECT_TRUE(up_to_coefficient(x, ten_x));
    EXPECT_TRUE(up_to_coefficient(ten_x, x));
}


TEST(MonomialTest, Operators) {
    typedef std::pair<I, P> entry_pair;
    auto reg = registry();
    reg->reset();

    // Values
    auto x = reg->new_monomial_variable();
    auto y = reg->new_monomial_variable();
    auto z = reg->new_monomial_variable();
    auto composite = 2 * y * z * x;

    // Verify inner structure (such as ordering)
    EXPECT_EQ(composite.coefficient, 2);
    EXPECT_FALSE(composite.is_constant());
    EXPECT_THAT(composite.powers, testing::ElementsAre(entry_pair{x.powers[0].first, 1},
                                                       entry_pair{y.powers[0].first, 1},
                                                       entry_pair{z.powers[0].first, 1}));

    // Check equality between different forms
    EXPECT_EQ(composite / 2, x * y * z);
    EXPECT_EQ(composite / x, 2 * y * z);
    EXPECT_EQ(composite / y, 2 * x * z);
    EXPECT_EQ(composite / z, 2 * x * y);

    // Check for errors on non integer division
    EXPECT_THROW(composite / 4, std::runtime_error);
    EXPECT_THROW(composite / (x * x), std::runtime_error);
    EXPECT_THROW(composite / (y * y), std::runtime_error);
    EXPECT_THROW(composite / (z * z), std::runtime_error);
    EXPECT_THROW(composite / 0, std::runtime_error);
}

TEST(MonomialTest, FloorCeil) {
    typedef std::pair<I, P> entry_pair;
    auto reg = registry();
    reg->reset();
    auto five = Monomial(5);

    // Values
    auto x = reg->new_monomial_variable();
    auto y = reg->new_monomial_variable();
    auto composite = five * x * x * y;

    // Testing numerical floor and ceil
    EXPECT_EQ(floor(C(1), C(2)), 0);
    EXPECT_EQ(floor(C(-1), C(2)), -1);
    EXPECT_EQ(floor(C(1), C(-2)), -1);
    EXPECT_EQ(floor(C(-1), C(-2)), 0);
    EXPECT_EQ(floor(C(2), C(2)), 1);
    EXPECT_EQ(floor(C(-2), C(2)), -1);
    EXPECT_EQ(floor(C(2), C(-2)), -1);
    EXPECT_EQ(floor(C(-2), C(-2)), 1);
    EXPECT_EQ(floor(C(0), C(2)), 0);
    EXPECT_EQ(floor(C(0), C(-2)), 0);
    EXPECT_EQ(ceil(C(1), C(2)), 1);
    EXPECT_EQ(ceil(C(-1), C(2)), 0);
    EXPECT_EQ(ceil(C(1), C(-2)), 0);
    EXPECT_EQ(ceil(C(-1), C(-2)), 1);
    EXPECT_EQ(ceil(C(2), C(2)), 1);
    EXPECT_EQ(ceil(C(-2), C(2)), -1);
    EXPECT_EQ(ceil(C(2), C(-2)), -1);
    EXPECT_EQ(ceil(C(-2), C(-2)), 1);
    EXPECT_EQ(ceil(C(0), C(2)), 0);
    EXPECT_EQ(ceil(C(0), C(-2)), 0);

    // Constant operations
    EXPECT_EQ(floor(five, 3), 1);
    EXPECT_EQ(floor(3, five), 0);
    EXPECT_EQ(floor(0, five), 0);
    EXPECT_EQ(ceil(2, five), 1);
    EXPECT_EQ(ceil(five, 2), 3);
    EXPECT_EQ(ceil(0, five), 0);


    // Exact floor divisions
    EXPECT_EQ(floor(composite, x * x), five * y);
    EXPECT_EQ(floor(composite, y), five * x * x);
    EXPECT_EQ(floor(composite, 5), x * x * y);
    // Exact ceil divisions
    EXPECT_EQ(ceil(composite, x * x), five * y);
    EXPECT_EQ(ceil(composite, y), five * x * x);
    EXPECT_EQ(ceil(composite, 5), x * x * y);

    // Symbolic floor divisions
    auto floor_3 = floor(composite, 3);
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

    // Symbolic ceil divisions
    auto ceil_3 = ceil(composite, 3);
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

TEST(MonomialTest, MinMax) {
    typedef std::pair<I, P> entry_pair;
    auto reg = registry();
    reg->reset();
    auto five = Monomial(5);

    // Values
    auto x = reg->new_monomial_variable();
    auto y = reg->new_monomial_variable();
    auto composite = five * x * x * y;

    // Testing numerical min and max
    EXPECT_EQ(min(C(1), C(2)), 1);
    EXPECT_EQ(min(C(2), C(1)), 1);
    EXPECT_EQ(min(C(2), C(2)), 2);
    EXPECT_EQ(max(C(1), C(2)), 2);
    EXPECT_EQ(max(C(2), C(1)), 2);
    EXPECT_EQ(max(C(2), C(2)), 2);

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
    auto min_x3 = min(composite, x * x * x);
    auto min_y2 = min(composite, y * y);
    EXPECT_EQ(min_3.coefficient, 1);
    EXPECT_EQ(min_3.powers.size(), 1);
    EXPECT_EQ(min_3.powers[0].second, 1);
    EXPECT_EQ(min_x3.coefficient, 1);
    EXPECT_EQ(min_x3.powers.size(), 1);
    EXPECT_EQ(min_x3.powers[0].second, 1);
    EXPECT_EQ(min_y2.coefficient, 1);
    EXPECT_EQ(min_y2.powers.size(), 1);
    EXPECT_EQ(min_y2.powers[0].second, 1);

    // Symbolic max
    auto max_3 = max(composite, 3);
    auto max_x3 = max(composite, x * x * x);
    auto max_y2 = max(composite, y * y);
    EXPECT_EQ(max_3.coefficient, 1);
    EXPECT_EQ(max_3.powers.size(), 1);
    EXPECT_EQ(max_3.powers[0].second, 1);
    EXPECT_EQ(max_x3.coefficient, 1);
    EXPECT_EQ(max_x3.powers.size(), 1);
    EXPECT_EQ(max_x3.powers[0].second, 1);
    EXPECT_EQ(max_y2.coefficient, 1);
    EXPECT_EQ(max_y2.powers.size(), 1);
    EXPECT_EQ(max_y2.powers[0].second, 1);
}


TEST(MonomialTest, Eval) {
    typedef std::pair<I, P> entry_pair;
    typedef std::vector<std::pair<I, C>> value_vec;
    auto reg = registry();
    reg->reset();
    auto two = Monomial(2);
    auto five = Monomial(5);

    // Values
    const C x_val = 3;
    const C y_val = 5;
    const C z_val = 7;
    const std::vector<C> values{x_val, y_val, z_val};
    auto x = reg->new_monomial_variable();
    auto y = reg->new_monomial_variable();
    auto z = reg->new_monomial_variable();

    // Constant
    EXPECT_EQ(two.eval(), 2);
    EXPECT_EQ(five.eval(), 5);
    // Simple
    EXPECT_EQ(x.eval(values), x_val);
    EXPECT_EQ(y.eval(values), y_val);
    EXPECT_EQ(z.eval(values), z_val);
    // Using second type of eval
    EXPECT_EQ(x.eval(value_vec{{0, x_val}}), x_val);
    EXPECT_EQ(y.eval(value_vec{{1, y_val}}), y_val);
    EXPECT_EQ(z.eval(value_vec{{2, z_val}}), z_val);

    // Complex
    EXPECT_EQ((2 * x * x * y).eval(values), 2 * x_val * x_val * y_val);
    EXPECT_EQ((5 * y * y * z).eval(values), 5 * y_val * y_val * z_val);
    EXPECT_EQ((3 * z * z * x).eval(values), 3 * z_val * z_val * x_val);
    // Using second type of eval
    EXPECT_EQ((2 * x * x * y).eval(value_vec{{1, y_val}, {0, x_val}}), 2 * x_val * x_val * y_val);
    EXPECT_EQ((5 * y * y * z).eval(value_vec{{1, y_val}, {2, z_val}}), 5 * y_val * y_val * z_val);
    EXPECT_EQ((3 * z * z * x).eval(value_vec{{2, z_val}, {0, x_val}}), 3 * z_val * z_val * x_val);

    // Floor and ceil division
    EXPECT_EQ(floor(5 * x * x * y, 2).eval(values), 112);
    EXPECT_EQ(floor(y * y * z, 7).eval(values), 25);
    EXPECT_EQ(floor(2 * x * y * z, 1000).eval(values), 0);
    EXPECT_EQ(ceil(5 * x * x * y, 2).eval(values), 113);
    EXPECT_EQ(ceil(y * y * z, 7).eval(values), 25);
    EXPECT_EQ(ceil(2 * x * y * z, 1000).eval(values), 1);
    // Using second type of eval
    EXPECT_EQ(floor(5 * x * x * y, 2).eval(value_vec{{1, y_val}, {0, x_val}}), 112);
    EXPECT_EQ(floor(y * y * z, 7).eval(value_vec{{1, y_val}, {2, z_val}}), 25);
    EXPECT_EQ(floor(two * x * y * z, 1000).eval(value_vec{{1, y_val}, {2, z_val}, {0, x_val}}), 0);
    EXPECT_EQ(ceil(5 * x * x * y, 2).eval(value_vec{{1, y_val}, {0, x_val}}), 113);
    EXPECT_EQ(ceil(y * y * z, 7).eval(value_vec{{1, y_val}, {2, z_val}}), 25);
    EXPECT_EQ(ceil(two * x * y * z, 1000).eval(value_vec{{1, y_val}, {2, z_val}, {0, x_val}}), 1);

    // Exception for zero division on eval
    EXPECT_THROW(floor(5 * x * y, x * x).eval(value_vec{{1, y_val}, {0, 0}}), std::runtime_error);
    EXPECT_THROW(ceil(5 * x * y, x * x).eval(value_vec{{1, y_val}, {0, 0}}), std::runtime_error);
    // Exception for not provided variables
    EXPECT_THROW(floor(5 * x * y, x * x).eval(value_vec{{1, y_val}}), std::runtime_error);
    EXPECT_THROW(ceil(5 * x * y, x * x).eval(value_vec{{0, x_val}}), std::runtime_error);

    // Min and max
    EXPECT_EQ(min(5 * x * x, y * y * y).eval(values), 45);
    EXPECT_EQ(min(y * y * z, 100).eval(values), 100);
    EXPECT_EQ(min(150, x * y * z).eval(values), 105);
    EXPECT_EQ(max(5 * x * x, y * y * y).eval(values), 125);
    EXPECT_EQ(max(y * y * z, 100).eval(values), 175);
    EXPECT_EQ(max(150, x * y * z).eval(values), 150);
    // Using second type of eval
    EXPECT_EQ(min(5 * x * x, y * y * y).eval(value_vec{{1, y_val}, {0, x_val}}), 45);
    EXPECT_EQ(min(y * y * z, 100).eval(value_vec{{1, y_val}, {2, z_val}}), 100);
    EXPECT_EQ(min(150, x * y * z).eval(value_vec{{1, y_val}, {2, z_val}, {0, x_val}}), 105);
    EXPECT_EQ(max(5 * x * x, y * y * y).eval(value_vec{{1, y_val}, {0, x_val}}), 125);
    EXPECT_EQ(max(y * y * z, 100).eval(value_vec{{1, y_val}, {2, z_val}}), 175);
    EXPECT_EQ(max(150, x * y * z).eval(value_vec{{1, y_val}, {2, z_val}, {0, x_val}}), 150);

    // Exception for not provided variables
    EXPECT_THROW(min(5 * x * x, x * y * y).eval(value_vec{{1, y_val}}), std::runtime_error);
    EXPECT_THROW(max(5 * x * x, x * y * y).eval(value_vec{{0, x_val}}), std::runtime_error);
}