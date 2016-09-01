//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_EXTRA_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_EXTRA_OPS_H

namespace md {
    namespace sym {
        C floor(C dividend, C divisor);

        C ceil(C dividend, C divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  floor(const Monomial  &dividend, const Monomial  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  floor(const Monomial  &dividend, const C divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  floor(const C dividend, const Monomial  &divisor);


        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Polynomial  &dividend, const Polynomial  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Polynomial  &dividend, const Monomial  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Monomial  &dividend, const Polynomial  &divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  floor(const Polynomial  &dividend, const C divisor);

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  floor(const C dividend, const Polynomial  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Monomial  ceil(const Monomial  &dividend, const Monomial  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  ceil(const Monomial  &dividend, const C divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  ceil(const C dividend, const Monomial  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Polynomial  &dividend, const Polynomial  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Polynomial  &dividend, const Monomial  &divisor);

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Monomial  &dividend, const Polynomial  &divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  ceil(const Polynomial  &dividend, const C divisor);

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  ceil(const C dividend, const Polynomial  &divisor);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_EXTRA_OPS_H
