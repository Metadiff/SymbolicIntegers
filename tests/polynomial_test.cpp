//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "symbolic_integers.h"

template<typename CC, typename II, typename PP>
struct TypeDefinitions {
    typedef CC C;
    typedef II I;
    typedef PP P;
};

template<typename>
class PolynomialTest : public testing::Test {};
typedef TypeDefinitions<short, unsigned short, unsigned short> Short;
typedef TypeDefinitions<int, unsigned int, unsigned int> Int;
typedef TypeDefinitions<long, unsigned long, unsigned long> Long;
typedef TypeDefinitions<long long, unsigned long long, unsigned long long> LongLong;
typedef testing::Types<Short, Int, Long, LongLong> Integers;
using namespace md::sym;

TYPED_TEST_CASE(PolynomialTest, Integers);

TYPED_TEST(PolynomialTest, Constructor) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();

    auto zero = Polynomial(0);
    EXPECT_EQ(zero.monomials.size(), 0);
    EXPECT_TRUE(zero.is_constant());

    // Polynomial with 1 variable
    auto x = Polynomial::new_variable();
    EXPECT_EQ(x.monomials.size(), 1);
    EXPECT_EQ(x.monomials[0].coefficient, 1);
    EXPECT_FALSE(x.is_constant());
    EXPECT_THAT(x.monomials[0].powers, testing::ElementsAre(entry_pair{0, 1}));

    // From constant
    auto two = Polynomial(2);
    EXPECT_EQ(two.monomials.size(), 1);
    EXPECT_EQ(two.monomials[0].coefficient, 2);
    EXPECT_TRUE(two.is_constant());
    EXPECT_EQ(two.monomials[0].powers.size(), 0);

    // From monomial
    x = Polynomial(x.monomials[0]);
    EXPECT_EQ(x.monomials.size(), 1);
    EXPECT_EQ(x.monomials[0].coefficient, 1);
    EXPECT_FALSE(x.is_constant());
    EXPECT_THAT(x.monomials[0].powers, testing::ElementsAre(entry_pair{0, 1}));

    x.monomials[0].coefficient = 2;
    // From another
    auto two_x = Polynomial(x);
    EXPECT_EQ(two_x.monomials.size(), 1);
    EXPECT_EQ(two_x.monomials[0].coefficient, 2);
    EXPECT_FALSE(two_x.is_constant());
    EXPECT_THAT(two_x.monomials[0].powers, testing::ElementsAre(entry_pair{0, 1}));
}

TYPED_TEST(PolynomialTest, Equality) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();

    // Equality with integers
    auto two = Polynomial(2);
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_NE(two, 1);
    EXPECT_NE(1, two);

    // Not equality between 'x' and a constant
    auto two_2 = Polynomial(2);
    auto x = Polynomial::new_variable();
    EXPECT_EQ(two, two_2);
    EXPECT_EQ(two_2, two);
    EXPECT_NE(two, x);
    EXPECT_NE(x, two);
    EXPECT_NE(two_2, x);
    EXPECT_NE(x, two_2);

    // Equality with 'x' as monomial
    auto x_monomial = Monomial::specific_variable(0);
    EXPECT_EQ(x, x_monomial);
    EXPECT_EQ(x_monomial, x);

    // Non equality with 'y' as monomial
    auto y_monomial = Monomial::specific_variable(1);
    EXPECT_NE(x, y_monomial);
    EXPECT_NE(y_monomial, x);

    // Equality and non equality between polynomials
    auto x_again = Polynomial::specific_variable(0);
    auto y = Polynomial::specific_variable(1);
    EXPECT_EQ(x, x_again);
    EXPECT_EQ(x_again, x);
    EXPECT_NE(x, y);
    EXPECT_NE(y, x);
    EXPECT_EQ(y, y_monomial);
    EXPECT_EQ(y_monomial, y);
}

TYPED_TEST(PolynomialTest, AdditionOperators) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();

    // Compare x + y + 2
    auto x_monomial = Monomial();
    auto x = Polynomial::specific_variable(0);
    auto y = Polynomial::specific_variable(1);
    auto xpyp1_1 = x + y + 1;
    auto xpyp1_2 = x_monomial + y + 1;
    EXPECT_FALSE(xpyp1_1.is_constant());
    EXPECT_FALSE(xpyp1_2.is_constant());
    EXPECT_EQ(xpyp1_1, xpyp1_2);
    EXPECT_EQ(xpyp1_1.monomials.size(), 3);
    EXPECT_EQ(xpyp1_2.monomials.size(), 3);
    for(auto i=0;i<3;++i) {
        EXPECT_EQ(xpyp1_1.monomials[i], xpyp1_2.monomials[i]);
    }

    auto two_xpyp1 = xpyp1_1 + xpyp1_2;
    EXPECT_EQ(two_xpyp1.monomials.size(),3);
    EXPECT_FALSE(two_xpyp1.is_constant());
    for(auto i=0;i<3;++i) {
        EXPECT_EQ(two_xpyp1.monomials[i].coefficient, 2);
        EXPECT_TRUE(up_to_coefficient(two_xpyp1.monomials[i], xpyp1_1.monomials[i]));
    }

    // Check subtraction
    auto two = two_xpyp1 - 2 * Polynomial::specific_variable(0) - 2 * Polynomial::specific_variable(1);
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_TRUE(two.is_constant());
}

