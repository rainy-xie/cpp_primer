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

#include <tr1/memory>
using std::tr1::shared_ptr;
// using std::unique_ptr; // not part of TR1

void deleter(int *p) { delete[] p; }

int main() {
  /* unique_ptr is not available in pre-C++ 11 libraries

          // up points to an array of ten uninitialized ints
          unique_ptr<int[]> up(new int[10]);
          for (size_t i = 0; i != 10; ++i)
                  up[i] = i;  // assign a new value to each of the elements
          up.release();   // automatically uses delete[] to destroy its pointer
  */

  // to use a shared_ptr we must supply a deleter
  shared_ptr<int> sp(new int[10], deleter);
  // shared_ptrs don't have subscript operator
  // and don't support pointer arithmetic
  for (size_t i = 0; i != 10; ++i)
    *(sp.get() + i) = i; // use get to get a built-in pointer
  sp.reset();            // uses the function we supplied
                         // that uses delete[] to free the array
}
