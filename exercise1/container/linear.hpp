
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

  // ...

public:

  // Destructor
  ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const LinearContainer&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual const Data& operator[](const ulong index) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  inline virtual Data& operator[](const ulong index) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data& Front() const; // (mutable version; concrete function must throw std::length_error when empty)

  inline const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data& Back() const; // (mutable version; concrete function must throw std::length_error when empty)

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

  // ...

public:

  // Destructor
  ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SortableLinearContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const SortableLinearContainer&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  void Sort() noexcept;

protected:

  // Auxiliary member functions

  void QuickSort(ulong left, ulong right) noexcept;
  ulong Partition(ulong left, ulong right) noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
