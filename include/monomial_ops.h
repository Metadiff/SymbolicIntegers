//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_MONOMIAL_OPS_H
#define METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_MONOMIAL_OPS_H

namespace md {
    namespace sym {
        template<typename C, typename I, typename P>
        bool operator==(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
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

        template<typename C, typename I, typename P>
        bool operator!=(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
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

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(const Monomial <C, I, P> &lhs, const T rhs) {
            return lhs.is_constant() and (lhs.coefficient == rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(const Monomial <C, I, P> &lhs, const T rhs) {
            return (not lhs.is_constant()) or (lhs.coefficient != rhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(const T lhs, const Monomial <C, I, P> &rhs) {
            return rhs.is_constant() and (rhs.coefficient == lhs);
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(const T lhs, const Monomial <C, I, P> &rhs) {
            return (not rhs.is_constant()) or (rhs.coefficient != lhs);
        }

        template<typename C, typename I, typename P>
        bool up_to_coefficient(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
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

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(const T lhs, const Monomial <C, I, P> &rhs) {
            return rhs.is_constant();
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(const Monomial <C, I, P> &lhs, const T rhs) {
            return lhs.is_constant();
        }

        /**
         * An monomial m1 is compared to monomial m2 in the following order of precedence:
         * 1. Check if the lowest variable id in m1 and m2 are equal.
         *    - If they are not than whoever has the lowest is "before" the other.
         * 2.If they are equal compare the power of this variable.
         *    - Whoever has the higher is "before" the other.
         * 3. If the they are equal continue with next lowest variable by id.
         * 4. If all are equal compare coefficients.
         *
         * For instance a^2b^1 is "before" 100ab^300, since a^2 <-> a.
         */
        template<typename C, typename I, typename P>
        bool less_than_comparator(const Monomial <C, I, P> &monomial1, const Monomial <C, I, P> &monomial2) {
            auto max = monomial1.powers.size() > monomial2.powers.size() ? monomial2.powers.size()
                                                                         : monomial1.powers.size();
            for (auto i = 0; i < max; ++i) {
                if (monomial1.powers[i].first < monomial2.powers[i].first) {
                    return true;
                } else if (monomial1.powers[i].first > monomial2.powers[i].first) {
                    return false;
                } else if (monomial1.powers[i].second > monomial2.powers[i].second) {
                    return true;
                } else if (monomial1.powers[i].second < monomial2.powers[i].second) {
                    return false;
                }
            }
            if (monomial1.powers.size() < monomial2.powers.size()) {
                return false;
            } else if (monomial1.powers.size() > monomial2.powers.size()) {
                return true;
            } else {
                return monomial1.coefficient > monomial2.coefficient;
            }
        }

        template<typename C, typename I, typename P>
        Monomial <C, I, P> operator+(const Monomial <C, I, P> &rhs) {
            return rhs;
        }

        template<typename C, typename I, typename P>
        Monomial <C, I, P> operator-(const Monomial <C, I, P> &rhs) {
            auto result = Monomial<C, I, P>(rhs);
            result.coefficient = -result.coefficient;
            return result;
        }

        template<typename C, typename I, typename P>
        Monomial <C, I, P> operator*(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            auto result = Monomial<C, I, P>(lhs.coefficient * rhs.coefficient);
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
                    result.powers.push_back(
                            std::pair < I, P > {lhs.powers[i1].first, lhs.powers[i1].second + rhs.powers[i2].second});
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

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> operator*(const Monomial <C, I, P> &lhs, const T rhs) {
            auto result = Monomial<C, I, P>(lhs);
            result.coefficient *= rhs;
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> operator*(const T lhs, const Monomial <C, I, P> &rhs) {
            auto result = Monomial<C, I, P>(rhs);
            result.coefficient *= lhs;
            return result;
        }

        template<typename C, typename I, typename P>
        Monomial <C, I, P> operator/(const Monomial <C, I, P> &lhs, const Monomial <C, I, P> &rhs) {
            auto result = Monomial<C, I, P>(1);
            if (lhs.coefficient % rhs.coefficient != 0) {
                throw NonIntegerDivision();
            }
            result.coefficient = lhs.coefficient / rhs.coefficient;
            auto i1 = 0;
            auto i2 = 0;
            while (i1 < lhs.powers.size() and i2 < rhs.powers.size()) {
                if (lhs.powers[i1].first < rhs.powers[i2].first) {
                    result.powers.push_back(lhs.powers[i1]);
                    ++i1;
                } else if (lhs.powers[i1].first > rhs.powers[i2].first) {
                    throw NonIntegerDivision();
                } else {
                    if (lhs.powers[i1].second < rhs.powers[i2].second) {
                        throw NonIntegerDivision();
                    } else if (lhs.powers[i1].second > rhs.powers[i2].second) {
                        result.powers.push_back(
                                std::pair < I, P > {lhs.powers[i1].first,
                                                    lhs.powers[i1].second - rhs.powers[i2].second});
                    }
                    ++i1;
                    ++i2;
                }
            }
            if (i2 < rhs.powers.size()) {
                throw NonIntegerDivision();
            }
            while (i1 < lhs.powers.size()) {
                result.powers.push_back(lhs.powers[i1]);
                ++i1;
            }
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> operator/(const Monomial <C, I, P> &lhs, const T rhs) {
            if (rhs == 0 or lhs.coefficient % rhs != 0) {
                throw NonIntegerDivision();
            }
            auto result = Monomial<C, I, P>(lhs);
            result.coefficient /= rhs;
            return result;
        }

        template<typename C, typename I, typename P, typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial <C, I, P> operator/(const T lhs, const Monomial <C, I, P> &rhs) {
            if ((not rhs.is_constant()) or rhs.coefficient == 0 or lhs % rhs.coefficient != 0) {
                throw NonIntegerDivision();
            }
            return Monomial<C, I, P>(lhs / rhs.coefficient);
        }

//        /**
//         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P>
//        Monomial<C, I, P> floor(const Monomial<C, I, P> &dividend, const Monomial<C, I, P> &divisor) {
//            if (dividend.is_constant() and divisor.is_constant()) {
//                return Monomial<C, I, P>(dividend.eval() / divisor.eval());
//            } else {
//                try {
//                    auto result = dividend / divisor;
//                    return result;
//                } catch (...) {
//                    Monomial<C, I, P>::floor_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
//                    return Monomial<C, I, P>();
//                }
//            }
//        };
//
//        /**
//         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P, typename T>
//        Polynomial<C, I, P> floor(const Monomial<C, I, P> &dividend, const T divisor) {
//            if (dividend.is_constant()) {
//                return Polynomial<C, I, P>(dividend.eval() / divisor);
//            } else if (dividend.coefficient % divisor == 0) {
//                return dividend / divisor;
//            } else {
//                Polynomial<C, I, P>::floor_registry.push_back(
//                        {Polynomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
//                return Polynomial::new_variable();
//            }
//        };
//
//        /**
//         * Makes a floor division, e.g. returns the integer representation of floor(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P, typename T>
//        Polynomial<C, I, P> floor(const T dividend, const Monomial<C, I, P> &divisor) {
//            if (divisor.is_constant()) {
//                return Polynomial<C, I, P>(dividend / divisor.eval());
//            } else {
//                Polynomial<C, I, P>::floor_registry.push_back(
//                        {Polynomial<C, I, P>::total_ids, {dividend, Polynomial<C, I, P>(divisor)}});
//                return Polynomial<C, I, P>::new_variable();
//            }
//        };
//
////            /**
////             * Makes a floor division, e.g. returns the integer representation of floor(a/b)
////             * @param dividend
////             * @param divisor
////             * @return
////             */
////            template<typename C, typename I, typename P>
////            Monomial<C, I, P> floor(const C dividend, const C divisor) {
////                return Monomial<C, I, P>(dividend / divisor);
////            };
//
//        /**
//         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P>
//        Monomial<C, I, P> ceil(const Monomial<C, I, P> &dividend, const Monomial<C, I, P> &divisor) {
//            if (dividend.is_constant() and divisor.is_constant()) {
//                C dividend_value = dividend.eval();
//                C divisor_value = divisor.eval();
//                C value = 0;
//                if (dividend_value > divisor_value) {
//                    if (dividend_value % divisor_value == 0) {
//                        value = dividend_value / divisor_value;
//                    } else {
//                        value = dividend_value / divisor_value + 1;
//                    }
//                }
//                return Monomial<C, I, P>(value);
//            } else {
//                try {
//                    auto result = dividend / divisor;
//                    return result;
//                } catch (...) {
//                    Monomial<C, I, P>::ceil_registry.push_back({Monomial<C, I, P>::total_ids, {dividend, divisor}});
//                    return Monomial<C, I, P>();
//                }
//            }
//        };
//
//        /**
//         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P, typename T>
//        Monomial<C, I, P> ceil(const Monomial<C, I, P> &dividend, const T divisor) {
//            if (dividend.is_constant()) {
//                C dividend_value = dividend.eval();
//                C value = 0;
//                if (dividend_value > divisor) {
//                    if (dividend_value % divisor == 0) {
//                        value = dividend_value / divisor;
//                    } else {
//                        value = dividend_value / divisor + 1;
//                    }
//                }
//                return Monomial<C, I, P>(value);
//            } else if (dividend.coefficient % divisor == 0) {
//                return dividend / divisor;
//            } else {
//                Monomial<C, I, P>::ceil_registry.push_back(
//                        {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
//                return Monomial<C, I, P>();
//            }
//        };
//
//        /**
//         * Makes a ceil division, e.g. returns the integer representation of ceil(a/b)
//         * @param dividend
//         * @param divisor
//         * @return
//         */
//        template<typename C, typename I, typename P, typename T>
//        Monomial<C, I, P> ceil(const T dividend, const Monomial<C, I, P> &divisor) {
//            if (divisor.is_constant()) {
//                C divisor_value = divisor.eval();
//                C value = 0;
//                if (dividend > divisor_value) {
//                    if (dividend % divisor_value == 0) {
//                        value = dividend / divisor_value;
//                    } else {
//                        value = dividend / divisor_value + 1;
//                    }
//                }
//                return Monomial<C, I, P>(value);
//            } else {
//                Monomial<C, I, P>::ceil_registry.push_back(
//                        {Monomial<C, I, P>::total_ids, {dividend, Monomial<C, I, P>(divisor)}});
//                return Monomial<C, I, P>();
//            }
//        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_MONOMIAL_OPS_H
