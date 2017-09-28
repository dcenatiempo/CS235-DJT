/***********************************************************************
 * Header:
 *    QUEUE
 * Summary:
 *    This will contain the queue class that is similar to the queue
 *    class, except it is FIFO/LILO
 * Author
 *    Devin Cenatiempo, Justin Fryar, Tyler Austin
 ************************************************************************/

#ifndef queue_h
#define queue_h
#include <new>
#include <iostream>
namespace custom
{
/************************************************
 * queue
 * A class that holds stuff FIFO/LILO
 ***********************************************/
template <class T>
class queue {
private:
   T * data;         // dynamically allocated array of T
   int numPush;      // incremented every time push() called
   int numPop;       // incremented every time pop() called
   int numCapacity;  // how many items the queue can hold
   // returns index of head (front)
   int iHead () const { return numPop % numCapacity; }
   // return index of tail (back)
   int iTail () const { return (numPush - 1) % numCapacity; }
public:
   // constructors and destructors
   queue() {this->numPush = 0; this->numPop = 0; this->numCapacity = 0; this->data = nullptr;}
   queue(int capacity) throw (const char *);
   queue(const queue & rhs) throw (const char *);
   ~queue();
   // standard container interfaces
   int  size()     const { return numPush - numPop;  }
   bool empty()    const { return numPush == numPop; }
   void clear()          { numPush = 0; numPop = 0;  }
   queue & operator = (const queue & rhs) throw (const char *);
   // queue specific methods
   void push(T data) throw (const char *);
   void pop();
   T & front()     throw (const char *);
   T front() const throw (const char *);
   T & back()      throw (const char *);
   T back() const  throw (const char *);
};

/**********************************************
 * queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the queue to capacity
 **********************************************/
template <class T>
queue <T> :: queue(int capacity)
throw (const char *)
{
   this->numPush = 0;
   this->numPop = 0;
   this->numCapacity = capacity;
   // do nothing if there is nothing to do.
   if (numCapacity <= 0)
   {
      this->data = nullptr;
      return;
   }
   // attempt to allocate
   try
      { data = new T[capacity]; }
   catch (std::bad_alloc)
      { throw "ERROR: Unable to allocate buffer"; }
}

/*******************************************
 * queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs)
throw (const char *)
{
   // do nothing if there is nothing to do
   if (rhs.size() == 0)
   {
      numPush = 0;
      numPop = 0;
      numCapacity = 0;
      data = nullptr;
      return;
   }
   // attempt to allocate
   try
      { data = new T[rhs.numCapacity]; }
   catch (std::bad_alloc)
      { throw "ERROR: Unable to allocate buffer"; }
   // copy over the capacity
   numPush = rhs.size();
   numPop = 0;
   numCapacity = rhs.size();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numPush; i++)
      data[i] = rhs.data[ (rhs.iHead() + i) % rhs.numCapacity ];
}

/*******************************************
 * queue :: DECONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: ~queue()
{
   delete [] data;
}
/*******************************************
 * queue :: Assignment
 *******************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs)
throw (const char *)
{
   numPop = 0;
   numPush = rhs.size();
   
   if (size() > numCapacity)
   {
      // attempt to allocate memory
      try
         { data = new T[rhs.size()]; }
      catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate buffer"; }
      numCapacity = numPush;
   }
   for (int i = 0; i < numPush; i++)
      data[i] = rhs.data[ (rhs.iHead() + i) % rhs.numCapacity ];
   return *this;
}

/*****************************************************
 * queue :: PUSH
 * Adds an element to the queue.
 * If the queue is full,
 * then the capacity will be doubled.
 * void --> void
 *****************************************************/
template <class T>
void queue <T> :: push(T data)
throw(const char *)
{
   //---Create New queue:---
   //Checks whether the queue is empty
   if (numCapacity <= 0)
   {
      numPop = 0;
      numCapacity = 1;
      try
         { this->data = new T[1]; }
      catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for queue"; }
   }
   else if (numCapacity == size())
   {
      numCapacity *= 2;
      // attempt to allocate memory
      try
      {
         T * tempData = new T[numCapacity];
         // copy data to a new, larger array
         for (int i = iHead(); i < (iHead()+size()); i++)
         {
            if (i< numCapacity/2)
               tempData[i % numCapacity] = this->data[i];
            else tempData[i % numCapacity] = this->data[(i-numCapacity/2)%(numCapacity/2)];
         }
         
         // save data to correct location
         delete [] this->data;
         this->data = tempData;
      }
      catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for queue"; }
   }
   
   //---Add Element to queue:---
   //attempt to allocate memory
   numPush++;
   this->data[iTail()] = data;
   
   //std::cerr << "elements: " << size() << "/" << numCapacity << std::endl;
   //std::cerr << "push: " << numPush << ", pop: " << numPop << std::endl;
   //std::cerr << "iHead: " << this->data[iHead()] << " at index " << iHead() << std::endl;
   //std::cerr << " iTail: " << this->data[iTail()] << " at index " << iTail() << std::endl;
}
   
/*****************************************************
 * queue :: POP
 * Removes an element from the end of the queue,
 * serving to reduce the size by one.
 * void --> void
 *****************************************************/
template <class T>
void queue <T> :: pop()
{
   // if the queue is empty, there is nothing to do.
   if(size() == 0 || numCapacity <= 0)
      return;
   else
      numPop++;
}

/*****************************************************
 * queue :: BACK
 * Returns the element currently
 * at the end of the queue.
 * A non-constant method which returns by-reference.
 * void --> Object Reference
 *****************************************************/
template <class T>
T & queue <T> :: back()
throw (const char *)
{
   // if the queue is empty, throw an error.
   if(size() == 0 || numCapacity <= 0)
      throw "ERROR: attempting to access an element in an empty queue";
   return data[ iTail() ];
}

/*****************************************************
 * queue :: BACK - CONST
 * Returns the element currently
 * at the end of the queue.
 * A constant method which returns const by-reference.
 * void --> Object
 *****************************************************/
template <class T>
T queue <T> :: back() const
throw (const char *)
{
   // if the queue is empty, throw an error.
   if(size() == 0 || numCapacity <= 0)
      throw "ERROR: attempting to access an element in an empty queue";
   return data[ iTail() ];
}

/*****************************************************
 * queue :: FRONT
 * Returns the element at front of queue
 * A non-constant method which returns by-reference.
 * void --> Object Reference
 *****************************************************/
template <class T>
T & queue <T> :: front()
throw (const char *)
{
   // if the queue is empty, throw an error.
   if(size() == 0 || numCapacity <= 0)
      throw "ERROR: attempting to access an element in an empty queue";
   return data[ iHead() ];
}

/*****************************************************
 * queue :: FRONT - CONST
 * Returns the element at front of queue
 * A constant method which returns const by-reference.
 * void --> Object
 *****************************************************/
template <class T>
T queue <T> :: front() const
throw (const char *)
{
   // if the queue is empty, throw an error.
   if(size() == 0 || numCapacity <= 0)
      throw "ERROR: attempting to access an element in an empty queue";
   return data[ iHead() ];
}
   
}; // end custom namespace
#endif /* queue_h */
