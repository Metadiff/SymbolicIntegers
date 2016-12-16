//
// Created by alex on 12/11/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_IMPL_H

namespace md {
    namespace sym {
        template <typename I, typename C, typename P>
        bool Polynomial<I, C, P>::is_constant() const {
            switch (monomials.size()) {
                case 0:
                    return true;
                case 1:
                    return monomials[0].is_constant();
                default:
                    return false;
            }
        }

        template <typename I, typename C, typename P>
        C Polynomial<I, C, P>::eval(std::unordered_map<I, C> const &values) const {
            C value = 0;
            for (auto i = 0; i < monomials.size(); ++i) {
                value += monomials[i].eval(values);
            }
            return value;
        }

        template <typename I, typename C, typename P>
        std::string to_string(Polynomial<I, C, P> const & polynomial, id_print<I> print) {
            if (polynomial.monomials.size() == 0) {
                return "0";
            }
            std::string result = to_string(polynomial.monomials[0], print);
            for (auto i = 1; i < polynomial.monomials.size(); ++i) {
                if (polynomial.monomials[i].coefficient > 0) {
                    result += " + " + to_string(polynomial.monomials[i], print);
                } else if (polynomial.monomials[i].coefficient < 0) {
                    result += " " + to_string(polynomial.monomials[i], print);
                }
            }
            return result;
        }

        template <typename I, typename C, typename P>
        std::string to_code(Polynomial<I, C, P> const & polynomial, id_print<I> print) {
            if (polynomial.monomials.size() == 0) {
                return "0";
            }
            std::string result = to_code(polynomial.monomials[0], print);
            for (auto i = 1; i < polynomial.monomials.size(); ++i) {
                if (polynomial.monomials[i].coefficient > 0) {
                    result += " + " + to_code(polynomial.monomials[i], print);
                } else if (polynomial.monomials[i].coefficient < 0) {
                    result += " " + to_code(polynomial.monomials[i], print);
                }
            }
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_POLYNOMIAL_IMPL_H

