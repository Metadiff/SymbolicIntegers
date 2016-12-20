# Symbolic Integers

[![Build Status](https://travis-ci.org/Metadiff/symbolic-integers.svg?branch=master)](https://travis-ci.org/Metadiff/symints)
[![License](https://img.shields.io/badge/Licence-Apache2.0-blue.svg)](./LICENSE)
[![GitHub version](https://badge.fury.io/gh/Metadiff%2Fsymbolic-integers.svg)](https://badge.fury.io/gh/Metadiff%2Fsymbolic-integers)

A header only library for manipulation and evaluation of symbolic integer polynomials.

## Template types arguments
All of the symbolic expressions have three template types associated with them. 

   1. *I* - the type that uniquely identifies a single symbolic variable
   2. *C* - the type of the free coefficient in every monomial
   3. *P* - the type of the power used in every monomial

## Overview

The main class you most likely will be using is `Polynomial<I, C, P>`, which 
represents any symbolic polynomial. The easiest way to create single variables
(e.g. like `a`, `b`, `c` ...) is by calling `variable(I id)`. The will be a 
unique identification of the variable. From there you can use standard 
arithmetic operators with both other symbolic expressions and with constants. 

If you want to evaluate a symbolic expression, you can call its `eval` method,
which requires you to specify a mapping from unique identifiers to their assignments.

You can also use automatic deduction to solve a system of equations. 

The ordering of both the polynomials and monomials are based on 
[Graded reverse lexicographic order](https://en.wikipedia.org/wiki/Monomial_order#Graded_reverse_lexicographic_order)
derived from the ordering on `I`. Note that this requires the comparison operators
to be implemented for type `I`.

The library provide a method `to_stirng` to convert any expression to a humanly 
readable format. Additionally the `to_code` method renders powers as repeated 
multiplications, and the output string would look like code snippet. 

## Installation
Since this is only a header only library all you have to do is to 
include the main header file `symbolic_integers.h`.

If you want to run the tests or compile the example you will need to 
build the project. Don't forget to initialize the googletest submodule 
via `git submodule update --init --recursive`. 
 
## Example usage

Below is the code for a the example found in the `examples` directory.

```c++
#include "symbolic_integers.h"
#include "iostream"

typedef std::string I;
typedef int64_t C;
typedef uint8_t P;
std::function<std::string(std::string)> const print = [](I id) {return id;};

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

    values = {{"a", 5}, {"b", 3}, {"c", 8}};
    md::sym::ImplicitValues<std::string, int64_t, uint8_t> implicit_values = {{poly1, poly1.eval(values)},
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
```

The output of the program:
```c++

==================================================
Displaying polynomials (string representation = code representation):
5b + 2 = 5 * b + 2
ab = a * b
ab + ac + b + c = a * b + a * c + b + c
a^2 - ab + 12 = a * a - a * b + 12
2ac + 3a + 2bc + 3b + 2c + 3 = 2 * a * c + 3 * a + 2 * b * c + 3 * b + 2 * c + 3
floor(b^2, a^2) = floor(b * b, a * a)
ceil(b^2, a^2) = ceil(b * b, a * a)
min(ab + 12, ab + a) = min(a * b + 12, a * b + a)
max(ab + 12, ab + a) = ceil(b * b, a * a)
max(floor(a^2, b) - 4, ceil(c, b) + 1) = min(a * b + 12, a * b + a)
==================================================
Evaluating for a = 3, b = 2, c = 5.
5b + 2 = 12 [Expected 12]
ab = 6 [Expected 6]
ab + ac + b + c = 28 [Expected 28]
a^2 - ab + 12 = 15 [Expected 15]
2ac + 3a + 2bc + 3b + 2c + 3 = 78 [Expected 78]
floor(b^2, a^2) = 0 [Expected 0]
ceil(b^2, a^2) = 1 [Expected 1]
min(ab + 12, ab + a) = 9 [Expected 9]
max(ab + 12, ab + a) = 18 [Expected 18]
max(floor(a^2, b) - 4, ceil(c, b) + 1) = 4 [Expected 4]
==================================================
Deduced values: 
a = 5 [Expected: 5]
b = 3 [Expected: 3]
c = 8 [Expected: 8]
==================================================
Displaying polynomials (string representation = code representation):
5b + 2 = 5 * b + 2
ab = a * b
ab + ac + b + c = a * b + a * c + b + c
a^2 - ab + 12 = a * a - a * b + 12
2ac + 3a + 2bc + 3b + 2c + 3 = 2 * a * c + 3 * a + 2 * b * c + 3 * b + 2 * c + 3
floor(b^2, a^2) = floor(b * b, a * a)
ceil(b^2, a^2) = ceil(b * b, a * a)
min(ab + 12, ab + a) = min(a * b + 12, a * b + a)
max(ab + 12, ab + a) = ceil(b * b, a * a)
max(floor(a^2, b) - 4, ceil(c, b) + 1) = min(a * b + 12, a * b + a)
==================================================
Evaluating for a = 3, b = 2, c = 5.
5b + 2 = 12 [Expected 12]
ab = 6 [Expected 6]
ab + ac + b + c = 28 [Expected 28]
a^2 - ab + 12 = 15 [Expected 15]
2ac + 3a + 2bc + 3b + 2c + 3 = 78 [Expected 78]
floor(b^2, a^2) = 0 [Expected 0]
ceil(b^2, a^2) = 1 [Expected 1]
min(ab + 12, ab + a) = 9 [Expected 9]
max(ab + 12, ab + a) = 18 [Expected 18]
max(floor(a^2, b) - 4, ceil(c, b) + 1) = 4 [Expected 4]
==================================================
Deduced values: 
a = 5 [Expected: 5]
b = 3 [Expected: 3]
c = 8 [Expected: 8]
==================================================
```

You can check out the tests in the `tests` folder for more examples.

## Limitations

Currently, the automatic deduction for solving system of equations 
is pretty limited. The main reason is that for the purposes that the 
project has been developed it is sufficient. A more powerful and complete
algorithm would probably use 
[Grobner basis](https://en.wikipedia.org/wiki/Gr%C3%B6bner_basis).

## License
The project is distrusted under the Apache 2.0 License.

## Contributing
If you want to contribute in any way please make an Issue or submit a PR
request describing its functionality.
