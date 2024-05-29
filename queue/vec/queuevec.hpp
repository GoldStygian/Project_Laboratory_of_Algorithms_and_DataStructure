#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class QueueVec:
virtual public Queue<Data>,
virtual protected Vector<Data> {
// Must extend Queue<Data>, Vector<Data>

private:

protected:

  //coda circolare
  ulong idHead {0};
  ulong idTail {0};

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  QueueVec(): Vector<Data>(4) {};

  // Specific constructor
  QueueVec(const TraversableContainer<Data>&); // A stack obtained from a TraversableContainer
  QueueVec(MappableContainer<Data>&&); // A stack obtained from a MappableContainer

  // Copy constructor
  QueueVec(const QueueVec& queue): Vector<Data>(queue), idHead(queue.idHead), idTail(queue.idTail) {};

  // Move constructor
  QueueVec(QueueVec&&);

  // Destructor
  ~QueueVec() = default;

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&);

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  inline bool operator!=(const QueueVec&) const noexcept;

  // Specific member functions (inherited from Queue)
  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override; // Override Container member
  inline ulong Size() const noexcept override; // Override Container member

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member

protected:

  void Expand();
  void Reduce();
  void Resize(ulong, ulong);

};

}

#include "queuevec.cpp"

#endif
