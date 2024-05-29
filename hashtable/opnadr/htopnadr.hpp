#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

#include "../hashtable.hpp"

#include <cstdio>

namespace lasd {

template <typename Data>
class HashTableOpnAdr: virtual public HashTable<Data> {
// Must extend HashTable<Data>

private:

  void init_perm();
  ulong Probing(const ulong) const;

protected:

  struct Slot{
    
    public:
      bool deleted = false;
      Data element {};
    
      Slot(Slot& slt): deleted(slt.deleted), element(slt.element){}
      Slot(const Data& data): element(data) {};
      Slot(Data&& data){ std::swap(element, data); };

  };

  using HashTable<Data>::size;
  using HashTable<Data>::M;

  Vector<Slot*> hashTable {};
  Vector<ulong> perm {};

public:

  // Default constructor
  HashTableOpnAdr() = default;

  // Specific constructors
  HashTableOpnAdr(const ulong); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data>&); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const ulong, const TraversableContainer<Data>&); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data>&&); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong, MappableContainer<Data>&&); // A hash table of a given size obtained from a MappableContainer

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&);

  // Destructor
  ~HashTableOpnAdr(); 

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&);

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  inline bool operator!=(const HashTableOpnAdr&) const noexcept;

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  // Specific member functions (inherited from ResizableContainer)
  void Resize(const ulong); // Resize the hashtable to a given size

  // Specific member functions (inherited from ClearableContainer)
  void  Clear() override; // Override Container member

  void debug() override{ // del

    // if (perm == nullptr) printf("perm non è inizzializzato\n");
    // else{
    //   printf("Perm verctor:\n");
    //   perm->Traverse(
    //     [](const Data& data){
    //       std::cout<<data<<" ";
    //     }
    //   );
    // printf("\n");
    // }

    std::cout<<"M: "<<M<<" size: "<<size<<"\n";

    ulong slot {0};

    hashTable.Traverse(
      [&slot](const Slot* slt){
       if (slt != nullptr) std::cout<<"["<<slot<<"]: "<<slt->element<<" deleted: "<<slt->deleted<<"\n";
       else std::cout<<"["<<slot<<"]: null\n";
        ++slot;
      }
    );

  }

protected:

  // Auxiliary member functions
  ulong HashKey(const Data&) const override;
  ulong Find(const Data&) const noexcept; // ritorna M se non trovato altrimenti l'indice nella hashTable
  ulong FindEmpty(const Data&);
  // type Remove(argument);

};

}

#include "htopnadr.cpp"

#endif
