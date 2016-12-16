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
class PolynomialTest : public testing::Test {};
typedef TypeDefinitions<std::string, int16_t, uint8_t> Int16;
typedef TypeDefinitions<std::string, int32_t, uint8_t> Int32;
typedef TypeDefinitions<std::string, int64_t, uint8_t> Int64;
typedef testing::Types<Int16, Int32, Int64> Integers;

TYPED_TEST_CASE(PolynomialTest, Integers);

TYPED_TEST(PolynomialTest, Constructor) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto zero = TestPolynomial(0);
    auto two = TestPolynomial(2);

    // Constant comparison
    EXPECT_EQ(zero.monomials.size(), 0);
    EXPECT_TRUE(zero.is_constant());

    // Polynomial with 1 variable
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    EXPECT_EQ(a.monomials.size(), 1);
    EXPECT_EQ(a.monomials[0].coefficient, 1);
    EXPECT_FALSE(a.is_constant());
    EXPECT_THAT(a.monomials[0].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1}));

    // From constant
    EXPECT_EQ(two.monomials.size(), 1);
    EXPECT_EQ(two.monomials[0].coefficient, 2);
    EXPECT_TRUE(two.is_constant());
    EXPECT_EQ(two.monomials[0].powers.size(), 0);

    // From monomial
    a = TestPolynomial(a.monomials[0]);
    EXPECT_EQ(a.monomials.size(), 1);
    EXPECT_EQ(a.monomials[0].coefficient, 1);
    EXPECT_FALSE(a.is_constant());
    EXPECT_THAT(a.monomials[0].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1}));

    a.monomials[0].coefficient = 2;
    // From another
    auto two_x = TestPolynomial(a);
    EXPECT_EQ(two_x.monomials.size(), 1);
    EXPECT_EQ(two_x.monomials[0].coefficient, 2);
    EXPECT_FALSE(two_x.is_constant());
    EXPECT_THAT(two_x.monomials[0].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1}));
}

TYPED_TEST(PolynomialTest, Equality) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto two = TestPolynomial(2);
    auto two_2 = TestPolynomial(2);

    // Equality with integers
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_NE(two, 1);
    EXPECT_NE(1, two);

    // Not equality between 'a' and a constant
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    EXPECT_EQ(two, two_2);
    EXPECT_EQ(two_2, two);
    EXPECT_NE(two, a);
    EXPECT_NE(a, two);
    EXPECT_NE(two_2, a);
    EXPECT_NE(a, two_2);

    // Equality with 'a' as monomial
    auto a_monomial = TestMonomial(TestComposite(Id, "a"));
    EXPECT_EQ(a, a_monomial);
    EXPECT_EQ(a_monomial, a);

    // Non equality with 'b' as monomial
    auto b_monomial = TestMonomial(TestComposite(Id, "b"));
    EXPECT_NE(a, b_monomial);
    EXPECT_NE(b_monomial, a);

    // Equality and non equality between polynomials
    auto a_again = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    EXPECT_EQ(a, a_again);
    EXPECT_EQ(a_again, a);
    EXPECT_NE(a, b);
    EXPECT_NE(b, a);
    EXPECT_EQ(b, b_monomial);
    EXPECT_EQ(b_monomial, b);
}

