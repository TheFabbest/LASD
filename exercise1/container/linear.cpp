
namespace lasd {

/* ************************************************************************** */
// TODO controlla queste 4
template <typename Data>
inline const Data& LinearContainer<Data>::Front() const{
  return std::move(operator[](0));
}

template <typename Data>
inline Data& LinearContainer<Data>::Front(){
  return operator[](0);
}

template <typename Data>
inline const Data& LinearContainer<Data>::Back() const{
  return std::move(operator[](this->size-1));
}

template <typename Data>
inline Data& LinearContainer<Data>::Back(){
  return operator[](this->size-1);
}

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun function) const{
    this->PreOrderTraverse(function);
}

// TODO vedi se va bene
template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun function) const{
    this->PreOrderMap(function);
}

// TODO vedi se va bene
template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun function) const{
    this->PostOrderMap(function);
}

template <typename Data>
inline void LinearContainer<Data>::Map(MapFun function) const{
    this->PreOrderMap(function);
}

template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun function) const{
  ulong i;
  for (i = 0; i < this->size; ++i)
  {
    function(operator[](i));
  }
}

template <typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun function) const{
  ulong i;
  for (i = this->size-1; i >= 0; --i)
  {
    function(operator[](i));
  }
}

// SortableLinearContainer
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  this->QuickSort(0, size-1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong left, ulong right) noexcept {
  if (left < right) {
    ulong partitionIndex = Partition(left, right);
    QuickSort(left, partitionIndex - 1); 
    QuickSort(partitionIndex + 1, right); 
  } 
}

template <typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong left, ulong right) noexcept {
  Data pivot = operator[](left); 
  ulong i = left;
  ulong j = right; 
  while (i < j) { 
    while (operator[](i) <= pivot && i <= right - 1) { 
      i++; 
    } 
    while (operator[](j) > pivot && j >= left + 1) { 
      j--; 
    } 
    if (i < j) { 
      std::swap(operator[](i), operator[](j)); 
    }
  } 
  std::swap(operator[](left), operator[](j)); 
  return j; 
}

/* ************************************************************************** */

}
