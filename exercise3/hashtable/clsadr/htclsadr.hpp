
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {
  // Must extend HashTable<Data>

private:

  static const unsigned long MIN_SIZE = 1; // TODO Posso?

protected:

  // using HashTable<Data>::???; TODO

  using HashTable<Data>::size;
  using HashTable<Data>::coeff_a;
  using HashTable<Data>::coeff_b;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::SetCoeffs;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;
  Vector<BST<Data>> table;

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const unsigned long size); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data>& traversable); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(unsigned long size, const TraversableContainer<Data>& traversable); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data>&& mappable); // A hash table obtained from a MappableContainer
  HashTableClsAdr(unsigned long size, MappableContainer<Data>&& mappable); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>& other);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr();

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

protected:
  virtual inline unsigned long TableSize() const noexcept override;

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
