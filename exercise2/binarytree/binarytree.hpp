
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

// TODO inverti commenti
//#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
//#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data>,
                    virtual public InOrderTraversableContainer<Data>, virtual public BreadthTraversableContainer<Data>{
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>,
  //             InOrderTraversableContainer<Data>,
  //             BreadthTraversableContainer<Data>

private:

protected:
  using Container::size;

public:

  struct Node {

  protected:
    Data data;

    // Comparison operators
    bool operator==(const Node& other) const noexcept; // Comparison of abstract types is possible, but is not visible.
    inline bool operator!=(const Node& other) const noexcept; // Comparison of abstract types is possible, but is not visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node& operator=(Node&&) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    const Data& Element() const noexcept; // Immutable access to the element (concrete function should not throw exceptions)

    inline bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree& other) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree& other) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun function) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun function) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun function) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  inline void InOrderTraverse(TraverseFun function) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  void BreadthTraverse(TraverseFun function) const override; // Override BreadthTraversableContainer member

protected:

  void PreOrderTraverse(TraverseFun function, const Node& curr) const;

  void PostOrderTraverse(TraverseFun function, const Node& curr) const;

  void InOrderTraverse(TraverseFun function, const Node& curr) const;

  void BreadthTraverse(TraverseFun function, const Node& curr) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer, virtual public BinaryTree<Data>,
                          virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>,
                          virtual public InOrderMappableContainer<Data>, virtual public BreadthMappableContainer<Data> {
  // Must extend ClearableContainer,
  //             BinaryTree<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>,
  //             InOrderMappableContainer<Data>,
  //             BreadthMappableContainer<Data>

private:

protected:

  using Container::size;
  using typename BinaryTree<Data>::Node;

public:

  struct MutableNode : virtual Node {
    // Must extend Node

    friend class MutableBinaryTree<Data>;
    using Node::data;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode& operator=(const MutableNode&) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode& operator=(MutableNode&&) noexcept = delete; // Move assignment of abstract types is not possible.


    /* ********************************************************************** */

    // Specific member functions

    Data& Element() noexcept; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree& operator=(const MutableBinaryTree&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode& Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun function) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun function) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun function) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  inline void InOrderMap(MapFun function) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  // TODO + inline
  void BreadthMap(MapFun function) override; // Override BreadthMappableContainer member

protected:
  
  void PreOrderMap(MapFun function, Node& curr) const;

  void PostOrderMap(MapFun function, Node& curr) const;

  void InOrderMap(MapFun function, Node& curr) const;

  // TODO
  //void BreadthTraverse(TraverseFun function, Node& curr) const;

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  using typename BinaryTree<Data>::Node;
  BinaryTree<Data> *tree = nullptr;
  StackLst<Node*> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data>& other);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator<Data>& operator=(const BTPreOrderIterator<Data>& other);

  // Move assignment
  BTPreOrderIterator<Data>& operator=(BTPreOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTPreOrderIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTPreOrderIterator<Data>{
  // Must extend MutableIterator<Data>,
  //             BTPreOrderIterator<Data>

private:

  // ...

protected:

  using BTPreOrderIterator<Data>::Terminated;
  using BTPreOrderIterator<Data>::stack;

public:

  // Specific constructors
  BTPreOrderMutableIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& other);

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline BTPreOrderMutableIterator<Data>& operator=(const BTPreOrderMutableIterator<Data>& other);

  // Move assignment
  inline BTPreOrderMutableIterator<Data>& operator=(BTPreOrderMutableIterator<Data>&& other) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderMutableIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTPreOrderMutableIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:
  using typename BinaryTree<Data>::Node;
  BinaryTree<Data> *tree = nullptr;
  StackLst<Node*> stack;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>& other);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator<Data>& operator=(const BTPostOrderIterator<Data>& other);

  // Move assignment
  BTPostOrderIterator<Data>& operator=(BTPostOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTPostOrderIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTPostOrderIterator<Data>{
  // Must extend MutableIterator<Data>,
  //             BTPostOrderIterator<Data>

private:

  // ...

protected:

  using BTPostOrderIterator<Data>::Terminated;
  using BTPostOrderIterator<Data>::stack;

public:
  // Specific constructors
  BTPostOrderMutableIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& other);

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline BTPostOrderMutableIterator<Data>& operator=(const BTPostOrderMutableIterator<Data>& other);

  // Move assignment
  inline BTPostOrderMutableIterator<Data>& operator=(BTPostOrderMutableIterator<Data>&& other) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderMutableIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTPostOrderMutableIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  using typename BinaryTree<Data>::Node;
  BinaryTree<Data> *tree = nullptr;
  StackLst<Node*> stack;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>& other);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator<Data>& operator=(const BTInOrderIterator<Data>& other);

  // Move assignment
  BTInOrderIterator<Data>& operator=(BTInOrderIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTInOrderIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTInOrderIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTInOrderIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  BTInOrderMutableIterator(const BinaryTree<Data> &binarytree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& other);

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline BTInOrderMutableIterator<Data>& operator=(const BTInOrderMutableIterator<Data>& other);

  // Move assignment
  inline BTInOrderMutableIterator<Data>& operator=(BTInOrderMutableIterator<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderMutableIterator<Data>& other) const noexcept;
  inline bool operator!=(const BTInOrderMutableIterator<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator {
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:
  using typename BinaryTree<Data>::Node;
  BinaryTree<Data> *tree = nullptr;
  QueueLst<Node*> queue;

public:

  // Specific constructors
  // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthIterator(argument) specifiers;

  // Move constructor
  // BTBreadthIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthIterator() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator {
  // Must extend MutableIterator<Data>,
  //             BTBreadthIterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTBreadthMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthMutableIterator(argument) specifiers;

  // Move constructor
  // BTBreadthMutableIterator(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthMutableIterator() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
