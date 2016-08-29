//
// Created by alex on 29/08/16.
//

#ifndef SYMBOLIC_INTEGERS_BASE_MONOMIAL_H
#define SYMBOLIC_INTEGERS_BASE_MONOMIAL_H

namespace md{
    namespace sym{
        /**
         * An instance of a single symbolic monomial
         */
        class Monomial {
        public:
            static I total_ids;
            /**
             * @param id
             * @return
             */
            static Monomial specific_variable(I id){
                auto result = Monomial(1);
                if(total_ids <= id){
                    total_ids = id + 1;
                }
                result.powers.push_back({id, 1});
                return result;
            }

            /** A power first argument is the id of the variable, the second is the actual power */
            std::vector <std::pair<I, P>> powers;
            /** The constant coefficient */
            C coefficient;

            Monomial() : coefficient(1) {
                powers.push_back({total_ids, 1});
                ++total_ids;
            }

            Monomial(const C value) : coefficient(value) {}

            Monomial(const Monomial &monomial) {
                powers = monomial.powers;
                coefficient = monomial.coefficient;
            }

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

        I Monomial::total_ids = 0;
    }
}
#endif //SYMBOLIC_INTEGERS_BASE_MONOMIAL_H
