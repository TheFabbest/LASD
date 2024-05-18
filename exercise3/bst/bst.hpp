
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer, virtual public DictionaryContainer<Data>, virtual public BinaryTree<Data>, virtual protected BinaryTreeLnk<Data> {
  // Must extend ClearableContainer,
  //             DictionaryContainer<Data>,
  //             BinaryTree<Data>,
  //             BinaryTreeLnk<Data>

private:

  // ...

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

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
  virtual ~BST() = default;

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

  virtual const Data& Min() const; // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data& data) const; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data& data); // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data& data); // (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data& data) const; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data& data); // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data& data); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  using BinaryTreeLnk<Data>::Root;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& data) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&& data) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data& data) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data& data) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using BinaryTreeLnk<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

  virtual Data DataNDelete(NodeLnk * ptr);

  virtual NodeLnk* Detach(NodeLnk*& node);

  virtual NodeLnk *DetachMin(NodeLnk *& node) noexcept;
  virtual NodeLnk *DetachMax(NodeLnk *& node) noexcept;

  // detaches "node->left" from the tree and returns a pointer to node
  virtual NodeLnk* Skip2Left(NodeLnk *& node) noexcept;
  virtual NodeLnk* Skip2Right(NodeLnk *& node) noexcept;

  virtual NodeLnk*& FindPointerToMin(NodeLnk*& root) noexcept; // Both mutable & unmutable versions
  virtual const NodeLnk* const & FindPointerToMin(const NodeLnk* const & root) const noexcept;
  virtual NodeLnk*& FindPointerToMax(NodeLnk*& root) noexcept; // Both mutable & unmutable versions
  virtual const NodeLnk* const & FindPointerToMax(const NodeLnk* const & root) const noexcept;

  virtual NodeLnk*& FindPointerTo(NodeLnk*& root, const Data& data) noexcept; // Both mutable & unmutable versions
  virtual const NodeLnk* const & FindPointerTo(const NodeLnk* const & root, const Data &data) const noexcept;

  virtual NodeLnk*& FindPointerToPredecessor(NodeLnk*& root, const Data& data) noexcept; // Both mutable & unmutable versions
  virtual const NodeLnk* const & FindPointerToPredecessor(const NodeLnk* const & root, const Data& data) const noexcept;
  virtual NodeLnk*& FindPointerToSuccessor(NodeLnk*& root, const Data& data) noexcept; // Both mutable & unmutable versions
  virtual const NodeLnk* const & FindPointerToSuccessor(const NodeLnk* const & root, const Data& data) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
