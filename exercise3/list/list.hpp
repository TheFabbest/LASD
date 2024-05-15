
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

protected:

  using Container::size;

  struct Node {

    Data data;
    Node *next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data& data);
    Node(Data&& data) noexcept;
    
    /* ********************************************************************** */

    // Copy constructor
    Node(const Node & node);

    // Move constructor
    Node(Node && node) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const struct Node&) const noexcept;
    inline bool operator!=(const struct Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    virtual Node * Clone(Node*);
  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  inline List(const TraversableContainer<Data>& traversable); // A list obtained from a TraversableContainer
  inline List(MappableContainer<Data>&& mappable); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data> & list);

  // Move constructor
  List(List<Data> && list) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  inline bool operator!=(const List&) const noexcept;

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

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& data); // Copy of the value
  bool Insert(Data&& data); // Move of the value
  bool Remove(const Data& data);

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long index) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long index) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)


  const Data& Front() const; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front(); // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back(); // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun function) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun function) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun function) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun function) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun function) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun function) override; // Override PostOrderMappableContainer member

protected:

  void PostOrderTraverse(TraverseFun function, Node *curr) const;  
  void PostOrderMap(MapFun function, Node *curr);

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
