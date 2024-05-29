#ifndef TESTABLE_HPP
#define TESTABLE_HPP

#include "container.hpp"

namespace lasd {

template <typename Data>
class TestableContainer : virtual public lasd::Container{// Must extend Container

private:

protected:

public:

  // Destructor
  virtual ~TestableContainer() = default;

  // Copy assignment
  // Copy assignment of abstract types is not possible.
  TestableContainer& operator=(const TestableContainer&) = delete;

  // Move assignment
  // Move assignment of abstract types is not possible.
  TestableContainer& operator=(TestableContainer &&) = delete;

  // Comparison operators
  // Comparison of abstract types is not possible.
  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(const TestableContainer&) const noexcept = delete;

  // Specific member function
  // (concrete function should not throw exceptions)
  virtual bool Exists(const Data&) const noexcept = 0;

};

}//name space

#endif
