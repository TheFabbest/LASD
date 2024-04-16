#include <stdexcept>
namespace lasd {

/* ************************************************************************** */
// Vector
// constructors
template<typename Data>
Vector<Data>::Vector(const unsigned long size)
{
  Resize(size);
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& traversable) : Vector(traversable.Size())
{
  unsigned long i = 0;
  traversable.Traverse(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& mappable) : Vector(mappable.Size())
{
  unsigned long i = 0;
  mappable.Map(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}

// TODO override
template <typename Data>
const Data& Vector<Data>::Back() const{
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
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

//
template <typename Data>
Data& Vector<Data>::Back(){
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
}

template <typename Data>
void Vector<Data>::Resize(const unsigned long newsize){
  delete Elements;
  //Elements = new;
  // TODO
}

/* ************************************************************************** */

}
