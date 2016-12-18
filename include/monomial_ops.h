//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator+(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator-(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H
