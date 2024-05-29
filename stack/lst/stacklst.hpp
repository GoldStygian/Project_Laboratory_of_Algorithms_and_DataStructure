#ifndef STACKLST_HPP
#define STACKLST_HPP

#include "../stack.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class StackLst:
virtual public Stack<Data>,
virtual protected List<Data> {
// Must extend Stack<Data>, List<Data>

private:

protected:

  using List<Data>::size;

public:

  // Default constructor
  StackLst() = default;

  // Specific constructor
  StackLst(const TraversableContainer<Data>& container): List<Data>(container) {}; // A stack obtained from a TraversableContainer
  StackLst(MappableContainer<Data>&& container): List<Data>(std::move(container)) {}; // A stack obtained from a MappableContainer

  // Copy constructor
  StackLst(const StackLst& SL): List<Data>(SL) {};

  // Move constructor
  StackLst(StackLst&& SL): List<Data>(SL) {};

  // Destructor
  ~StackLst() = default;

  // Copy assignment
  StackLst& operator=(const StackLst&);

  // Move assignment
  StackLst& operator=(StackLst&&);

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  inline bool operator!=(const StackLst&) const noexcept;

  // Specific member functions (inherited from Stack)
  inline const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline Data& Top() override; // Override Stack member (mutable version; must throw std::length_error when empty)
  inline void Pop() override; // Override Stack member (must throw std::length_error when empty)
  inline Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  inline void Push(const Data&) override; // Override Stack member (copy of the value)
  inline void Push(Data&&) override; // Override Stack member (move of the value)

  // Specific member function (inherited from ClearableContainer)
  using List<Data>::Clear;

};

}

#include "stacklst.cpp"

#endif
