#include <stdexcept>
namespace lasd {

/* ************************************************************************** */
// Vector
// constructors
// TODO chiedi se va bene
template<typename Data>
Vector<Data>::Vector(const unsigned long size)
{
  Resize(size);
}

// copy constructor
// TODO mog
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& other)
{
  size = other.size;
  Elements = new Data[size];
  std::copy(other.Elements, other.Elements + size, Elements);
}

// TODO mog
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& other) noexcept
{
  std::swap(Elements, other.size);
  std::swap(size, other.size);
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
      this->operator[](i++) = std::move(current);
    }
  );
}

// destructor
// TODO mog
template <typename Data>
Vector<Data>::~Vector(){
  delete[] Elements;
}

// operator=
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data> & other){
  Vector<Data> tmp = new Vector<Data>(other);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
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

/* ************************************************************************** */

}
