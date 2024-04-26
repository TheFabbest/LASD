
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

// TODO mog
template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor

  /* ************************************************************************ */

  virtual ~DictionaryContainer() = default;
  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer&) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const DictionaryContainer&) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data& data) = 0; // Copy of the value
  virtual bool Insert(Data&& data) = 0; // Move of the value
  virtual bool Remove(const Data& data) = 0;

  inline virtual bool InsertAll(const TraversableContainer<Data> &container); // Copy of the value; From TraversableContainer; True if all are inserted
  inline virtual bool InsertAll(MappableContainer<Data> &&container); // Move of the value; From MappableContainer; True if all are inserted
  inline virtual bool RemoveAll(const TraversableContainer<Data> &container); // From TraversableContainer; True if all are removed

  inline virtual bool InsertSome(const TraversableContainer<Data> &container); // Copy of the value; From TraversableContainer; True if some are inserted
  inline virtual bool InsertSome(MappableContainer<Data> &&container); // Move of the value; From MappableContainer; True if some are inserted
  inline virtual bool RemoveSome(const TraversableContainer<Data> &container); // From TraversableContainer; True if some are removed

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
