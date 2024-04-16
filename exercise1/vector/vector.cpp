
namespace lasd {

/* ************************************************************************** */
// Vector
// constructors
template<typename Data>
Vector<Data>::Vector(const ulong size)
{
  Resize(size);
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& traversable) : Vector(traversable.Size())
{
  ulong i = 0;
  traversable.Traverse(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& mappable) : Vector(mappable.Size())
{
  ulong i = 0;
  mappable.Map(
    [this, &i](const Data &current){
      this->operator[](i++) = current;
    }
  );
}


template <typename Data>
const Data& Vector<Data>::Back() const override{
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
}

// direct access operators
template <typename Data>
Data& Vector<Data>::operator[](const ulong index) override
{
  if (index < size) return Elements[index];
  throw std::out_of_range("Index " + std::to_string(index) + " is incorrect for vector of size " + std::to_string(size))
}

template <typename Data>
const Data& Vector<Data>::operator[](const ulong index) const override
{
  if (index < size) return Elements[index];
  throw std::out_of_range("Index " + std::to_string(index) + " is incorrect for vector of size " + std::to_string(size))
}

//
template <typename Data>
Data& Vector<Data>::Back() override{
  if (Empty()) throw std::length_error("Empty vector");
  return Elements[size-1];
}

template <typename Data>
void Vector<Data>::Resize(const ulong newsize) override{
  delete Elements;
  //Elements = new;
  // TODO
}

/* ************************************************************************** */

}
