//
// Created by alex on 24/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_BASE_H
#define METADIFF_SYMBOLIC_INTEGERS_TEMPLATED_BASE_H
namespace md {
    namespace sym {
        template<typename T1, typename T2,
                typename = std::enable_if<std::is_integral<T1>::value>,
                typename = std::enable_if<std::is_integral<T2>::value>>
        auto floor(T1 dividend, T2 divisor) -> decltype(dividend / divisor) {
            if(divisor == 0){
                throw DivisionByZero();
            }
            if((dividend >= 0 and divisor > 0)
               or (dividend <= 0 and divisor < 0)
               or (dividend % divisor == 0)){
                return (dividend / divisor);
            }
            return dividend / divisor - 1;
        };

        template<typename T1, typename T2,
                typename = std::enable_if<std::is_integral<T1>::value>,
                typename = std::enable_if<std::is_integral<T2>::value>>
        auto ceil(T1 dividend, T2 divisor) -> decltype(dividend / divisor){
            if(divisor == 0){
                throw DivisionByZero();
            }
            if((dividend >= 0 and divisor < 0) or (dividend <= 0 and divisor > 0)){
                return dividend / divisor;
            }
            if(dividend % divisor == 0){
                return dividend / divisor;
            }
            return dividend / divisor + 1;
        };

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

            /**
             * @param values
             * @return The value of the monomial evaluated at the provided values.
             */
            template<typename T>
            T eval(const std::vector <std::pair<I, T>> &values) const;

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

