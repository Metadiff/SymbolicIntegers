//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRNT_BASE_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRNT_BASE_POLYNOMIAL_H

namespace md{
    namespace sym{
        /** The class represents a symbolic polynoimal in the form of a sum of n monomials - m_1 + m_2 + m_3 ... + m_n */
        class Polynomial {
        public:
            /** A vector of all of the monomials */
            std::vector <Monomial> monomials;

            /** Copy constructor */
            Polynomial(Polynomial const &polynomial) :
                    monomials(polynomial.monomials) {};

            /** Constructor from single monomial */
            Polynomial(const Monomial &monomial) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            /** Constructor from a constant varaible */
            Polynomial(const C value) {
                if (value != 0) {
                    monomials.push_back(Monomial(value));
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
            C eval(const std::vector <C> &values) const;

            /** @brief Evaluates the polynomial assuming that the vector provided contains pairs
             * of <i, value> which specify the value of the variable with id 'i'.
             *
             * @param values
             * @return The value of the polynomial evaluted at the provided values.
             */
            C eval(const std::vector <std::pair<I, C>> &values) const;

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

        inline std::ostream &operator<<(std::ostream &f, Polynomial const &polynomial){
            return  f << polynomial.to_string();
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRNT_BASE_POLYNOMIAL_H
