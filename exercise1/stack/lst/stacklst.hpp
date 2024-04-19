
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual protected List<Data>{
  // Must extend Stack<Data>,
  //             List<Data>

private:

  // ...

protected:

  using typename List<Data>::Node;
  using List<Data>::head;
  using List<Data>::tail;

  // ...

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data>& traversable); // A stack obtained from a TraversableContainer
  StackLst(MappableContainer<Data>&& mappable); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst& other);

  // Move constructor
  StackLst(StackLst&& other);

  /* ************************************************************************ */

  // Destructor
  ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst& other) noexcept;

  // Move assignment
  StackLst& operator=(StackLst&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (non-mutable version; concrete function must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (mutable version; concrete function must throw std::length_error when empty)
  void Pop() override; // Override Stack member (concrete function must throw std::length_error when empty)
  Data& TopNPop() override; // Override Stack member (concrete function must throw std::length_error when empty)
  void Push(const Data& data) override; // Override Stack member Copy of the value
  void Push(Data&& data) override; // Override Stack member Move of the value  

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
