//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H

namespace md{
    namespace sym{
        /** The class represents a symbolic monomial in the form of C * a(id_1)^p_1 * a(id_2)^p_2 * ... * a(id_n)^p_n */
        template <typename I, typename C, typename P>
        class Monomial {
        public:
            /** A vector of pairds (id, power), which represent the var(id)^power in the monomial */
            std::vector <std::pair<Composite<I, C, P>, P>> powers;
            /** The constant coefficient */
            C coefficient;

            /** Constructor from a constant value */
            Monomial(C const & value): coefficient(value){}

            /** From composite */
            Monomial(Composite<I, C, P> const &composite):
                    powers({{composite, 1}}),
                    coefficient(1){}

            /** From composite and power */
            Monomial(Composite<I, C, P> const &composite, P const power):
                    powers({{composite, power}}),
                    coefficient(1){}

            /** Copy constructor */
            Monomial(Monomial<I, C, P> const &monomial):
                    powers(monomial.powers),
                    coefficient(monomial.coefficient){}

            /** Default constructor returns 0 */
            Monomial(): Monomial(0) {}

            /**
             * @return True only if the monomial is constant and does not depend on any symbolic integers.
             */
            bool is_constant() const;

            /** @brief Evaluates the monomial assuming that the vector provided contains pairs
             * of <i, value> which specify the value of the variable with id 'i'.
             *
             * @param values
             * @return The value of the monomial evaluted at the provided values.
             */
            C eval(std::unordered_map<I, C> const &values) const;

            Monomial<I, C, P>& operator*=(Monomial<I, C, P> const & rhs);

            Monomial<I, C, P>& operator/=(Monomial<I, C, P> const & rhs);
        };

        /** @brief Returns a humanly presentable string representation of the Monomial
         *
         * @param monomial
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Monomial<I, C, P> const & monomial, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Monomial
         *
         * @param monomial
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_code(Monomial<I, C, P> const & monomial, id_print<I> print);

        template <typename C, typename P>
        std::ostream &operator<<(std::ostream &f, Monomial<std::string, C, P> const &monomial){
            std::function<std::string(std::string)> identity = [](std::string id) { return id; };
            return  f << to_string(monomial,  identity);
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H
