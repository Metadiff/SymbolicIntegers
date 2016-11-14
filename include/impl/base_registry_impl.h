//
// Created by alex on 12/11/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_IMPL_H

namespace md{
    namespace sym{
        template <typename C, typename I, typename P>
        std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> Registry<C, I, P>::get_floor(I id) {
            for (auto i = 0; i < floor_registry.size(); ++i) {
                if (floor_registry[i].first == id) {
                    return floor_registry[i];
                }
            }
            return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
        };

        template <typename C, typename I, typename P>
        std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> Registry<C, I, P>::get_ceil(I id) {
            for (auto i = 0; i < ceil_registry.size(); ++i) {
                if (ceil_registry[i].first == id) {
                    return ceil_registry[i];
                }
            }
            return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
        };

        template <typename C, typename I, typename P>
        std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> Registry<C, I, P>::get_min(I id) {
            for (auto i = 0; i < min_registry.size(); ++i) {
                if (min_registry[i].first == id) {
                    return min_registry[i];
                }
            }
            return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
        };

        template <typename C, typename I, typename P>
        std::pair <I, std::pair<Polynomial<C, I, P>, Polynomial<C, I, P>>> Registry<C, I, P>::get_max(I id) {
            for (auto i = 0; i < max_registry.size(); ++i) {
                if (max_registry[i].first == id) {
                    return max_registry[i];
                }
            }
            return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
        };

        template <typename C, typename I, typename P>
        void Registry<C, I, P>::reset(){
            total_ids = 0;
            floor_registry.clear();
            ceil_registry.clear();
            min_registry.clear();
            max_registry.clear();
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> Registry<C, I, P>::new_variable() {
            return Polynomial<C, I, P>(new_monomial_variable());
        }

        template <typename C, typename I, typename P>
        Monomial<C, I, P> Registry<C, I, P>::new_monomial_variable(){
            auto monomial = Monomial<C, I, P>(1);
            monomial.powers.push_back({total_ids, 1});
            ++total_ids;
            return monomial;
        }

        template <typename C, typename I, typename P>
        Polynomial<C, I, P> Registry<C, I, P>::specific_variable(I id){
            return Polynomial<C, I, P>(specific_monomial_variable(id));
        }
        
        template <typename C, typename I, typename P>
        Monomial<C, I, P> Registry<C, I, P>::specific_monomial_variable(I id){
            auto monomial = Monomial<C, I, P>(1);
            if(total_ids <= id){
                total_ids = id + I(1);
            }
            monomial.powers.push_back({id, 1});
            return monomial;
        }

        template <typename C, typename I, typename P>
        void reduce_polynomials(std::shared_ptr<Registry<C, I, P>> registry,
                                std::vector <std::pair<Polynomial<C, I, P>, C>> &polynomials,
                                std::vector<std::pair<I, C>> const & values,
                                I id, C value){
            for(auto i = 0; i < polynomials.size(); ++i){
                for(auto j = 0; j < polynomials[i].first.monomials.size(); ++j){
                    for(auto v = 0; v < polynomials[i].first.monomials[j].powers.size(); ++v){
                        auto var_id = polynomials[i].first.monomials[j].powers[v].first;
                        auto var_p = polynomials[i].first.monomials[j].powers[v].second;
                        if(var_id == id){
                            polynomials[i].first.monomials[j].coefficient *= pow(value, var_p);
                            polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                            --v;
                            continue;
                        }
                        if(registry->get_floor(var_id).first != 0){
                            try {
                                auto floor_value = registry->specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(floor_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                        if(registry->get_ceil(var_id).first != 0) {
                            try {
                                auto ceil_value = registry->specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(ceil_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                        if(registry->get_min(var_id).first != 0){
                            try {
                                auto min_value = registry->specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(min_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                        if(registry->get_max(var_id).first != 0){
                            try {
                                auto max_value = registry->specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(max_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                    }
                    // Check if the monomial is the up to a constant to some previous and combine if so
                    for(auto k = 0; k < j; ++k){
                        if(up_to_coefficient(polynomials[i].first.monomials[j], polynomials[i].first.monomials[k])){
                            polynomials[i].first.monomials[k].coefficient += polynomials[i].first.monomials[j].coefficient;
                            polynomials[i].first.monomials.erase(polynomials[i].first.monomials.begin()+j);
                            --j;
                            break;
                        }
                    }
                }
            }
        };

        template <typename C, typename I, typename P>
        std::vector<std::pair<I, C>> Registry<C, I, P>::deduce_values(std::vector <std::pair<Polynomial<C, I, P>, C>> const &implicit_values){
            std::vector<std::pair<Polynomial<C, I, P>, C>> work = implicit_values;
            std::vector<std::pair<I, C>> values;
            for(auto i = 0; i < work.size(); ++i){
                // Remove constant polynomials
                if(work[i].first.is_constant()){
                    if(work[i].first.eval() != work[i].second){
                        MISSING_VALUE()
                    }
                    work.erase(work.begin() + i);
                    --i;
                    continue;
                }
                // Eliminate constant monomials from the current one
                for(auto j = 0; j < work[i].first.monomials.size(); ++j){
                    if(work[i].first.monomials[j].is_constant()){
                        work[i].second -= work[i].first.monomials[j].eval();
                        work[i].first.monomials.erase(work[i].first.monomials.begin() + j);
                        --j;
                    }
                }
                if(work[i].first.monomials.size() == 1 and work[i].first.monomials[0].powers.size() == 1){
                    // This means that the polynomial is of the form c * x^n and we can evaluate it
                    C c = work[i].first.monomials[0].coefficient;
                    I id = work[i].first.monomials[0].powers[0].first;
                    P power = work[i].first.monomials[0].powers[0].second;
                    C value = C(pow(work[i].second / c, 1.0 / power));
                    if(pow(value, power) * c != work[i].second){
                        MISSING_VALUE()
                    }
                    // Add to the values
                    values.push_back({id, value});
                    // Remove current polynomial from list
                    work.erase(work.begin() + i);
                    // Reduce all other polynomials
                    if(work.size() == 0){
                        break;
                    }
                    reduce_polynomials(this->shared_from_this(), work, values, id, value);
                    // Start from begin again
                    i = -1;
                }
            }
            if(work.size() > 0){
                MISSING_VALUE()
            }
            return values;
        }
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_IMPL_H
