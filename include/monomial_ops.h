//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, T const rhs);

        /**
         * A Monomial<I, C, P> m1 is compared to Monomial<I, C, P> m2 in the following order of precedence:
         * 1. Check if the lowest variable id in m1 and m2 are equal.
         *    - If they are not than whoever has the lowest is "before" the other.
         * 2.If they are equal compare the power of this variable.
         *    - Whoever has the higher is "before" the other.
         * 3. If the they are equal continue with next lowest variable by id.
         * 4. If all are equal compare coefficients.
         *
         * For instance a^2b^1 is "before" 100ab^300, since a^2 <-> a.
         */
        template <typename I, typename C, typename P>
        bool less_than_comparator(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator+(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator-(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(T const lhs, Monomial<I, C, P> const &rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_H
