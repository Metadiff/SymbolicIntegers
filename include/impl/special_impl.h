//
// Created by alex on 16/12/16.
//

#ifndef SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H
#define SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H

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
            return Polynomial<I, C, P>(Monomial<I, C, P>(Composite<I, C, P>(Id, id)));
        };

        template <typename I, typename C, typename P>
        Monomial<I, C, P> reduce(Monomial<I, C, P> const & monomial, std::unordered_map<I, C> const & values) {
            if(monomial.is_constant()){
                return monomial;
            }
            auto result = Monomial<I, C, P>(monomial.coefficient);
            for(auto i = 0; i < monomial.powers.size(); ++i){
                Composite<I, C, P> const & c = monomial.powers[i].first;
                if(c.type == Id){
                    auto const provided = values.find(c.id);
                    if(provided == values.end()){
                        result.powers.push_back(monomial.powers[i]);
                    } else {
                        result.coefficient *= pow(provided->second, monomial.powers[i].second);
                    }
                } else {
                    auto const left = reduce(*c.compound.first, values);
                    auto const right = reduce(*c.compound.second, values);
                    auto const left_ptr = (left == *c.compound.first) ? c.compound.first :
                                    std::make_shared<Polynomial<I, C, P>>(std::move(left));
                    auto const right_ptr = (right == *c.compound.second) ? c.compound.second :
                                     std::make_shared<Polynomial<I, C, P>>(std::move(right));
                    auto const composite = Composite<I, C, P>(c.type, left_ptr, right_ptr);
                    if(left.is_constant() && right.is_constant()) {
                        result.coefficient *= composite.eval({});
                    } else {
                        result *= Monomial<I, C, P>(composite, monomial.powers[i].second);
                    }
                }
            }
            return result;
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> reduce(Polynomial<I, C, P> const & polynomial, std::unordered_map<I, C> const & values) {
            auto result = Polynomial<I, C, P>(0);
            for(auto i = 0; i < polynomial.monomials.size(); ++i){
                result += reduce(polynomial.monomials[i], values);
            }
            return result;
        };

        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(ImplicitValues <I, C, P> & original_values) {
            auto implicit_values = original_values;
            auto indexes = std::vector<int>(original_values.size());
            for(auto i = 0; i < implicit_values.size(); ++i){
                indexes.push_back(i);
            }
            std::unordered_map<I, C> values;
            for(auto i = 0; i < implicit_values.size(); ++i){
                Polynomial<I, C, P> const & poly = implicit_values[i].first;
                C const & poly_value = implicit_values[i].second;
                // Verify if constant
                if(poly.is_constant()) {
                    C value = poly.eval({});
                    if(value != poly_value) {
                        throw exceptions::incompatible_values<I, C, P>(original_values[indexes[i]].first,
                                                                       value, poly_value);
                    }
                    // Remove current polynomial from list
                    implicit_values.erase(implicit_values.begin() + i);
                    indexes.erase(indexes.begin() + i);
                    --i;
                    continue;
                }
                // If the polynomial is in the form a * x^n + b deduce value of 'x'
                if((poly.monomials.size() == 1 || (poly.monomials.size() == 2 and poly.monomials[1].is_constant()))
                   and poly.monomials[0].powers.size() == 1 and poly.monomials[0].powers[0].first.type == Id) {
                    // b
                    C additive = poly.monomials.size() == 1 ? 0 : poly.monomials[1].eval({});
                    // a
                    C multiplicative = poly.monomials[0].coefficient;
                    // x
                    I id = poly.monomials[0].powers[0].first.id;
                    // n
                    P power = poly.monomials[0].powers[0].second;
                    C value = C(pow((implicit_values[i].second - additive) / multiplicative, 1.0 / power));
                    C reconstructed = pow(value, power) * multiplicative + additive;
                    // Verify this gives back correctly the value, as 'C' is integer
                    if(reconstructed != implicit_values[i].second){
                        throw exceptions::incompatible_values<I, C, P>(original_values[indexes[i]].first,
                                                                       reconstructed, implicit_values[i].second);
                    }
                    // Add to the values
                    values[id] = value;
                    // Remove current polynomial from list
                    implicit_values.erase(implicit_values.begin() + i);
                    indexes.erase(indexes.begin() + i);
                    // Reduce all other polynomials
                    for (auto j = 0; j < implicit_values.size(); ++j){
                        implicit_values[j].first = reduce(implicit_values[j].first, values);
                    }
                    // Start from begin again
                    i = -1;
                }
            }
            if(implicit_values.size() > 0){
                throw exceptions::missing_value();
            }
            return values;
        }
    }
}
#endif //SYMBOLICINTEGERS_SRT_SPECIAL_IMPL_H
