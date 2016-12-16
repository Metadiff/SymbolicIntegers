//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H

namespace md {
    namespace sym {

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
        bool operator==(Monomial<I, C, P> const &lhs, T const rhs) {
            return lhs.is_constant() and (lhs.coefficient == rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Monomial<I, C, P> const &lhs, T const rhs) {
            return (not lhs.is_constant()) or (lhs.coefficient != rhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Monomial<I, C, P> const &rhs) {
            return rhs.is_constant() and (rhs.coefficient == lhs);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Monomial<I, C, P> const &rhs) {
            return (not rhs.is_constant()) or (rhs.coefficient != lhs);
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

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(T const lhs, Monomial<I, C, P> const &rhs) {
            return rhs.is_constant();
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, T const rhs) {
            return lhs.is_constant();
        }

        template <typename I, typename C, typename P>
        bool less_than_comparator(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto max = lhs.powers.size() > rhs.powers.size() ? rhs.powers.size()
                                                             : lhs.powers.size();
            for (auto i = 0; i < max; ++i) {
                if (lhs.powers[i].first < rhs.powers[i].first) {
                    return true;
                } else if (lhs.powers[i].first > rhs.powers[i].first) {
                    return false;
                } else if (lhs.powers[i].second > rhs.powers[i].second) {
                    return true;
                } else if (lhs.powers[i].second < rhs.powers[i].second) {
                    return false;
                }
            }
            if (lhs.powers.size() < rhs.powers.size()) {
                return false;
            } else if (lhs.powers.size() > rhs.powers.size()) {
                return true;
            } else {
                return lhs.coefficient > rhs.coefficient;
            }
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

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator*(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto result = Monomial<I, C, P>(lhs.coefficient * rhs.coefficient);
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < lhs.powers.size() and i2 < rhs.powers.size()) {
                if (lhs.powers[i1].first < rhs.powers[i2].first) {
                    result.powers.push_back(lhs.powers[i1]);
                    ++i1;
                } else if (lhs.powers[i1].first > rhs.powers[i2].first) {
                    result.powers.push_back(rhs.powers[i2]);
                    ++i2;
                } else {
                    result.powers.push_back({lhs.powers[i1].first, lhs.powers[i1].second + rhs.powers[i2].second});
                    ++i1;
                    ++i2;
                }
            }
            while (i1 < lhs.powers.size()) {
                result.powers.push_back(lhs.powers[i1]);
                ++i1;
            }
            while (i2 < rhs.powers.size()) {
                result.powers.push_back(rhs.powers[i2]);
                ++i2;
            }
            return result;
        }

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
        Monomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            if(rhs.coefficient == 0){
                ZERO_DIVISION()
            }
            auto result = Monomial<I, C, P>(1);
            if (lhs.coefficient % rhs.coefficient != 0) {
                NON_INTEGER_DIVISION()
            }
            result.coefficient = lhs.coefficient / rhs.coefficient;
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < lhs.powers.size() and i2 < rhs.powers.size()) {
                if (lhs.powers[i1].first < rhs.powers[i2].first) {
                    result.powers.push_back(lhs.powers[i1]);
                    ++i1;
                } else if (lhs.powers[i1].first > rhs.powers[i2].first) {
                    NON_INTEGER_DIVISION()
                } else {
                    if (lhs.powers[i1].second < rhs.powers[i2].second) {
                        NON_INTEGER_DIVISION()
                    } else if (lhs.powers[i1].second > rhs.powers[i2].second) {
                        result.powers.push_back({lhs.powers[i1].first,
                                                 lhs.powers[i1].second - rhs.powers[i2].second});
                    }
                    ++i1;
                    ++i2;
                }
            }
            if (i2 < rhs.powers.size()) {
                NON_INTEGER_DIVISION()
            }
            while (i1 < lhs.powers.size()) {
                result.powers.push_back(lhs.powers[i1]);
                ++i1;
            }
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, T const rhs) {
            if(rhs == 0){
                ZERO_DIVISION()
            }
            if (lhs.coefficient % rhs != 0) {
                NON_INTEGER_DIVISION()
            }
            auto result = Monomial<I, C, P>(lhs);
            result.coefficient /= rhs;
            return result;
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> operator/(T const lhs, Monomial<I, C, P> const &rhs) {
            if(rhs.coefficient == 0){
                ZERO_DIVISION()
            }
            if ((not rhs.is_constant()) or lhs % rhs.coefficient != 0) {
                NON_INTEGER_DIVISION()
            }
            return Monomial<I, C, P>(lhs / rhs.coefficient);
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_OPS_IMPL_H