TYPED_TEST(PolynomialTest, MultuplyOperators) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();
    
    auto x = Polynomial::new_variable();
    auto y = Polynomial::new_variable();
    auto xy_plus_x_square_plus_one = x * y + x * x + 1;
    auto xy_plus_y_square_plus_two = x * y + y * y + 2;
    
    // x^3y  + 2x^2y^2 + 2x^2 + xy^3 + 3xy + y^2 + 2
    auto product = xy_plus_x_square_plus_one * xy_plus_y_square_plus_two;
    EXPECT_EQ(product.monomials.size(), 7);
    EXPECT_EQ(product.monomials[0].coefficient, 1);
    EXPECT_THAT(product.monomials[0].powers, testing::ElementsAre(entry_pair{0, 3},
                                                                  entry_pair{1, 1}));
    EXPECT_EQ(product.monomials[1].coefficient, 2);
    EXPECT_THAT(product.monomials[1].powers, testing::ElementsAre(entry_pair{0, 2},
                                                                  entry_pair{1, 2}));
    EXPECT_EQ(product.monomials[2].coefficient, 2);
    EXPECT_THAT(product.monomials[2].powers, testing::ElementsAre(entry_pair{0, 2}));
    EXPECT_EQ(product.monomials[3].coefficient, 1);
    EXPECT_THAT(product.monomials[3].powers, testing::ElementsAre(entry_pair{0, 1},
                                                                  entry_pair{1, 3}));
    EXPECT_EQ(product.monomials[4].coefficient, 3);
    EXPECT_THAT(product.monomials[4].powers, testing::ElementsAre(entry_pair{0, 1},
                                                                  entry_pair{1, 1}));
    EXPECT_EQ(product.monomials[5].coefficient, 1);
    EXPECT_THAT(product.monomials[5].powers, testing::ElementsAre(entry_pair{1, 2}));

    EXPECT_EQ(product.monomials[6].coefficient, 2);
    EXPECT_EQ(product.monomials[6].powers.size(), 0);

    // Check division
    EXPECT_EQ(product / xy_plus_x_square_plus_one, xy_plus_y_square_plus_two);
    EXPECT_EQ(product / xy_plus_y_square_plus_two, xy_plus_x_square_plus_one);

    // Test for exception
    EXPECT_THROW(product / x * x, md::sym::NonIntegerDivision);
}

