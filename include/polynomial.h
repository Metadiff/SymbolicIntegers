//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H

namespace md{
    namespace sym{
        /** The class represents a symbolic polynoimal in the form of a sum of n monomials - m_1 + m_2 + m_3 ... + m_n */
        template <typename I, typename C, typename P>
        class Polynomial {
        public:
            /** A vector of all of the monomials */
            std::vector <Monomial<I, C, P>> monomials;

            /** Copy constructor */
            Polynomial(Polynomial<I, C, P> const &polynomial) :
                    monomials(polynomial.monomials) {};

            /** Constructor from single Monomial */
            Polynomial(Monomial<I, C, P> const &monomial) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            /** Constructor from single Composite */
            Polynomial(Composite<I, C, P> const &composite) {
                monomials.push_back(Monomial<I, C, P>(composite));
            };

            /** Constructor from a constant variable */
            Polynomial(C const value) {
                if (value != 0) {
                    monomials.push_back(Monomial<I, C, P>(value));
                }
            }

            /** Default constructor returns 0 */
            Polynomial() {};

            /**
             * @return True only if the polynomial is constant and does not depend on any symbolic integers.
             */
            bool is_constant() const;

            /** @brief Evaluates the polynomial assuming that the vector provided contains pairs
             * of <i, value> which specify the value of the variable with id 'i'.
             *
             * @param values
             * @return The value of the polynomial evaluted at the provided values.
             */
            C eval(std::unordered_map<I, C> const &values) const;
        };

        /** @brief Returns a humanly presentable string representation of the Polynomial
         *
         * @param polynomial
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Polynomial<I, C, P> const & polynomial, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Polynomial
         *
         * @param polynomial
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_code(Polynomial<I, C, P> const & polynomial, id_print<I> print);

        template <typename C, typename P>
        std::ostream &operator<<(std::ostream &f, Polynomial<std::string, C, P> const &polynomial){
            std::function<std::string(std::string)> identity = [](std::string id) { return id; };
            return  f << to_string(polynomial,  identity);
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H
