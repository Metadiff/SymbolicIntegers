//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_H

namespace md {
    namespace sym {
        /**
         * Makes a floor division, e.g. returns the result of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto floor(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor);

        /**
         * Makes a ceil division, e.g. returns the result of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto ceil(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor);

        /**
         * Takes the minmum of the two values
         * @param left
         * @param right
         * @return
         */
        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto min(C1 const left, C2 const right) -> decltype(left + right);

        /**
         * Takes the maximum of the two values
         * @param left
         * @param right
         * @return
         */
        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto max(C1 const left, C2 const right) -> decltype(left + right);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P>
        Monomial<I, C, P> floor(Monomial<I, C, P> const  &dividend, Monomial<I, C, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> floor(Monomial<I, C, P> const  &dividend, T const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> floor(T const dividend, Monomial<I, C, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const  &dividend, Polynomial<I, C, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const  &dividend, Monomial<I, C, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Monomial<I, C, P> const  &dividend, Polynomial<I, C, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const  &dividend, T const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> floor(T const dividend, Polynomial<I, C, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template <typename I, typename C, typename P>
        Monomial<I, C, P> ceil(Monomial<I, C, P> const  &dividend, Monomial<I, C, P> const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> ceil(Monomial<I, C, P> const  &dividend, T const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> ceil(T const dividend, Monomial<I, C, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> ceil(Polynomial<I, C, P> const  &dividend, Polynomial<I, C, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P>  ceil(Polynomial<I, C, P> const  &dividend, Monomial<I, C, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> ceil(Monomial<I, C, P> const  &dividend, Polynomial<I, C, P> const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> ceil(Polynomial<I, C, P> const  &dividend, T const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> ceil(T const dividend, Polynomial<I, C, P> const  &divisor);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Monomial<I, C, P> min(Monomial<I, C, P> const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> min(Monomial<I, C, P> const  &left, T const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> min(T const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Monomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, T const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> min(T const  &left, Polynomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Monomial<I, C, P> max(Monomial<I, C, P> const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> max(Monomial<I, C, P> const  &left, T const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> max(T const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, Monomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Monomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, T const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> max(T const  &left, Polynomial<I, C, P> const  &right);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_H
