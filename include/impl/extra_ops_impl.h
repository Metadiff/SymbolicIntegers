//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_IMPL_H

namespace md {
    namespace sym {

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> primitive(I id){
            return Polynomial<I, C, P>(Composite<I, C, P>(Id, id));
        }

        template <typename I, typename C, typename P>
        void reduce_polynomials(std::vector <std::pair<Polynomial<I, C, P>, C>> &implicit_values,
                                std::unordered_map<I, C> const & values){
            for(auto i = 0; i < implicit_values.size(); ++i){
                Polynomial<I, C, P>& poly = implicit_values[i].first;
                for(auto j = 0; j < poly.monomials.size(); ++j){
                    Monomial<I, C, P>& mon = poly.monomials[j];
                    for(auto v = 0; v < mon.powers.size(); ++v){
                        try {
                            auto value = mon.powers[v].first.eval(values);
                            mon.coefficient *= pow(value, mon.powers[v].second);
                            mon.powers.erase(mon.powers.begin() + v);
                            --v;
                            continue;
                        } catch (...) {}
                    }
                    // Check if the monomial is the up to a constant to some previous and combine if so
                    for(auto k = 0; k < j; ++k){
                        if(up_to_coefficient(mon, poly.monomials[k])){
                            poly.monomials[k].coefficient += mon.coefficient;
                            poly.monomials.erase(poly.monomials.begin()+j);
                            --j;
                            break;
                        }
                    }
                }
            }
        };

