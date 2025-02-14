
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>, virtual protected List<Data>{
  // Must extend Queue<Data>,
  //             List<Data>

private:

  // ...

protected:

  // ...

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data>& traversable); // A queue obtained from a TraversableContainer
  QueueLst(MappableContainer<Data>&& mappable); // A queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst& other);

  // Move constructor
  QueueLst(QueueLst&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueLst<Data>& operator=(const QueueLst& other);

  // Move assignment
  inline QueueLst& operator=(QueueLst&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)


  inline const Data& Head() const override; // Override Queue member (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data& Head() override; // Override Queue member (mutable version; concrete function must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (concrete function must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (concrete function must throw std::length_error when empty)
  inline void Enqueue(const Data& data) override; // Override Queue member (copy of the value)
  inline void Enqueue(Data&& data) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
