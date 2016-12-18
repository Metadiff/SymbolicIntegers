//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_IMPL_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Polynomial<I, C, P> const &lhs, T const rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Polynomial<I, C, P> const &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            return (lhs.monomials.size() == 0 and rhs == 0) or (lhs.monomials.size() == 1 and lhs.monomials[0] == rhs);
        }

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return (rhs.monomials.size() == 0 and lhs == 0) or (rhs.monomials.size() == 1 and rhs.monomials[0] == lhs);
        }

        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
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

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Polynomial<I, C, P> const &lhs, T const rhs) {
            return not(lhs == rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Polynomial<I, C, P> const &rhs) {
            return not(lhs == rhs);
        }

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            return not(lhs == rhs);
        }

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return not(lhs == rhs);
        }

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return not(lhs == rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &rhs) {
            return rhs;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &rhs) {
            Polynomial<I, C, P> result = Polynomial<I, C, P>(rhs);
            for (auto i = 0; i < rhs.monomials.size(); ++i) {
                result.monomials[i].coefficient = -result.monomials[i].coefficient;
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto result = Polynomial<I, C, P>(0);
            if (up_to_coefficient(lhs, rhs)) {
                if (lhs.coefficient != -rhs.coefficient) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs.coefficient;
                }
            } else if (grevlex_gt(lhs, rhs)) {
                result.monomials.push_back(lhs);
                result.monomials.push_back(rhs);
            } else {
                result.monomials.push_back(rhs);
                result.monomials.push_back(lhs);
            }
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, T const rhs) {
            auto result = Polynomial<I, C, P>(0);
            if (lhs.is_constant()) {
                if (lhs.coefficient != -rhs) {
                    result.monomials.push_back(lhs);
                    result.monomials[0].coefficient += rhs;
                }
            } else {
                result.monomials.push_back(lhs);
                result.monomials.push_back(Monomial<I, C, P>(rhs));
            }
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Monomial<I, C, P> const &rhs) {
            return rhs + lhs;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P>& Polynomial<I, C, P>::operator+=(Polynomial<I, C, P> const &rhs){
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < this->monomials.size() and i2 < rhs.monomials.size()) {
                if (up_to_coefficient(this->monomials[i1], rhs.monomials[i2])) {
                    if (this->monomials[i1].coefficient != -rhs.monomials[i2].coefficient) {
                        this->monomials[i1].coefficient += rhs.monomials[i2].coefficient;
                        ++i1;
                    } else {
                        this->monomials.erase(this->monomials.begin() + i1);
                    }
                    ++i2;
                } else if (grevlex_gt(this->monomials[i1], rhs.monomials[i2])) {
                    ++i1;
                } else {
                    this->monomials.insert(this->monomials.begin() + i1, rhs.monomials[i2]);
                    ++i1;
                    ++i2;
                }
            }
            while (i2 < rhs.monomials.size()) {
                this->monomials.push_back(rhs.monomials[i2]);
                ++i2;
            }
            return *this;
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            Polynomial<I, C, P> result = lhs;
            result += rhs;
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            return lhs + Polynomial<I, C, P>(rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return rhs + lhs;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, T const rhs) {
            return lhs + Polynomial<I, C, P>(rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Polynomial<I, C, P> const &rhs) {
            return rhs + lhs;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, T const rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Monomial<I, C, P> const rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, T const rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Polynomial<I, C, P> const &rhs) {
            return lhs + (-rhs);
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            auto result = Polynomial<I, C, P>(0);
            auto partial = Polynomial<I, C, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                partial.monomials.clear();
                for (auto j = 0; j < rhs.monomials.size(); ++j) {
                    partial.monomials.push_back(lhs.monomials[i] * rhs.monomials[j]);
                }
                result = result + partial;
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto result = Polynomial<I, C, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Monomial<I, C, P> const lhs, Polynomial<I, C, P> const rhs) {
            return rhs * lhs;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(T const lhs, Polynomial<I, C, P> const rhs) {
            return rhs * lhs;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, T const rhs) {
            auto result = Polynomial<I, C, P>(0);
            for (int i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] * rhs);
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            if(rhs.monomials.size() == 0){
                throw exceptions::division_by_zero();
            }
            auto result = Polynomial<I, C, P>(0);
            auto reminder = Polynomial<I, C, P>(lhs);
            Monomial<I, C, P> next_monomial;
            while (not reminder.is_constant()) {
                next_monomial = (reminder.monomials[0] / rhs.monomials[0]);
                result = result + next_monomial;
                auto s = rhs * next_monomial;
                reminder = reminder - s;
            }
            if (reminder != 0) {
                throw exceptions::division_by_zero();
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            if(rhs.coefficient == 0){
                throw exceptions::division_by_zero();
            }
            auto result = Polynomial<I, C, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); i++) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            if(rhs.monomials.size() == 0){
                throw exceptions::division_by_zero();
            }
            if (rhs.monomials.size() != 1) {
                throw exceptions::non_integer_division();
            }
            auto result = Polynomial<I, C, P>(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, T const rhs) {
            if(rhs == 0){
                throw exceptions::division_by_zero();
            }
            auto result = Polynomial<I, C, P>(0);
            for (auto i = 0; i < lhs.monomials.size(); ++i) {
                result.monomials.push_back(lhs.monomials[i] / rhs);
            }
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(T const lhs, Polynomial<I, C, P> const rhs) {
            if(rhs == 0){
                throw exceptions::division_by_zero();
            }
            if (rhs.monomials.size() != 1) {
                throw exceptions::non_integer_division();
            }
            auto result = Polynomial<I, C, P>(0);
            result.monomials.push_back(lhs / rhs.monomials[0]);
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_OPS_IMPL_H