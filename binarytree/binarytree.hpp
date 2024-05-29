#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"

#include "../queue/vec/queuevec.hpp"
//#include "../queue/lst/queuelst.hpp"

namespace lasd {

template <typename Data>
class BinaryTree:
virtual public PreOrderTraversableContainer<Data>,
virtual public PostOrderTraversableContainer<Data>,
virtual public InOrderTraversableContainer<Data>,
virtual public BreadthTraversableContainer<Data> {

private:

protected:

  using Container::size;

public:

  struct Node {

    protected:

      // Comparison operators
      bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.
      inline bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.

    public:

      // bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.
      // inline bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.

      friend class BinaryTree<Data>;

      // Destructor
      virtual ~Node() = default;

      // Copy assignment
      Node& operator=(const Node&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      Node& operator=(Node&&) = delete; // Move assignment of abstract types is not possible.

      // Specific member functions

      virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

      virtual inline bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
      virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
      virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exception
      virtual const Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
      virtual const Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };


  // Destructor
  virtual ~BinaryTree() = default;

  // Copy assignment
  BinaryTree& operator=(const BinaryTree&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.
  inline bool operator!=(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.

  // Specific member functions
  virtual const Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  // Specific member function (inherited from InOrderTraversableContainer)
  inline void InOrderTraverse(TraverseFun) const override; // Override InOrderTraversableContainer member

  // Specific member function (inherited from BreadthTraversableContainer)
  inline void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions
  void PreOrderTraverse(TraverseFun, const Node&) const;
  void PostOrderTraverse(TraverseFun, const Node&) const;
  void InOrderTraverse(TraverseFun, const Node&) const;
  void BreadthTraverse(TraverseFun, const Node&) const;

};

template <typename Data>
class MutableBinaryTree:
virtual public ClearableContainer,
virtual public BinaryTree<Data>,
virtual public PreOrderMappableContainer<Data>,
virtual public PostOrderMappableContainer<Data>,
virtual public InOrderMappableContainer<Data>,
virtual public BreadthMappableContainer<Data>
{
// Must extend ClearableContainer,
//             BinaryTree<Data>,
//             PreOrderMappableContainer<Data>,
//             PostOrderMappableContainer<Data>,
//             InOrderMappableContainer<Data>,
//             BreadthMappableContainer<Data>

private:

protected:

public:

  struct MutableNode: virtual public BinaryTree<Data>::Node {// Must extend Node

    friend class MutableBinaryTree<Data>;

    // Destructor
    virtual ~MutableNode() = default;

    // Copy assignment
    MutableNode& operator=(const MutableNode&) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode& operator=(MutableNode&&) = delete; // Move assignment of abstract types is not possible.

    // Specific member functions
    using BinaryTree<Data>::Node::RightChild;
    using BinaryTree<Data>::Node::LeftChild;
    using BinaryTree<Data>::Node::Element;

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
    
    virtual MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  // Destructor
  virtual ~MutableBinaryTree() = default;

  // Copy assignment
  MutableBinaryTree& operator=(const MutableBinaryTree&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableBinaryTree& operator=(MutableBinaryTree&&) = delete; // Move assignment of abstract types is not possible.

  // Specific member functions
  using BinaryTree<Data>::Root;
  virtual MutableNode& Root() = 0; // (concrete function must throw std::length_error when empty)

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override; // Override MappableContainer member

  // Specific member function (inherited from PreOrderMappableContainer)
  inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  // Specific member function (inherited from InOrderMappableContainer)
  inline void InOrderMap(MapFun) override; // Override InOrderMappableContainer member

  // Specific member function (inherited from BreadthMappableContainer)
  inline void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  void PreOrderMap(MapFun, MutableNode&);
  void PostOrderMap(MapFun, MutableNode&);
  void InOrderMap(MapFun, MutableNode&);
  void BreadthMap(MapFun, MutableNode&);

};

template <typename Data>
class BTPreOrderIterator:
virtual public ForwardIterator<Data>,
virtual public ResettableIterator<Data>
{
// Must extend ForwardIterator<Data>,
//             ResettableIterator<Data>

private:

protected:

  const struct BinaryTree<Data>::Node* root = nullptr;

  const struct BinaryTree<Data>::Node* current = nullptr;
  StackVec<const struct BinaryTree<Data>::Node*> stk; //C.Default

public:

  BTPreOrderIterator() = default;

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&&);

  // Destructor
  virtual ~BTPreOrderIterator();

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator&);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&&);

  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept;
  inline bool operator!=(const BTPreOrderIterator&) const noexcept;

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator)
  
  BTPreOrderIterator& operator++(); // (throw std::out_of_range when terminated)

  // Specific member functions (inherited from ForwardIterator)

  void Reset() noexcept; // (should not throw exceptions)

};

template <typename Data>
class BTPreOrderMutableIterator:
virtual public MutableIterator<Data>,
virtual public BTPreOrderIterator<Data>
 {
  // Must extend MutableIterator<Data>,
  //             BTPreOrderIterator<Data>

private:

protected:

  // struct MutableBinaryTree<Data>::MutableNode* current = nullptr;
  // StackVec<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTPreOrderMutableIterator(BinaryTree<Data>& tree): BTPreOrderIterator<Data>(tree){}// An iterator over a given mutable binary tree

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator& itr): BTPreOrderIterator<Data>(itr){};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&& itr): BTPreOrderIterator<Data>(std::move(itr)){};

