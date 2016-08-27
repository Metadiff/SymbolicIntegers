//
// Created by alex on 27/08/16.
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
class DeductionTest : public testing::Test {};
typedef TypeDefinitions<short, unsigned short, unsigned short> Short;
typedef TypeDefinitions<int, unsigned int, unsigned int> Int;
typedef TypeDefinitions<long, unsigned long, unsigned long> Long;
typedef TypeDefinitions<long long, unsigned long long, unsigned long long> LongLong;
typedef testing::Types<Short, Int, Long, LongLong> Integers;
using namespace md::sym;

TYPED_TEST_CASE(DeductionTest, Integers);

TYPED_TEST(DeductionTest, VariableDeduction) {
    typedef Monomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Monomial;
    typedef Polynomial<typename TypeParam::C, typename TypeParam::I, typename TypeParam::P> Polynomial;
    typedef std::pair<typename TypeParam::I, typename TypeParam::P> entry_pair;
    typedef std::vector<std::pair<typename TypeParam::I, typename TypeParam::C>> value_vec;
    Polynomial::reset_registry();

    // Base variables
    auto x = Polynomial::new_variable();
    auto y = Polynomial::new_variable();
    auto z = Polynomial::new_variable();

    // Example 1
    auto poly1 = x;
    auto poly2 = x * y * 2;
    auto poly3 = x*x*y*y*z*z*5 + x*x*y + 3;

    auto x_val = 1;
    auto y_val = 3;
    auto z_val = 7;
    auto val1 = x_val;
    auto val2 = x_val * y_val * 2;
    auto val3 = 5 * x_val * x_val * y_val * y_val * z_val * z_val + x_val * x_val * y_val + 3;

    std::vector<std::pair<Polynomial, typename TypeParam::C>> implicit_values {{poly1, val1}, {poly2, val2}, {poly3, val3}};
    auto values = Polynomial::deduce_values(implicit_values);
    EXPECT_EQ(poly1.eval(values), val1);
    EXPECT_EQ(poly2.eval(values), val2);
    EXPECT_EQ(poly3.eval(values), val3);
    EXPECT_EQ((x * x).eval(values), x_val * x_val);
    EXPECT_EQ((y * y).eval(values), y_val * y_val);
    EXPECT_EQ((z * z).eval(values), z_val * z_val);

    // TODO Example 2

    // TODO Example 3
}
