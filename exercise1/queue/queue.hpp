
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~Queue();

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Queue& operator=(Queue&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Queue&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  const Data& Head() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  Data& Head(); // (mutable version; concrete function must throw std::length_error when empty)
  void Dequeue(); // (concrete function must throw std::length_error when empty)
  Data& HeadNDequeue(); // (concrete function must throw std::length_error when empty)
  void Enqueue(const Data& data); // Copy of the value
  void Enqueue(Data&& data); // Move of the value

};

/* ************************************************************************** */

}

#endif
