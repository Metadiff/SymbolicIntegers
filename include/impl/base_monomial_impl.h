//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_BASE_MONOMIAL_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_BASE_MONOMIAL_IMPL_H

namespace md{
    namespace sym{
        template <typename C, typename I, typename P>
        bool Monomial<C, I, P>::is_constant() const {
            return powers.size() == 0;
        }

        template <typename C, typename I, typename P>
        C Monomial<C, I, P>::eval(std::vector<C> const &values) const {
            C value = coefficient, cur_value;
            std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> var;
            for (auto i = 0; i < powers.size(); ++i) {
                if ((var = registry<C, I, P>()->get_floor(powers[i].first)).first != 0) {
                    C dividend = var.second.first.eval(values);
                    C divisor = var.second.second.eval(values);
                    cur_value = floor(dividend, divisor);
                } else if ((var = registry<C, I, P>()->get_ceil(powers[i].first)).first != 0) {
                    C dividend = var.second.first.eval(values);
                    C divisor = var.second.second.eval(values);
                    cur_value = ceil(dividend, divisor);
                } else if ((var = registry<C, I, P>()->get_min(powers[i].first)).first != 0) {
                    C left = var.second.first.eval(values);
                    C right = var.second.second.eval(values);
                    cur_value = min(left, right);
                } else if ((var = registry<C, I, P>()->get_max(powers[i].first)).first != 0) {
                    C left = var.second.first.eval(values);
                    C right = var.second.second.eval(values);
                    cur_value = max(left, right);
                } else if (values.size() <= powers[i].first) {
                    MISSING_VALUE()
                } else {
                    cur_value = values[powers[i].first];
                }
                value *= pow(cur_value, powers[i].second);
            }
            return value;
        }

        template <typename C, typename I, typename P>
        C Monomial<C, I, P>::eval(std::vector <std::pair<I, C>> const &values) const {
            C value = coefficient, cur_value;
            std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> var;
            for (auto i = 0; i < powers.size(); ++i) {
                if ((var = registry<C, I, P>()->get_floor(powers[i].first)).first != 0) {
                    C dividend = var.second.first.eval(values);
                    C divisor = var.second.second.eval(values);
                    cur_value = floor(dividend, divisor);
                    value *= pow(cur_value, powers[i].second);
                } else if ((var = registry<C, I, P>()->get_ceil(powers[i].first)).first != 0) {
                    C dividend = var.second.first.eval(values);
                    C divisor = var.second.second.eval(values);
                    cur_value = ceil(dividend, divisor);
                    value *= pow(cur_value, powers[i].second);
                } else if ((var = registry<C, I, P>()->get_min(powers[i].first)).first != 0) {
                    C left = var.second.first.eval(values);
                    C right = var.second.second.eval(values);
                    cur_value = min(left, right);
                    value *= pow(cur_value, powers[i].second);
                } else if ((var = registry<C, I, P>()->get_max(powers[i].first)).first != 0) {
                    C left = var.second.first.eval(values);
                    C right = var.second.second.eval(values);
                    cur_value = max(left, right);
                    value *= pow(cur_value, powers[i].second);
                } else {
                    bool found = false;
                    for(auto j = 0; j < values.size(); ++j){
                        if(values[j].first == powers[i].first){
                            cur_value = values[j].second;
                            value *= pow(cur_value, powers[i].second);
                            found = true;
                            break;
                        }
                    }
                    if(not found){
                        MISSING_VALUE()
                    }
                }
            }
            return value;
        }

        template <typename C, typename I, typename P>
        C Monomial<C, I, P>::eval() const {
            return eval(std::vector < C > {});
        }

        template <typename C, typename I, typename P>
        std::string Monomial<C, I, P>::to_string() const {
            if (powers.size() == 0) {
                return std::to_string(coefficient);
            }

            std::string result;
            if (coefficient != 1) {
                if (coefficient == -1) {
                    result += "-";
                } else {
                    result += std::to_string(coefficient);
                }
            }
            std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> var;
            for (auto i = 0; i < powers.size(); ++i) {
                if ((var = registry<C, I, P>()->get_floor(powers[i].first)).first != 0) {
                    result += "floor(" + var.second.first.to_string() + " / " +
                              var.second.second.to_string() + ")";
                } else if ((var = registry<C, I, P>()->get_ceil(powers[i].first)).first != 0) {
                    result += "ceil(" + var.second.first.to_string() + " / " +
                              var.second.second.to_string() + ")";
                } else if ((var = registry<C, I, P>()->get_min(powers[i].first)).first != 0) {
                    result += "min(" + var.second.first.to_string() + " / " +
                              var.second.second.to_string() + ")";
                } else if ((var = registry<C, I, P>()->get_max(powers[i].first)).first != 0) {
                    result += "max(" + var.second.first.to_string() + " / " +
                              var.second.second.to_string() + ")";
                } else {
                    result += ('a' + powers[i].first);
                    auto n = powers[i].second;
                    if (n > 1) {
                        result += '^';
                        result += std::to_string(n);
                    }
                }
            }
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_BASE_MONOMIAL_IMPL_H
