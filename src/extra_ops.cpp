//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {
        C floor(C const dividend, C const divisor) {
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor > 0)
               or (dividend <= 0 and divisor < 0)
               or (dividend % divisor == 0)){
                return (dividend / divisor);
            }
            return dividend / divisor - 1;
        };

        C ceil(C const dividend, C const divisor){
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor < 0) or (dividend <= 0 and divisor > 0)){
                return dividend / divisor;
            }
            if(dividend % divisor == 0){
                return dividend / divisor;
            }
            return dividend / divisor + 1;
        };

        C min(C const left, C const right) {
            return left < right ? left : right;
        };

        C max(C const left, C const right) {
            return left > right ? left : right;
        };


        Monomial floor(Monomial const &dividend, Monomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                auto dividend_value = dividend.eval();
                auto divisor_value = divisor.eval();
                return Monomial(floor(dividend_value, divisor_value));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->floor_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_monomial_variable();
            }
        };

        Monomial floor(Monomial const &dividend, C const divisor) {
            if (dividend.is_constant()) {
                return Monomial(floor(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            registry()->floor_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_monomial_variable();
        };

        Monomial floor(C const dividend, Monomial const &divisor) {
            if (divisor.is_constant()) {
                return Monomial(floor(dividend, divisor.eval()));
            }
            registry()->floor_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_monomial_variable();
        };

        Polynomial floor(Polynomial const &dividend, Polynomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(dividend.eval() / divisor.eval());
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->floor_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial floor(Polynomial const &dividend, Monomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->floor_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial floor(Monomial const &dividend, Polynomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(floor(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->floor_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial floor(Polynomial const &dividend, C const divisor) {
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
            registry()->floor_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_variable();
        };

        Polynomial floor(C const dividend, Polynomial const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(floor(dividend, divisor.eval()));
            }
            registry()->floor_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_variable();
        };

        Monomial ceil(Monomial const &dividend, Monomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->ceil_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_monomial_variable();
            }
        };

        Monomial ceil(Monomial const &dividend, C const divisor) {
            if (dividend.is_constant()) {
                return Monomial(ceil(dividend.eval(), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            registry()->ceil_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_monomial_variable();
        };

        Monomial ceil(C const dividend, Monomial const &divisor) {
            if (divisor.is_constant()) {
                return Monomial(ceil(dividend, divisor.eval()));
            }
            registry()->ceil_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_monomial_variable();
        };

        Polynomial ceil(Polynomial const &dividend, Polynomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->ceil_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial ceil(Polynomial const &dividend, Monomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->ceil_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial ceil(Monomial const &dividend, Polynomial const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial(ceil(dividend.eval(), divisor.eval()));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                registry()->ceil_registry.push_back({registry()->total_ids, {dividend, divisor}});
                return registry()->new_variable();
            }
        };

        Polynomial ceil(Polynomial const &dividend, C const divisor) {
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
            registry()->ceil_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_variable();
        };

        Polynomial ceil(C const dividend, Polynomial const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial(ceil(dividend, divisor.eval()));
            }
            registry()->ceil_registry.push_back(
                    {registry()->total_ids, {dividend, divisor}});
            return registry()->new_variable();
        };

        Monomial min(Monomial const  &left, Monomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial(min(left.coefficient, right.coefficient));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Monomial min(Monomial const  &left, C const  &right){
            if (left.is_constant()) {
                return Monomial(min(left.coefficient, right));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Monomial min(C const  &left, Monomial const  &right){
            if (right.is_constant()) {
                return Monomial(min(left, right.coefficient));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Polynomial min(Polynomial const  &left, Polynomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(min(left.eval(), right.eval()));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial min(Polynomial const  &left, Monomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(min(left.eval(), right.coefficient));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial min(Monomial const  &left, Polynomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(min(left.coefficient, right.eval()));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial min(Polynomial const  &left, C const  &right){
            if (left.is_constant()) {
                return Polynomial(min(left.eval(), right));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial min(C const  &left, Polynomial const  &right){
            if (right.is_constant()) {
                return Polynomial(min(left, right.eval()));
            } else {
                registry()->min_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Monomial max(Monomial const  &left, Monomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial(max(left.coefficient, right.coefficient));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Monomial max(Monomial const  &left, C const  &right){
            if (left.is_constant()) {
                return Monomial(max(left.coefficient, right));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Monomial max(C const  &left, Monomial const  &right){
            if (right.is_constant()) {
                return Monomial(max(left, right.coefficient));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_monomial_variable();
            }
        }

        Polynomial max(Polynomial const  &left, Polynomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(max(left.eval(), right.eval()));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial max(Polynomial const  &left, Monomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(max(left.eval(), right.coefficient));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial max(Monomial const  &left, Polynomial const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial(max(left.coefficient, right.eval()));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial max(Polynomial const  &left, C const  &right){
            if (left.is_constant()) {
                return Polynomial(max(left.eval(), right));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }

        Polynomial max(C const  &left, Polynomial const  &right){
            if (right.is_constant()) {
                return Polynomial(max(left, right.eval()));
            } else {
                registry()->max_registry.push_back({registry()->total_ids, {left, right}});
                return registry()->new_variable();
            }
        }
    }
}
