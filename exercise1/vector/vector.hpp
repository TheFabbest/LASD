
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer, virtual public LinearContainer<Data>{
  // Must extend ResizableContainer,
  //             LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

  Data* Elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // TODO perche mappable &&
  Vector(const unsigned long size); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data>& traversable); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data>&& mappable); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // TODO perche non Vector<Data> e perche non e noexcept
  Vector(const Vector& other);

  // Move constructor
  Vector(const Vector&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector& other);

  // Move assignment
  Vector& operator=(Vector&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector&) const noexcept;
  inline bool operator!=(const Vector&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const unsigned long newsize) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long index) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long index) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  // SortableVector() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // SortableVector(argument) specifiers; // A vector with a given initial dimension
  // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
  // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(argument) specifiers;

  // Move constructor
  // SortableVector(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
