
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

  // TODO mog
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
  Vector(Vector&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector& other);

  // Move assignment
  Vector& operator=(Vector&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  inline bool operator!=(const Vector<Data>&) const noexcept;

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

  const Data& Front() const; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front(); // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back(); // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // TODO mog
  using Container::size;
  using LinearContainer<Data>::operator[];

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const unsigned long size); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data>& traversable); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data>&& mappable); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // TODO perche non Vector<Data> e perche non e noexcept
  SortableVector(const SortableVector<Data>& other);

  // Move constructor
  SortableVector(SortableVector<Data>&& other) noexcept;
 
  /* ************************************************************************ */

  // Destructor
  ~SortableVector();

  /* ************************************************************************ */

   // Copy assignment
  SortableVector& operator=(const SortableVector<Data>& other);

  // Move assignment
  SortableVector& operator=(SortableVector<Data>&& other) noexcept;

  // TODO reimplementa ricerca (?)


protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
