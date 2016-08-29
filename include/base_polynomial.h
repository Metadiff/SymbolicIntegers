//
// Created by alex on 29/08/16.
//

#ifndef SYMBOLIC_INTEGERS_BASE_POLYNOMIAL_H
#define SYMBOLIC_INTEGERS_BASE_POLYNOMIAL_H

namespace md{
    namespace sym{
        /**
         * An instance of a single symbolic polynomial
         */
        class Polynomial {
        public:
            static Polynomial zero;
            static Polynomial one;
            static std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> floor_registry;
            static std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> ceil_registry;

            static std::pair <I, std::pair<Polynomial, Polynomial>> get_floor(I id) {
                for (auto i = 0; i < floor_registry.size(); ++i) {
                    if (floor_registry[i].first == id) {
                        return floor_registry[i];
                    }
                }
                return {0, {Polynomial(0), Polynomial(0)}};
            };

            static std::pair <I, std::pair<Polynomial, Polynomial>> get_ceil(I id) {
                for (auto i = 0; i < ceil_registry.size(); ++i) {
                    if (ceil_registry[i].first == id) {
                        return ceil_registry[i];
                    }
                }
                return {0, {Polynomial(0), Polynomial(0)}};
            };

            /**
             * Resets and erases all of the symbolic variables registry
             */
            static void reset_registry(){
                Monomial::total_ids = 0;
                floor_registry.clear();
                ceil_registry.clear();
            }

            /**
             * Returns an unused symbolic integer
             * @return
             */
            static Polynomial new_variable() {
                return Polynomial(Monomial());
            }

            /**
             * Returns the symbolic integer representing the concrete id
             * @return
             */
            static Polynomial specific_variable(I id){
                return Polynomial(Monomial::specific_variable(id));
            }

            /**
             * The list of monoimals of the polynomial.
             * Note: The vector is always sorted according to less_then_comparator
             */
            std::vector <Monomial> monomials;

            Polynomial(const Polynomial &polynomial) :
                    monomials(polynomial.monomials) {};

            Polynomial(const Monomial &monomial) {
                if (monomial != 0) {
                    monomials.push_back(monomial);
                }
            };

            Polynomial(const C value) {
                if (value != 0) {
                    monomials.push_back(Monomial(value));
                }
            }

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

            static std::vector<std::pair<I, C>> deduce_values(
                    const std::vector <std::pair<Polynomial, C>> &implicit_values);
        };
    }
}
#endif //SYMBOLIC_INTEGERS_BASE_POLYNOMIAL_H
