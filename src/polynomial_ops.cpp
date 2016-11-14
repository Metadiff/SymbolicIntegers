//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {
        
        bool operator==(Polynomial const &lhs, Polynomial const &rhs) {
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

        bool operator!=(Polynomial const &lhs, Polynomial const &rhs) {
            return not(lhs == rhs);
        }

        bool operator==(Polynomial const &lhs, Monomial const &rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        bool operator!=(Polynomial const &lhs, Monomial const &rhs) {
            return not(lhs == rhs);
        }

        bool operator==(Monomial const &lhs, Polynomial const &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        bool operator!=(Monomial const &lhs, Polynomial const &rhs) {
            return not(lhs == rhs);
        }

        bool operator==(Polynomial const &lhs, C const rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        bool operator!=(Polynomial const &lhs, C const rhs) {
            return not(lhs == rhs);
        }

        bool operator==(C const lhs, Polynomial const &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        bool operator!=(C const lhs, Polynomial const &rhs) {
            return not(lhs == rhs);
        }

        Polynomial operator+(Polynomial const &rhs) {
            return rhs;
        }

        Polynomial operator-(Polynomial const &rhs) {
            Polynomial result = Polynomial(rhs);
            for (auto i = 0; i < rhs.monomials.size(); ++i) {
                result.monomials[i].coefficient = -result.monomials[i].coefficient;
            }
            return result;
        }

        Polynomial operator+(Monomial const &lhs, Monomial const &rhs) {
            auto result = Polynomial(0);
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

        Polynomial operator+(Monomial const &lhs, C const rhs) {
            auto result = Polynomial(0);
            if (lhs.is_constant()) {
                if (lhs.coefficient != -rhs) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs;
                }
            } else {
                result.monomials.push_back(lhs);
                result.monomials.push_back(Monomial(rhs));
            }
            return result;
        }

        Polynomial operator+(C const lhs, Monomial const &rhs) {
            return rhs + lhs;
        }

        Polynomial operator+(Polynomial const &lhs, Polynomial const &rhs) {
            auto result = Polynomial(0);
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

        Polynomial operator+(Polynomial const &lhs, Monomial const &rhs) {
            return lhs + Polynomial(rhs);
        }

        Polynomial operator+(Monomial const &lhs, Polynomial const &rhs) {
            return rhs + lhs;
        }

        Polynomial operator+(Polynomial const &lhs, C const rhs) {
            return lhs + Polynomial(rhs);
        }

        Polynomial operator+(C const lhs, Polynomial const &rhs) {
            return rhs + lhs;
        }

        Polynomial operator-(Monomial const &lhs, Monomial const &rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(Monomial const &lhs, C const rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(C const lhs, Monomial const rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(Polynomial const &lhs, Polynomial const &rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(Polynomial const &lhs, Monomial const &rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(Monomial const &lhs, Polynomial const &rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(Polynomial const &lhs, C const rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator-(C const lhs, Polynomial const &rhs) {
            return lhs + (-rhs);
        }

        Polynomial operator*(Polynomial const &lhs, Polynomial const &rhs) {
            auto result = Polynomial(0);
            auto partial = Polynomial(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                partial.monomials.clear();
                for (auto j = 0; j < rhs.monomials.size(); ++j) {
                    partial.monomials.push_back(lhs.monomials[i] * rhs.monomials[j]);
                }
                result = result + partial;
            }
            return result;
        }

        Polynomial operator*(Polynomial const &lhs, Monomial const &rhs) {
            auto result = Polynomial(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        Polynomial operator*(Monomial const lhs, Polynomial const rhs) {
            return rhs * lhs;
        }

        Polynomial operator*(Polynomial const &lhs, C const rhs) {
            auto result = Polynomial(0);
            for (int i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        Polynomial operator*(C const lhs, Polynomial const rhs) {
            return rhs * lhs;
        }

        Polynomial operator/(Polynomial const &lhs, Polynomial const &rhs) {
            if(rhs.monomials.size() == 0){
                ZERO_DIVISION()
            }
            auto result = Polynomial(0);
            auto reminder = Polynomial(lhs);
            Monomial next_monomial;
            while (not reminder.is_constant()) {
                next_monomial = (reminder.monomials[0] / rhs.monomials[0]);
                result = result + next_monomial;
                auto s = rhs * next_monomial;
                reminder = reminder - s;
            }
            if (reminder != 0) {
                ZERO_DIVISION()
            }
            return result;
        }

        Polynomial operator/(Polynomial const &lhs, Monomial const &rhs) {
            if(rhs.coefficient == 0){
                ZERO_DIVISION()
            }
            auto result = Polynomial(0);
            for (auto i = 0; i < lhs.monomials.size(); i++) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        Polynomial operator/(Monomial const &lhs, Polynomial const &rhs) {
            if(rhs.monomials.size() == 0){
                ZERO_DIVISION()
            }
            if (rhs.monomials.size() != 1) {
                NON_INTEGER_DIVISION()
            }
            auto result = Polynomial(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }

        Polynomial operator/(Polynomial const &lhs, C const rhs) {
            if(rhs == 0){
                ZERO_DIVISION()
            }
            auto result = Polynomial(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        Polynomial operator/(C const lhs, Polynomial const rhs) {
            if(rhs == 0){
                ZERO_DIVISION()
            }
            if (rhs.monomials.size() != 1) {
                NON_INTEGER_DIVISION()
            }
            auto result = Polynomial(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }
    }
}