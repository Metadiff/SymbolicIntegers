//
// Created by alex on 01/09/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H

namespace md{
    namespace sym{
        class Registry:  public std::enable_shared_from_this<Registry>{
        public:
            I total_ids;
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> floor_registry;
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> ceil_registry;

            Registry(): total_ids(0){};

            std::pair <I, std::pair<Polynomial, Polynomial>> get_floor(I id) {
                for (auto i = 0; i < floor_registry.size(); ++i) {
                    if (floor_registry[i].first == id) {
                        return floor_registry[i];
                    }
                }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return {0, {Polynomial(0, this->shared_from_this()), Polynomial(0, this->shared_from_this())}};
#else
                return {0, {Polynomial(0), Polynomial(0)}};
#endif
            };

            std::pair <I, std::pair<Polynomial, Polynomial>> get_ceil(I id) {
                for (auto i = 0; i < ceil_registry.size(); ++i) {
                    if (ceil_registry[i].first == id) {
                        return ceil_registry[i];
                    }
                }
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                return {0, {Polynomial(0, this->shared_from_this()), Polynomial(0, this->shared_from_this())}};
#else
                return {0, {Polynomial(0), Polynomial(0)}};
#endif
              };

            /**
             * Resets and erases all of the symbolic variables registry
             */
            void reset(){
                total_ids = 0;
                floor_registry.clear();
                ceil_registry.clear();
            }

            /**
             * Returns an unused symbolic integer
             * @return
             */
            Polynomial new_variable() {
                return Polynomial(new_monomial_variable());
            }

            Monomial new_monomial_variable(){
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                auto monomial = Monomial(1, this->shared_from_this());
#else
                auto monomial = Monomial(1);
#endif
                monomial.powers.push_back({total_ids, 1});
                ++total_ids;
                return monomial;
            }

            /**
             * Returns the symbolic integer representing the concrete id
             * @return
             */
            Polynomial specific_variable(I id){
                return Polynomial(specific_monomial_variable(id));
            }

            Monomial specific_monomial_variable(I id){
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
                auto monomial = Monomial(1, this->shared_from_this());
#else
                auto monomial = Monomial(1);
#endif
                if(total_ids <= id){
                    total_ids = id + 1;
                }
                monomial.powers.push_back({id, 1});
                return monomial;
            }

            std::vector<std::pair<I, C>> deduce_values(
                    const std::vector <std::pair<Polynomial, C>> &implicit_values);

        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H
