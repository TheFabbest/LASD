
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
  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

  // ...

  struct NodeLnk : virtual MutableNode { // Must extend MutableNode
  private:

    // ...

  protected:
    NodeLnk *left = nullptr;
    NodeLnk *right = nullptr;
    Data data;

  public:
    friend class BinaryTreeLnk<Data>;
    // specific constructors
    NodeLnk(const Data& data);
    NodeLnk(Data&& data) noexcept;

    // copy constructor
    NodeLnk(const NodeLnk& other);
    // move constructor
    NodeLnk(NodeLnk&& other) noexcept;

    // copy assignment
    NodeLnk operator=(const NodeLnk& other);
    // move assignment
    NodeLnk operator=(NodeLnk&& other) noexcept;

    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node& LeftChild() const override; // TODO Node o NodeLnk
    virtual const Node& RightChild() const override;
    virtual MutableNode& LeftChild() override;
    virtual MutableNode& RightChild() override;

    inline const Data& Element() const noexcept override;
    inline Data& Element() noexcept override;
  };

  NodeLnk *root = nullptr;
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

  const NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeLnk& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
