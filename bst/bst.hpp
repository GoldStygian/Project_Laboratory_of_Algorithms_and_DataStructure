#ifndef BST_HPP
#define BST_HPP

#include "../binarytree/lnk/binarytreelnk.hpp"

namespace lasd {

template <typename Data>
class BST:
virtual public ClearableContainer,
virtual public DictionaryContainer<Data>,
virtual public BinaryTree<Data>,
virtual public BinaryTreeLnk<Data>
{


private:

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;


  // Specific constructors
  BST(const TraversableContainer<Data>&); // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data>&&); // A bst obtained from a MappableContainer


  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&);


  // Destructor
  ~BST();

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&);


  // Comparison operators
  bool operator==(const BST&) const noexcept;
  bool operator!=(const BST&) const noexcept;

  // Specific member functions
  Data& Min(); // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  Data& Max(); // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  // Specific member function (inherited from BinaryTree)
  const BinaryTreeLnk<Data>::NodeLnk& Root() const override; // Override BinaryTree member

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

  NodeLnk* RemoveHelper(NodeLnk*, const Data&);
  
  NodeLnk* DeleteNode(NodeLnk*);
  
  NodeLnk* Skip2LeftDel(NodeLnk*);
  
  NodeLnk* Skip2RightDel(NodeLnk*);

  // NodeLnk* Insert(NodeLnk*, const Data&);
  
  /*---------*/

  Data DataNDelete(NodeLnk*);

  // NodeLnk* Detach(argument);
  NodeLnk* DetachMin(NodeLnk*, NodeLnk*);
  NodeLnk* DetachMax(NodeLnk*, NodeLnk*);

  NodeLnk* Skip2Left(NodeLnk*);
  NodeLnk* Skip2Right(NodeLnk*);

  NodeLnk* FindPointerToMin(NodeLnk*) const; // Both mutable & unmutable versions
  NodeLnk* FindPointerToMax(NodeLnk*) const; // Both mutable & unmutable

  NodeLnk* FindPointerToMin(const NodeLnk*) const; // Both mutable & unmutable versions
  NodeLnk* FindPointerToMax(const NodeLnk*) const; // Both mutable & unmutable versions

  //NodeLnk* FindPointerTo(const NodeLnk*, const Data&) const; // Both mutable & unmutable versions

  NodeLnk* FindPointerToPredecessor(NodeLnk*, const Data&, NodeLnk*) const; // unmutable versions
  NodeLnk* FindPointerToSuccessor(NodeLnk*, const Data&, NodeLnk*) const; // unmutable versions
  NodeLnk* FindPointerToPredecessor(NodeLnk*, const Data&, NodeLnk*); // mutable versions
  NodeLnk* FindPointerToSuccessor(NodeLnk*, const Data&, NodeLnk*); // mutable versions

};

}

#include "bst.cpp"

#endif
