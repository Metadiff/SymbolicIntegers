//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_MONOMIAL_H

#include "vector"
#include "memory"
#include "math.h"

namespace md{
    namespace sym{
        /** A Registry for which symbolic variables have been used */
        class Registry;
        /** An instance of a single symbolic monomial */
        class Monomial {
        public:
            /**
             * A vector of monomial powers (a^n),
             * first argument is the id of the variable,
             * the second is the actual power
             */
            std::vector <std::pair<I, P>> powers;
            /** The constant coefficient */
            C coefficient;
#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            /** Registry to which this instance is linked to */
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
            /** A static Registry for all variables */
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
             * The values vector contains at i'th position the value
             * of the symbolic variable with id 'i'.
             * @param values
             * @return The value of the monomial evaluated at the values.
             */
            C eval(const std::vector <C> &values) const;

            /**
             * The values vector is a mapping between symbolic variable id
             * and its actual value.
             * @param values
             * @return The value of the monomial evaluated at the values.
             */
            C eval(const std::vector <std::pair<I, C>> &values) const;

            /**
             * Valid only for constant monomials
             * @return The value of the monomial
             */
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
