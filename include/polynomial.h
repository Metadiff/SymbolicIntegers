//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_H

namespace md{
    namespace sym{
        /** The class represents a symbolic polynoimal in the form of a sum of n monomials - m_1 + m_2 + m_3 ... + m_n */
        template <typename C, typename I, typename P>
        class Polynomial {
        public:
            /** A vector of all of the monomials */
            std::vector <Monomial<C, I, P>> monomials;

            /** Copy constructor */
            Polynomial(Polynomial<C, I, P> const &polynomial) :
                    monomials(polynomial.monomials) {};

            /** Constructor from single monomial */
            Polynomial(Monomial<C, I, P> const &monomial) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            /** Constructor from a constant varaible */
            Polynomial(C const value) {
                if (value != 0) {
                    monomials.push_back(Monomial<C, I, P>(value));
                }
            }

            /** Default constructor returns 0 */
            Polynomial() {};

            /**
             * @return True only if the polynomial is constant and does not depend on any symbolic integers.
             */
            bool is_constant() const;

            /** @brief Evaluates the polynomial assuming that the vector provided at position 'i'
             * contains the value of the symbolic integer with id 'i'.
             *
             * @param values
             * @return The value of the polynomial evaluted at the provided values.
             */
            C eval(std::vector <C> const &values) const;

            /** @brief Evaluates the polynomial assuming that the vector provided contains pairs
             * of <i, value> which specify the value of the variable with id 'i'.
             *
             * @param values
             * @return The value of the polynomial evaluted at the provided values.
             */
            C eval(std::vector <std::pair<I, C>> const &values) const;

            /** @brief  Evaluates the polynomial assuming it is constant.
             *
             * @return The value of the polynomial
             */
            C eval() const;

            /**
             * @return A string representation of the polynomial
             */
            std::string to_string() const;
        };

        /** @brief Returns a humanly presentable string representation of the Polynomial
         *
         * @param polynomial
         * @return
         */
        template <typename C, typename I, typename P>
        std::string to_string(Polynomial<C, I, P> const & polynomial);

        /** @brief Returns a code equivalent string representation of the Polynomial
         *
         * @param polynomial
         * @return
         */
        template <typename C, typename I, typename P>
        std::string to_code(Polynomial<C, I, P> const & polynomial);

        template <typename C, typename I, typename P>
        std::ostream &operator<<(std::ostream &f, Polynomial<C, I, P> const &polynomial){
            return  f << to_string(polynomial);
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_H
