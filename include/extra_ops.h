//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_H

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
        template<typename C, typename I, typename P>
        Monomial<C, I, P> floor(Monomial<C, I, P> const  &dividend, Monomial<C, I, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> floor(Monomial<C, I, P> const  &dividend, T const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> floor(T const dividend, Monomial<C, I, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const  &dividend, Polynomial<C, I, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const  &dividend, Monomial<C, I, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(Monomial<C, I, P> const  &dividend, Polynomial<C, I, P> const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> floor(Polynomial<C, I, P> const  &dividend, T const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> floor(T const dividend, Polynomial<C, I, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Monomial<C, I, P> ceil(Monomial<C, I, P> const  &dividend, Monomial<C, I, P> const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> ceil(Monomial<C, I, P> const  &dividend, T const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> ceil(T const dividend, Monomial<C, I, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> ceil(Polynomial<C, I, P> const  &dividend, Polynomial<C, I, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P>  ceil(Polynomial<C, I, P> const  &dividend, Monomial<C, I, P> const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> ceil(Monomial<C, I, P> const  &dividend, Polynomial<C, I, P> const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> ceil(Polynomial<C, I, P> const  &dividend, T const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> ceil(T const dividend, Polynomial<C, I, P> const  &divisor);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Monomial<C, I, P> min(Monomial<C, I, P> const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> min(Monomial<C, I, P> const  &left, T const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> min(T const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> min(Monomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> min(Polynomial<C, I, P> const  &left, T const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> min(T const  &left, Polynomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Monomial<C, I, P> max(Monomial<C, I, P> const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> max(Monomial<C, I, P> const  &left, T const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<C, I, P> max(T const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, Monomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> max(Monomial<C, I, P> const  &left, Polynomial<C, I, P> const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> max(Polynomial<C, I, P> const  &left, T const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        template<typename C, typename I, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<C, I, P> max(T const  &left, Polynomial<C, I, P> const  &right);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_EXTRA_OPS_H
