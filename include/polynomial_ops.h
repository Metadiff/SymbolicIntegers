//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRNT_POLYNOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SRNT_POLYNOMIAL_OPS_H

namespace md {
    namespace sym {
        bool operator==(Polynomial const &lhs, Polynomial const &rhs);

        bool operator!=(Polynomial const &lhs, Polynomial const &rhs);

        bool operator==(Polynomial const &lhs, Monomial const &rhs);

        bool operator!=(Polynomial const &lhs, Monomial const &rhs);

        bool operator==(Monomial const &lhs, Polynomial const &rhs);

        bool operator!=(Monomial const &lhs, Polynomial const &rhs);

        bool operator==(Polynomial const &lhs, C const rhs);

        bool operator!=(Polynomial const &lhs, C const rhs);

        bool operator==(C const lhs, Polynomial const &rhs);

        bool operator!=(C const lhs, Polynomial const &rhs);

        Polynomial  operator+(Polynomial const &rhs);

        Polynomial  operator-(Polynomial const &rhs);

        Polynomial  operator+(Monomial const &lhs, Monomial const &rhs);

        Polynomial  operator+(Monomial const &lhs, C const rhs);

        Polynomial  operator+(C const lhs, Monomial const &rhs);

        Polynomial  operator+(Polynomial const &lhs, Polynomial const &rhs);

        Polynomial  operator+(Polynomial const &lhs, Monomial const &rhs);

        Polynomial  operator+(Monomial const &lhs, Polynomial const &rhs);

        Polynomial  operator+(Polynomial const &lhs, C const rhs);

        Polynomial  operator+(C const lhs, Polynomial const &rhs);

        Polynomial  operator-(Monomial const &lhs, Monomial const &rhs);

        Polynomial  operator-(Monomial const &lhs, C const rhs);

        Polynomial  operator-(C const lhs, Monomial const rhs);

        Polynomial  operator-(Polynomial const &lhs, Polynomial const &rhs);

        Polynomial  operator-(Polynomial const &lhs, Monomial const &rhs);

        Polynomial  operator-(Monomial const &lhs, Polynomial const &rhs);

        Polynomial  operator-(Polynomial const &lhs, C const rhs);

        Polynomial  operator-(C const lhs, Polynomial const &rhs);

        Polynomial  operator*(Polynomial const &lhs, Monomial const &rhs);

        Polynomial  operator*(Polynomial const &lhs, Polynomial const &rhs);

        Polynomial  operator*(Monomial const lhs, Polynomial const rhs);

        Polynomial  operator*(Polynomial const &lhs, C const rhs);

        Polynomial  operator*(C const lhs, Polynomial const rhs);

        Polynomial  operator/(Polynomial const &lhs, Polynomial const &rhs);

        Polynomial  operator/(Polynomial const &lhs, Monomial const &rhs);

        Polynomial  operator/(Monomial const &lhs, Polynomial const &rhs);

        Polynomial  operator/(Polynomial const &lhs, C const rhs);

        Polynomial  operator/(C const lhs, Polynomial const rhs);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_SRNT_POLYNOMIAL_OPS_H
