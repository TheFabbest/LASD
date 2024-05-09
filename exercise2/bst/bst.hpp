
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer, virtual public DictionaryContainer<Data>, virtual public BinaryTree<Data>, virtual public BinaryTreeLnk<Data> {
  // Must extend ClearableContainer,
  //             DictionaryContainer<Data>,
  //             BinaryTree<Data>,
  //             BinaryTreeLnk<Data>

private:

  // ...

protected:

  // using BinaryTreeLnk<Data>::???;

  // ...

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data>& traversable); // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data>&& mappable) noexcept; // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>& other);

  // Move constructor
  BST(BST<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST();

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>& operator=(const BST<Data>& other);

  // Move assignment
  BST<Data>& operator=(BST<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BST<Data>& other) const noexcept;
  inline bool operator!=(const BST<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  const Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  const Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data& data) const; // (concrete function must throw std::length_error when not found)
  const Data PredecessorNRemove(const Data& data); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data& data); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data& data) const; // (concrete function must throw std::length_error when not found)
  const Data SuccessorNRemove(const Data& data); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data& data); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  virtual const Node& Root() const override; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data& data) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&& data) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data& data) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data& data) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // TODO NON DA FARE
  // type Clear(argument) specifiers; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

  // type DataNDelete(argument) specifiers;

  // type Detach(argument) specifiers;

  // type DetachMin(argument) specifiers;
  // type DetachMax(argument) specifiers;

  // type Skip2Left(argument) specifiers;
  // type Skip2Right(argument) specifiers;

  // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions

  // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions

  // type FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
  // type FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
