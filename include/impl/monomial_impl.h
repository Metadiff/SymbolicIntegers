//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_IMPL_H

namespace md{
    namespace sym{
        template <typename I, typename C, typename P>
        bool Monomial<I, C, P>::is_constant() const {
            return powers.empty();
        }

        template <typename I, typename C, typename P>
        C Monomial<I, C, P>::eval(std::unordered_map<I, C> const &values) const {
            C value = coefficient;
            for (auto i = 0; i < powers.size(); ++i) {
                value *= pow(powers[i].first.eval(values), powers[i].second);
            }
            return value;
        }

        template <typename I, typename C, typename P>
        std::string to_string(Monomial<I, C, P> const & monomial, id_print<I> print) {
            if (monomial.coefficient == 0) {
                return "+ 0";
            } else if (monomial.powers.empty() && monomial.coefficient < 0) {
                return "- " + std::to_string(- monomial.coefficient);
            } else if (monomial.powers.empty() && monomial.coefficient > 0) {
                return std::to_string(monomial.coefficient);
            }
            std::string result;
            if (monomial.coefficient == -1) {
                result += "- ";
            } else if (monomial.coefficient < 0) {
                result += "- " + std::to_string(- monomial.coefficient);
            } else if (monomial.coefficient != 1) {
                result += std::to_string(monomial.coefficient);
            }
            for (auto i = 0; i < monomial.powers.size(); ++i) {
                if (monomial.powers[i].second == 1){
                    result += to_string(monomial.powers[i].first, print);
                } else {
                    result += to_string(monomial.powers[i].first, print) + "^"
                              + std::to_string(monomial.powers[i].second);
                }
            }
            return result;
        }

        template <typename I, typename C, typename P>
        std::string to_code(Monomial<I, C, P> const & monomial, id_print<I> print) {
            if (monomial.coefficient == 0) {
                return "+ 0";
            } else if (monomial.powers.empty() && monomial.coefficient < 0) {
                return "- " + std::to_string(- monomial.coefficient);
            } else if (monomial.powers.empty() && monomial.coefficient > 0) {
                return std::to_string(monomial.coefficient);
            }
            std::string result;
            if (monomial.coefficient == -1) {
                result += "- ";
            } else if (monomial.coefficient < 0) {
                result += "- " + std::to_string(- monomial.coefficient);
            } else if (monomial.coefficient != 1) {
                result += std::to_string(monomial.coefficient);
            }
            for (auto i = 0; i < monomial.powers.size(); ++i) {
                if (i == 0 && (monomial.coefficient == 1 || monomial.coefficient == -1)){
                    result += to_code(monomial.powers[i].first, print);
                    for(auto j = 1; j < monomial.powers[i].second; ++j) {
                        result += " * " + to_code(monomial.powers[i].first, print);
                    }
                } else {
                    for(auto j = 0; j < monomial.powers[i].second; ++j) {
                        result += " * " + to_code(monomial.powers[i].first, print);
                    }
                }
            }
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_IMPL_H
