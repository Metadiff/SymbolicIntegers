//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H

namespace md {
    namespace sym {

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Monomial<I, C, P> const &lhs, T const rhs) {
            return lhs.is_constant() and (lhs.coefficient == rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Monomial<I, C, P> const &rhs) {
            return rhs.is_constant() and (rhs.coefficient == lhs);
        }

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            if (lhs.coefficient != rhs.coefficient or lhs.powers.size() != rhs.powers.size()) {
                return false;
            }
            for (auto i = 0; i < lhs.powers.size(); ++i) {
                if (lhs.powers[i] != rhs.powers[i]) {
                    return false;
                }
            }
            return true;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Monomial<I, C, P> const &lhs, T const rhs) {
            return (not lhs.is_constant()) or (lhs.coefficient != rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Monomial<I, C, P> const &rhs) {
            return (not rhs.is_constant()) or (rhs.coefficient != lhs);
        }

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            if (lhs.coefficient != rhs.coefficient or lhs.powers.size() != rhs.powers.size()) {
                return true;
            }
            for (auto i = 0; i < lhs.powers.size(); ++i) {
                if (lhs.powers[i] != rhs.powers[i]) {
                    return true;
                }
            }
            return false;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(T const lhs, Monomial<I, C, P> const &rhs) {
            return rhs.is_constant();
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator+(Monomial<I, C, P> const &rhs) {
            return rhs;
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator-(Monomial<I, C, P> const &rhs) {
            auto result = Monomial<I, C, P>(rhs);
            result.coefficient = -result.coefficient;
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, T const rhs) {
            return lhs.is_constant();
        }

        template <typename I, typename C, typename P>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            if (lhs.powers.size() != rhs.powers.size()) {
                return false;
            }
            for (auto i = 0; i < lhs.powers.size(); ++i) {
                if (lhs.powers[i] != rhs.powers[i]) {
                    return false;
                }
            }
            return true;
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P>& Monomial<I, C, P>::operator*=(Monomial<I, C, P> const & rhs){
            this->coefficient *= rhs.coefficient;
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < this->powers.size() and i2 < rhs.powers.size()) {
                if (this->powers[i1].first == rhs.powers[i2].first ) {
                    this->powers[i1].second += rhs.powers[i2].second;
                    ++i1;
                    ++i2;
                } else if (grevlex_gt(this->powers[i1].first, rhs.powers[i2].first)) {
                    ++i1;
                } else {
                    this->powers.insert(this->powers.begin() + i1, rhs.powers[i2]);
                    ++i1;
                    ++i2;
                }
            }
            while (i2 < rhs.powers.size()) {
                this->powers.push_back(rhs.powers[i2]);
                ++i2;
            }
            return *this;
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator*(Monomial<I, C, P> const &lhs, T const rhs) {
            auto result = Monomial<I, C, P>(lhs);
            result.coefficient *= rhs;
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator*(T const lhs, Monomial<I, C, P> const &rhs) {
            auto result = Monomial<I, C, P>(rhs);
            result.coefficient *= lhs;
            return result;
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator*(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto result = Monomial<I, C, P>(lhs);
            result *= rhs;
            return result;
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P>& Monomial<I, C, P>::operator/=(Monomial<I, C, P> const & rhs){
            if(rhs.coefficient == 0){
                throw exceptions::division_by_zero();
            }
            if (this->coefficient % rhs.coefficient != 0) {
                throw exceptions::non_integer_division();;
            }
            this->coefficient /= rhs.coefficient;
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < this->powers.size() and i2 < rhs.powers.size()) {
                if (this->powers[i1].first == rhs.powers[i2].first) {
                    if (this->powers[i1].second < rhs.powers[i2].second) {
                        throw exceptions::non_integer_division();;
                    } else if (this->powers[i1].second > rhs.powers[i2].second) {
                        this->powers[i1].second -= rhs.powers[i2].second;
                        ++i1;
                    } else {
                        this->powers.erase(this->powers.begin() + i1);
                    }
                    ++i2;
                } else if (grevlex_gt(this->powers[i1].first, rhs.powers[i2].first)) {
                    ++i1;
                } else {
                    throw exceptions::non_integer_division();;
                }
            }
            if (i2 < rhs.powers.size()) {
                throw exceptions::non_integer_division();;
            }
            return *this;
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, T const rhs) {
            if(rhs == 0){
                throw exceptions::division_by_zero();
            }
            if (lhs.coefficient % rhs != 0) {
                throw exceptions::non_integer_division();;
            }
            auto result = Monomial<I, C, P>(lhs);
            result.coefficient /= rhs;
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator/(T const lhs, Monomial<I, C, P> const &rhs) {
            if(rhs.coefficient == 0){
                throw exceptions::division_by_zero();
            }
            if ((not rhs.is_constant()) or lhs % rhs.coefficient != 0) {
                throw exceptions::non_integer_division();;
            }
            return Monomial<I, C, P>(lhs / rhs.coefficient);
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto result = Monomial<I, C, P>(lhs);
            result /= rhs;
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H