
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
  HashTableClsAdr(const TraversableContainer<Data>& traversable); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const TraversableContainer<Data>& traversable, unsigned long size); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data>&& mappable); // A hash table obtained from a MappableContainer
  HashTableClsAdr(MappableContainer<Data>&& mappable, unsigned long size); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>& other);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() = default; // TODO vedi (anche in btvec)

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr<Data>& operator=(const HashTableClsAdr<Data>& other);

  // Move assignment
  HashTableClsAdr<Data>& operator=(HashTableClsAdr<Data>&& other) noexcept;

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

  bool Exists(const Data& data) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(unsigned long size) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
