//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRNT_EXTRA_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_SRNT_EXTRA_OPS_H

namespace md {
    namespace sym {
        /**
         * Makes a floor division, e.g. returns the result of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        C floor(C const dividend, C const divisor);

        /**
         * Makes a ceil division, e.g. returns the result of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        C ceil(C const dividend, C const divisor);

        /**
         * Takes the minmum of the two values
         * @param left
         * @param right
         * @return
         */
        C min(C const left, C const right);

        /**
         * Takes the maximum of the two values
         * @param left
         * @param right
         * @return
         */
        C max(C const left, C const right);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial floor(Monomial const  &dividend, Monomial const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial floor(Monomial const  &dividend, C const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial floor(C const dividend, Monomial const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(Polynomial const  &dividend, Polynomial const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(Polynomial const  &dividend, Monomial const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(Monomial const  &dividend, Polynomial const  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(Polynomial const  &dividend, C const divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(C const dividend, Polynomial const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Monomial ceil(Monomial const  &dividend, Monomial const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial ceil(Monomial const  &dividend, C const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial ceil(C const dividend, Monomial const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial ceil(Polynomial const  &dividend, Polynomial const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(Polynomial const  &dividend, Monomial const  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial ceil(Monomial const  &dividend, Polynomial const  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial ceil(Polynomial const  &dividend, C const divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial ceil(C const dividend, Polynomial const  &divisor);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial min(Monomial const  &left, Monomial const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial min(Monomial const  &left, C const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial min(C const  &left, Monomial const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial min(Polynomial const  &left, Polynomial const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial min(Polynomial const  &left, Monomial const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial min(Monomial const  &left, Polynomial const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial min(Polynomial const  &left, C const  &right);

        /**
         * Takes the minimum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial min(C const  &left, Polynomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial max(Monomial const  &left, Monomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial max(Monomial const  &left, C const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Monomial max(C const  &left, Monomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial max(Polynomial const  &left, Polynomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial max(Polynomial const  &left, Monomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial max(Monomial const  &left, Polynomial const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial max(Polynomial const  &left, C const  &right);

        /**
         * Takes the maximum of the two variables
         * @param left
         * @param right
         * @return
         */
        Polynomial max(C const  &left, Polynomial const  &right);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRNT_EXTRA_OPS_H
