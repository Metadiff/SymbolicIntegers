//
// Created by alex on 16/12/16.
//

#ifndef SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H
#define SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H

#include "iostream"
namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool grevlex_gt(Composite<I, C, P> const &lhs, Composite<I, C, P> const &rhs) {
            switch (lhs.type) {
                case Id:
                    switch (rhs.type) {
                        case Id:
                            return lhs.id < rhs.id;
                        default:
                            return true;
                    };
                case Max:
                    switch (rhs.type) {
                        case Max: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                return grevlex_gt(*lhs.compound.second, *rhs.compound.second);
                            } else {
                                return grevlex_gt(*lhs.compound.first, *rhs.compound.first);
                            }
                        }
                        case Id:
                            return false;
                        default:
                            return true;
                    };
                case Min:
                    switch (rhs.type) {
                        case Min: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                return grevlex_gt(*lhs.compound.second, *rhs.compound.second);
                            } else {
                                return grevlex_gt(*lhs.compound.first, *rhs.compound.first);
                            }
                        };
                        case Id:
                            return false;
                        case Max:
                            return false;
                        default:
                            return true;
                    };
                case Ceil:
                    switch (rhs.type) {
                        case Ceil: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                return grevlex_gt(*lhs.compound.second, *rhs.compound.second);
                            } else {
                                return grevlex_gt(*lhs.compound.first, *rhs.compound.first);
                            }
                        };
                        case Floor:
                            return true;
                        default:
                            return false;
                    };
                default:
                    switch (rhs.type) {
                        case Floor: {
                            if (*lhs.compound.first == *rhs.compound.first) {
                                return grevlex_gt(*lhs.compound.second, *rhs.compound.second);
                            } else {
                                return grevlex_gt(*lhs.compound.first, *rhs.compound.first);
                            }
                        }
                        default:
                            return false;
                    }
            }
            return false;
        };

        template <typename I, typename C, typename P>
        bool grevlex_gt(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs) {
            auto m = std::min(lhs.powers.size(), rhs.powers.size());
            for (auto i = 0; i < m; ++i) {
                if (lhs.powers[i].first == rhs.powers[i].first) {
                    if(lhs.powers[i].second != rhs.powers[i].second){
                        return lhs.powers[i].second > rhs.powers[i].second;
                    }
                } else {
                    auto c =  grevlex_gt(lhs.powers[i].first, rhs.powers[i].first) ? ">" : "<";
                    return grevlex_gt(lhs.powers[i].first, rhs.powers[i].first);
                }
            }
            if (lhs.powers.size() != rhs.powers.size()){
                return lhs.powers.size() > rhs.powers.size();
            } else {
                return lhs.coefficient > rhs.coefficient;
            }
        };

        template <typename I, typename C, typename P>
        bool grevlex_gt(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs) {
            auto m = std::min(lhs.monomials.size(), rhs.monomials.size());
            for (auto i = 0; i < m; ++i) {
                if (lhs.monomials[i] != rhs.monomials[i]) {
                    return grevlex_gt(lhs.monomials[i], rhs.monomials[i]);
                }
            }
            return lhs.monomials.size() > rhs.monomials.size();
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> primitive(I id){
            return Polynomial<I, C, P>(Composite<I, C, P>(Id, id));
        }

        template <typename I, typename C, typename P>
        void reduce_polynomials(std::vector <std::pair<Polynomial<I, C, P>, C>> &implicit_values,
        std::unordered_map<I, C> const & values){
            for(auto i = 0; i < implicit_values.size(); ++i){
                Polynomial<I, C, P>& poly = implicit_values[i].first;
                for(auto j = 0; j < poly.monomials.size(); ++j){
                    Monomial<I, C, P>& mon = poly.monomials[j];
                    for(auto v = 0; v < mon.powers.size(); ++v){
                        try {
                            auto value = mon.powers[v].first.eval(values);
                            mon.coefficient *= pow(value, mon.powers[v].second);
                            mon.powers.erase(mon.powers.begin() + v);
                            --v;
                            continue;
                        } catch (...) {}
                    }
                    // Check if the monomial is the up to a constant to some previous and combine if so
                    for(auto k = 0; k < j; ++k){
                        if(up_to_coefficient(mon, poly.monomials[k])){
                            poly.monomials[k].coefficient += mon.coefficient;
                            poly.monomials.erase(poly.monomials.begin()+j);
                            --j;
                            break;
                        }
                    }
                }
            }
        };

        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(std::vector <std::pair<Polynomial<I, C, P>, C>> implicit_values){
            std::unordered_map<I, C> values;
            for(auto i = 0; i < implicit_values.size(); ++i){
                Polynomial<I, C, P>& poly = implicit_values[i].first;
                C& poly_value = implicit_values[i].second;
                // Remove polynomial if it is constant
                if(poly.is_constant()){
                    if(poly.eval({}) != poly_value){
                        INCOMPATIBLE_VALUES(poly.eval({}), poly_value)
                    }
                    implicit_values.erase(implicit_values.begin() + i);
                    --i;
                    continue;
                }
                // Eliminate constant monomials from the polynomial
                for(auto j = 0; j < poly.monomials.size(); ++j){
                    Monomial<I, C, P>& mon = poly.monomials[j];
                    if(mon.is_constant()){
                        poly_value -= mon.eval({});
                        poly.monomials.erase(poly.monomials.begin() + j);
                        --j;
                    }
                }
                if(poly.monomials.size() == 1 and poly.monomials[0].powers.size() == 1 and
                poly.monomials[0].powers[0].first.type == Id){
                    // This means that the polynomial is of the form c * x^n and we can evaluate it
                    C c = poly.monomials[0].coefficient;
                    I id = poly.monomials[0].powers[0].first.id;
                    P power = poly.monomials[0].powers[0].second;
                    C value = C(pow(implicit_values[i].second / c, 1.0 / power));
                    if(pow(value, power) * c != poly_value){
                        INCOMPATIBLE_VALUES(pow(value, power) * c, poly_value)
                    }
                    // Add to the values
                    values[id] = value;
                    // Remove current polynomial from list
                    implicit_values.erase(implicit_values.begin() + i);
                    // Reduce all other polynomials
                    if(implicit_values.size() == 0){
                        break;
                    }
                    reduce_polynomials(implicit_values, values);
                    // Start from begin again
                    i = -1;
                }
            }
            if(implicit_values.size() > 0){
                MISSING_VALUE()
            }
            return values;
        }
    }
}
#endif //SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H
