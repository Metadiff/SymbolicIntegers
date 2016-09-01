//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NON_TEMPLATED_BASE_POLYNOMIAL_H

namespace md{
    namespace sym{
        /**
         * An instance of a single symbolic polynomial
         */
        class Polynomial {
        public:
            /**
             * The list of monoimals of the polynomial.
             * Note: The vector is always sorted according to less_then_comparator
             */
            std::vector <Monomial> monomials;

#ifdef METADIFF_SYMBOLIC_INTEGERS_DYNAMIC_REGISTRY
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

            C eval(const std::vector <C> &values) const {
                C value = 0;
                for (auto i = 0; i < monomials.size(); ++i) {
                    value += monomials[i].eval(values);
                }
                return value;
            }

            C eval(const std::vector <std::pair<I, C>> &values) const {
                C value = 0;
                for (auto i = 0; i < monomials.size(); ++i) {
                    value += monomials[i].eval(values);
                }
                return value;
            }

            C eval() const {
                return eval(std::vector < C > {});
            }

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
