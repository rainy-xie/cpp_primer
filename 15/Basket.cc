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

#include "Basket.h"
#include "Quote.h"

#include <cstddef>
using std::size_t;

#include <set>
using std::multiset;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <tr1/memory>
using std::tr1::shared_ptr;

// debugging routine to check contents in a Basket
void Basket::display(ostream &os) const {
  os << "Basket size: " << items.size() << endl;

  // print each distinct ISBN in the Basket along with
  // count of how many copies are ordered and what their price will be
  // upper_bound returns an iterator to the next item in the set
  for (multiset<shared_ptr<Quote>>::iterator next_item = items.begin();
       next_item != items.end(); next_item = items.upper_bound(*next_item)) {
    // we know there's at least one element with this key in the Basket
    os << (*next_item)->isbn() << " occurs " << items.count(*next_item)
       << " times"
       << " for a price of " << (*next_item)->net_price(items.count(*next_item))
       << endl;
  }
}

double Basket::total_receipt(ostream &os) const {
  double sum = 0.0; // holds the running total

  // iter refers to the first element in a batch of elements with the same ISBN
  // upper_bound returns an iterator to the element just past the end of that
  // batch
  for (multiset<shared_ptr<Quote>>::iterator iter = items.begin();
       iter != items.end(); iter = items.upper_bound(*iter)) {
    // we know there's at least one element with this key in the Basket
    // print the line item for this book
    sum += print_total(os, **iter, items.count(*iter));
  }
  os << "Total Sale: " << sum << endl; // print the final overall total
  return sum;
}
