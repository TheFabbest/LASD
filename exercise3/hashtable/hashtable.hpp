
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  // TODO vedi quaderno e chiedi
  unsigned long operator() const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data>{
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

  // ...

protected:

  // using DictionaryContainer<Data>::???;

  // ...

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators (TODO not required)
  bool operator==(const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable& other) const noexcept = delete;// Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  // type HashKey(argument) specifiers;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
