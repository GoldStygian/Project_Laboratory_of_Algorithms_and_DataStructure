#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP


#include "../binarytree.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeLnk: virtual public MutableBinaryTree<Data>{ // Must extend MutableBinaryTree<Data>

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk: virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

    private:

    protected:

      friend class BinaryTreeLnk<Data>;
      
      // struct NodeLnk* Sx = nullptr;
      // struct NodeLnk* Dx = nullptr;

    public:
    
      Data element;
      struct NodeLnk* Sx = nullptr;
      struct NodeLnk* Dx = nullptr;

      NodeLnk(const Data&);
      NodeLnk(Data&&);

      ~NodeLnk();
      
      // Specific member functions (MutableBinaryTree & BinaryTree)
      Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
      const Data& Element() const noexcept override;

      bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
      bool HasRightChild() const noexcept override; // (concrete function should not throw exception

      // const typename BinaryTree<Data>::Node& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
      // const typename BinaryTree<Data>::Node& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

      // MutableBinaryTree<Data>::MutableNode& LeftChild() override; //Node& // (concrete function must throw std::out_of_range when not existent)
      // MutableBinaryTree<Data>::MutableNode& RightChild() override; //Node& // (concrete function must throw std::out_of_range when not existent)

      const NodeLnk& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
      const NodeLnk& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

      NodeLnk& LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
      NodeLnk& RightChild() override;
      
  };

  NodeLnk* root = nullptr;
    
  void insert(const Data&);
  void insert(Data&&);
  NodeLnk* copyTree(const NodeLnk*);
  // void copyTree2(const BinaryTreeLnk&);

public:

  // Default constructor
  BinaryTreeLnk() = default;

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&&); // A binary tree obtained from a MappableContainer

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&);

  // Destructor
  ~BinaryTreeLnk();

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&);

  // Comparison operators
  inline bool operator==(const BinaryTreeLnk&) const noexcept;
  inline bool operator!=(const BinaryTreeLnk&) const noexcept;

  // Specific member functions (inherited from BinaryTree)
  const BinaryTree<Data>::Node& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  // Specific member function (inherited from MutableBinaryTree)
  MutableBinaryTree<Data>::MutableNode& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member

};


}

#include "binarytreelnk.cpp"

#endif
