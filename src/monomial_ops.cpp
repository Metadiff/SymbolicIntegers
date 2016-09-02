//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"
namespace md {
    namespace sym {
        
        bool operator==(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
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

        bool operator!=(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
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

        bool operator==(const Monomial &lhs, const C rhs) {
            return lhs.is_constant() and (lhs.coefficient == rhs);
        }

        bool operator!=(const Monomial &lhs, const C rhs) {
            return (not lhs.is_constant()) or (lhs.coefficient != rhs);
        }

        
        bool operator==(const C lhs, const Monomial &rhs) {
            return rhs.is_constant() and (rhs.coefficient == lhs);
        }

        bool operator!=(const C lhs, const Monomial &rhs) {
            return (not rhs.is_constant()) or (rhs.coefficient != lhs);
        }

        bool up_to_coefficient(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
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

        bool up_to_coefficient(const C lhs, const Monomial &rhs) {
            return rhs.is_constant();
        }

        bool up_to_coefficient(const Monomial &lhs, const C rhs) {
            return lhs.is_constant();
        }

        bool less_than_comparator(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
#endif
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

        Monomial operator+(const Monomial &rhs) {
            return rhs;
        }

        Monomial operator-(const Monomial &rhs) {
            auto result = Monomial(rhs);
            result.coefficient = -result.coefficient;
            return result;
        }

        Monomial operator*(const Monomial &lhs, const Monomial &rhs) {
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Monomial(lhs.coefficient * rhs.coefficient, lhs.registry);
#else
            auto result = Monomial(lhs.coefficient * rhs.coefficient);
#endif
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

        Monomial operator*(const Monomial &lhs, const C rhs) {
            auto result = Monomial(lhs);
            result.coefficient *= rhs;
            return result;
        }

        Monomial operator*(const C lhs, const Monomial &rhs) {
            auto result = Monomial(rhs);
            result.coefficient *= lhs;
            return result;
        }

        Monomial operator/(const Monomial &lhs, const Monomial &rhs) {
            if(rhs.coefficient == 0){
                throw DivisionByZero();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            if(lhs.registry != rhs.registry){
                throw DifferentRegistries();
            }
            auto result = Monomial(1, lhs.registry);
#else
            auto result = Monomial(1);
#endif
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

        Monomial operator/(const Monomial &lhs, const C rhs) {
            if(rhs == 0){
                throw DivisionByZero();
            }
            if (lhs.coefficient % rhs != 0) {
                throw NonIntegerDivision();
            }
            auto result = Monomial(lhs);
            result.coefficient /= rhs;
            return result;
        }

        Monomial operator/(const C lhs, const Monomial &rhs) {
            if(rhs.coefficient == 0){
                throw DivisionByZero();
            }
            if ((not rhs.is_constant()) or lhs % rhs.coefficient != 0) {
                throw NonIntegerDivision();
            }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            return Monomial(lhs / rhs.coefficient, rhs.registry);
#else
            return Monomial(lhs / rhs.coefficient);
#endif
        }
    }
}