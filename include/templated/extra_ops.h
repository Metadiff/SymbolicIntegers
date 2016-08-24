//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_EXTRA_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_EXTRA_OPS_H

namespace md {
    namespace sym {
        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Monomial <C, I, P> floor(const Monomial <C, I, P> &dividend, const Monomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial<C, I, P>(dividend.eval() / divisor.eval());
            } else {
                try {
                    auto result = dividend / divisor;
                    return result;
                } catch (...) {
                    Polynomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                    return Monomial<C, I, P>();
                }
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T>
        Monomial <C, I, P> floor(const Monomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                return Monomial<C, I, P>(dividend.eval() / divisor);
            } else if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            } else {
                Polynomial<C, I, P>::floor_registry.push_back(
                        {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
                return Monomial<C, I, P>();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T>
        Monomial <C, I, P> floor(const T dividend, const Monomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                return Monomial<C, I, P>(dividend / divisor.eval());
            } else {
                Polynomial<C, I, P>::floor_registry.push_back(
                        {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
                return Monomial<C, I, P>();
            }
        };


        /**
             * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
             * @param dividend
             * @param divisor
             * @return
             */
        template<typename C, typename I, typename P>
        Monomial <C, I, P> ceil(const Monomial <C, I, P> &dividend, const Monomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                C dividend_value = dividend.eval();
                C divisor_value = divisor.eval();
                C value = 0;
                if (dividend_value > divisor_value) {
                    if (dividend_value % divisor_value == 0) {
                        value = dividend_value / divisor_value;
                    } else {
                        value = dividend_value / divisor_value + 1;
                    }
                }
                return Monomial<C, I, P>(value);
            } else {
                try {
                    auto result = dividend / divisor;
                    return result;
                } catch (...) {
                    Polynomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                    return Monomial<C, I, P>();
                }
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T>
        Monomial <C, I, P> ceil(const Monomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                C dividend_value = dividend.eval();
                C value = 0;
                if (dividend_value > divisor) {
                    if (dividend_value % divisor == 0) {
                        value = dividend_value / divisor;
                    } else {
                        value = dividend_value / divisor + 1;
                    }
                }
                return Monomial<C, I, P>(value);
            } else if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            } else {
                Polynomial<C, I, P>::ceil_registry.push_back(
                        {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
                return Monomial<C, I, P>();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T>
        Monomial <C, I, P> ceil(const T dividend, const Monomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                C divisor_value = divisor.eval();
                C value = 0;
                if (dividend > divisor_value) {
                    if (dividend % divisor_value == 0) {
                        value = dividend / divisor_value;
                    } else {
                        value = dividend / divisor_value + 1;
                    }
                }
                return Monomial<C, I, P>(value);
            } else {
                Polynomial<C, I, P>::ceil_registry.push_back(
                        {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
                return Monomial<C, I, P>();
            }
        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_EXTRA_OPS_H
