//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_OPS_H

namespace md {
    namespace sym {
        template<typename C, typename I, typename P>
        bool operator==(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        bool operator!=(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        bool operator==(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        bool operator!=(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        bool operator==(Monomial<C, I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        bool operator!=(Monomial<C, I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator+(Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator-(Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator+(Monomial<C, I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator+(Monomial<C, I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator+(T const lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator+(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator+(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator+(Monomial<C, I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator+(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator+(T const lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator-(Monomial<C, I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator-(Monomial<C, I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator-(T const lhs, Monomial<C, I, P> const rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator-(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator-(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator-(Monomial<C, I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator-(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator-(T const lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator*(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator*(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator*(Monomial<C, I, P> const lhs, Polynomial<C ,I, P> const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator*(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator*(T const lhs, Polynomial<C ,I, P> const rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator/(Polynomial<C ,I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator/(Polynomial<C ,I, P> const &lhs, Monomial<C, I, P> const &rhs);

        template<typename C, typename I, typename P>
        Polynomial<C ,I, P> operator/(Monomial<C, I, P> const &lhs, Polynomial<C ,I, P> const &rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator/(Polynomial<C ,I, P> const &lhs, T const rhs);

        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C ,I, P> operator/(T const lhs, Polynomial<C ,I, P> const rhs);
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_OPS_H