TYPED_TEST(PolynomialTest, AdditionOperators) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    // Compare a + b + 2
    auto a_monomial = TestMonomial(TestComposite(Id, "a"));
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto a_plus_b_plus_1 = a + b + 1;
    auto a_plus_b_plus_1_v2 = a_monomial + b + 1;
    EXPECT_FALSE(a_plus_b_plus_1.is_constant());
    EXPECT_FALSE(a_plus_b_plus_1_v2.is_constant());
    EXPECT_EQ(a_plus_b_plus_1, a_plus_b_plus_1_v2);
    EXPECT_EQ(a_plus_b_plus_1.monomials.size(), 3);
    EXPECT_EQ(a_plus_b_plus_1_v2.monomials.size(), 3);
    for(auto i=0;i<3;++i) {
        EXPECT_EQ(a_plus_b_plus_1.monomials[i], a_plus_b_plus_1_v2.monomials[i]);
    }

    auto two_a_plus_b_plus_1 = a_plus_b_plus_1 + a_plus_b_plus_1_v2;
    EXPECT_EQ(two_a_plus_b_plus_1.monomials.size(),3);
    EXPECT_FALSE(two_a_plus_b_plus_1.is_constant());
    for(auto i=0;i<3;++i) {
        EXPECT_EQ(two_a_plus_b_plus_1.monomials[i].coefficient, 2);
        EXPECT_TRUE(up_to_coefficient(two_a_plus_b_plus_1.monomials[i], a_plus_b_plus_1.monomials[i]));
    }

    // Check subtraction
    auto two = two_a_plus_b_plus_1 -
            2 * primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a") -
            2 * primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    EXPECT_EQ(two, 2);
    EXPECT_EQ(2, two);
    EXPECT_TRUE(two.is_constant());
}

TYPED_TEST(PolynomialTest, MultuplyOperators) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    // Values
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto ab_plus_a_square_plus_one = a * b + a * a + 1;
    auto ab_plus_b_square_plus_two = a * b + b * b + 2;

    // a^3y + 2a^2b^2 + 2a^2 + ab^3 + 3ab + b^2 + 2
    auto product = ab_plus_a_square_plus_one * ab_plus_b_square_plus_two;
    EXPECT_EQ(product.monomials.size(), 7);
    EXPECT_EQ(product.monomials[0].coefficient, 1);
    EXPECT_THAT(product.monomials[0].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 3},
                                                                  entry_pair{TestComposite(Id, "b"), 1}));
    EXPECT_EQ(product.monomials[1].coefficient, 2);
    EXPECT_THAT(product.monomials[1].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 2},
                                                                  entry_pair{TestComposite(Id, "b"), 2}));
    EXPECT_EQ(product.monomials[2].coefficient, 2);
    EXPECT_THAT(product.monomials[2].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 2}));
    EXPECT_EQ(product.monomials[3].coefficient, 1);
    EXPECT_THAT(product.monomials[3].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1},
                                                                  entry_pair{TestComposite(Id, "b"), 3}));
    EXPECT_EQ(product.monomials[4].coefficient, 3);
    EXPECT_THAT(product.monomials[4].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "a"), 1},
                                                                  entry_pair{TestComposite(Id, "b"), 1}));
    EXPECT_EQ(product.monomials[5].coefficient, 1);
    EXPECT_THAT(product.monomials[5].powers, testing::ElementsAre(entry_pair{TestComposite(Id, "b"), 2}));

    EXPECT_EQ(product.monomials[6].coefficient, 2);
    EXPECT_EQ(product.monomials[6].powers.size(), 0);

    // Check division
    EXPECT_EQ(product / ab_plus_a_square_plus_one, ab_plus_b_square_plus_two);
    EXPECT_EQ(product / ab_plus_b_square_plus_two, ab_plus_a_square_plus_one);

    // Test for exception
    EXPECT_THROW(product / a * a, std::runtime_error);
}

