/***********************************************************************
 * Header:
 *    Transaction
 * Summary:
 *    This class contains the implementation of transactions.
 * Authors:
 *
 ************************************************************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

class Transaction
{
public:
   Transaction() {
      this->qty = 1;
      this->price = 1;
   }
   Transaction(int qty, Dollars price) {
      this->qty = qty;
      this->price = price;
   }
   Transaction(const Transaction & rhs) {
      qty = rhs.qty;
      price = rhs.price;
   }
   
   // Gets the count of remaining shares bought in this transaction;
   // this can't be added to, but shares can be sold
   int getQty() const { return qty; }
   
   // Get share price (share price can't be changed once set at creation time)
   // only read
   Dollars getPrice() const { return price; }
   
   
   // Gets the profit for this transaction
   Dollars getProfit() const;
   
   // Sells a subset of the shares, reducing the share count by the
   // amount sold; returns the number of shares sold - in case
   // a caller tries to sell more shares than available
   Transaction sellShares(int in_sellCount, Dollars in_salePrice);
   
   // Displays the transaction
   void display(std::ostream & out) const;
   
private:
   int qty;       // number of shares
   Dollars price; // +sold -bought

};

std::ostream & operator << (std::ostream & out, const Transaction & rhs);

#endif // !TRANSACTION_H
