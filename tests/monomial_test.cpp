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

TYPED_TEST_CASE(MonomialTest, Integers);

TYPED_TEST(MonomialTest, MonomialConstructor) {
    typedef md::sym::Monomial<TypeParam, TypeParam> Monomial;
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

TYPED_TEST(MonomialTest, MonomialEquality) {
    typedef md::sym::Monomial<TypeParam, TypeParam> Monomial;
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
    EXPECT_TRUE(md::sym::up_to_coefficient(0, two));
    EXPECT_TRUE(md::sym::up_to_coefficient(0, two_2));
    EXPECT_FALSE(md::sym::up_to_coefficient(0, x));

    // Up to coefficient equality for 'x' and '10x'
    auto ten_x = Monomial(10);
    ten_x.powers.push_back(x.powers[0]);
    EXPECT_TRUE(md::sym::up_to_coefficient(x, ten_x));
    EXPECT_TRUE(md::sym::up_to_coefficient(ten_x, x));
}


TYPED_TEST(MonomialTest, MonomialOperators) {
    typedef md::sym::Monomial<TypeParam, TypeParam> Monomial;

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

TYPED_TEST(MonomialTest, MonomialFloor) {
    typedef md::sym::Monomial<TypeParam, TypeParam> Monomial;

    auto x = Monomial();
    auto y = Monomial();
    auto five = Monomial(5);
    auto three = Monomial(3);
    auto two = Monomial(2);
    auto composite = five * x * x * y;

    // Constant expressions
    EXPECT_EQ(md::sym::floor(five, two), two);
    EXPECT_EQ(md::sym::ceil(five, two), three);

    // Exact divisions
    EXPECT_EQ(md::sym::floor(composite, x * x), five * y);
    EXPECT_EQ(md::sym::ceil(composite, y), five * x * x);
    EXPECT_EQ(md::sym::ceil(composite, 5), x * x * y);

    // Partial divisions
    auto floor_3 = md::sym::floor(composite, three);
    auto floor_x3 = md::sym::floor(composite, x * x * x);
    auto floor_y2 = md::sym::floor(composite, y * y);
    EXPECT_EQ(floor_3.coefficient, 1);
    EXPECT_EQ(floor_3.powers.size(), 1);
    EXPECT_EQ(floor_3.powers[0].second, 1);
    EXPECT_EQ(floor_x3.coefficient, 1);
    EXPECT_EQ(floor_x3.powers.size(), 1);
    EXPECT_EQ(floor_x3.powers[0].second, 1);
    EXPECT_EQ(floor_y2.coefficient, 1);
    EXPECT_EQ(floor_y2.powers.size(), 1);
    EXPECT_EQ(floor_y2.powers[0].second, 1);
}

//
//TYPED_TEST(SymbolicTest, MonomialProductAndDivision) {
//    typedef md::symbolic::SymbolicMonomial<TypeParam, TypeParam> Monomial;
//    auto x = Monomial::variable(0);
//    auto y = Monomial::variable(1);
//    auto z = Monomial::variable(2);
//    auto composite = 2 * y * z * x;
//
//    // Verify inner structure (such as ordering)
//    EXPECT_EQ(composite.coefficient, 2);
//    EXPECT_FALSE(composite.is_constant());
//    EXPECT_THAT(composite.powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 1},
//                                                       std::pair<TypeParam, TypeParam>{1, 1},
//                                                       std::pair<TypeParam, TypeParam>{2, 1}));
//
//    // Check equality between different forms
//    EXPECT_EQ(composite / 2, x * y * z);
//    EXPECT_EQ(composite / x, 2 * y * z);
//    EXPECT_EQ(composite / y, 2 * x * z);
//    EXPECT_EQ(composite / z, 2 * x * y);
//
//    // Check for errors on non integer division
//    EXPECT_THROW(composite / 4, md::symbolic::NonIntegerDivision);
//    EXPECT_THROW(composite / (x * x), md::symbolic::NonIntegerDivision);
//    EXPECT_THROW(composite / (y * y), md::symbolic::NonIntegerDivision);
//    EXPECT_THROW(composite / (z * z), md::symbolic::NonIntegerDivision);
//}
//
//TYPED_TEST(SymbolicTest, PolynomialConstructor) {
//    typedef md::symbolic::SymbolicMonomial<TypeParam, TypeParam> Monomial;
//    typedef md::symbolic::SymbolicPolynomial<TypeParam, TypeParam> Polynomial;
//    // Constant polynomial 0
//    auto zero = Polynomial();
//    EXPECT_EQ(zero.monomials.size(), 0);
//    EXPECT_TRUE(zero.is_constant());
//
//    // Polynomial with 1 variable
//    auto x = Polynomial::variable(0);
//    EXPECT_EQ(x.monomials.size(), 1);
//    EXPECT_EQ(x.monomials[0].coefficient, 1);
//    EXPECT_FALSE(x.is_constant());
//    EXPECT_THAT(x.monomials[0].powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 1}));
//
//    // From constant
//    auto two = Polynomial(2);
//    EXPECT_EQ(two.monomials.size(), 1);
//    EXPECT_EQ(two.monomials[0].coefficient, 2);
//    EXPECT_TRUE(two.is_constant());
//    EXPECT_EQ(two.monomials[0].powers.size(), 0);
//
//    // From monomial
//    auto x_monomial = Monomial::variable(0);
//    x = Polynomial(x_monomial);
//    EXPECT_EQ(x.monomials.size(), 1);
//    EXPECT_EQ(x.monomials[0].coefficient, 1);
//    EXPECT_FALSE(x.is_constant());
//    EXPECT_THAT(x.monomials[0].powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 1}));
//
//    x.monomials[0].coefficient = 2;
//    // From another
//    auto two_x = Polynomial(x);
//    EXPECT_EQ(two_x.monomials.size(), 1);
//    EXPECT_EQ(two_x.monomials[0].coefficient, 2);
//    EXPECT_FALSE(two_x.is_constant());
//    EXPECT_THAT(two_x.monomials[0].powers, testing::ElementsAre(std::pair<TypeParam, TypeParam>{0, 1}));
//}
//
//
//TYPED_TEST(SymbolicTest, PolynomialEquality) {
//    typedef md::symbolic::SymbolicMonomial<TypeParam, TypeParam> Monomial;
//    typedef md::symbolic::SymbolicPolynomial<TypeParam, TypeParam> Polynomial;
//    // Equality with integers
//    auto two = Polynomial(2);
//    EXPECT_EQ(two, 2);
//    EXPECT_EQ(2, two);
//    EXPECT_NE(two, 1);
//    EXPECT_NE(1, two);
//
//    // Not equality between 'x' and a constant
//    auto two_2 = Polynomial(2);
//    auto x = Polynomial::variable(0);
//    EXPECT_EQ(two, two_2);
//    EXPECT_EQ(two_2, two);
//    EXPECT_NE(two, x);
//    EXPECT_NE(x, two);
//    EXPECT_NE(two_2, x);
//    EXPECT_NE(x, two_2);
//
//    // Equality with 'x' as monomial
//    auto x_monomial = Monomial::variable(0);
//    EXPECT_EQ(x, x_monomial);
//    EXPECT_EQ(x_monomial, x);
//
//    // Non equality with 'y' as monomial
//    auto y_monomial = Monomial::variable(1);
//    EXPECT_NE(x, y_monomial);
//    EXPECT_NE(y_monomial, x);
//
//    // Equality and non equality between polynomials
//    auto x_again = Polynomial::variable(0);
//    auto y = Polynomial::variable(1);
//    EXPECT_EQ(x, x_again);
//    EXPECT_EQ(x_again, x);
//    EXPECT_NE(x, y);
//    EXPECT_NE(y, x);
//}
//
//TYPED_TEST(SymbolicTest, PolynomialAddition) {
//    typedef md::symbolic::SymbolicMonomial<TypeParam, TypeParam> Monomial;
//    typedef md::symbolic::SymbolicPolynomial<TypeParam, TypeParam> Polynomial;
//
//    // Compare x + y + 2
//    auto x_monomial = Monomial::variable(0);
//    auto x = Polynomial::variable(0);
//    auto y = Polynomial::variable(1);
//    auto x_plus_y = x + y + 1;
//    auto x_plus_y_2 = x_monomial + y + 1;
//    EXPECT_FALSE(x_plus_y.is_constant());
//    EXPECT_FALSE(x_plus_y_2.is_constant());
//    EXPECT_EQ(x_plus_y, x_plus_y_2);
//    EXPECT_EQ(x_plus_y.monomials.size(), 3);
//    EXPECT_EQ(x_plus_y_2.monomials.size(), 3);
//    for (int i = 0; i < 3; i++) {
//        EXPECT_EQ(x_plus_y.monomials[i], x_plus_y_2.monomials[i]);
//    }
//
//    auto two_x_plus_y = x_plus_y + x_plus_y_2;
//    EXPECT_EQ(two_x_plus_y.monomials.size(), 3);
//    EXPECT_FALSE(two_x_plus_y.is_constant());
//    for (int i = 0; i < 3; i++) {
//        EXPECT_EQ(two_x_plus_y.monomials[i].coefficient, 2);
//        EXPECT_TRUE(md::symbolic::up_to_coefficient(two_x_plus_y.monomials[i], x_plus_y.monomials[i]));
//    }
//
//    // Check subtraction
//    auto two = two_x_plus_y - 2 * Polynomial::variable(0) - 2 * Polynomial::variable(1);
//    EXPECT_EQ(two, 2);
//    EXPECT_EQ(2, two);
//    EXPECT_TRUE(two.is_constant());
//}
//
//TYPED_TEST(SymbolicTest, PolynomialProductAndDivision) {
//    typedef md::symbolic::SymbolicMonomial<TypeParam, TypeParam> Monomial;
//    typedef md::symbolic::SymbolicPolynomial<TypeParam, TypeParam> Polynomial;
//    typedef std::pair<TypeParam, TypeParam> pairIP;
//    auto x = Polynomial::variable(0);
//    auto y = Polynomial::variable(1);
//    auto xy_plus_x_square_plus_one = x * y + x * x + 1;
//    auto xy_plus_y_square_plus_two = x * y + y * y + 2;
//    // x^3y  + 2x^2y^2 + 2x^2 + xy^3 + 3xy + y^2 + 2
//    auto product = xy_plus_x_square_plus_one * xy_plus_y_square_plus_two;
//    EXPECT_EQ(product.monomials.size(), 7);
//    EXPECT_EQ(product.monomials[0].coefficient, 1);
//    EXPECT_THAT(product.monomials[0].powers, testing::ElementsAre(pairIP{0, 3},
//                                                                  pairIP{1, 1}));
//    EXPECT_EQ(product.monomials[1].coefficient, 2);
//    EXPECT_THAT(product.monomials[1].powers, testing::ElementsAre(pairIP{0, 2},
//                                                                  pairIP{1, 2}));
//    EXPECT_EQ(product.monomials[2].coefficient, 2);
//    EXPECT_THAT(product.monomials[2].powers, testing::ElementsAre(pairIP{0, 2}));
//    EXPECT_EQ(product.monomials[3].coefficient, 1);
//    EXPECT_THAT(product.monomials[3].powers, testing::ElementsAre(pairIP{0, 1},
//                                                                  pairIP{1, 3}));
//    EXPECT_EQ(product.monomials[4].coefficient, 3);
//    EXPECT_THAT(product.monomials[4].powers, testing::ElementsAre(pairIP{0, 1},
//                                                                  pairIP{1, 1}));
//    EXPECT_EQ(product.monomials[5].coefficient, 1);
//    EXPECT_THAT(product.monomials[5].powers, testing::ElementsAre(pairIP{1, 2}));
//
//    EXPECT_EQ(product.monomials[6].coefficient, 2);
//    EXPECT_EQ(product.monomials[6].powers.size(), 0);
//
//    // Check division
//    EXPECT_EQ(product / xy_plus_x_square_plus_one, xy_plus_y_square_plus_two);
//    EXPECT_EQ(product / xy_plus_y_square_plus_two, xy_plus_x_square_plus_one);
//
//    // Test for exception
//    EXPECT_THROW(product / x * x, md::symbolic::NonIntegerDivision);
//}
//
int main(int argc, char **argv) {
//    typedef md::sym::Monomial<unsigned long, unsigned int> Monomial;
    // Equality with integers
//    auto two = Monomial(2);
//    std::cout << (two == 2) << std::endl;
//    std::cout << two.eval() << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}