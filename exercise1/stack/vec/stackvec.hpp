
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

  unsigned long top = 0;

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
  inline bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (non-mutable version; concrete function must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (mutable version; concrete function must throw std::length_error when empty)
  void Pop() override; // Override Stack member (concrete function must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (concrete function must throw std::length_error when empty)
  void Push(const Data& data) override; // Override Stack member Copy of the value
  void Push(Data&& data) override; // Override Stack member Move of the value  

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  inline unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void AdjustSizeBeforePush();
  void AdjustSizeAfterPop();

  void Resize(const unsigned long newsize);
};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
