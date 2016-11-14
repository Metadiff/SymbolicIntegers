//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SNT_POLYNOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SNT_POLYNOMIAL_OPS_H

namespace md {
    namespace sym {
        bool operator==(const Polynomial  &lhs, const Polynomial  &rhs);

        bool operator!=(const Polynomial  &lhs, const Polynomial  &rhs);

        bool operator==(const Polynomial  &lhs, const Monomial  &rhs);

        bool operator!=(const Polynomial  &lhs, const Monomial  &rhs);

        bool operator==(const Monomial  &lhs, const Polynomial  &rhs);

        bool operator!=(const Monomial  &lhs, const Polynomial  &rhs);

        bool operator==(const Polynomial  &lhs, const C rhs);

        bool operator!=(const Polynomial  &lhs, const C rhs);

        bool operator==(const C lhs, const Polynomial  &rhs);

        bool operator!=(const C lhs, const Polynomial  &rhs);

        Polynomial  operator+(const Polynomial  &rhs);

        Polynomial  operator-(const Polynomial  &rhs);

        Polynomial  operator+(const Monomial  &lhs, const Monomial  &rhs);

        Polynomial  operator+(const Monomial  &lhs, const C rhs);

        Polynomial  operator+(const C lhs, const Monomial  &rhs);

        Polynomial  operator+(const Polynomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator+(const Polynomial  &lhs, const Monomial  &rhs);

        Polynomial  operator+(const Monomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator+(const Polynomial  &lhs, const C rhs);

        Polynomial  operator+(const C lhs, const Polynomial  &rhs);

        Polynomial  operator-(const Monomial  &lhs, const Monomial  &rhs);

        Polynomial  operator-(const Monomial  &lhs, const C rhs);

        Polynomial  operator-(const C lhs, const Monomial  rhs);

        Polynomial  operator-(const Polynomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator-(const Polynomial  &lhs, const Monomial  &rhs);

        Polynomial  operator-(const Monomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator-(const Polynomial  &lhs, const C rhs);

        Polynomial  operator-(const C lhs, const Polynomial  &rhs);

        Polynomial  operator*(const Polynomial  &lhs, const Monomial  &rhs);

        Polynomial  operator*(const Polynomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator*(const Monomial  lhs, const Polynomial  rhs);

        Polynomial  operator*(const Polynomial  &lhs, const C rhs);

        Polynomial  operator*(const C lhs, const Polynomial  rhs);

        Polynomial  operator/(const Polynomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator/(const Polynomial  &lhs, const Monomial  &rhs);

        Polynomial  operator/(const Monomial  &lhs, const Polynomial  &rhs);

        Polynomial  operator/(const Polynomial  &lhs, const C rhs);

        Polynomial  operator/(const C lhs, const Polynomial  rhs);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_SNT_POLYNOMIAL_OPS_H
