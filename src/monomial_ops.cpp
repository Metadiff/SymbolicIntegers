//
// Created by alex on 29/08/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {

        bool operator==(Monomial const &lhs, Monomial const &rhs) {
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

        bool operator!=(Monomial const &lhs, Monomial const &rhs) {
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

        bool operator==(Monomial const &lhs, C const rhs) {
            return lhs.is_constant() and (lhs.coefficient == rhs);
        }

        bool operator!=(Monomial const &lhs, C const rhs) {
            return (not lhs.is_constant()) or (lhs.coefficient != rhs);
        }


        bool operator==(C const lhs, Monomial const &rhs) {
            return rhs.is_constant() and (rhs.coefficient == lhs);
        }

        bool operator!=(C const lhs, Monomial const &rhs) {
            return (not rhs.is_constant()) or (rhs.coefficient != lhs);
        }

        bool up_to_coefficient(Monomial const &lhs, Monomial const &rhs) {
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

        bool up_to_coefficient(C const lhs, Monomial const &rhs) {
            return rhs.is_constant();
        }

        bool up_to_coefficient(Monomial const &lhs, C const rhs) {
            return lhs.is_constant();
        }

        bool less_than_comparator(Monomial const &lhs, Monomial const &rhs) {
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

        Monomial operator+(Monomial const &rhs) {
            return rhs;
        }

        Monomial operator-(Monomial const &rhs) {
            auto result = Monomial(rhs);
            result.coefficient = -result.coefficient;
            return result;
        }

        Monomial operator*(Monomial const &lhs, Monomial const &rhs) {
            auto result = Monomial(lhs.coefficient * rhs.coefficient);
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

        Monomial operator*(Monomial const &lhs, C const rhs) {
            auto result = Monomial(lhs);
            result.coefficient *= rhs;
            return result;
        }

        Monomial operator*(C const lhs, Monomial const &rhs) {
            auto result = Monomial(rhs);
            result.coefficient *= lhs;
            return result;
        }

        Monomial operator/(Monomial const &lhs, Monomial const &rhs) {
            if(rhs.coefficient == 0){
                ZERO_DIVISION()
            }
            auto result = Monomial(1);
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
                        result.powers.push_back(
                                std::pair < I, P > {lhs.powers[i1].first,
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

        Monomial operator/(Monomial const &lhs, C const rhs) {
            if(rhs == 0){
                ZERO_DIVISION()
            }
            if (lhs.coefficient % rhs != 0) {
                NON_INTEGER_DIVISION()
            }
            auto result = Monomial(lhs);
            result.coefficient /= rhs;
            return result;
        }

        Monomial operator/(C const lhs, Monomial const &rhs) {
            if(rhs.coefficient == 0){
                ZERO_DIVISION()
            }
            if ((not rhs.is_constant()) or lhs % rhs.coefficient != 0) {
                NON_INTEGER_DIVISION()
            }
            return Monomial(lhs / rhs.coefficient);
        }
    }
}