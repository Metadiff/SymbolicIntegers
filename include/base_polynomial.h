//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_POLYNOMIAL_H

namespace md{
    namespace sym{
        /** An instance of a single symbolic polynomial */
        class Polynomial {
        public:
            /**
             * The list of monomials comprising the polynomial
             * Note: The vector is always sorted according to less_then_comparator
             */
            std::vector <Monomial> monomials;

#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
            /** Registry to which this instance is linked to */
            std::shared_ptr<Registry> registry;

            Polynomial(const Polynomial &polynomial) :
                    monomials(polynomial.monomials),
                    registry(polynomial.registry) {};

            Polynomial(const Monomial &monomial):
                    registry(monomial.registry) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            Polynomial(const C value, std::shared_ptr<Registry> registry):
                    registry(registry) {
                if (value != 0) {
                    monomials.push_back(Monomial(value, registry));
                }
            }

            Polynomial(std::shared_ptr<Registry> registry): Polynomial(0, registry) {};

            Polynomial() {};
#else
            /** A static Registry for all variables */
            const static std::shared_ptr<Registry> registry;

            Polynomial(const Polynomial &polynomial) :
                    monomials(polynomial.monomials) {};

            Polynomial(const Monomial &monomial) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            Polynomial(const C value) {
                if (value != 0) {
                    monomials.push_back(Monomial(value));
                }
            }

            Polynomial(): Polynomial(0) {};
#endif
            /**
             * @return true if the monomial represents a constant
             */
            bool is_constant() const {
                switch (monomials.size()) {
                    case 0:
                        return true;
                    case 1:
                        return monomials[0].is_constant();
                    default:
                        return false;
                }
            }

            /**
             * The values vector contains at i'th position the value
             * of the symbolic variable with id 'i'.
             * @param values
             * @return The value of the polynomial evaluated at the values.
             */
            C eval(const std::vector <C> &values) const {
                C value = 0;
                for (auto i = 0; i < monomials.size(); ++i) {
                    value += monomials[i].eval(values);
                }
                return value;
            }

            /**
             * The values vector is a mapping between symbolic variable id
             * and its actual value.
             * @param values
             * @return The value of the polynomial evaluated at the values.
             */
            C eval(const std::vector <std::pair<I, C>> &values) const {
                C value = 0;
                for (auto i = 0; i < monomials.size(); ++i) {
                    value += monomials[i].eval(values);
                }
                return value;
            }

            /**
             * Valid only for constant monomials
             * @return The value of the polynomial
             */
            C eval() const {
                return eval(std::vector < C > {});
            }

            /**
             * @return A string representation of the monomial
             */
            std::string to_string() const {
                if (monomials.size() == 0) {
                    return "0";
                }
                std::string result = monomials[0].to_string();
                for (auto i = 1; i < monomials.size(); ++i) {
                    if (monomials[i].coefficient > 0) {
                        result += "+" + monomials[i].to_string();
                    } else {
                        result += monomials[i].to_string();
                    }
                }
                return result;
            }
        };

        std::ostream &operator<<(std::ostream &f, const Polynomial &polynomial);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_POLYNOMIAL_H
