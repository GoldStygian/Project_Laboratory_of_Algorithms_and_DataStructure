#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeVec: virtual public MutableBinaryTree<Data>{ // Must extend MutableBinaryTree<Data>

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeVec: virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

    private:

    protected:

    public:
      Vector<NodeVec*> *ptrVec = nullptr;
      Data element {};
      ulong pos {};

      //copy costruttore
      NodeVec(const Data &, ulong, Vector<NodeVec*>*);

      //Move costruttore
      NodeVec(Data&&, ulong, Vector<NodeVec*>*);

      //Distrtuttore
      ~NodeVec();

      Data& Element() noexcept override;
      const Data& Element() const noexcept override;

      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;

      const NodeVec& LeftChild() const override;
      const NodeVec& RightChild() const override;

      NodeVec& LeftChild() override;
      NodeVec& RightChild() override;

  };

  Vector<NodeVec*> vec; //size 0

public:

  // Default constructor
  BinaryTreeVec() = default;

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&&); // A binary tree obtained from a MappableContainer

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&);

  // Destructor
  ~BinaryTreeVec();

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&);

  // Comparison operators
  inline bool operator==(const BinaryTreeVec&) const noexcept;
  inline bool operator!=(const BinaryTreeVec&) const noexcept;

  // Specific member functions (inherited from BinaryTree)
  //const BinaryTree<Data>::Node& Root() const override; // Override BinaryTree member (throw std::length_error when empty)
  const NodeVec& Root() const override;

  // Specific member function (inherited from MutableBinaryTree)
  //MutableBinaryTree<Data>::MutableNode& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)
  NodeVec& Root() override;

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member
  
  // Specific member function (inherited from BreadthTraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

  // Specific member function (inherited from BreadthMappableContainer
  using typename MappableContainer<Data>::MapFun;
  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!
  void BreadthTraverse(TraverseFun, NodeVec&) const;
  void BreadthMap(MapFun, NodeVec&);

};

}

#include "binarytreevec.cpp"

#endif
