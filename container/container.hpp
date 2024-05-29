#ifndef CONTAINER_HPP
#define CONTAINER_HPP

namespace lasd {

typedef unsigned long ulong;

class Container {

private:

protected:

  ulong size {0};
  Container() = default;

public:

  // Destructor
  ~Container() = default;

  // Copy assignment
  Container& operator=(const Container&) = delete;
  // Copy assignment of abstract types is not possible. Devo conoscere la struttura dati sottostante
  // const perche una copia non modifica i dati
  // con delete elimino la possibilità di assegnamento

  // Move assignment
  Container& operator=(Container &&) = delete; // Move assignment of abstract types is not possible.
  //noexcept??

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types is not possible.

  // Specific member functions
  virtual bool Empty() const noexcept{  // (concrete function should not throw exceptions)
    return (size == 0);
  }

  virtual ulong Size() const noexcept{// (concrete function should not throw exceptions)
    return size;
  }

};

class ClearableContainer : virtual public Container {

private:

protected:

public:

  // Destructor
  ~ClearableContainer() = default;

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete; 
  // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=(ClearableContainer &&) = delete;
  // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const ClearableContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(ClearableContainer &&) const noexcept= delete; // Comparison of abstract types is not possible.

  // Specific member functions
  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer{ // Must extend ClearableContainer

private:

protected:

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&)= delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer& operator=(ResizableContainer &&) = delete; // Move assignment of abstract types is not possible.

  // Comparison operators
  bool operator==(const ResizableContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResizableContainer&) const noexcept= delete; // Comparison of abstract types is not possible.

  // Specific member functions
  virtual inline void Resize(const ulong) = 0;
  
  // Specific member function (inherited from ClearableContainer)
  virtual void Clear() override{
    Resize(0);
  };

};

}

#endif