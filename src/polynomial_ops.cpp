//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {
        
        bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            if (lhs.monomials.size() != rhs.monomials.size()) {
                return false;
            }
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                if (lhs.monomials[i] != rhs.monomials[i]) {
                    return false;
                }
            }
            return true;
        }

        
        bool operator!=(const Polynomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return not(lhs == rhs);
        }

        
        bool operator==(const Polynomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        
        bool operator!=(const Polynomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return not(lhs == rhs);
        }

        
        bool operator==(const Monomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        
        bool operator!=(const Monomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return not(lhs == rhs);
        }

        
        bool operator==(const Polynomial &lhs, const C rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        
        bool operator!=(const Polynomial &lhs, const C rhs) {
            return not(lhs == rhs);
        }

        
        bool operator==(const C lhs, const Polynomial &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        
        bool operator!=(const C lhs, const Polynomial &rhs) {
            return not(lhs == rhs);
        }

        
        Polynomial operator+(const Polynomial &rhs) {
            return rhs;
        }

        
        Polynomial operator-(const Polynomial &rhs) {
            Polynomial result = Polynomial(rhs);
            for (auto i = 0; i < rhs.monomials.size(); ++i) {
                result.monomials[i].coefficient = -result.monomials[i].coefficient;
            }
            return result;
        }

        
        Polynomial operator+(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            if (up_to_coefficient(lhs, rhs)) {
                if (lhs.coefficient != -rhs.coefficient) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs.coefficient;
                }
            } else if (less_than_comparator(lhs, rhs)) {
                result.monomials.push_back(lhs);
                result.monomials.push_back(rhs);
            } else {
                result.monomials.push_back(rhs);
                result.monomials.push_back(lhs);
            }
            return result;
        }

        
        Polynomial operator+(const Monomial &lhs, const C rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            if (lhs.is_constant()) {
                if (lhs.coefficient != -rhs) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs;
                }
            } else {
                result.monomials.push_back(lhs);
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                result.monomials.push_back(Monomial(rhs, lhs.registry));
#else
                result.monomials.push_back(Monomial(rhs));
#endif
            }
            return result;
        }

        
        Polynomial operator+(const C lhs, const Monomial &rhs) {
            return rhs + lhs;
        }

        
        Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < lhs.monomials.size() and i2 < rhs.monomials.size()) {
                if (up_to_coefficient(lhs.monomials[i1], rhs.monomials[i2])) {
                    if (lhs.monomials[i1].coefficient != -rhs.monomials[i2].coefficient) {
                        result.monomials.push_back(lhs.monomials[i1]);
                        result.monomials.back().coefficient += rhs.monomials[i2].coefficient;
                    }
                    ++i1;
                    ++i2;
                } else if (less_than_comparator(lhs.monomials[i1], rhs.monomials[i2])) {
                    result.monomials.push_back(lhs.monomials[i1]);
                    ++i1;
                } else {
                    result.monomials.push_back(rhs.monomials[i2]);
                    ++i2;
                }
            }
            while (i1 < lhs.monomials.size()) {
                result.monomials.push_back(lhs.monomials[i1]);
                ++i1;
            }
            while (i2 < rhs.monomials.size()) {
                result.monomials.push_back(rhs.monomials[i2]);
                ++i2;
            }
            return result;
        }

        
        Polynomial operator+(const Polynomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return lhs + Polynomial(rhs);
        }

        
        Polynomial operator+(const Monomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return rhs + lhs;
        }

        
        Polynomial operator+(const Polynomial &lhs, const C rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            return lhs + Polynomial(rhs, lhs.registry);
#else
            return lhs + Polynomial(rhs);
#endif
        }

        
        Polynomial operator+(const C lhs, const Polynomial &rhs) {
            return rhs + lhs;
        }

        
        Polynomial operator-(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const Monomial &lhs, const C rhs) {
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const C lhs, const Monomial rhs) {
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const Polynomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const Monomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const Polynomial &lhs, const C rhs) {
            return lhs + (-rhs);
        }

        
        Polynomial operator-(const C lhs, const Polynomial &rhs) {
            return lhs + (-rhs);
        }

        
        Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
            auto partial = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
            auto partial = Polynomial(0);
#endif
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                partial.monomials.clear();
                for (auto j = 0; j < rhs.monomials.size(); ++j) {
                    partial.monomials.push_back(lhs.monomials[i] * rhs.monomials[j]);
                }
                result = result + partial;
            }
            return result;
        }

        
        Polynomial operator*(const Polynomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        
        Polynomial operator*(const Monomial lhs, const Polynomial rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
            return rhs * lhs;
        }

        
        Polynomial operator*(const Polynomial &lhs, const C rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            for (int i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        
        Polynomial operator*(const C lhs, const Polynomial rhs) {
            return rhs * lhs;
        }

        
        Polynomial operator/(const Polynomial &lhs, const Polynomial &rhs) {
            if(rhs.monomials.size() == 0){
                throw DivisionByZero();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif

            auto reminder = Polynomial(lhs);
            Monomial next_monomial;
            while (not reminder.is_constant()) {
                next_monomial = (reminder.monomials[0] / rhs.monomials[0]);
                result = result + next_monomial;
                auto s = rhs * next_monomial;
                reminder = reminder - s;
            }
            if (reminder != 0) {
                throw NonIntegerDivision();
            }
            return result;
        }

        
        Polynomial operator/(const Polynomial &lhs, const Monomial &rhs) {
            if(rhs.coefficient == 0){
                throw DivisionByZero();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            for (auto i = 0; i < lhs.monomials.size(); i++) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        
        Polynomial operator/(const Monomial &lhs, const Polynomial &rhs) {
            if(rhs.monomials.size() == 0){
                throw DivisionByZero();
            }
            if (rhs.monomials.size() != 1) {
                throw NonIntegerDivision();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }

        
        Polynomial operator/(const Polynomial &lhs, const C rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            auto result = Polynomial(0, lhs.registry);
#else
            auto result = Polynomial(0);
#endif
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        
        Polynomial operator/(const C lhs, const Polynomial rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            if (rhs.monomials.size() != 1) {
                throw NonIntegerDivision();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            auto result = Polynomial(0, rhs.registry);
#else
            auto result = Polynomial(0);
#endif
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }
    }
}