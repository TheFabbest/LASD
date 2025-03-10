
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
  
  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

  struct NodeVec : virtual MutableNode { // Must extend MutableNode

  private:

    // ...

  protected:
    friend class BinaryTreeVec<Data>;

    bool valid = false;
    Data data{};
    BinaryTreeVec *tree = nullptr;
    inline unsigned long BaseAddress() const noexcept;
    inline unsigned long Index() const noexcept;

  public:
    NodeVec() = default;

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

    inline const Data& Element() const noexcept override;
    inline Data& Element() noexcept override;

    virtual ~NodeVec() = default;
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
  virtual ~BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>& other);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec<Data>&& other) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeVec<Data>& other) const noexcept;
  inline bool operator!=(const BinaryTreeVec<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Node& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  virtual void BreadthTraverse(TraverseFun function) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;
  virtual void BreadthMap(MapFun function) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
