#include <stdexcept>
#include <iostream>
using namespace std;
namespace lasd {

/* ************************************************************************** */
// Vector
// constructors
template<typename Data>
Vector<Data>::Vector(const unsigned long size)
{

  cout << "size constr vec" << endl;
  this->size = size;
  Elements = new Data[size]();
}

// copy constructor
// TODO mog
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& other)
{

  cout << "cop constr vec" << endl;
  size = other.size;
  Elements = new Data[size];
  std::copy(other.Elements, other.Elements + size, Elements);
}

// TODO mog
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& other) noexcept
{
  cout << "move constr vec" << endl;
  std::swap(Elements, other.Elements);
  std::swap(size, other.size);
}

// TODO mog
template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& traversable) : Vector(traversable.Size())
{

  cout << "travers vec" << endl;
  unsigned long i = 0;
  traversable.Traverse(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}

// TODO mog
template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& mappable) : Vector(mappable.Size())
{
  cout << "map vec" << endl;
  unsigned long i = 0;
  mappable.Map(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}

// destructor
// TODO mog
template <typename Data>
Vector<Data>::~Vector(){
  cout << "vec distr" << endl;
  delete[] Elements;
}

// operator=
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data> & other){
  cout << "cop= vec" << endl;
  Vector<Data> *tmp = new Vector<Data>(other);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data> && other) noexcept{
  cout << "mov= vec" << endl;
  std::swap(Elements, other.Elements);
  std::swap(size, other.size);
  return *this;
}

// direct access operators
template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index)
{
  if (index < size) return Elements[index];
  throw std::out_of_range("Index " + std::to_string(index) + " is incorrect for vector of size " + std::to_string(size));
}

template <typename Data>
const Data& Vector<Data>::operator[](const unsigned long index) const
{
  if (index < size) return Elements[index];
  throw std::out_of_range("Index " + std::to_string(index) + " is incorrect for vector of size " + std::to_string(size));
}

// Front and Back
// TODO override
template <typename Data>
const Data& Vector<Data>::Back() const{
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
}

template <typename Data>
Data& Vector<Data>::Back(){
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
}

template <typename Data>
const Data& Vector<Data>::Front() const{
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[0];
}

template <typename Data>
Data& Vector<Data>::Front(){
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[0];
}

// comparators
// todo mog
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> &other) const noexcept{
  if (other.size != size) return false;
  unsigned long i;
  for (i = 0; i < size; ++i)
  {
    if (Elements[i] != other.Elements[i]) return false;
  }
  return true;
}

//todo mog (simile)
template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& other) const noexcept
{
  return !(operator==(other));
}


// TODO mog
template <typename Data>
void Vector<Data>::Clear() noexcept
{
  delete []Elements;
  Elements = nullptr;
  size = 0;
}

// TODO mog
template <typename Data>
void Vector<Data>::Resize(const unsigned long newsize){
  if (newsize == 0) Clear();
  else if (size != newsize)
  {
    Data * TmpElements = new Data[newsize]{};
    ulong minsize = (size < newsize) ? size : newsize;
    for (unsigned long index = 0; index < minsize; ++index)
    {
      std::swap(Elements[index], TmpElements[index]);
    }
    std::swap(Elements, TmpElements);
    size = newsize;
    delete[] TmpElements;
  }
}

// SortableVector
template <typename Data>
SortableVector<Data>::SortableVector(const unsigned long size) : Vector<Data>::Vector(size){};

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data>& traversable) : Vector<Data>::Vector(traversable){}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data>&& mappable) : Vector<Data>::Vector(std::move(mappable)){}


// TODO mog le prox 4
// Copy constructor
template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data>& other):Vector<Data>::Vector(other){}

// Move constructor
template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data>&& other) noexcept : Vector<Data>::Vector(std::move(other)){}

// Copy assignment
template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& other){
  Vector<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& other) noexcept{
  Vector<Data>::operator=(std::move(other));
  return *this;
}


/* ************************************************************************** */

}