TYPED_TEST(PolynomialTest, FloorCeil) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto three = TestPolynomial(3);
    auto five = TestPolynomial(5);

    // Values
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto ab_plus_a_square_plus_one = a * b + a * a + 1;
    auto ab_plus_b_square_plus_two = a * b + b * b + 2;

    // a^3y  + 2a^2b^2 + 2a^2 + ab^3 + 3ab + b^2 + 2
    auto product = 2 * ab_plus_a_square_plus_one * ab_plus_b_square_plus_two;

    // Constant expressions
    EXPECT_EQ(ceil(five, 2), 3);
    EXPECT_EQ(floor(3, five), 0);
    EXPECT_EQ(ceil(2, five), 1);
    EXPECT_EQ(floor(0, five), 0);
    EXPECT_EQ(ceil(0, five), 0);

    // Exact floor divisions
    EXPECT_EQ(floor(product, ab_plus_a_square_plus_one), 2 * ab_plus_b_square_plus_two);
    EXPECT_EQ(floor(product, ab_plus_b_square_plus_two), 2 * ab_plus_a_square_plus_one);
    EXPECT_EQ(floor(product * a, a), product);
    EXPECT_EQ(floor(product * b, b), product);
    EXPECT_EQ(floor(product, 2), ab_plus_a_square_plus_one * ab_plus_b_square_plus_two);
    // Exact ceil divisions
    EXPECT_EQ(ceil(product, ab_plus_a_square_plus_one), 2 * ab_plus_b_square_plus_two);
    EXPECT_EQ(ceil(product, ab_plus_b_square_plus_two), 2 * ab_plus_a_square_plus_one);
    EXPECT_EQ(ceil(product * a, a), product);
    EXPECT_EQ(ceil(product * b, b), product);
    EXPECT_EQ(ceil(product, 2), ab_plus_a_square_plus_one * ab_plus_b_square_plus_two);

    // Symbolic floor divisions
    auto floor_3 = floor(product, three);
    auto floor_x = floor(product, a);
    auto floor_y = floor(product, b);
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

    // Symbolic ceil divisions
    auto ceil_3 = ceil(product, three);
    auto ceil_x = ceil(product, a);
    auto ceil_y = ceil(product, b);
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
}

TYPED_TEST(PolynomialTest, MinMax) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;

    auto five = TestPolynomial(5);

    // Values
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto ab_plus_a_square_plus_one = a * b + a * a + 1;
    auto ab_plus_b_square_plus_two = a * b + b * b + 2;

    // a^3y  + 2x^2y^2 + 2x^2 + xy^3 + 3xy + b^2 + 2
    auto product = 2 * ab_plus_a_square_plus_one * ab_plus_b_square_plus_two;

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
    auto min_1 = min((product, ab_plus_a_square_plus_one), 2 * ab_plus_b_square_plus_two);
    auto min_2 = min(product * a, a);
    auto min_3 = min(product * b, b);
    EXPECT_EQ(min_1.monomials.size(), 1);
    EXPECT_EQ(min_1.monomials[0].coefficient, 1);
    EXPECT_EQ(min_1.monomials[0].powers.size(), 1);
    EXPECT_EQ(min_1.monomials[0].powers[0].second, 1);
    EXPECT_EQ(min_2.monomials.size(), 1);
    EXPECT_EQ(min_2.monomials[0].coefficient, 1);
    EXPECT_EQ(min_2.monomials[0].powers.size(), 1);
    EXPECT_EQ(min_2.monomials[0].powers[0].second, 1);
    EXPECT_EQ(min_3.monomials.size(), 1);
    EXPECT_EQ(min_3.monomials[0].coefficient, 1);
    EXPECT_EQ(min_3.monomials[0].powers.size(), 1);
    EXPECT_EQ(min_3.monomials[0].powers[0].second, 1);

    // Symbolic max
    auto max_1 = max((product, ab_plus_a_square_plus_one), 2 * ab_plus_b_square_plus_two);
    auto max_2 = max(product * a, a);
    auto max_3 = max(product * b, b);
    EXPECT_EQ(max_1.monomials.size(), 1);
    EXPECT_EQ(max_1.monomials[0].coefficient, 1);
    EXPECT_EQ(max_1.monomials[0].powers.size(), 1);
    EXPECT_EQ(max_1.monomials[0].powers[0].second, 1);
    EXPECT_EQ(max_2.monomials.size(), 1);
    EXPECT_EQ(max_2.monomials[0].coefficient, 1);
    EXPECT_EQ(max_2.monomials[0].powers.size(), 1);
    EXPECT_EQ(max_2.monomials[0].powers[0].second, 1);
    EXPECT_EQ(max_3.monomials.size(), 1);
    EXPECT_EQ(max_3.monomials[0].coefficient, 1);
    EXPECT_EQ(max_3.monomials[0].powers.size(), 1);
    EXPECT_EQ(max_3.monomials[0].powers[0].second, 1);
}

