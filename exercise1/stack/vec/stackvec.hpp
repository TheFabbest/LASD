
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data> {
  // Must extend Stack<Data>,
  //             Vector<Data>

private:

  // ...

protected:

  unsigned long head = 0;
  unsigned long tail = 0;

  static const unsigned long MIN_SIZE = 4; 

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor

  StackVec(const TraversableContainer<Data>& traversable); // A stack obtained from a TraversableContainer
  StackVec(MappableContainer<Data>&& mappable); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data>&);

  // Move constructor
  StackVec(StackVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec<Data>& operator=(const StackVec& other);

  // Move assignment
  StackVec& operator=(StackVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // type Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  // type Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  // type Pop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type TopNPop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type Push(argument) specifiers; // Override Stack member (copy of the value)
  // type Push(argument) specifiers; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Empty() specifiers; // Override Container member

  // type Size() specifiers; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
