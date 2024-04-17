
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~Stack(); // TODO = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack& operator=(const Stack&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Stack& operator=(Stack&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Stack&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Top() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Top(); // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Pop(); // (concrete function must throw std::length_error when empty)
  virtual Data& TopNPop(); // (concrete function must throw std::length_error when empty)
  virtual void Push(const Data& data); // Copy of the value
  virtual void Push(Data&& data); // Move of the value
  
};

/* ************************************************************************** */

}

#endif
