//
// Created by alex on 12/11/16.
//

#include "symbolic_integers.h"

namespace md {
    namespace sym {
        bool Polynomial::is_constant() const {
            switch (monomials.size()) {
                case 0:
                    return true;
                case 1:
                    return monomials[0].is_constant();
                default:
                    return false;
            }
        }

        C Polynomial::eval(const std::vector <C> &values) const {
            C value = 0;
            for (auto i = 0; i < monomials.size(); ++i) {
                value += monomials[i].eval(values);
            }
            return value;
        }

        C Polynomial::eval(const std::vector <std::pair<I, C>> &values) const {
            C value = 0;
            for (auto i = 0; i < monomials.size(); ++i) {
                value += monomials[i].eval(values);
            }
            return value;
        }

        C Polynomial::eval() const {
            return eval(std::vector < C > {});
        }

        std::string Polynomial::to_string() const {
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
    }
}
