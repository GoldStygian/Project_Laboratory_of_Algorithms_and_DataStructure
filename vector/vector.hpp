#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <string>
#include "../container/container.hpp"
#include "../container/linear.hpp"

namespace lasd {

template <typename Data>
class Vector :
virtual public ResizableContainer,
virtual public LinearContainer<Data>{
// Must extend ResizableContainer, LinearContainer<Data>

private:

protected:

  using Container::size;
  Data * Elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  // Specific constructors
  Vector(const ulong); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&&);

  // Destructor
  ~Vector();

  // Copy assignment
  Vector& operator=(const Vector&);

  // Move assignment
  Vector& operator=(Vector&&);

  // Comparison operators
  bool operator==(const Vector&) const noexcept;
  bool operator!=(const Vector&) const noexcept;
  bool operator<(const Vector&) const noexcept; //only for test
  bool operator>(const Vector&) const noexcept; //only for test

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; // Override ClearableContainer member

  // Specific member function (inherited from ResizableContainer)
  void Resize(const ulong) override; // Override ResizableContainer member

  // Specific member functions (inherited from LinearContainer)
  const Data& operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const ulong) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

};

template <typename Data>
class SortableVector:
virtual public Vector<Data>,
virtual public SortableLinearContainer<Data>{
// Must extend Vector<Data>, SortableLinearContainer<Data>

private:

protected:

  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  // Specific constructors
  SortableVector(const ulong); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  // Comparison operators
  bool operator==(const SortableVector&) const noexcept;
  bool operator!=(const SortableVector&) const noexcept;

  // Destructor
  ~SortableVector() = default;

  // Copy constructor
  SortableVector(const SortableVector&);

  // Move constructor
  SortableVector(SortableVector&&);

  // Copy assignment
  SortableVector& operator=(const SortableVector&);

  // Move assignment
  SortableVector& operator=(SortableVector&&);

};

}
#include "vector.cpp"

#endif
