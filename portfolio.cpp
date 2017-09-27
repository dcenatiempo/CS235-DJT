//
//  portfolio.cpp
//  project03
//
//  Created by Devin Cenatiempo on 9/27/17.
//  Copyright © 2017 Devin Cenatiempo. All rights reserved.
//

#include "portfolio.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
//using namespace std;
using namespace custom;

/* private variables
 queue <Transaction> holdings;
 queue <Transaction> saleHistory;
 queue <Dollars> proceeds;
 */
int Portfolio :: countShares(queue <Transaction> temp){
   int count = 0;
   int size = temp.size();
   for (int i = 0; i < size; i++ )
   {
      count += temp.front().getQty();
      temp.pop();
   }
   return count;
}
Dollars Portfolio::getProceeds() const{
   queue <Dollars> proceedsQueue = proceeds;
   Dollars totalProceeds = 0;
   for (int i = 0; i < proceeds.size(); i++)
   {
      totalProceeds += proceedsQueue.front();
      proceedsQueue.pop();
   }
   return totalProceeds;
}

void Portfolio :: buy(int qty, Dollars price)
{
   holdings.push(Transaction(qty, price));
}

void Portfolio :: sell(int qty, Dollars price)
{
   Dollars cost = 0;
   Dollars rev = price * qty;
   int tempQty = qty;
   int total = countShares(holdings);
   if (qty > total)
   {
      cout << "Error: Cannot sell more shares than you own!\n";
      cout << "You only have " << total << " shares to sell\n";
   }
   else
   {
      saleHistory.push(Transaction(qty, price));
      while (tempQty)
      {
         if (holdings.front().getQty() <= tempQty)
         {
            cost += holdings.front().getPrice() * holdings.front().getQty();
            tempQty -= holdings.front().getQty();
            holdings.pop();
            
         }
         else if (holdings.front().getQty() > tempQty)
         {
            cost += holdings.front().getPrice() * tempQty;
            holdings.front() = Transaction(holdings.front().getQty() - tempQty, holdings.front().getPrice());
            tempQty = 0;
         }
      }
      proceeds.push(rev-cost);
   }
}

void Portfolio :: display(std::ostream & out) const
{
   cout << "Currently held:\n";
   if (holdings.size() > 0)
   {
      queue <Transaction> tempHoldings = holdings;
      for (int i = 0; i < holdings.size(); i++)
      {
         cout << "\tBought " << tempHoldings.front().getQty() << " shares at " << tempHoldings.front().getPrice() << endl;
         tempHoldings.pop();
      }
      //Bought 20 shares at $1.75
   }
   if (saleHistory.size() > 0)
   {
      cout << "Sell History:\n";
      queue <Transaction> tempSales = saleHistory;
      queue <Dollars> tempProceeds = proceeds;
      for (int i = 0; i < saleHistory.size(); i++)
      {
         cout << "\tSold " << tempSales.front().getQty() << " shares at " << tempSales.front().getPrice() << " for a profit of " << tempProceeds.front() << endl;
         tempSales.pop();
         tempProceeds.pop();
      }
      //Sold 2 shares at $2.00 for a profit of $1.00
   }
   cout << "Proceeds: " << getProceeds();
   cout << endl;
   //Proceeds: $1.00
}

std::ostream & operator << (std::ostream & out, const Portfolio & rhs)
{
   return out;
}