TYPED_TEST(PolynomialTest, Eval) {
    typedef Composite<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestComposite;
    typedef Monomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestMonomial;
    typedef Polynomial<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P> TestPolynomial;
    typedef std::pair<TestComposite, typename TypeParam::P> entry_pair;
    typedef std::unordered_map<typename TypeParam::I, typename TypeParam::C> ValueVec;

    auto two = TestPolynomial(2);

    // Values
    const typename TypeParam::C a_val = 3;
    const typename TypeParam::C b_val = 5;
    const typename TypeParam::C c_val = 7;
    auto a = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("a");
    auto b = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("b");
    auto c = primitive<typename TypeParam::I, typename TypeParam::C, typename TypeParam::P>("c");
    auto ab_plus_a_square_plus_one = a * b + a * a + 1;
    auto ab_plus_b_square_plus_two = a * b + b * b + 2;
    ValueVec values = {{"a", a_val}, {"b", b_val}, {"c", c_val}};

    // a^3y  + 2a^2b^2 + 2a^2 + ab^3 + 3ab + b^2 + 2
    auto product = ab_plus_a_square_plus_one * ab_plus_b_square_plus_two;

    // Simple
    EXPECT_EQ(two.eval(values), 2);
    EXPECT_EQ(two.eval(values), 2);
    EXPECT_EQ(a.eval(values), a_val);
    EXPECT_EQ(b.eval(values), b_val);

    // Complex
    auto v1 = a_val * b_val + a_val * a_val + 1;
    auto v2 = a_val * b_val + b_val * b_val + 2;
    EXPECT_EQ(ab_plus_a_square_plus_one.eval(values), v1);
    EXPECT_EQ(ab_plus_b_square_plus_two.eval(values), v2);
    EXPECT_EQ(product.eval(values), v1 * v2);

    // Floor and ceil
    EXPECT_EQ(floor(product, 3).eval(values), floor(product.eval(values), 3));
    EXPECT_EQ(floor(product, a).eval(values), floor(product.eval(values), a.eval(values)));
    EXPECT_EQ(floor(product, b).eval(values), floor(product.eval(values), b.eval(values)));
    EXPECT_EQ(ceil(product, 3).eval(values), ceil(product.eval(values), 3));
    EXPECT_EQ(ceil(product, a).eval(values), ceil(product.eval(values), a.eval(values)));
    EXPECT_EQ(ceil(product, b).eval(values), ceil(product.eval(values), b.eval(values)));

    // Min and Max
    EXPECT_EQ(min(product, ab_plus_a_square_plus_one).eval(values),
              std::min(product.eval(values), ab_plus_a_square_plus_one.eval(values)));
    EXPECT_EQ(min(product, ab_plus_b_square_plus_two).eval(values),
              std::min(product.eval(values), ab_plus_b_square_plus_two.eval(values)));
    EXPECT_EQ(min(ab_plus_a_square_plus_one, ab_plus_b_square_plus_two).eval(values),
              std::min(ab_plus_a_square_plus_one.eval(values), ab_plus_b_square_plus_two.eval(values)));
    EXPECT_EQ(max(product, ab_plus_a_square_plus_one).eval(values),
              std::max(product.eval(values), ab_plus_a_square_plus_one.eval(values)));
    EXPECT_EQ(max(product, ab_plus_b_square_plus_two).eval(values),
              std::max(product.eval(values), ab_plus_b_square_plus_two.eval(values)));
    EXPECT_EQ(max(ab_plus_a_square_plus_one, ab_plus_b_square_plus_two).eval(values),
              std::max(ab_plus_a_square_plus_one.eval(values), ab_plus_b_square_plus_two.eval(values)));
}


