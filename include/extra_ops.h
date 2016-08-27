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
                auto dividend_value = dividend.eval();
                auto divisor_value = divisor.eval();
                return Monomial<C, I, P>(floor(dividend_value, divisor_value));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Monomial<C, I, P>();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> floor(const Monomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                return Monomial<C, I, P>(floor(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial<C, I, P>::floor_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
            return Monomial<C, I, P>();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> floor(const T dividend, const Monomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                return Monomial<C, I, P>(floor(dividend, divisor.eval()));
            }
            Polynomial<C, I, P>::floor_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
            return Monomial<C, I, P>();
        };


        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(const Polynomial <C, I, P> &dividend, const Polynomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(dividend.eval() / divisor.eval());
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(const Polynomial <C, I, P> &dividend, const Monomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> floor(const Monomial <C, I, P> &dividend, const Polynomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> floor(const Polynomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend.eval(), divisor));
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
            Polynomial<C, I, P>::floor_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
            return Polynomial<C, I, P>::new_variable();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> floor(const T dividend, const Polynomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<C, I, P>(floor(dividend, divisor.eval()));
            }
            Polynomial<C, I, P>::floor_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
            return Polynomial<C, I, P>::new_variable();
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
                return Monomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Monomial<C, I, P>();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> ceil(const Monomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                return Monomial<C, I, P>(ceil(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial<C, I, P>::ceil_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
            return Monomial<C, I, P>();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> ceil(const T dividend, const Monomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                return Monomial<C, I, P>(ceil(dividend, divisor.eval()));
            }
            Polynomial<C, I, P>::ceil_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
            return Monomial<C, I, P>();
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial <C, I, P> ceil(const Polynomial <C, I, P> &dividend, const Polynomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial <C, I, P> ceil(const Polynomial <C, I, P> &dividend, const Monomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */
        template<typename C, typename I, typename P>
        Polynomial <C, I, P> ceil(const Monomial <C, I, P> &dividend, const Polynomial <C, I, P> &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
                return Polynomial<C, I, P>::new_variable();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> ceil(const Polynomial <C, I, P> &dividend, const T divisor) {
            if (dividend.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend.eval(), divisor));
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
            Polynomial<C, I, P>::floor_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
            return Polynomial<C, I, P>::new_variable();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */
        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> ceil(const T dividend, const Polynomial <C, I, P> &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<C, I, P>(ceil(dividend, divisor.eval()));
            }
            Polynomial<C, I, P>::ceil_registry.push_back(
                    {Monomial<C, I, P>::total_ids, {Polynomial<C, I, P>(dividend), divisor}});
            return Polynomial<C, I, P>::new_variable();
        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_EXTRA_OPS_H
