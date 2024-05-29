
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

  static const Hashable<Data> encodingHash;

  // TODO
  unsigned long coeff_a;
  unsigned long coeff_b;


  static constexpr unsigned long primes[37] = {23, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759,
    411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969, 105359939, 210719881, 421439783, 842879579,
    1685759167, 3371518343, 6743036717, 13486073473, 26972146961, 53944293929, 107888587883, 215777175787, 431554351609,
    863108703229, 1726217406467, 3452434812973, 6904869625971};

public:
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;

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
  bool operator!=(const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  virtual inline unsigned long HashKey(const Data& data) const noexcept;
  virtual unsigned long HashKey(unsigned long key) const noexcept; // chiav ind

  virtual inline unsigned long TableSize() const noexcept = 0;
  inline void SetCoeffs() noexcept; //todo elimina e chiama costruttore hashtable
  unsigned long NextPrime(unsigned long expectedsize) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