        template <typename I, typename C, typename P>
        std::unordered_map<I, C> deduce_values(std::vector <std::pair<Polynomial<I, C, P>, C>> implicit_values){
            std::unordered_map<I, C> values;
            for(auto i = 0; i < implicit_values.size(); ++i){
                Polynomial<I, C, P>& poly = implicit_values[i].first;
                C& poly_value = implicit_values[i].second;
                // Remove polynomial if it is constant
                if(poly.is_constant()){
                    if(poly.eval({}) != poly_value){
                        INCOMPATIBLE_VALUES(poly.eval({}), poly_value)
                    }
                    implicit_values.erase(implicit_values.begin() + i);
                    --i;
                    continue;
                }
                // Eliminate constant monomials from the polynomial
                for(auto j = 0; j < poly.monomials.size(); ++j){
                    Monomial<I, C, P>& mon = poly.monomials[j];
                    if(mon.is_constant()){
                        poly_value -= mon.eval({});
                        poly.monomials.erase(poly.monomials.begin() + j);
                        --j;
                    }
                }
                if(poly.monomials.size() == 1 and poly.monomials[0].powers.size() == 1 and
                   poly.monomials[0].powers[0].first.type == Id){
                    // This means that the polynomial is of the form c * x^n and we can evaluate it
                    C c = poly.monomials[0].coefficient;
                    I id = poly.monomials[0].powers[0].first.id;
                    P power = poly.monomials[0].powers[0].second;
                    C value = C(pow(implicit_values[i].second / c, 1.0 / power));
                    if(pow(value, power) * c != poly_value){
                        INCOMPATIBLE_VALUES(pow(value, power) * c, poly_value)
                    }
                    // Add to the values
                    values[id] = value;
                    // Remove current polynomial from list
                    implicit_values.erase(implicit_values.begin() + i);
                    // Reduce all other polynomials
                    if(implicit_values.size() == 0){
                        break;
                    }
                    reduce_polynomials(implicit_values, values);
                    // Start from begin again
                    i = -1;
                }
            }
            if(implicit_values.size() > 0){
                MISSING_VALUE()
            }
            return values;
        }

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto floor(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor) {
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor > 0)
               or (dividend <= 0 and divisor < 0)
               or (dividend % divisor == 0)){
                return (dividend / divisor);
            }
            return dividend / divisor - 1;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto ceil(C1 const dividend, C2 const divisor) -> decltype(dividend / divisor) {
            if(divisor == 0){
                ZERO_DIVISION()
            }
            if((dividend >= 0 and divisor < 0) or (dividend <= 0 and divisor > 0)){
                return dividend / divisor;
            }
            if(dividend % divisor == 0){
                return dividend / divisor;
            }
            return dividend / divisor + 1;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto min(C1 const left, C2 const right) -> decltype(left + right){
            return left < right ? left : right;
        };

        template<typename C1, typename C2,
                typename = std::enable_if<std::is_integral<C1>::value>,
                typename = std::enable_if<std::is_integral<C2>::value>>
        auto max(C1 const left, C2 const right) -> decltype(left + right){
            return left > right ? left : right;
        };

        template <typename I, typename C, typename P>
        Monomial<I, C, P> floor(Monomial<I, C, P> const &dividend, Monomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                auto dividend_value = dividend.eval({});
                auto divisor_value = divisor.eval({});
                return Monomial<I, C, P>(floor(dividend_value, divisor_value));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> floor(Monomial<I, C, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Monomial<I, C, P>(floor(dividend.eval({}), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> floor(T const dividend, Monomial<I, C, P> const &divisor) {
            if (divisor.is_constant()) {
                return Monomial<I, C, P>(floor(dividend, divisor.eval({})));
            }
            return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const &dividend, Polynomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(dividend.eval({}) / divisor.eval({}));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const &dividend, Monomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(floor(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> floor(Monomial<I, C, P> const &dividend, Polynomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(floor(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> floor(Polynomial<I, C, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Polynomial<I, C, P>(floor(dividend.eval({}), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> floor(T const dividend, Polynomial<I, C, P> const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<I, C, P>(floor(dividend, divisor.eval({})));
            }
            return Composite<I, C, P>(Floor, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P>
        Monomial<I, C, P> ceil(Monomial<I, C, P> const &dividend, Monomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Monomial<I, C, P>(ceil(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> ceil(Monomial<I, C, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Monomial<I, C, P>(ceil(dividend.eval({}), divisor));
            }
            if (dividend.coefficient % divisor == 0) {
                return dividend / divisor;
            }
            return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> ceil(T const dividend, Monomial<I, C, P> const &divisor) {
            if (divisor.is_constant()) {
                return Monomial<I, C, P>(ceil(dividend, divisor.eval({})));
            }
            return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> ceil(Polynomial<I, C, P> const &dividend, Polynomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(ceil(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> ceil(Polynomial<I, C, P> const &dividend, Monomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(ceil(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> ceil(Monomial<I, C, P> const &dividend, Polynomial<I, C, P> const &divisor) {
            if (dividend.is_constant() and divisor.is_constant()) {
                return Polynomial<I, C, P>(ceil(dividend.eval({}), divisor.eval({})));
            }
            try {
                return dividend / divisor;
            } catch (const std::runtime_error& e) {
                return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                          std::make_shared<Polynomial<I, C, P>>(divisor));
            }
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> ceil(Polynomial<I, C, P> const &dividend, T const divisor) {
            if (dividend.is_constant()) {
                return Polynomial<I, C, P>(ceil(dividend.eval({}), divisor));
            }
            bool all_divisible = true;
            for(auto i=0;i<dividend.monomials.size();++i){
                if(dividend.monomials[i].coefficient % divisor != 0){
                    all_divisible = false;
                }
            }
            if(all_divisible){
                return dividend / divisor;
            }
            return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> ceil(T const dividend, Polynomial<I, C, P> const &divisor) {
            if (divisor.is_constant()) {
                return Polynomial<I, C, P>(ceil(dividend, divisor.eval({})));
            }
            return Composite<I, C, P>(Ceil, std::make_shared<Polynomial<I, C, P>>(dividend),
                                      std::make_shared<Polynomial<I, C, P>>(divisor));
        };

        template <typename I, typename C, typename P>
        Monomial<I, C, P> min(Monomial<I, C, P> const  &left, Monomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial<I, C, P>(min(left.coefficient, right.coefficient));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> min(Monomial<I, C, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Monomial<I, C, P>(min(left.coefficient, right));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> min(T const  &left, Monomial<I, C, P> const  &right){
            if (right.is_constant()) {
                return Monomial<I, C, P>(min(left, right.coefficient));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(min(left.eval({}), right.eval({})));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, Monomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(min(left.eval({}), right.coefficient));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> min(Monomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(min(left.coefficient, right.eval({})));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> min(Polynomial<I, C, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Polynomial<I, C, P>(min(left.eval({}), right));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> min(T const  &left, Polynomial<I, C, P> const  &right){
            if (right.is_constant()) {
                return Polynomial<I, C, P>(min(left, right.eval({})));
            } else {
                return Composite<I, C, P>(Min, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Monomial<I, C, P> max(Monomial<I, C, P> const  &left, Monomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Monomial<I, C, P>(max(left.coefficient, right.coefficient));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> max(Monomial<I, C, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Monomial<I, C, P>(max(left.coefficient, right));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Monomial<I, C, P> max(T const  &left, Monomial<I, C, P> const  &right){
            if (right.is_constant()) {
                return Monomial<I, C, P>(max(left, right.coefficient));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(max(left.eval({}), right.eval({})));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, Monomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(max(left.eval({}), right.coefficient));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P>
        Polynomial<I, C, P> max(Monomial<I, C, P> const  &left, Polynomial<I, C, P> const  &right){
            if (left.is_constant() and right.is_constant()) {
                return Polynomial<I, C, P>(max(left.coefficient, right.eval({})));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> max(Polynomial<I, C, P> const  &left, T const  &right){
            if (left.is_constant()) {
                return Polynomial<I, C, P>(max(left.eval({}), right));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                                          std::make_shared<Polynomial<I, C, P>>(right));
            }
        }

        template <typename I, typename C, typename P,
                typename T, typename = std::enable_if<std::is_integral<T>::value>>
        Polynomial<I, C, P> max(T const  &left, Polynomial<I, C, P> const  &right){
            if (right.is_constant()) {
                return Polynomial<I, C, P>(max(left, right.eval({})));
            } else {
                return Composite<I, C, P>(Max, std::make_shared<Polynomial<I, C, P>>(left),
                        std::make_shared<Polynomial<I, C, P>>(right));
            }
        }
    }
}

#endif //METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_IMPL_H
