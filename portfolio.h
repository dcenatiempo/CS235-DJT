/***********************************************************************
 * Header:
 *    Portfolio
 * Summary:
 *    This class contains the data about a customers portfolio.
 * Authors:
 *
 ************************************************************************/
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "queue.h"         // for QUEUE
#include "transaction.h"   // for TRANSACTIONS
#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT


using namespace custom;

class Portfolio
{
public:
   Portfolio() { proceeds = 0;};
   ~Portfolio() {};
   void buy(int number, Dollars price);
   void sell(int number, Dollars price);
   void display(std::ostream & out) const;
   Dollars getProceeds() const;
   
private:
   queue <Transaction> holdings;
   queue <Transaction> saleHistory;
   queue <Dollars> proceeds;
   int countShares(queue <Transaction> temp);
};

#endif
