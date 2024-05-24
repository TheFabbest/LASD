
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

// 2^48 primo max
// riduz. dopo
// todo per random limite size?

// hash enc dat-> chiav
template <typename Data>
class Hashable {

public:
  unsigned long operator()(const Data& data) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data>{
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;

  static const Hashable<Data> encodingHash;

  // TODO
  unsigned long coeff_a;
  unsigned long coeff_b;

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

  virtual inline unsigned long HashKey(const Data& data) const noexcept;
  virtual unsigned long HashKey(const ulong key) const noexcept; // chiav ind

  virtual inline unsigned long TableSize() const noexcept = 0;
  inline void SetCoeffs() noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