            template<typename T>
            T eval(const std::vector <std::pair<I, T>> &values) const {
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

            template<typename T>
            static std::vector<std::pair<I, T>> deduce_values(
                    const std::vector <std::pair<Polynomial<C, I, P>, T>> &implicit_values);
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

        template<typename C, typename I, typename P>
        template<typename T>
        T Monomial<C, I, P>::eval(const std::vector <T> &values) const {
            static_assert(std::numeric_limits<T>::is_integer, "T can be only integer type");
            T value = coefficient;
            for (auto i = 0; i < powers.size(); ++i) {
                T cur_value;
                auto floor_poly = Polynomial<C, I, P>::get_floor(powers[i].first);
                auto ceil_poly = Polynomial<C, I, P>::get_ceil(powers[i].first);
                if (floor_poly.first != 0) {
                    T dividend = floor_poly.second.first.eval(values);
                    T divisor = floor_poly.second.second.eval(values);
                    cur_value = floor(dividend, divisor);
                } else if (ceil_poly.first != 0) {
                    T dividend = ceil_poly.second.first.eval(values);
                    T divisor = ceil_poly.second.second.eval(values);
                    cur_value = ceil(dividend, divisor);
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
        template<typename T>
        T Monomial<C, I, P>::eval(const std::vector <std::pair<I, T>> &values) const {
            static_assert(std::numeric_limits<T>::is_integer, "T can be only integer type");
            T value = coefficient;
            for (auto i = 0; i < powers.size(); ++i) {
                T cur_value;
                auto floor_poly = Polynomial<C, I, P>::get_floor(powers[i].first);
                auto ceil_poly = Polynomial<C, I, P>::get_ceil(powers[i].first);
                if (floor_poly.first != 0) {
                    T dividend = floor_poly.second.first.eval(values);
                    T divisor = floor_poly.second.second.eval(values);
                    cur_value = floor(dividend, divisor);
                } else if (ceil_poly.first != 0) {
                    T dividend = ceil_poly.second.first.eval(values);
                    T divisor = ceil_poly.second.second.eval(values);
                    cur_value = ceil(dividend, divisor);
                } else {
                    bool found = false;
                    for(auto j = 0; j < values.size(); ++j){
                        if(values[j].first == powers[i].first){
                            cur_value = values[j].second;
                            found = true;
                            break;
                        }
                    }
                    if(not found){
                        throw EvaluationFailure();
                    }
                }
                value *= pow(cur_value, powers[i].second);
            }
            return value;
        }


        template<typename C, typename I, typename P, typename T>
        void reduce_polynomials(std::vector <std::pair<Polynomial<C, I, P>, T>> &polynomials,
                                const std::vector<std::pair<I, T>>& values,
                                I id, T value){
            for(auto i = 0; i < polynomials.size(); ++i){
                for(auto j = 0; j < polynomials[i].first.monomials.size(); ++j){
                    for(auto v = 0; v < polynomials[i].first.monomials[j].powers.size(); ++v){
                        auto var_id = polynomials[i].first.monomials[j].powers[v].first;
                        auto var_p = polynomials[i].first.monomials[j].powers[v].second;
                        if(var_id == id){
                            polynomials[i].first.monomials[j].coefficient *= pow(value, var_p);
                            polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                            --v;
                            continue;
                        }
                        if(Polynomial<C, I, P>::get_floor(var_id).first != 0){
                            try {
                                auto floor_value = Polynomial<C, I, P>::specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(floor_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                        if(Polynomial<C, I, P>::get_ceil(var_id).first != 0) {
                            try {
                                auto ceil_value = Polynomial<C, I, P>::specific_variable(var_id).eval(values);
                                polynomials[i].first.monomials[j].coefficient *= pow(ceil_value, var_p);
                                polynomials[i].first.monomials[j].powers.erase(polynomials[i].first.monomials[j].powers.begin() + v);
                                --v;
                                continue;
                            } catch (...) {}
                        }
                    }
                    // Check if the monomial is the up to a constant to some previous and combine if so
                    for(auto k = 0; k < j; ++k){
                        if(up_to_coefficient(polynomials[i].first.monomials[j], polynomials[i].first.monomials[k])){
                            polynomials[i].first.monomials[k].coefficient += polynomials[i].first.monomials[j].coefficient;
                            polynomials[i].first.monomials.erase(polynomials[i].first.monomials.begin()+j);
                            --j;
                            break;
                        }
                    }
                }
            }
        };

        template<typename C, typename I, typename P>
        template<typename T>
        std::vector<std::pair<I, T>> Polynomial<C, I, P>::deduce_values(
                const std::vector <std::pair<Polynomial<C, I, P>, T>> &implicit_values){
            std::vector<std::pair<Polynomial<C, I, P>, T>> work = implicit_values;
            std::vector<std::pair<I, T>> values;
            for(auto i = 0; i < work.size(); ++i){
                // Remove constant polynomials
                if(work[i].first.is_constant()){
                    if(work[i].first.eval() != work[i].second){
                        throw EvaluationFailure();
                    }
                    work.erase(work.begin() + i);
                    --i;
                    continue;
                }
                // Eliminate constant monomials from the current one
                for(auto j = 0; j < work[i].first.monomials.size(); ++j){
                    if(work[i].first.monomials[j].is_constant()){
                        work[i].second -= work[i].first.monomials[j].eval();
                        work[i].first.monomials.erase(work[i].first.monomials.begin() + j);
                        --j;
                    }
                }
                if(work[i].first.monomials.size() == 1 and work[i].first.monomials[0].powers.size() == 1){
                    // This means that the polynomial is of the form c * x^n and we can evaluate it
                    C c = work[i].first.monomials[0].coefficient;
                    I id = work[i].first.monomials[0].powers[0].first;
                    P power = work[i].first.monomials[0].powers[0].second;
                    T value = T(pow(work[i].second / c, 1.0 / power));
                    if(pow(value, power) * c != work[i].second){
                        throw EvaluationFailure();
                    }
                    // Add to the values
                    values.push_back({id, value});
                    // Remove current polynomial from list
                    work.erase(work.begin() + i);
                    // Reduce all other polynomials
                    if(work.size() == 0){
                        break;
                    }
                    reduce_polynomials(work, values, id, value);
                    // Start from begin again
                    i = -1;
                }
            }
            if(work.size() > 0){
                throw EvaluationFailure();
            }
            return values;
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
