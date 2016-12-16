//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Monomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(T const lhs, Polynomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Monomial<I, C, P> const lhs, Polynomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(T const lhs, Polynomial<I, C, P> const rhs);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_H
