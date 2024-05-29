#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>

#include "testable.hpp"

namespace lasd {

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data>{ // Must extend TestableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TraversableContainer& operator=(TraversableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const TraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.
  bool operator!=(const TraversableContainer&) const noexcept = delete; // Comparison of abstract types might be possible.

  // Specific member function
  //alias per una funzione che dovrebbe specificare come scorrere i dati una sola volta
  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0; //funzione che scorre tutta la struttura dati

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const; //fa operaioni sui dati

  // Specific member function (inherited from TestableContainer)
  inline virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data>{ // Must extend TraversableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default; 

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(PreOrderTraversableContainer&) const = delete; // Comparison of abstract types might be possible.
  bool operator!=(PreOrderTraversableContainer&) const = delete; // Comparison of abstract types might be possible.

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  /*Quindi, l’istruzione using typename TraversableContainer<Data>::TraverseFun; 
  sta dicendo al compilatore di C++ che TraversableContainer<Data>::TraverseFun 
  è un tipo e che dovrebbe essere accessibile nel contesto corrente senza dover 
  utilizzare il nome completo
  */

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  // Specific member function (inherited from TraversableContainer)
  inline virtual void Traverse(TraverseFun) const override = 0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data>{ // Must extend TraversableContainer<Data>

private:

protected:

public:

virtual ~PostOrderTraversableContainer() = default; 

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(PostOrderTraversableContainer&) const = delete; // Comparison of abstract types might be possible.
  bool operator!=(PostOrderTraversableContainer&) const = delete; // Comparison of abstract types might be possible.

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  /*Quindi, l’istruzione using typename TraversableContainer<Data>::TraverseFun; 
  sta dicendo al compilatore di C++ che TraversableContainer<Data>::TraverseFun 
  è un tipo e che dovrebbe essere accessibile nel contesto corrente senza dover 
  utilizzare il nome completo
  */

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  // Specific member function (inherited from TraversableContainer)
  inline virtual void Traverse(TraverseFun) const override = 0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer : virtual public TraversableContainer<Data>{// Must extend TraversableContainer<Data>

private:


protected:

public:

  // Destructor
  virtual ~InOrderTraversableContainer() = default;

  // Copy assignment
  InOrderTraversableContainer& operator=(const InOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  InOrderTraversableContainer& operator=(InOrderTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const InOrderTraversableContainer&) = delete; // Comparison of abstract types might be possible.
  bool operator!=(const InOrderTraversableContainer&) = delete; // Comparison of abstract types might be possible.

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;

  virtual void InOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator InOrderFold(FoldFun<Accumulator>, Accumulator) const;

  // Specific member function (inherited from TraversableContainer)
  inline virtual void Traverse(TraverseFun) const override = 0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer : virtual public TraversableContainer<Data>{ // Must extend TraversableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~BreadthTraversableContainer() = default;

  // Copy assignment
  BreadthTraversableContainer& operator=(const BreadthTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BreadthTraversableContainer& operator=(BreadthTraversableContainer&&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const BreadthTraversableContainer&) = delete; // Comparison of abstract types might be possible.
  bool operator!=(const BreadthTraversableContainer&) = delete; // Comparison of abstract types might be possible.

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;

  virtual void BreadthTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator BreadthFold(FoldFun<Accumulator>, Accumulator) const;

  // Specific member function (inherited from TraversableContainer)
  inline virtual void Traverse(TraverseFun) const override = 0; // Override TraversableContainer member

};

}

#include "traversable.cpp"

#endif