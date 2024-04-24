#include <stdexcept>
#include <iostream>
namespace lasd {

/* ************************************************************************** */
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> &other) const noexcept{
  if (this->size != other.size) return false;
  unsigned long index;
  for (index = 0; index < this->size; ++index)
  {
    if (this->operator[](index) != other[index]) return false;
  }
  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &other) const noexcept{
  return !(this->operator==(other));
}

// TODO controlla queste 4
template <typename Data>
inline const Data& LinearContainer<Data>::Front() const{
  if (this->size < 1) throw std::length_error("LinearContainer is Empty");
  return operator[](0);
}

template <typename Data>
inline Data& LinearContainer<Data>::Front(){
  if (this->size < 1) throw std::length_error("LinearContainer is Empty");
  return operator[](0);
}

template <typename Data>
inline const Data& LinearContainer<Data>::Back() const{
  if (this->size < 1) throw std::length_error("LinearContainer is Empty");
  return operator[](this->size-1);
}

template <typename Data>
inline Data& LinearContainer<Data>::Back(){
  if (this->size < 1) throw std::length_error("LinearContainer is Empty");
  return operator[](this->size-1);
}

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun function) const{
    this->PreOrderTraverse(function);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun function) const{
    // TODO this->PreOrderMap(function);
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
      function(operator[](i));
    }
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun function) const{
  unsigned long i = this->size;
  while (i > 0)
  {
    function(operator[](--i));
  }
}

template <typename Data>
inline void LinearContainer<Data>::Map(MapFun function){
    this->PreOrderMap(function);
}

template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun function){
  unsigned long i;
  for (i = 0; i < this->size; ++i)
  {
    function(operator[](i));
  }
}

template <typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun function){
  unsigned long i = this->size;
  while (i > 0)
  {
    function(operator[](--i));
  }
}

// SortableLinearContainer
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  if (this->size <= 1) return;
  this->QuickSort(0, this->size-1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(unsigned long left, unsigned long right) noexcept {
  if (left < right) {
    unsigned long partitionIndex = Partition(left, right);
    QuickSort(left, partitionIndex);
    QuickSort(partitionIndex + 1, right); 
  } 
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::Partition(unsigned long left, unsigned long right) noexcept {
  Data pivot = this->operator[](left);
  unsigned long i = left-1;
  unsigned long j = right+1;
  do { 
    do { 
      j--; 
    } while (this->operator[](j) > pivot);
    do{
      i++; 
    } while (this->operator[](i) < pivot && i <= right - 1);

    if (i < j) { 
      std::swap(this->operator[](i), this->operator[](j)); 
    }
  } while (i < j);
  return j; 
}

/* ************************************************************************** */

}
