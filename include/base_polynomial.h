//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_BASE_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_BASE_POLYNOMIAL_H

namespace md{
    namespace sym{
        /**
         * An instance of a single symbolic polynomial
         */
        class Polynomial {
        public:
            Polynomial() {};
            std::shared_ptr<Registry> registry;
            /**
             * The list of monoimals of the polynomial.
             * Note: The vector is always sorted according to less_then_comparator
             */
            std::vector <Monomial> monomials;

            Polynomial(const Polynomial &polynomial) :
                    registry(polynomial.registry),
                    monomials(polynomial.monomials) {};

            Polynomial(const Monomial &monomial):
                    registry(monomial.registry){
                if (monomial != 0) {
                    monomials.push_back(monomial);
                }
            };

            Polynomial(const C value, std::shared_ptr<Registry> registry):
                    registry(registry){
                if (value != 0) {
                    monomials.push_back(Monomial(value, registry));
                }
            }

            Polynomial(std::shared_ptr<Registry> registry): Polynomial(0, registry) {};

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

        class Registry:  public std::enable_shared_from_this<Registry>{
        public:
            I total_ids;
            Polynomial zero;
            Polynomial one;
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> floor_registry;
            std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> ceil_registry;

            Registry(): total_ids(0){};

            void init(){
                std::shared_ptr<Registry> ptr = this->shared_from_this();
                zero = Polynomial(0, ptr);
                one = Polynomial(1, ptr);
            }

            std::pair <I, std::pair<Polynomial, Polynomial>> get_floor(I id) {
                for (auto i = 0; i < floor_registry.size(); ++i) {
                    if (floor_registry[i].first == id) {
                        return floor_registry[i];
                    }
                }
                return {0, {Polynomial(0, this->shared_from_this()), Polynomial(0, this->shared_from_this())}};
            };

            std::pair <I, std::pair<Polynomial, Polynomial>> get_ceil(I id) {
                for (auto i = 0; i < ceil_registry.size(); ++i) {
                    if (ceil_registry[i].first == id) {
                        return ceil_registry[i];
                    }
                }
                return {0, {Polynomial(0, this->shared_from_this()),
                            Polynomial(0, this->shared_from_this())}};
            };

            /**
             * Resets and erases all of the symbolic variables registry
             */
            void reset(){
                total_ids = 0;
                floor_registry.clear();
                ceil_registry.clear();
            }

            /**
             * Returns an unused symbolic integer
             * @return
             */
            Polynomial new_variable() {
                return Polynomial(new_monomial_variable());
            }

            Monomial new_monomial_variable(){
                auto monomial = Monomial(1, this->shared_from_this());
                monomial.powers.push_back({total_ids, 1});
                ++total_ids;
                return monomial;
            }

            /**
             * Returns the symbolic integer representing the concrete id
             * @return
             */
            Polynomial specific_variable(I id){
                return Polynomial(specific_monomial_variable(id));
            }

            Monomial specific_monomial_variable(I id){
                auto result = Monomial(1, this->shared_from_this());
                if(total_ids <= id){
                    total_ids = id + 1;
                }
                result.powers.push_back({id, 1});
                return result;
            }

            std::vector<std::pair<I, C>> deduce_values(
                    const std::vector <std::pair<Polynomial, C>> &implicit_values);

        };
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_NO_TEMPLATE_REGISTRY_BASE_POLYNOMIAL_H
