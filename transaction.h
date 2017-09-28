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

class Transaction
{
public:
   // constructors
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
   
   
private:
   int qty;       // number of shares
   Dollars price; // +sold -bought

};

#endif // !TRANSACTION_H
