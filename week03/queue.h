/***********************************************************************
* Header:
*    QUEUE    
* Summary:
*    This is a template class for Queue as well as related template
*    member functions. This is meant to replicate Queue from Standard
*    as much as possible.
* Author
*    Tyler Aston, Kylor Kersavage, Mathew
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue 
{
 public:
  // Constructos
  Queue();
  Queue(const int& nCap);
  Queue(const Queue<T>& rhs);
  ~Queue();
  
  // Overloading
  Queue<T> & operator=(const Queue& rhs);
  
  // Mutators
  void grow();
  void clear();
  void push(const T & item);
  void pop();
  
  // Accessors 
  bool empty();
  int  capacity();
  int  size();
  T & back();
  T & front();
  
 private:
  //Data
  int numItems;
  int cap;
  T   *data;
  int frontIndex;
  int backIndex;
};

/************************************************************************
* CONSTRUCTOR
* This is where all data is intialized to 0.
************************************************************************/
template <class T>
Queue<T>::Queue()
{
  numItems = 0;
  cap = 0;
  data = new T [cap];
  frontIndex = 0;
  backIndex = 0;
}

/************************************************************************
* NON-CONSTRUCTOR
* This is where all data is intialized to 0 except capacity, which is
* passed as a parameter.
************************************************************************/
template <class T>
Queue<T>::Queue(const int& nCap)
{
  numItems = 0;
  cap = nCap;
  data = new T [cap];
  frontIndex = 0;
  backIndex = 0;
}

/************************************************************************
* COPY CONSTRUCTOR
* This is where all data is intialized from another object. Pointers
* are done with a deep copy.
************************************************************************/
template <class T>
Queue<T>::Queue(const Queue<T>& rhs)
{
  numItems = 0;
  cap = 0;
  numItems = rhs.numItems;
  cap = rhs.cap;
  frontIndex = rhs.frontIndex;
  backIndex = rhs.backIndex;
  
  try
    {
      data = new T [cap];
    }
  catch (std::bad_alloc& ba)
    {
      std::cerr << "ERROR: Unable to allocate a new buffer for Queue." << '\n';
    }
  
  for (int i = frontIndex; i < backIndex; ++i)
    {
      data[i] = rhs.data[i];
    }
}

/************************************************************************
* DESTRUCTOR
* Where any allocated pointer data is freed.
************************************************************************/
template <class T>
Queue<T>::~Queue()
{
  delete[] data;
}

/**********************************************************************
 * OPERATOR OVERLOADING =
 * This deep copies the right object to the left and bounds checking.
 ***********************************************************************/
template <class T>
Queue<T> & Queue<T>::operator=(const Queue& rhs)
{
  numItems = 0;
  cap = 0;
  numItems = rhs.numItems;
  cap = rhs.cap;
  frontIndex = rhs.frontIndex;
  backIndex = rhs.backIndex;
  
  try
    {
      data = new T [cap];
    }
  catch (std::bad_alloc& ba)
    {
      std::cerr << "ERROR: Unable to allocate a new buffer for Queue." << '\n';
    }
  
  for (int i = frontIndex; i < backIndex; ++i)
    {
      data[i] = rhs.data[i];
    }
  
  return *this;
}

/**********************************************************************
 * POP
 * This will change number of items to one less if there is any items
 ***********************************************************************/
template <class T>
void Queue<T>::pop()
{
  if (numItems == 0)
    {
      throw "ERROR: Unable to pop from an empty Queue";
    }
  numItems--;
  frontIndex++;
  // grow();
}

/**********************************************************************
 * FRONT
 * Returns the first item in the Queue if there is any items
 ***********************************************************************/
template <class T>
T & Queue<T>::front()
{
  if (numItems == 0)
    {
      throw "ERROR: Unable to reference the element from an empty Queue";
    }
  return data[frontIndex];
}

/**********************************************************************
 * BACK
 * Returns the last item in the Queue if there is any items
 ***********************************************************************/
template <class T>
T & Queue<T>::back()
{
  if (numItems == 0)
    {
      throw "ERROR: Unable to reference the element from an empty Queue";
    }
  return data[backIndex];
}
/**********************************************************************
 * PUSH
 * This will make sure there is enough space for add an item, then
 * it will put the item onto the top of the Queue.
 ***********************************************************************/
template <class T>
void Queue<T>::push(const T & item)
{
  if (cap <= numItems)
    {
      if (cap == 0)
	{
	  cap = 1;
	}
      else
	cap *= 2;	
      grow();		
    }
  data[numItems] = item;
  numItems++;
}

/**********************************************************************
 * GROW
 * A new array is created to store data so we can then delete data array
 * and re-allocate new memory at greater size and set laction to location
 * of our original data.
 ***********************************************************************/
template <class T>
void Queue<T>::grow()
{
  try
    {
      T * tempPtr = new T [cap];
      if (numItems > 0)
	{        
	  for (int i = 0; i < numItems; ++i)
	    {
	      tempPtr[i] = data[i];
	    }
	  delete[] data;
	}       
      data = tempPtr;  
    }
  catch (std::bad_alloc& ba)
    {
      std::cerr << "ERROR: Unable to allocate a new buffer for Queue." << '\n';
    }    
}

/**********************************************************************
 * CLEAR
 * Returns true if there are no items in the Queue.
 ***********************************************************************/
template <class T>
void Queue<T>::clear()
{
  while (numItems != 0)
    pop();
}

/**********************************************************************
 * EMPTY
 * Returns true if there are no items in the Queue.
 ***********************************************************************/
template <class T>
bool Queue<T>::empty()
{
  if (size() != 0)
    return false;
  else
    return true;
}

/**********************************************************************
 * CAPACITY
 * Simply returns capactiy as an int.
 ***********************************************************************/
template <class T>
int Queue<T>::capacity()
{
  return cap;
}

/**********************************************************************
 * SIZE
 * Simply returns the number of items as an int.
 ***********************************************************************/
template <class T>
int Queue<T>::size()
{
  return numItems;
}

#endif // QUEUE_H