  // Destructor
  ~BTPreOrderMutableIterator() = default; //implementato ni BTPreOrderIterator

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&);

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&);

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator&) const noexcept;
  bool operator!=(const BTPreOrderMutableIterator&) const noexcept;

  // Specific member functions (inherited from MutableIterator)
  Data& operator*(); // (throw std::out_of_range when terminated)

  void Test(){
    if (this->current == nullptr) std::cout<<"current null\n";
    else std::cout<<"current :"<<this->current->Element()<<"\n";

    // if (root == nullptr) std::cout<<"root null\n";
    // else std::cout<<"root :"<<root->Element()<<"\n";
  }

};

template <typename Data>
class BTPostOrderIterator:
virtual public ForwardIterator<Data>,
virtual public ResettableIterator<Data>
{
// Must extend ForwardIterator<Data>,
//             ResettableIterator<Data>

private:

  void getMostLeftLeaf();
  // funzione che scorre tutta l'albero per ottenere
  // la foglia più a sinistra 

protected:

  const struct BinaryTree<Data>::Node* root = nullptr;

  const struct BinaryTree<Data>::Node* current = nullptr;
  StackVec<const struct BinaryTree<Data>::Node*> stk;

public:

  BTPostOrderIterator() = default;

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator&);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&&);

  // Destructor
  virtual ~BTPostOrderIterator();

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator&);

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator&&);

  // Comparison operators
  bool operator==(const BTPostOrderIterator&) const noexcept;
  inline bool operator!=(const BTPostOrderIterator&) const noexcept;

  // Specific member functions (inherited from Iterator)
  const Data& operator*() const; // (throw std::out_of_range when terminated)
  inline bool Terminated() const noexcept; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator)
  BTPostOrderIterator& operator++(); // (throw std::out_of_range when terminated)

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept; // (should not throw exceptions)

};

template <typename Data>
class BTPostOrderMutableIterator:
virtual public MutableIterator<Data>,
virtual public BTPostOrderIterator<Data>
{
  // Must extend MutableIterator<Data>,
  //             BTPostOrderIterator<Data>

private:

protected:

  // struct MutableBinaryTree<Data>::MutableNode* current = nullptr;
  // StackVec<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTPostOrderMutableIterator(BinaryTree<Data>& tree): BTPostOrderIterator<Data>(tree){}; // An iterator over a given mutable binary tree

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator& itr): BTPostOrderIterator<Data>(itr){};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& itr): BTPostOrderIterator<Data>(std::move(itr)){};

  // Destructor
  ~BTPostOrderMutableIterator() = default;

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&);

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&);

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator&) const noexcept;
  bool operator!=(const BTPostOrderMutableIterator&) const noexcept;

  // Specific member functions (inherited from MutableIterator)

  Data& operator*(); // (throw std::out_of_range when terminated)

};

