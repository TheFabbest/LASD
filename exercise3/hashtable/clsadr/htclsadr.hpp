
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
// #include ...

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {
  // Must extend HashTable<Data>

private:

  static const unsigned long MIN_SIZE = 8;

protected:

  // using HashTable<Data>::???;

  Vector<List<Data>> table;

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const unsigned long size); // A hash table of a given size
  // HashTableClsAdr(argument) specifiers; // A hash table obtained from a TraversableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table of a given size obtained from a TraversableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table obtained from a MappableContainer
  // HashTableClsAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // HashTableClsAdr(argument) specifiers;

  // Move constructor
  // HashTableClsAdr(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~HashTableClsAdr() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data>& other) const noexcept;
  inline bool operator!=(const HashTableClsAdr<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data &data) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data &&data) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data &data) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
