/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "portfolio.h"
using namespace std;
using namespace custom;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // your code here...
   Portfolio myPortfolio;
   string instruction;
   int qty;
   Dollars price;
   try
   {
      do
      {
         cout << " > ";
         cin  >> instruction;
         if (instruction == "buy")
         {
            //need to add validation/error handling
            cin >> qty;
            cin >> price;
            myPortfolio.buy(qty, price);
         }
         else if (instruction == "sell")
         {
            //need to add validation/error handling
            cin >> qty;
            cin >> price;
            myPortfolio.sell(qty, price);
         }
         else if (instruction == "display")
         {
            myPortfolio.display(cout);
            
         }
         else if (instruction == "quit")
         {
            break;
         }
         else
         {
            cout << "Invalid command\n";
            cin.ignore(1000,'\n');
            cin.clear();
         }
      }
      while (instruction != "quit");
   }
   catch (const char * error)
   {
      cout << error << endl;
   }

}


