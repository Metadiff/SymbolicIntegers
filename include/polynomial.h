//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H
#define METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H

namespace md{
    namespace sym{
        /** A symbolic polynomial represented as  m_1 + m_2 + ... + m_n. */
        template <typename I, typename C, typename P>
        class Polynomial {
        public:
            /** A vector of the monomials m_i, where m_i is a Monomial. */
            std::vector <Monomial<I, C, P>> monomials;

            /** Constructor from a constant variable */
            Polynomial(C const value) {
                if (value != 0) {
                    monomials.push_back(Monomial<I, C, P>(value));
                }
            }

            /*** Constructor from a Composite */
            Polynomial(Composite<I, C, P> const &composite) {
                monomials.push_back(Monomial<I, C, P>(composite));
            };

            /** Constructor for a composite raised to a power */
            Polynomial(Composite<I, C, P> const &composite, P const power) {
                monomials.push_back(Monomial<I, C, P>(composite, power));
            };

            /** Constructor from a Monomial */
            Polynomial(Monomial<I, C, P> const &monomial) {
                if (monomial.coefficient != 0) {
                    monomials.push_back(monomial);
                }
            };

            /** Copy constructor */
            Polynomial(Polynomial<I, C, P> const &polynomial) :
                    monomials(polynomial.monomials) {};

            /** Default constructor returns 0 */
            Polynomial() {};

            /** True only if the polynomial is constant and does not depend on any symbolic variables. */
            bool is_constant() const;

            /** Evaluates the Polynomial given the provided mapping of identifier to value assignment. */
            C eval(std::unordered_map<I, C> const &values) const;

            Polynomial<I, C, P>& operator+=(Polynomial<I, C, P> const & rhs);

            Polynomial<I, C, P>& operator-=(Polynomial<I, C, P> const & rhs);

            Polynomial<I, C, P>& operator*=(Polynomial<I, C, P> const & rhs);

            Polynomial<I, C, P>& operator/=(Polynomial<I, C, P> const & rhs);
        };

        /** @brief Returns a humanly presentable string representation of the Polynomial
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_string(Polynomial<I, C, P> const & polynomial, id_print<I> print);

        /** @brief Returns a code equivalent string representation of the Polynomial
         *
         * @param composite
         * @param print - print function for how to convert the identifier of type `I` to string
         * @return
         */
        template <typename I, typename C, typename P>
        std::string to_code(Polynomial<I, C, P> const & polynomial, id_print<I> print);

        template <typename C, typename P>
        std::ostream &operator<<(std::ostream &f, Polynomial<std::string, C, P> const &polynomial){
            std::function<std::string(std::string)> identity = [](std::string id) { return id; };
            return  f << to_string(polynomial,  identity);
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator==(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator==(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        bool operator!=(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        bool operator!=(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator+(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator+(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Monomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator-(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator-(T const lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator*(T const lhs, Polynomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Monomial<I, C, P> const lhs, Polynomial<I, C, P> const rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator*(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, Monomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> operator/(Monomial<I, C, P> const &lhs, Polynomial<I, C, P> const &rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(Polynomial<I, C, P> const &lhs, T const rhs);

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> operator/(T const lhs, Polynomial<I, C, P> const rhs);
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_H
