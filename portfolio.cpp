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

void Portfolio :: sell(int salesQty, Dollars salesPrice)
{
   Dollars cost = 0;
   Dollars rev = 0;
   int tempQty = salesQty;
   int totalShares = countShares(holdings);
   if (salesQty > totalShares)
   {
      cout << "Error: Cannot sell more shares than you own!\n";
      cout << "You only have " << totalShares << " shares to sell\n";
   }
   else
   {
      while (tempQty)
      {
         int purchaseQty = holdings.front().getQty();
         Dollars purchasePrice = holdings.front().getPrice();
         if (purchaseQty <= tempQty)
         {
            cost = purchasePrice * purchaseQty;
            rev = salesPrice*purchaseQty;
            tempQty -= purchaseQty;
            holdings.pop();
            saleHistory.push(Transaction(purchaseQty, salesPrice));
            proceeds.push(rev-cost);
         }
         else if (purchaseQty > tempQty)
         {
            cost = purchasePrice * tempQty;
            rev = salesPrice*tempQty;
            holdings.front() = Transaction(purchaseQty - tempQty, purchasePrice);
            saleHistory.push(Transaction(tempQty, salesPrice));
            proceeds.push(rev-cost);
            tempQty = 0;
         }
      }

   }
}

void Portfolio :: display(std::ostream & out) const
{
   if (holdings.size() > 0)
   {
      cout << "Currently held:\n";
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
