#ifndef QUEUELST_HPP
#define QUEUELST_HPP

#include "../queue.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class QueueLst:
virtual public Queue<Data>,
virtual protected List<Data>{
// Must extend Queue<Data>, List<Data>

private:

protected:

public:

  // Default constructor
  QueueLst() = default;

  // Specific constructor
  QueueLst(const TraversableContainer<Data>& container): List<Data>(container) {}; // A stack obtained from a TraversableContainer
  QueueLst(MappableContainer<Data>&& container): List<Data>(std::move(container)) {}; // A stack obtained from a MappableContainer

  // Copy constructor
  QueueLst(const QueueLst& queue): List<Data>(queue) {};

  // Move constructor
  QueueLst(QueueLst&& queue): List<Data>(std::move(queue)) {};

  // Destructor
  ~QueueLst() = default;

  // Copy assignment
  QueueLst& operator=(const QueueLst&);

  // Move assignment
  QueueLst& operator=(QueueLst&&);

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  inline bool operator!=(const QueueLst&) const noexcept;

  // Specific member functions (inherited from Queue)
  inline const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  inline Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  inline void Enqueue(Data&&) override; // Override Queue member (move of the value)

  // Specific member function (inherited from ClearableContainer)
  using List<Data>::Clear;

};

}

#include "queuelst.cpp"

#endif
