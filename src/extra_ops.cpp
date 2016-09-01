//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {
        C floor(C dividend, C divisor) {
            if(divisor == 0){
                throw DivisionByZero();
            }
            if((dividend >= 0 and divisor > 0)
               or (dividend <= 0 and divisor < 0)
               or (dividend % divisor == 0)){
                return (dividend / divisor);
            }
            return dividend / divisor - 1;
        };

        C ceil(C dividend, C divisor){
            if(divisor == 0){
                throw DivisionByZero();
            }
            if((dividend >= 0 and divisor < 0) or (dividend <= 0 and divisor > 0)){
                return dividend / divisor;
            }
            if(dividend % divisor == 0){
                return dividend / divisor;
            }
            return dividend / divisor + 1;
        };


        Monomial floor(const Monomial &dividend, const Monomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
                auto dividend_value = dividend.eval();
                auto divisor_value = divisor.eval();
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(floor(dividend_value, divisor_value), dividend.registry);
#else
                return Monomial(floor(dividend_value, divisor_value));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_monomial_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Monomial floor(const Monomial &dividend, const C divisor) {
            if (dividend.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(floor(dividend.eval(), divisor), dividend.registry);
#else
                return Monomial(floor(dividend.eval(), divisor));
#endif
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
#else
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, divisor}});
#endif
            return dividend.registry->new_monomial_variable();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Monomial floor(const C dividend, const Monomial &divisor) {
            if (divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(floor(dividend, divisor.eval()), divisor.registry);
#else
                return Monomial(floor(dividend, divisor.eval()));
#endif
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
#else
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {dividend, divisor}});
#endif
            return divisor.registry->new_monomial_variable();
        };


        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial floor(const Polynomial &dividend, const Polynomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(dividend.eval() / divisor.eval(), dividend.registry);
#else
                return Polynomial(dividend.eval() / divisor.eval());
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial floor(const Polynomial &dividend, const Monomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(floor(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Polynomial(floor(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial floor(const Monomial &dividend, const Polynomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(floor(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Polynomial(floor(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial floor(const Polynomial &dividend, const C divisor) {
            if (dividend.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(floor(dividend.eval(), divisor), dividend.registry);
#else
                return Polynomial(floor(dividend.eval(), divisor));
#endif
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
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
#else
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, divisor}});
#endif
            return dividend.registry->new_variable();
        };

        /**
         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial floor(const C dividend, const Polynomial &divisor) {
            if (divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(floor(dividend, divisor.eval()), divisor.registry);
#else
                return Polynomial(floor(dividend, divisor.eval()));
#endif
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
#else
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {dividend, divisor}});
#endif
            return divisor.registry->new_variable();
        };


        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */

        Monomial ceil(const Monomial &dividend, const Monomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Monomial(ceil(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_monomial_variable();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Monomial ceil(const Monomial &dividend, const C divisor) {
            if (dividend.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(ceil(dividend.eval(), divisor), dividend.registry);
#else
                return Monomial(ceil(dividend.eval(), divisor));
#endif
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
#else
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, divisor}});
#endif
            return dividend.registry->new_monomial_variable();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Monomial ceil(const C dividend, const Monomial &divisor) {
            if (divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Monomial(ceil(dividend, divisor.eval()), divisor.registry);
#else
                return Monomial(ceil(dividend, divisor.eval()));
#endif
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
#else
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {dividend, divisor}});
#endif
            return divisor.registry->new_monomial_variable();
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */

        Polynomial ceil(const Polynomial &dividend, const Polynomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */

        Polynomial ceil(const Polynomial &dividend, const Monomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
          * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
          * @param dividend
          * @param divisor
          * @return
          */

        Polynomial ceil(const Monomial &dividend, const Polynomial &divisor) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(dividend.registry != divisor.registry){
                throw DifferentRegistries();
            }
#endif
            if (dividend.is_constant() and divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
#else
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
#endif
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial ceil(const Polynomial &dividend, const C divisor) {
            if (dividend.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(ceil(dividend.eval(), divisor), dividend.registry);
#else
                return Polynomial(ceil(dividend.eval(), divisor));
#endif
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
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
#else
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, divisor}});
#endif
            return dividend.registry->new_variable();
        };

        /**
         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
         * @param dividend
         * @param divisor
         * @return
         */

        Polynomial ceil(const C dividend, const Polynomial &divisor) {
            if (divisor.is_constant()) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return Polynomial(ceil(dividend, divisor.eval()), divisor.registry);
#else
                return Polynomial(ceil(dividend, divisor.eval()));
#endif
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
#else
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {dividend, divisor}});
#endif
            return divisor.registry->new_variable();
        };
    }
}
