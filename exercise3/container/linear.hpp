
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>{
  // Must extend PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual const Data& operator[](const unsigned long index) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  inline virtual Data& operator[](const unsigned long index) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline virtual Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun function) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun function) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun function) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void  Map(MapFun function) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun function) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun function) override; // Override PostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data> {
  // Must extend LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;
  using LinearContainer<Data>::operator[];

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SortableLinearContainer&) const noexcept;
  inline bool operator!=(const SortableLinearContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() noexcept;

protected:

  // Auxiliary member functions

  void QuickSort(unsigned long left, unsigned long right) noexcept;
  unsigned long Partition(unsigned long left, unsigned long right) noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
