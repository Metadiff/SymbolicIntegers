//
// Created by alex on 12/11/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_IMPL_H

namespace md {
    namespace sym {
        template <typename C, typename I, typename P>
        bool Polynomial<C, I, P>::is_constant() const {
            switch (monomials.size()) {
                case 0:
                    return true;
                case 1:
                    return monomials[0].is_constant();
                default:
                    return false;
            }
        }

        template <typename C, typename I, typename P>
        C Polynomial<C, I, P>::eval(std::vector <C> const &values) const {
            C value = 0;
            for (auto i = 0; i < monomials.size(); ++i) {
                value += monomials[i].eval(values);
            }
            return value;
        }

        template <typename C, typename I, typename P>
        C Polynomial<C, I, P>::eval(std::vector <std::pair<I, C>> const &values) const {
            C value = 0;
            for (auto i = 0; i < monomials.size(); ++i) {
                value += monomials[i].eval(values);
            }
            return value;
        }

        template <typename C, typename I, typename P>
        C Polynomial<C, I, P>::eval() const {
            return eval(std::vector < C > {});
        }

        template <typename C, typename I, typename P>
        std::string to_string(Polynomial<C, I, P> const & polynomial) {
            if (polynomial.monomials.size() == 0) {
                return "0";
            }
            std::string result = to_string(polynomial.monomials[0]);
            for (auto i = 1; i < polynomial.monomials.size(); ++i) {
                if (polynomial.monomials[i].coefficient > 0) {
                    result += " + " + to_string(polynomial.monomials[i]);
                } else {
                    result += to_string(polynomial.monomials[i]);
                }
            }
            return result;
        }

        template <typename C, typename I, typename P>
        std::string to_code(Polynomial<C, I, P> const & polynomial) {
            if (polynomial.monomials.size() == 0) {
                return "0";
            }
            std::string result = to_code(polynomial.monomials[0]);
            for (auto i = 1; i < polynomial.monomials.size(); ++i) {
                if (polynomial.monomials[i].coefficient > 0) {
                    result += " + " + to_code(polynomial.monomials[i]);
                } else {
                    result += to_code(polynomial.monomials[i]);
                }
            }
            return result;
        }
    }
}
#endif //METADIFF_SYMBOLIC_INTEGERS_SRT_POLYNOMIAL_IMPL_H

