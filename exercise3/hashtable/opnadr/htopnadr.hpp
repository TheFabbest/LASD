
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include <utility>

#include "../hashtable.hpp"
// #include ...

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data>{
  // Must extend HashTable<Data>

private:

  // ...

protected:

  struct Pair {
    enum TriState {
      Present,
      Absent,
      Removed
    }
    
    TriState state = Absent;
    Data data{};
  }

  using HashTable<Data>::size;
  using HashTable<Data>::coeff_a;
  using HashTable<Data>::coeff_b;
  using HashTable<Data>::HashKey;

  Array<Pair> table;
  static const unsigned long MIN_SIZE = 32;

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const unsigned long size); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data>& traversable); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(unsigned long size, const TraversableContainer<Data>& traversable); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data>&& mappable); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(unsigned long size, MappableContainer<Data>&& mappable); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructorì
  HashTableOpnAdr(const HashTableOpnAdr<Data>& other);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr<Data>& operator=(const HashTableOpnAdr<Data>& other);

  // Move assignment
  HashTableOpnAdr<Data>& operator=(HashTableOpnAdr<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data>& other) const noexcept;
  inline bool operator!=(const HashTableOpnAdr<Data>& other) const noexcept;

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

  // Auxiliary member functions
  // TODO??? diff find (prima disponibile, indice) e findempty (prima cella vuota), hashkey fa anche probing? cioe prende indice? rand fino a ts-1
  // type HashKey(argument) specifiers;
  unsigned long Find(const Data& data) const noexcept;
  unsigned long FindEmpty(const Data& data) const noexcept;
  // type Remove(argument) specifiers;

  virtual inline unsigned long TableSize() const noexcept override;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
