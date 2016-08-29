//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_BASE_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_BASE_MONOMIAL_H

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

            /**
             *
             */
            static Monomial new_variable(){
                auto monomial = Monomial(1);
                monomial.powers.push_back({total_ids, 1});
                ++total_ids;
                return monomial;
            }

            /** A power first argument is the id of the variable, the second is the actual power */
            std::vector <std::pair<I, P>> powers;
            /** The constant coefficient */
            C coefficient;

            Monomial(const Monomial &monomial) {
                powers = monomial.powers;
                coefficient = monomial.coefficient;
            }

            Monomial(const C value) : coefficient(value) {}

            Monomial() : Monomial(0) {}

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

        std::ostream &operator<<(std::ostream &f, const Monomial &monomial);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_BASE_MONOMIAL_H
