#include "symbolic_integers.h"
#include "iostream"

typedef std::string I;
typedef int64_t C;
typedef uint8_t P;
typedef md::sym::Polynomial<I, C, P> SymInt;
typedef std::unordered_map<I, C> VecValues;
typedef std::vector<std::pair<SymInt, C>> ImplicitValues;
std::function<std::string(std::string)> const print = [](I id) {return id;};

int main(){
    // Get just the individual symbolic variables
    auto a = md::sym::variable<I, C, P>("a");
    auto b = md::sym::variable<I, C, P>("b");
    auto c = md::sym::variable<I, C, P>("c");

    // Build polynomials
    auto poly1 = a * a - a * b + 12;
    auto poly2 = (b + c) * (a + 1);
    auto poly3 = a * b;
    auto poly4 = (a + b + 1) * (c*2 + 3);
    auto poly5 = floor(b * b, a * a);
    auto poly6 = ceil(b * b, a * a);
    auto poly7 = min(a * b + 12, a * b + a);
    auto poly8 = max(a * b + 12, a * b + a);

    // Evaluate using a vector
    std::cout << "Human readable vs code representation:" << std::endl
              << poly1 << " = " << to_code(poly1, print) << std::endl
              << poly2 << " = " << to_code(poly2, print) << std::endl
              << poly3 << " = " << to_code(poly3, print) << std::endl
              << poly4 << " = " << to_code(poly4, print) << std::endl
              << poly5 << " = " << to_code(poly5, print) << std::endl
              << poly6 << " = " << to_code(poly6, print) << std::endl
              << poly7 << " = " << to_code(poly7, print) << std::endl
              << poly8 << " = " << to_code(poly8, print) << std::endl
              << "==================================================" << std::endl;
    // Evaluating using a vector of pairs
    VecValues vals1 {{"a", 3}, {"b", 2}, {"c", 5}};
    std::cout << "Evaluating for " << a << " = " << a.eval(vals1)
              << ", " << b << " = " << b.eval(vals1)
              << ", " << c << " = " << c.eval(vals1) << std::endl;
    std::cout << "Using 'eval'." << std::endl;
    std::cout << poly1 << " = " << poly1.eval(vals1) << " [Expected " << 15 << "]" << std::endl
              << poly2 << " = " << poly2.eval(vals1) << " [Expected " << 28 << "]" << std::endl
              << poly3 << " = " << poly3.eval(vals1) << " [Expected " << 6 << "]" << std::endl
              << poly4 << " = " << poly4.eval(vals1) << " [Expected " << 78 << "]" << std::endl
              << poly5 << " = " << poly5.eval(vals1) << " [Expected " << 0 << "]" << std::endl
              << poly6 << " = " << poly6.eval(vals1) << " [Expected " << 1 << "]" << std::endl
              << poly7 << " = " << poly7.eval(vals1) << " [Expected " << 9 << "]" << std::endl
              << poly8 << " = " << poly8.eval(vals1) << " [Expected " << 18 << "]" << std::endl
              << "==================================================" << std::endl;
    // Deducing variable values from polynomials
    auto a_val = 5;
    auto b_val = 3;
    auto c_val = 8;
    ImplicitValues implicit_values{{poly2, 66}, {poly3, 15}, {5*b + 2, 17}};
    VecValues deduced_values = md::sym::deduce_values(implicit_values);
    std::cout << "Deduced values: " << std::endl
              << "a = " << a.eval(deduced_values) << " [Expected: " << a_val << "]" << std::endl
              << "b = " << b.eval(deduced_values) << " [Expected: " << b_val << "]" << std::endl
              << "c = " << c.eval(deduced_values) << " [Expected: " << c_val << "]" << std::endl;
    return 0;
}
