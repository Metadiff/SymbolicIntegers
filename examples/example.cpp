#include "symbolic_integers.h"
#include "iostream"

typedef std::string I;
typedef int64_t C;
typedef uint8_t P;
std::function<std::string(std::string)> const print = [](I id) {return id;};
typedef md::sym::ImplicitValues<std::string, int64_t, uint8_t> ImplicitValues;

int main(){
    // Create symbolic variables
    auto a = md::sym::variable<I, C, P>("a");
    auto b = md::sym::variable<I, C, P>("b");
    auto c = md::sym::variable<I, C, P>("c");

    // Build polynomials
    auto poly1 = 5 * b + 2;
    auto poly2 = a * b;
    auto poly3 = (b + c) * (a + 1);
    auto poly4 = a * a - a * b + 12;
    auto poly5 = (a + b + 1) * (c*2 + 3);
    auto poly6 = floor(b * b, a * a);
    auto poly7 = ceil(b * b, a * a);
    auto poly8 = min(a * b + 12, a * b + a);
    auto poly9 = max(a * b + 12, a * b + a);
    auto poly10 = max(floor(a * a, b) - 4, ceil(c, b) + 1);

    // Polynomial printing
    std::cout << "==================================================" << std::endl
              << "Displaying polynomials (string representation = code representation):" << std::endl
              << poly1 << " = " << to_code(poly1, print) << std::endl
              << poly2 << " = " << to_code(poly2, print) << std::endl
              << poly3 << " = " << to_code(poly3, print) << std::endl
              << poly4 << " = " << to_code(poly4, print) << std::endl
              << poly5 << " = " << to_code(poly5, print) << std::endl
              << poly6 << " = " << to_code(poly6, print) << std::endl
              << poly7 << " = " << to_code(poly7, print) << std::endl
              << poly8 << " = " << to_code(poly8, print) << std::endl
              << poly9 << " = " << to_code(poly7, print) << std::endl
              << poly10 << " = " << to_code(poly8, print) << std::endl
              << "==================================================" << std::endl;

    // Polynomial evaluation
    std::unordered_map<std::string, int64_t > values = {{"a", 3}, {"b", 2}, {"c", 5}};
    std::cout << "Evaluating for a = 3, b = 2, c = 5." << std::endl;
    std::cout << poly1 << " = " << poly1.eval(values) << " [Expected " << 12 << "]" << std::endl
              << poly2 << " = " << poly2.eval(values) << " [Expected " << 6 << "]" << std::endl
              << poly3 << " = " << poly3.eval(values) << " [Expected " << 28 << "]" << std::endl
              << poly4 << " = " << poly4.eval(values) << " [Expected " << 15 << "]" << std::endl
              << poly5 << " = " << poly5.eval(values) << " [Expected " << 78 << "]" << std::endl
              << poly6 << " = " << poly6.eval(values) << " [Expected " << 0 << "]" << std::endl
              << poly7 << " = " << poly7.eval(values) << " [Expected " << 1 << "]" << std::endl
              << poly8 << " = " << poly8.eval(values) << " [Expected " << 9 << "]" << std::endl
              << poly9 << " = " << poly9.eval(values) << " [Expected " << 18 << "]" << std::endl
              << poly10 << " = " << poly10.eval(values) << " [Expected " << 4 << "]" << std::endl
              << "==================================================" << std::endl;

    // Variable deduction
    values = {{"a", 5}, {"b", 3}, {"c", 8}};
    ImplicitValues implicit_values = {{poly1, poly1.eval(values)},
                                      {poly2, poly2.eval(values)},
                                      {poly3, poly3.eval(values)}};
    std::unordered_map<std::string, int64_t > deduced_values = md::sym::deduce_values(implicit_values);
    std::cout << "Deduced values: " << std::endl
              << "a = " << deduced_values["a"] << " [Expected: 5]" << std::endl
              << "b = " << deduced_values["b"] << " [Expected: 3]" << std::endl
              << "c = " << deduced_values["c"] << " [Expected: 8]" << std::endl
              << "==================================================" << std::endl;
    return 0;
}

