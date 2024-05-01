
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data>{
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  //using BinaryTree<Data>::; TODO

  // ...

  struct NodeLnk : virtual public MutableNode { // Must extend MutableNode

  private:

    // ...

  protected:

    NodeLnk *next = nullptr;

  public:

    // ...

  };

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>& traversable); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&& mappable) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>& other);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>& other);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>& other) const noexcept;
  inline bool operator!=(const BinaryTreeLnk<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  // type Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
