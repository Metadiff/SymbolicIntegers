//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRNT_MONOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SRNT_MONOMIAL_OPS_H

namespace md {
    namespace sym {
        bool operator==(Monomial const &lhs, Monomial const &rhs);

        bool operator!=(Monomial const &lhs, Monomial const &rhs);

        bool operator==(Monomial const &lhs, C const rhs);

        bool operator!=(Monomial const &lhs, C const rhs);

        bool operator==(C const lhs, Monomial const &rhs);

        bool operator!=(C const lhs, Monomial const &rhs);

        bool up_to_coefficient(Monomial const &lhs, Monomial const &rhs);

        bool up_to_coefficient(C const lhs, Monomial const &rhs);

        bool up_to_coefficient(Monomial const &lhs, C const rhs);

        /**
         * A monomial m1 is compared to monomial m2 in the following order of precedence:
         * 1. Check if the lowest variable id in m1 and m2 are equal.
         *    - If they are not than whoever has the lowest is "before" the other.
         * 2.If they are equal compare the power of this variable.
         *    - Whoever has the higher is "before" the other.
         * 3. If the they are equal continue with next lowest variable by id.
         * 4. If all are equal compare coefficients.
         *
         * For instance a^2b^1 is "before" 100ab^300, since a^2 <-> a.
         */
        bool less_than_comparator(Monomial const &lhs, Monomial const &rhs);

        Monomial  operator+(Monomial const &rhs);

        Monomial  operator-(Monomial const &rhs);

        Monomial  operator*(Monomial const &lhs, Monomial const &rhs);

        Monomial  operator*(Monomial const &lhs, C const rhs);

        Monomial  operator*(C const lhs, Monomial const &rhs);

        Monomial  operator/(Monomial const &lhs, Monomial const &rhs);

        Monomial  operator/(Monomial const &lhs, C const rhs);

        Monomial  operator/(C const lhs, Monomial const &rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRNT_MONOMIAL_OPS_H