template <typename Data>
class BTInOrderIterator:
virtual public ForwardIterator<Data>,
virtual public ResettableIterator<Data>
{
// Must extend ForwardIterator<Data>,
//             ResettableIterator<Data>

private:

  void getMostLeftNode();

protected:

  const struct BinaryTree<Data>::Node* root = nullptr;

  const struct BinaryTree<Data>::Node* current = nullptr;
  StackVec<const struct BinaryTree<Data>::Node*> stk;

public:

  BTInOrderIterator() = default;

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator&);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&&);

  // Destructor
  virtual ~BTInOrderIterator();

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator&);

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&&);

  // Comparison operators
  bool operator==(const BTInOrderIterator&) const noexcept;
  bool operator!=(const BTInOrderIterator&) const noexcept;

  // Specific member  functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator& operator++(); // (throw std::out_of_range when terminated)

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept; // (should not throw exceptions)

};

template <typename Data>
class BTInOrderMutableIterator:
virtual public MutableIterator<Data>,
virtual public BTInOrderIterator<Data>
{
  // Must extend MutableIterator<Data>,
  //             BTInOrderIterator<Data>

private:

protected:

  // struct MutableBinaryTree<Data>::MutableNode* current = nullptr;
  // StackVec<struct MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTInOrderMutableIterator(BinaryTree<Data>& tree): BTInOrderIterator<Data>(tree){}; // An iterator over a given mutable binary tree

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator& itr): BTInOrderIterator<Data>(itr){};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator&& itr): BTInOrderIterator<Data>(std::move(itr)){};

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator&);

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&&);

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator&) const noexcept;
  bool operator!=(const BTInOrderMutableIterator&) const noexcept;

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

template <typename Data>
class BTBreadthIterator:
virtual public ForwardIterator<Data>,
virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

protected:

  const struct BinaryTree<Data>::Node* root = nullptr;

  //const struct BinaryTree<Data>::Node* current = nullptr;
  QueueVec<const struct BinaryTree<Data>::Node*> queue;

public:

  BTBreadthIterator() = default;

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&&);

  // Destructor
  virtual ~BTBreadthIterator();

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator&);

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator&&);

  // Comparison operators
  bool operator==(const BTBreadthIterator&) const noexcept;
  bool operator!=(const BTBreadthIterator&) const noexcept;

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator& operator++(); // (throw std::out_of_range when terminated)

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept; // (should not throw exceptions)

};

template <typename Data>
class BTBreadthMutableIterator: 
virtual public MutableIterator<Data>,
virtual public BTBreadthIterator<Data>
{
  // Must extend MutableIterator<Data>,
  //             BTBreadthIterator<Data>

private:

protected:

  // struct MutableBinaryTree<Data>::MutableNode* current = nullptr;
  // QueueVec<struct MutableBinaryTree<Data>::MutableNode*> queue;

public:

  // Specific constructors
  BTBreadthMutableIterator(BinaryTree<Data>& tree): BTBreadthIterator<Data>(tree){}; // An iterator over a given mutable binary tree

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator& itr): BTBreadthIterator<Data>(itr){};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator&& itr): BTBreadthIterator<Data>(std::move(itr)){};

  // Destructor
  ~BTBreadthMutableIterator() = default;

  // Copy assignment
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator&);

  // Move assignment
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&&);

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator&) const noexcept;
  bool operator!=(const BTBreadthMutableIterator&) const noexcept;

  // Specific member functions (inherited from MutableIterator)

  Data& operator*(); // (throw std::out_of_range when terminated)

};

}

#include "binarytree.cpp"

#endif
