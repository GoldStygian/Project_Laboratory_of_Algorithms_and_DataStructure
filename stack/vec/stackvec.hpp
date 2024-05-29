#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#include "../stack.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class StackVec:
virtual public Stack<Data>,
virtual protected Vector<Data>{
//Must extend Stack<Data>, Vector<Data>

private:

protected:

    ulong index = 0;
    using Vector<Data>::size;
    using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec(): Vector<Data>(1) {};

  // Specific constructor
  StackVec(const TraversableContainer<Data>& container): Vector<Data>(container), index(size) {}; // A stack obtained from a TraversableContainer
  StackVec(MappableContainer<Data>&& container): Vector<Data>(std::move(container)), index(size) {}; // A stack obtained from a MappableContainer

  // Copy constructor
  StackVec(const StackVec& SV): Vector<Data>(SV), index(SV.index){};

  // Move constructor
  StackVec(StackVec&& SV);

  // Destructor
  ~StackVec() = default;

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&);

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  inline bool operator!=(const StackVec&) const noexcept;

  // Specific member functions (inherited from Stack)
  inline const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline void Pop() override; // Override Stack member (must throw std::length_error when empty)
  inline Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  inline void Push(const Data&) override; // Override Stack member (copy of the value)
  inline void Push(Data&&) override; // Override Stack member (move of the value)

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override; // Override Container member

  inline ulong Size() const noexcept override; // Override Container member

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member

protected:

    void Reduce();
    void Expand();

};

}

#include "stackvec.cpp"

#endif
