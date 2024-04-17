
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer, virtual public LinearContainer<Data>, virtual public DictionaryContainer<Data>{
  // Must extend ClearableContainer,
  //             LinearContainer<Data>,
  //             DictionaryContainer<Data>

private:

  struct Node *head;
  struct Node *tail;

protected:

  // using Container::???;

  struct Node {

    Data data;
    struct Node *next;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data& data);
    Node(Data&& data);
    
    /* ********************************************************************** */

    // TODO
    // Copy constructor
    Node(const struct Node & node) noexcept;

    // Move constructor
    Node(struct Node && node) noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const struct Node&) const noexcept;
    bool operator!=(const struct Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    virtual Node * Clone(Node*);

  };

  // ...

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  inline List(const TraversableContainer<Data>& traversable); // A list obtained from a TraversableContainer
  inline List(MappableContainer<Data>&& mappable); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List & list) noexcept;

  // Move constructor
  List(const List && list) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data & data); // Copy of the value
  void InsertAtFront(Data && data); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data& data); // Copy of the value
  void InsertAtBack(Data&& data); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& data); // Copy of the value
  bool Insert(Data&& data); // Move of the value
  bool Remove(const Data& data) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long index) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long index) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  // type Front() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Front() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  // type Back() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Back() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
