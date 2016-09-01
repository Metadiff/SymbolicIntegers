//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_MONOMIAL_H

namespace md{
    namespace sym{
        class Registry;
        /**
         * An instance of a single symbolic monomial
         */
        class Monomial {
        public:
            /** A power first argument is the id of the variable, the second is the actual power */
            std::vector <std::pair<I, P>> powers;
            /** The constant coefficient */
            C coefficient;
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            std::shared_ptr<Registry> registry;
            Monomial(const Monomial &monomial):
                    powers(monomial.powers),
                    coefficient(monomial.coefficient),
                    registry(monomial.registry) {}

            Monomial(const C value, std::shared_ptr<Registry> registry) :
                    coefficient(value),
                    registry(registry) {}

            Monomial(std::shared_ptr<Registry> registry) :
                    Monomial(0, registry) {}
            Monomial(){};
#else
            const static std::shared_ptr<Registry> registry;
            Monomial(const Monomial &monomial):
                    powers(monomial.powers),
                    coefficient(monomial.coefficient){}

            Monomial(const C value): coefficient(value){}

            Monomial(): Monomial(0) {}
#endif
            /**
             * @return true if the monomial represents a constant
             */
            bool is_constant() const {
                return powers.size() == 0;
            }

            /**
             * @param values
             * @return The value of the monomial evaluated at the provided values.
             */
            C eval(const std::vector <C> &values) const;

            /**
             * @param values
             * @return The value of the monomial evaluated at the provided values.
             */
            C eval(const std::vector <std::pair<I, C>> &values) const;

            C eval() const {
                return eval(std::vector < C > {});
            }

            /**
             * @return A string representation of the monomial
             */
            std::string to_string() const;
        };

        std::ostream &operator<<(std::ostream &f, const Monomial &monomial);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_MONOMIAL_H
