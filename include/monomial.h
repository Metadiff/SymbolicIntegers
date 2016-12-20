//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H

namespace md{
    namespace sym{
        /** A symbolic monomial represented as  C * a_1^p_1 * a_2^p_2 * ... * a_n^p_n. */
        template <typename I, typename C, typename P>
        class Monomial {
        public:
            /** A vector of the pairs (a_i, p_i), where a_i is a Composite expression. */
            std::vector <std::pair<Composite<I, C, P>, P>> powers;
            /** The constant coefficient C */
            C coefficient;

            /** Constructor from a constant value */
            Monomial(C const & value): coefficient(value){}

            /** Constructor from a Composite */
            Monomial(Composite<I, C, P> const &composite):
                    powers({{composite, 1}}),
                    coefficient(1){}

            /** Constructor for a composite raised to a power */
            Monomial(Composite<I, C, P> const &composite, P const power):
                    powers({{composite, power}}),
                    coefficient(1){}

            /** Copy constructor */
            Monomial(Monomial<I, C, P> const &monomial):
                    powers(monomial.powers),
                    coefficient(monomial.coefficient){}

            /** Default constructor returns 0 */
            Monomial(): Monomial(0) {}

            /** True only if the monomial is constant and does not depend on any symbolic variables. */
            bool is_constant() const;

            /** Evaluates the Monomial given the provided mapping of identifier to value assignment. */
            C eval(std::unordered_map<I, C> const &values) const;

            Monomial<I, C, P>& operator*=(Monomial<I, C, P> const & rhs);

            Monomial<I, C, P>& operator/=(Monomial<I, C, P> const & rhs);
        };

        /** @brief Returns a humanly presentable string representation of the Monomial
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Monomial<I, C, P> const & monomial, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Monomial
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_code(Monomial<I, C, P> const & monomial, id_print<I> print);

        template <typename C, typename P>
        std::ostream &operator<<(std::ostream &f, Monomial<std::string, C, P> const &monomial){
            std::function<std::string(std::string)> identity = [](std::string id) { return id; };
            return  f << to_string(monomial,  identity);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator+(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P> operator-(Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P>
        bool up_to_coefficient(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator*(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator*(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P>  operator/(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Monomial<I, C, P>  operator/(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_MONOMIAL_H
