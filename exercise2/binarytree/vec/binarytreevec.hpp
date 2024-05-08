
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  struct NodeVec : virtual MutableNode { // Must extend MutableNode

  private:

    // ...

  protected:
    friend class BinaryTreeVec<Data>;

    bool valid = true;
    Data data;
    BinaryTreeVec &tree;

  public:
    NodeVec() = delete;

    // specific constructors
    NodeVec(BinaryTreeVec &binarytree, const Data& data);
    NodeVec(BinaryTreeVec &binarytree, Data&& data) noexcept;

    // copy constructor
    NodeVec(const NodeVec& other);
    // move constructor
    NodeVec(NodeVec&& other) noexcept;

    // copy assignment
    NodeVec operator=(const NodeVec& other);
    // move assignment
    NodeVec operator=(NodeVec&& other) noexcept;

    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node& LeftChild() const override;
    virtual const Node& RightChild() const override;
    virtual MutableNode& LeftChild() override;
    virtual MutableNode& RightChild() override;

  };
  
  Vector<NodeVec> vector;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>& traversable); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&& mappable) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>& other);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>& other);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec<Data>&& other) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>& other) const noexcept;
  inline bool operator!=(const BinaryTreeVec<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(TraverseFun function) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  virtual void BreadthMap(MapFun function) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
