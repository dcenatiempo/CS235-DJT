/**********************************
 * some code which may come in handy...
 *********************************/


#ifdef DEBUG
using std::cerr;
using std::endl;
/*******************************************************
 * debug display
 *******************************************************/
template <class T>
void queue <T> :: display() const
{
   // display the contents of the array
   cerr << "data = ";
   for (int i = 0; i < numCapacity; i++)
   {
      if (iHead() > iTail() && (i <= iTail() || i >= iHead()))
         cerr << data[i] <<  ' ';
      else if (iHead() <= iTail() && i >= iHead() && i <= iTail())
         cerr << data[i] << ' ';
      else
         cerr << "? ";
   }
   cerr << endl;

   // display the contents of the member variables
   cerr << "numPush     " << numPush << endl;
   cerr << "numPop      " << numPop  << endl;
   cerr << "numCapacity " << numCapacity << endl;

   // display the contents of the header and tail
   if (numCapacity)
   {
      cerr << "iHead()     " << iHead() << endl;
      cerr << "iTail()     " << iTail()  << endl;
   }
}
#else
template <class T>
void queue <T> :: display() const
{
}
#endif // DEBUG
