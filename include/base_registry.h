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
            /** A register for all variables which are result of a floor operation */
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> min_registry;
            /** A register for all variables which are result of a ceil operation */
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> max_registry;

            Registry(): total_ids(0){};

            /** @brief Returnst the entry of the floor registry for that id, if it does not exists returns empty
             * entry with id 0.
             *
             * @param id
             * @return The entry in the floor registry.
             */
            std::pair <I, std::pair<Polynomial, Polynomial>> get_floor(I id);

            /** @brief Returnst the entry of the ceil registry for that id, if it does not exists returns empty
            * entry with id 0.
            *
            * @param id
            * @return The entry in the ceil registry.
            */
            std::pair <I, std::pair<Polynomial, Polynomial>> get_ceil(I id);

            /** @brief Returnst the entry of the min registry for that id, if it does not exists returns empty
            * entry with id 0.
            *
            * @param id
            * @return The entry in the min registry.
            */
            std::pair <I, std::pair<Polynomial, Polynomial>> get_min(I id);

            /** @brief Returnst the entry of the max registry for that id, if it does not exists returns empty
            * entry with id 0.
            *
            * @param id
            * @return The entry in the max registry.
            */
            std::pair <I, std::pair<Polynomial, Polynomial>> get_max(I id);

            /** Resets the registry */
            void reset();

            /**
             * @return A new symbolic variable as a Polynomial
             */
            Polynomial new_variable();

            /**
             * @return A new symbolic variable as a Monomial
             */
            Monomial new_monomial_variable();

            /**
             * @param id
             * @return The symbolic variable corresponding to the id as a Polynomial
             */
            Polynomial specific_variable(I id);

            /**
             * @param id
             * @return The symbolic variable corresponding to the id as a Monomial
             */
            Monomial specific_monomial_variable(I id);

            /**
             * The method tries to deduce the values of all individual symbolic variables
             * based on the provided equations for several polynomials. Currently, the
             * method to do is very simple, a more sophisticated and better functioning method
             * would probably use <a href="https://en.wikipedia.org/wiki/Gr%C3%B6bner_basis">Grobner basis</a>.
             * @param implicit_values - a mapping from polynomial to a value, specifing an equation
             * @return The deduced single variables' values
             */
            std::vector<std::pair<I, C>> deduce_values(std::vector <std::pair<Polynomial, C>> const &implicit_values);
        };

        inline std::shared_ptr<Registry> registry(){
            static std::shared_ptr<Registry> registry;
            if(not registry){
                registry = std::make_shared<Registry>();
            }
            return registry;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_REGISTRY_H
