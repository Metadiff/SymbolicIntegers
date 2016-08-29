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
                return Monomial::new_variable();
            }
        };

        Monomial  floor(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(floor(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Monomial::new_variable();
        };

        Monomial  floor(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(floor(dividend, divisor.eval()));
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Monomial::new_variable();
        };

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

        Polynomial  floor(const C dividend, const Polynomial  &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(floor(dividend, divisor.eval()));
            }
            Polynomial::floor_registry.push_back(
                    {Monomial::total_ids, {dividend, Polynomial(divisor)}});
            return Polynomial::new_variable();
        };

        Monomial  ceil(const Monomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (...) {
                Polynomial::ceil_registry.push_back({Monomial::total_ids, {dividend, divisor}});
                return Monomial::new_variable();
            }
        };

        Monomial  ceil(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {dividend, Monomial(divisor)}});
            return Monomial::new_variable();
        };

        Monomial  ceil(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(ceil(dividend, divisor.eval()));
            }
            Polynomial::ceil_registry.push_back(
                    {Monomial::total_ids, {dividend, Monomial(divisor)}});
            return Monomial::new_variable();
        };

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
