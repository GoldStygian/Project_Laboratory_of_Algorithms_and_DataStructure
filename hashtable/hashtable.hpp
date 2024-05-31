#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <random>

#include "../container/dictionary.hpp"

#define MIN_SIZE 101
#define RESIZE_FACTOR 2

namespace lasd {

template <typename Data>
class Hashable {

public:

  ulong operator()(const Data&) noexcept; // (concrete function should not throw exceptions)

};

template <typename Data>
class HashTable: 
virtual public ResizableContainer,
virtual public DictionaryContainer<Data>
{
// Must extend ResizableContainer,
//             DictionaryContainer<Data>

private:

protected:

  using DictionaryContainer<Data>::size; //#elementi
  ulong M {0}; // perche Size() ritorna il numero di elementi non M

public:

  // Destructor
  ~HashTable() = default;

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

  virtual void debug(){ //del
    
    std::cout<<"#element: "<<size<<" alloc (M): "<<M<<"\n";

  }

protected:

  // Auxiliary member functions

  virtual ulong HashKey(const Data&) const;

};

}

#include "hashtable.cpp"

#endif
