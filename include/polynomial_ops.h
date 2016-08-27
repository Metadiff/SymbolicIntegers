//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_POLYNOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_POLYNOMIAL_OPS_H

namespace md {
    namespace sym {
        template<typename C, typename I, typename P>
        bool operator==(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
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

        template<typename C, typename I, typename P>
        bool operator!=(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return not(lhs == rhs);
        }

        template<typename C, typename I, typename P>
        bool operator==(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        template<typename C, typename I, typename P>
        bool operator!=(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            return not(lhs == rhs);
        }

        template<typename C, typename I, typename P>
        bool operator==(const Monomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        template<typename C, typename I, typename P>
        bool operator!=(const Monomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return not(lhs == rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(const Polynomial <C, I, P> &lhs, const T rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(const Polynomial <C, I, P> &lhs, const T rhs) {
            return not(lhs == rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(const T lhs, const Polynomial <C, I, P> &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(const T lhs, const Polynomial <C, I, P> &rhs) {
            return not(lhs == rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator+(const Polynomial <C, I, P> &rhs) {
            return rhs;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator-(const Polynomial <C, I, P> &rhs) {
            Polynomial<C, I, P> result = Polynomial<C, I, P>(rhs);
            for (auto i = 0; i < rhs.monomials.size(); ++i) {
                result.monomials[i].coefficient = -result.monomials[i].coefficient;
            }
            return result;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator+(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            auto result = Polynomial<C, I, P>(0);
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

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator+(const Monomial <C, I, P> &lhs, const T rhs) {
            auto result = Polynomial<C, I, P>(0);
            if (lhs.is_constant()) {
                if (lhs.coefficient != -rhs) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs;
                }
            } else {
                result.monomials.push_back(lhs);
                result.monomials.push_back(Monomial<C, I, P>(rhs));
            }
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator+(const T lhs, const Monomial <C, I, P> &rhs) {
            return rhs + lhs;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator+(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            auto result = Polynomial<C, I, P>(0);
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

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator+(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            return lhs + Polynomial<C, I, P>(rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator+(const Monomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return rhs + lhs;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator+(const Polynomial <C, I, P> &lhs, const T rhs) {
            return lhs + Polynomial<C, I, P>(rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator+(const T lhs, const Polynomial <C, I, P> &rhs) {
            return rhs + lhs;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator-(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator-(const Monomial <C, I, P> &lhs, const T rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator-(const T lhs, const Monomial <C, I, P> rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator-(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator-(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator-(const Monomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator-(const Polynomial <C, I, P> &lhs, const T rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator-(const T lhs, const Polynomial <C, I, P> &rhs) {
            return lhs + (-rhs);
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator*(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            auto result = Polynomial<C, I, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator*(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            auto result = Polynomial<C, I, P>(0);
            auto partial = Polynomial<C, I, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                partial.monomials.clear();
                for (auto j = 0; j < rhs.monomials.size(); ++j) {
                    partial.monomials.push_back(lhs.monomials[i] * rhs.monomials[j]);
                }
                result = result + partial;
            }
            return result;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator*(const Monomial <C, I, P> lhs, const Polynomial <C, I, P> rhs) {
            return rhs * lhs;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator*(const Polynomial <C, I, P> &lhs, const T rhs) {
            auto result = Polynomial<C, I, P>(0);
            for (int i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator*(const T lhs, const Polynomial <C, I, P> rhs) {
            return rhs * lhs;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator/(const Polynomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            auto result = Polynomial<C, I, P>(0);
            auto reminder = Polynomial<C, I, P>(lhs);
            Monomial<C, I, P> next_monomial;
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

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator/(const Polynomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            auto result = Polynomial<C, I, P>();
            for (auto i = 0; i < lhs.monomials.size(); i++) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        template<typename C, typename I, typename P>
        Polynomial <C, I, P> operator/(const Monomial <C, I, P> &lhs, const Polynomial <C, I, P> &rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            if (rhs.monomials.size() != 1) {
                throw NonIntegerDivision();
            }
            auto result = Polynomial<C, I, P>(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator/(const Polynomial <C, I, P> &lhs, const T rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            if (rhs == 0) {
                throw NonIntegerDivision();
            }
            auto result = Polynomial<C, I, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial <C, I, P> operator/(const T lhs, const Polynomial <C, I, P> rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            if (rhs.monomials.size() != 1) {
                throw NonIntegerDivision();
            }
            auto result = Polynomial<C, I, P>(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_POLYNOMIAL_OPS_H
