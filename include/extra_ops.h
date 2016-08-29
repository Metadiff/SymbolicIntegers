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
        Monomial  floor(const Monomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                auto dividend_value = dividend.eval();
                auto divisor_value = divisor.eval();
                return Monomial(floor(dividend_value, divisor_value));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::floor_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Monomial();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  floor(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(floor(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Monomial();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  floor(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(floor(dividend, divisor.eval()));
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Monomial();
        };


        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Polynomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(dividend.eval() / divisor.eval());
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::floor_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Polynomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::floor_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial floor(const Monomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::floor_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  floor(const Polynomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Polynomial::new_variable();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  floor(const C dividend, const Polynomial  &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(floor(dividend, divisor.eval()));
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Polynomial::new_variable();
        };


        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Monomial  ceil(const Monomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::ceil_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Monomial();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  ceil(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {dividend, Monomial(divisor)}});
            return Monomial();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Monomial  ceil(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(ceil(dividend, divisor.eval()));
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {dividend, Monomial(divisor)}});
            return Monomial();
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Polynomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::ceil_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Polynomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::ceil_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        Polynomial  ceil(const Monomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::ceil_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Polynomial::new_variable();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  ceil(const Polynomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Polynomial::new_variable();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        Polynomial  ceil(const C dividend, const Polynomial  &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(ceil(dividend, divisor.eval()));
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {Polynomial(dividend), divisor}});
            return Polynomial::new_variable();
        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_EXTRA_OPS_H
