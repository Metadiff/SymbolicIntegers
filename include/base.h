//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_BASE_H
#define METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_BASE_H
namespace md {
    namespace sym {
        /**
         * An instance of a single symbolic monomial
         */
        template<typename C, typename I, typename P>
        class Monomial {
        private:
            static_assert(std::numeric_limits<C>::is_integer, "C can be only instantiated with integer types");
            static_assert(std::numeric_limits<I>::is_integer, "I can be only instantiated with integer types");
            static_assert(not std::numeric_limits<I>::is_signed, "I can be only instantiated with unsigned types");
            static_assert(std::numeric_limits<P>::is_integer, "P can be only instantiated with unsigned types");
            static_assert(not std::numeric_limits<P>::is_signed, "P can be only instantiated with unsigned types");
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

            Monomial(const Monomial<C, I, P> &monomial) {
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
            template<typename T>
            T eval(const std::vector <T> &values) const;

            C eval() const {
                return eval(std::vector < C > {});
            }

            /**
             * @return A string representation of the monomial
             */
            std::string to_string() const;
        };

        template<typename C, typename I, typename P>
        I Monomial<C, I, P>::total_ids = 0;

        /**
         * An instance of a single symbolic polynomial
         */
        template<typename C, typename I, typename P>
        class Polynomial {
        public:
            static Polynomial<C, I, P> zero;
            static Polynomial<C, I, P> one;
            static std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> floor_registry;
            static std::vector <std::pair<I, std::pair < Polynomial, Polynomial>>> ceil_registry;

            static std::pair <I, std::pair<Polynomial, Polynomial>> get_floor(I id) {
                for (auto i = 0; i < floor_registry.size(); ++i) {
                    if (floor_registry[i].first == id) {
                        return floor_registry[i];
                    }
                }
                return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
            };

            static std::pair <I, std::pair<Polynomial, Polynomial>> get_ceil(I id) {
                for (auto i = 0; i < ceil_registry.size(); ++i) {
                    if (ceil_registry[i].first == id) {
                        return ceil_registry[i];
                    }
                }
                return {0, {Polynomial<C, I, P>(0), Polynomial<C, I, P>(0)}};
            };

            /**
             * Resets and erases all of the symbolic variables registry
             */
            static void reset_registry(){
                Monomial<C, I, P>::total_ids = 0;
                floor_registry.clear();
                ceil_registry.clear();
            }

            /**
             * Returns an unused symbolic integer
             * @return
             */
            static Polynomial new_variable() {
                return Polynomial(Monomial<C, I, P>());
            }

            /**
             * Returns the symbolic integer representing the concrete id
             * @return
             */
            static Polynomial specific_variable(I id){
                return Polynomial(Monomial<C, I, P>::specific_variable(id));
            }

            /**
             * The list of monoimals of the polynomial.
             * Note: The vector is always sorted according to less_then_comparator
             */
            std::vector <Monomial<C, I, P>> monomials;

            Polynomial(const Polynomial<C, I, P> &polynomial) :
                    monomials(polynomial.monomials) {};

            Polynomial(const Monomial<C, I, P> &monomial) {
                if (monomial != 0) {
                    monomials.push_back(monomial);
                }
            };

