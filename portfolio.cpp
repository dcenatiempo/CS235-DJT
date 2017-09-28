/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include "portfolio.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios;
using namespace custom;

/* private variables
 queue <Transaction> holdings;
 queue <Transaction> saleHistory;
 queue <Dollars> proceeds;
 */

/*****************************************************
 * PORTFOLIO :: COUNTSHARES
 * returns total # of shares in a Transaction queue
 * queue <Transaction> --> int
 *****************************************************/
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

/*****************************************************
 * PORTFOLIO :: GETPROCEEDS
 * returns total of proceeds from proceeds queue
 * void --> Dollars
 *****************************************************/
Dollars Portfolio::getProceeds() const
{
   queue <Dollars> proceedsQueue = proceeds;
   Dollars totalProceeds = 0;
   for (int i = 0; i < proceeds.size(); i++)
   {
      totalProceeds += proceedsQueue.front();
      proceedsQueue.pop();
   }
   return totalProceeds;
}

/*****************************************************
 * PORTFOLIO :: BUY
 * Adds a transaction to the holdings queue
 * int, Dollars --> void
 *****************************************************/
void Portfolio :: buy(int qty, Dollars price)
{
   holdings.push(Transaction(qty, price));
}

/*****************************************************
 * PORTFOLIO :: SELL
 * Sells specified stocks in portfolio
 * Adds transaction(s) to salesHistory queue
 * Mutates/Removes transaction(s) from holdings queue
 * int, Dollars --> void
 *****************************************************/
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
         // If selling more than what is contained in first item
         //   in holdings que, then completely remove that transaction
         //   and contine the loop
         if (purchaseQty <= tempQty)
         {
            cost = purchasePrice * purchaseQty;
            rev = salesPrice*purchaseQty;
            tempQty -= purchaseQty; // if these are equal, then loop ends
            holdings.pop();
            saleHistory.push(Transaction(purchaseQty, salesPrice));
            proceeds.push(rev-cost);
         }
         // if this condition is met, then loop ends
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

/*****************************************************
 * PORTFOLIO :: DISPLAY
 * Displays contents of portfolio
 * ostream --> void
 *****************************************************/
void Portfolio :: display(std::ostream & out) const
{
   if (holdings.size() > 0)
   {
      cout << "Currently held:\n";
      queue <Transaction> tempHoldings = holdings;
      for (int i = 0; i < holdings.size(); i++)
      {
         cout << "\tBought " << tempHoldings.front().getQty()
              << " shares at " << tempHoldings.front().getPrice() << endl;
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
         cout << "\tSold " << tempSales.front().getQty()
              << " shares at " << tempSales.front().getPrice()
              << " for a profit of " << tempProceeds.front() << endl;
         tempSales.pop();
         tempProceeds.pop();
      }
      //Sold 2 shares at $2.00 for a profit of $1.00
   }
   cout << "Proceeds: " << getProceeds() << endl;
   //Proceeds: $1.00
}
