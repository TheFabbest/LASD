
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data>{
  // Must extend Queue<Data>,
  //             Vector<Data>

private:

protected:

  unsigned long head = 0;
  unsigned long tail = 0;

  static const unsigned long MIN_SIZE = 4; 
  
  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data>& traversable); // A queue obtained from a TraversableContainer
  QueueVec(MappableContainer<Data>&& mappable); // A queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data>&);

  // Move constructor
  QueueVec(QueueVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~QueueVec() = default;

  /* ************************************************************************ */


  // Copy assignment
  QueueVec<Data>& operator=(const QueueVec& other);

  // Move assignment
  QueueVec& operator=(QueueVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const; // Override Queue member (non-mutable version; concrete function must throw std::length_error when empty)
  Data& Head(); // Override Queue member (mutable version; concrete function must throw std::length_error when empty)
  void Dequeue(); // Override Queue member (concrete function must throw std::length_error when empty)
  Data HeadNDequeue(); // Override Queue member (concrete function must throw std::length_error when empty)
  void Enqueue(const Data& data); // Override Queue member (copy of the value)
  void Enqueue(Data&& data); // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept; // Override Container member

  inline unsigned long Size() const noexcept; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void AdjustSizeBeforeEnqueue();
  void AdjustSizeAfterDequeue();
  inline unsigned long AllocatedSize();

  void Resize(const unsigned long newsize) override; // TODO vedi

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
