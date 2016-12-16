//
// Created by alex on 29/08/16.
//

#ifndef METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_IMPL_H
#define METADIFF_SYMBOLIC_INTEGERS_EXTRA_OPS_IMPL_H

namespace md {
    namespace sym {
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
