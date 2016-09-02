//
// Created by alex on 01/09/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H

namespace md{
    namespace sym{
        class Registry:  public std::enable_shared_from_this<Registry>{
        public:
            /** The total number of ids already used */
            I total_ids;
            /** A register for all variables which are result of a floor operation */
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> floor_registry;
            /** A register for all variables which are result of a ceil operation */
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> ceil_registry;

            Registry(): total_ids(0){};

            /**
             * @param id
             * @return The entry in the floor_registry for this variable if it exists,
             * otherwise an empty entry with id 0.
             */
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

            /**
             * @param id
             * @return The entry in the ceil_registry for this variable if it exists,
             * otherwise an empty entry with id 0.
             */
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
             * Resets the registry
             */
            void reset(){
                total_ids = 0;
                floor_registry.clear();
                ceil_registry.clear();
            }

            /**
             * @return A new symbolic variable as a Polynomial
             */
            Polynomial new_variable() {
                return Polynomial(new_monomial_variable());
            }

            /**
             * @return A new symbolic variable as a Monomial
             */
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
             * @param id
             * @return The symbolic variable corresponding to the id as a Polynomial
             */
            Polynomial specific_variable(I id){
                return Polynomial(specific_monomial_variable(id));
            }

            /**
             * @param id
             * @return The symbolic variable corresponding to the id as a Monomial
             */
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

            /**
             * The method tries to deduce the values of all individual symbolic variables
             * based on the provided equations for several polynomials. Currently, the
             * method to do is very simple, a more sophisticated and better functioning method
             * would probably use <a href="https://en.wikipedia.org/wiki/Gr%C3%B6bner_basis">Grobner basis</a>.
             * @param implicit_values - a mapping from polynomial to a value, specifing an equation
             * @return The deduced single variables' values
             */
            std::vector<std::pair<I, C>> deduce_values(
                    const std::vector <std::pair<Polynomial, C>> &implicit_values);

        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H