TYPED_TEST(PolynomialTest, FloorCeil) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();

    auto three = Polynomial(3);
    auto five = Polynomial(5);
    auto x = Polynomial::new_variable();
    auto y = Polynomial::new_variable();
    auto xy_plus_x_square_plus_one = x * y + x * x + 1;
    auto xy_plus_y_square_plus_two = x * y + y * y + 2;

    // x^3y  + 2x^2y^2 + 2x^2 + xy^3 + 3xy + y^2 + 2
    auto product = 2 * xy_plus_x_square_plus_one * xy_plus_y_square_plus_two;

    // Constant expressions
    EXPECT_EQ(ceil(five, 2), 3);
    EXPECT_EQ(floor(3, five), 0);
    EXPECT_EQ(ceil(2, five), 1);
    EXPECT_EQ(floor(0, five), 0);
    EXPECT_EQ(ceil(0, five), 0);

    // Exact floor divisions
    EXPECT_EQ(floor(product, xy_plus_x_square_plus_one), 2 * xy_plus_y_square_plus_two);
    EXPECT_EQ(floor(product, xy_plus_y_square_plus_two), 2 * xy_plus_x_square_plus_one);
    EXPECT_EQ(floor(product * x, x), product);
    EXPECT_EQ(floor(product * y, y), product);
    EXPECT_EQ(floor(product, 2), xy_plus_x_square_plus_one * xy_plus_y_square_plus_two);
    // Exact ceil divisions
    EXPECT_EQ(ceil(product, xy_plus_x_square_plus_one), 2 * xy_plus_y_square_plus_two);
    EXPECT_EQ(ceil(product, xy_plus_y_square_plus_two), 2 * xy_plus_x_square_plus_one);
    EXPECT_EQ(ceil(product * x, x), product);
    EXPECT_EQ(ceil(product * y, y), product);
    EXPECT_EQ(ceil(product, 2), xy_plus_x_square_plus_one * xy_plus_y_square_plus_two);

    // Partial floor divisions
    auto floor_3 = floor(product, three);
    auto floor_x = floor(product, x);
    auto floor_y = floor(product, y);
    EXPECT_EQ(floor_3.monomials.size(), 1);
    EXPECT_EQ(floor_3.monomials[0].coefficient, 1);
    EXPECT_EQ(floor_3.monomials[0].powers.size(), 1);
    EXPECT_EQ(floor_3.monomials[0].powers[0].second, 1);
    EXPECT_EQ(floor_x.monomials.size(), 1);
    EXPECT_EQ(floor_x.monomials[0].coefficient, 1);
    EXPECT_EQ(floor_x.monomials[0].powers.size(), 1);
    EXPECT_EQ(floor_x.monomials[0].powers[0].second, 1);
    EXPECT_EQ(floor_y.monomials.size(), 1);
    EXPECT_EQ(floor_y.monomials[0].coefficient, 1);
    EXPECT_EQ(floor_y.monomials[0].powers.size(), 1);
    EXPECT_EQ(floor_y.monomials[0].powers[0].second, 1);
    EXPECT_EQ(Polynomial::floor_registry.size(), 3);

    // Partial ceil divisions
    auto ceil_3 = ceil(product, three);
    auto ceil_x = ceil(product, x);
    auto ceil_y = ceil(product, y);
    EXPECT_EQ(ceil_3.monomials.size(), 1);
    EXPECT_EQ(ceil_3.monomials[0].coefficient, 1);
    EXPECT_EQ(ceil_3.monomials[0].powers.size(), 1);
    EXPECT_EQ(ceil_3.monomials[0].powers[0].second, 1);
    EXPECT_EQ(ceil_x.monomials.size(), 1);
    EXPECT_EQ(ceil_x.monomials[0].coefficient, 1);
    EXPECT_EQ(ceil_x.monomials[0].powers.size(), 1);
    EXPECT_EQ(ceil_x.monomials[0].powers[0].second, 1);
    EXPECT_EQ(ceil_y.monomials.size(), 1);
    EXPECT_EQ(ceil_y.monomials[0].coefficient, 1);
    EXPECT_EQ(ceil_y.monomials[0].powers.size(), 1);
    EXPECT_EQ(ceil_y.monomials[0].powers[0].second, 1);
    EXPECT_EQ(Polynomial::ceil_registry.size(), 3);
}

TYPED_TEST(PolynomialTest, Eval) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    Polynomial::reset_registry();

    // Values
    const typename TypeParam::C x_val = 3;
    const typename TypeParam::C y_val = 5;
    const typename TypeParam::C z_val = 7;
    const std::vector<typename TypeParam::C> values{x_val, y_val, z_val};

    auto two = Polynomial(2);
    auto x = Polynomial::new_variable();
    auto y = Polynomial::new_variable();
    auto xy_plus_x_square_plus_one = x * y + x * x + 1;
    auto xy_plus_y_square_plus_two = x * y + y * y + 2;

    // x^3y  + 2x^2y^2 + 2x^2 + xy^3 + 3xy + y^2 + 2
    auto product = xy_plus_x_square_plus_one * xy_plus_y_square_plus_two;

    // Simple
    EXPECT_EQ(two.eval(values), 2);
    EXPECT_EQ(two.eval(), 2);
    EXPECT_EQ(x.eval(values), x_val);
    EXPECT_EQ(y.eval(values), y_val);

    // Complex
    auto v1 = x_val * y_val + x_val * x_val + 1;
    auto v2 = x_val * y_val + y_val * y_val + 2;
    EXPECT_EQ(xy_plus_x_square_plus_one.eval(values), v1);
    EXPECT_EQ(xy_plus_y_square_plus_two.eval(values), v2);
    EXPECT_EQ(product.eval(values), v1 * v2);

    // Floor and ceil
    EXPECT_EQ(floor(product, 3).eval(values), floor(product.eval(values), 3));
    EXPECT_EQ(floor(product, x).eval(values), floor(product.eval(values), x.eval(values)));
    EXPECT_EQ(floor(product, y).eval(values), floor(product.eval(values), y.eval(values)));
    EXPECT_EQ(ceil(product, 3).eval(values), ceil(product.eval(values), 3));
    EXPECT_EQ(ceil(product, x).eval(values), ceil(product.eval(values), x.eval(values)));
    EXPECT_EQ(ceil(product, y).eval(values), ceil(product.eval(values), y.eval(values)));
}