            Polynomial(const C value) {
                if (value != 0) {
                    monomials.push_back(Monomial<C, I, P>(value));
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

            template<typename T>
            T eval(const std::vector <T> &values) const {
                T value = 0;
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

        template<typename C, typename I, typename P>
        std::vector <std::pair<I, std::pair < Polynomial<C, I, P>, Polynomial<C, I, P>>>>
        Polynomial<C, I, P>::floor_registry;
        template<typename C, typename I, typename P>
        std::vector <std::pair<I, std::pair < Polynomial<C, I, P>, Polynomial<C, I, P>>>>
        Polynomial<C, I, P>::ceil_registry;
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> Polynomial<C, I, P>::zero = Polynomial<C, I, P>(0);
        template<typename C, typename I, typename P>
        Polynomial<C, I, P> Polynomial<C, I, P>::one = Polynomial<C, I, P>(1);

        template<class C, class I, class P>
        template<class T>
        T Monomial<C, I, P>::eval(const std::vector <T> &values) const {
            static_assert(std::numeric_limits<T>::is_integer, "T can be only integer type");
            T value = coefficient;
            for (auto i = 0; i < powers.size(); ++i) {
                T cur_value;
                auto floor = Polynomial<C, I, P>::get_floor(powers[i].first);
                auto ceil = Polynomial<C, I, P>::get_ceil(powers[i].first);
                if (floor.first != 0) {
                    T dividend = floor.second.first.eval(values);
                    T divisor = floor.second.second.eval(values);
                    cur_value = dividend / divisor;
                } else if (ceil.first != 0) {
                    T dividend = ceil.second.first.eval(values);
                    T divisor = ceil.second.second.eval(values);
                    cur_value = 0;
                    if (dividend > divisor) {
                        if (dividend % divisor == 0) {
                            cur_value = dividend / divisor;
                        } else {
                            cur_value = dividend / divisor + 1;
                        }
                    }
                } else if (values.size() <= powers[i].first) {
                    throw EvaluationFailure();
                } else {
                    cur_value = values[powers[i].first];
                }
                value *= pow(cur_value, powers[i].second);
            }
            return value;
        }

        template<typename C, typename I, typename P>
        std::string Monomial<C, I, P>::to_string() const {
            if (powers.size() == 0) {
                return std::to_string(coefficient);
            }

            std::string result;
            if (coefficient != 1) {
                if (coefficient == -1) {
                    result += "-";
                } else {
                    result += std::to_string(coefficient);
                }
            }
            for (auto i = 0; i < powers.size(); ++i) {
                auto floor = Polynomial<C, I, P>::get_floor(powers[i].first);
                auto ceil = Polynomial<C, I, P>::get_ceil(powers[i].first);
                if (floor.first != 0) {
                    result += "floor(" + floor.second.first.to_string() + " / " +
                              floor.second.second.to_string() +
                              ")";
                } else if (ceil.first != 0) {
                    result +=
                            "ceil(" + ceil.second.first.to_string() + " / " + ceil.second.second.to_string() +
                            ")";
                } else {
                    result += ('a' + powers[i].first);
                    auto n = powers[i].second;
                    std::string super_scripts;
                    while (n > 0) {
                        auto reminder = n % 10;
                        n /= 10;
                        switch (reminder) {
                            case 0:
                                super_scripts = "\u2070" + super_scripts;
                                break;
                            case 1:
                                super_scripts = "\u00B9" + super_scripts;
                                break;
                            case 2:
                                super_scripts = "\u00B2" + super_scripts;
                                break;
                            case 3:
                                super_scripts = "\u00B3" + super_scripts;
                                break;
                            case 4:
                                super_scripts = "\u2074" + super_scripts;
                                break;
                            case 5:
                                super_scripts = "\u2075" + super_scripts;
                                break;
                            case 6:
                                super_scripts = "\u2076" + super_scripts;
                                break;
                            case 7:
                                super_scripts = "\u2077" + super_scripts;
                                break;
                            case 8:
                                super_scripts = "\u2078" + super_scripts;
                                break;
                            case 9:
                                super_scripts = "\u2079" + super_scripts;
                                break;
                        }
                    }
                    result += super_scripts;
                }
            }
            return result;
        }

        template<typename C, typename I, typename P>
        std::ostream &operator<<(std::ostream &f, const Monomial<C, I, P> &monomial) {
            return f << monomial.to_string();
        }

        template<typename C, typename I, typename P>
        std::ostream &operator<<(std::ostream &f, const Polynomial<C, I, P> &polynomial) {
            return f << polynomial.to_string();
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_BASE_H
