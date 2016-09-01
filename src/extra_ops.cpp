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
                return Monomial(floor(dividend_value, divisor_value), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_monomial_variable();
            }
        };

        Monomial  floor(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(floor(dividend.eval(), divisor), dividend.registry);
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
            return dividend.registry->new_monomial_variable();
        };

        Monomial  floor(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(floor(dividend, divisor.eval()), divisor.registry);
            }
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
            return divisor.registry->new_monomial_variable();
        };

        Polynomial floor(const Polynomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(dividend.eval() / divisor.eval(), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial floor(const Polynomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial floor(const Monomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->floor_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial  floor(const Polynomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor), dividend.registry);
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
            dividend.registry->floor_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
            return dividend.registry->new_variable();
        };

        Polynomial  floor(const C dividend, const Polynomial  &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(floor(dividend, divisor.eval()), divisor.registry);
            }
            divisor.registry->floor_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
            return divisor.registry->new_variable();
        };

        Monomial  ceil(const Monomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_monomial_variable();
            }
        };

        Monomial  ceil(const Monomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor), dividend.registry);
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
            return dividend.registry->new_monomial_variable();
        };

        Monomial  ceil(const C dividend, const Monomial  &divisor) {
            if (divisor.is_constant()) {
                return Monomial(ceil(dividend, divisor.eval()), divisor.registry);
            }
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
            return divisor.registry->new_monomial_variable();
        };

        Polynomial  ceil(const Polynomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial  ceil(const Polynomial  &dividend, const Monomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial  ceil(const Monomial  &dividend, const Polynomial  &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()), dividend.registry);
            }
            try {
                return dividend / divisor;
            } catch (...) {
                dividend.registry->ceil_registry.push_back({dividend.registry->total_ids, {dividend, divisor}});
                return dividend.registry->new_variable();
            }
        };

        Polynomial  ceil(const Polynomial  &dividend, const C divisor) {
            if (dividend.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor), dividend.registry);
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
            dividend.registry->ceil_registry.push_back(
                    {dividend.registry->total_ids, {dividend, Polynomial(divisor, dividend.registry)}});
            return dividend.registry->new_variable();
        };

        Polynomial  ceil(const C dividend, const Polynomial  &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(ceil(dividend, divisor.eval()), divisor.registry);
            }
            divisor.registry->ceil_registry.push_back(
                    {divisor.registry->total_ids, {Polynomial(dividend, divisor.registry), divisor}});
            return divisor.registry->new_variable();
        };
    }
}
