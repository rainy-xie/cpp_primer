/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 *
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
 *
 *
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 *
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address:
 *
 * 	Pearson Education, Inc.
 * 	Rights and Permissions Department
 * 	One Lake Street
 * 	Upper Saddle River, NJ  07458
 * 	Fax: (201) 236-3290
 */

// This file illustrates use of function, which is a C++ 11 library facility

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <map>
using std::map;

#include <utility>
using std::make_pair;

#include <string>
using std::string;

#include <tr1/functional>
using std::tr1::bind;
using std::tr1::function;
using namespace std::tr1::placeholders;

// ordinary function
int add(int i, int j) { return i + j; }

// functions to use in place of the lambda used in the original code
int mod(int i, int j) { return i % j; };
int mult(int i, int j) { return i * j; };

// function-object class
// In the first printing this struct was named div, but that name conflicts with
// the name of a C library function.  Compilers are permitted to put
// C library names in the global namespace.  Future printings will
// change the name of this calss to divide.
struct divide {
  int operator()(int denominator, int divisor) { return denominator / divisor; }
};

int main() {
  function<int(int, int)> f1 = add;      // function pointer
  function<int(int, int)> f2 = divide(); // callable class type
  function<int(int, int)> f3 = mult;     // function pointer
  cout << f1(4, 2) << endl;              // prints 6
  cout << f2(4, 2) << endl;              // prints 2
  cout << f3(4, 2) << endl;              // prints 8

  // table of callable objects corresponding to each binary operator
  // all the callables must take two ints and return an int
  // an element can be a function pointer, function object, or lambda
  map<string, function<int(int, int)>> binops;
  binops.insert(make_pair(string("+"), add)); // function pointer
  binops.insert(
      make_pair(string("-"), std::minus<int>())); // library function object
  binops.insert(
      make_pair(string("/"), divide()));       // user-defined function object
  binops.insert(make_pair(string("*"), mult)); // function pointer
  binops.insert(make_pair(string("%"), mod));  // function pointer

  cout << binops["+"](10, 5) << endl; // calls add(10, 5)
  cout << binops["-"](10, 5)
       << endl; // uses the call operator of the minus<int> object
  cout << binops["/"](10, 5)
       << endl; // uses the call operator of the divide object
  cout << binops["*"](10, 5) << endl; // calls the lambda function object
  cout << binops["%"](10, 5) << endl; // calls the lambda function object

  return 0;
}
