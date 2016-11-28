//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_MONOMIAL_H

namespace md{
    namespace sym{
        /** The class represents a symbolic monomial in the form of C * a(id_1)^p_1 * a(id_2)^p_2 * ... * a(id_n)^p_n */
        template <typename C, typename I, typename P>
        class Monomial {
        public:
            /** A vector of pairds (id, power), which represent the var(id)^power in the monomial */
            std::vector <std::pair<I, P>> powers;
            /** The constant coefficient */
            C coefficient;
            
            /** Copy constructor */
            Monomial(Monomial<C, I, P> const &monomial):
                    powers(monomial.powers),
                    coefficient(monomial.coefficient){}

            /** Constructor from a constant varaible */
            Monomial(C const value): coefficient(value){}

            /** Default constructor returns 0 */
            Monomial(): Monomial(0) {}

            /**
             * @return True only if the monomial is constant and does not depend on any symbolic integers.
             */
            bool is_constant() const;

            /** @brief Evaluates the monomial assuming that the vector provided at position 'i'
             * contains the value of the symbolic integer with id 'i'.
             *
             * @param values
             * @return The value of the monomial evaluted at the provided values.
             */
            C eval(std::vector <C> const &values) const;

            /** @brief Evaluates the monomial assuming that the vector provided contains pairs
             * of <i, value> which specify the value of the variable with id 'i'.
             *
             * @param values
             * @return The value of the monomial evaluted at the provided values.
             */
            C eval(std::vector <std::pair<I, C>> const &values) const;

            /** @brief  Evaluates the monomial assuming it is constant.
             *
             * @return The value of the monomial
             */
            C eval() const;

            /**
             * @return A string representation of the monomial
             */
            std::string to_string() const;
        };

        /** @brief Returns a humanly presentable string representation of the Monomial
        *
        * @param monomial
        * @return
        */
        template <typename C, typename I, typename P>
        std::string to_string(Monomial<C, I, P> const & monomial);

        /** @brief Returns a code equivalent string representation of the Monomial
         *
         * @param monomial
         * @return
         */
        template <typename C, typename I, typename P>
        std::string to_code(Monomial<C, I, P> const & monomial);

        template <typename C, typename I, typename P>
        std::ostream &operator<<(std::ostream &f, Monomial<C, I, P> const &monomial) {
            return f << to_string(monomial);
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_MONOMIAL_H
