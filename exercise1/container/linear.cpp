
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
    //this->PreOrderMap(function);
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
      function(operator[](i));
    }
}

// TODO vedi se va bene
template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun function) const{
  unsigned long i;
  for (i = this->size-1; i >= 0; --i)
  {
    function(operator[](i));
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
  unsigned long i;
  for (i = this->size-1; i >= 0; --i)
  {
    function(operator[](i));
  }
}

// SortableLinearContainer
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  this->QuickSort(0, this->size-1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(unsigned long left, unsigned long right) noexcept {
  if (left < right) {
    unsigned long partitionIndex = Partition(left, right);
    QuickSort(left, partitionIndex - 1); 
    QuickSort(partitionIndex + 1, right); 
  } 
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::Partition(unsigned long left, unsigned long right) noexcept {
  Data pivot = this->operator[](left); 
  unsigned long i = left;
  unsigned long j = right; 
  while (i < j) { 
    while (this->operator[](i) <= pivot && i <= right - 1) { 
      i++; 
    } 
    while (this->operator[](j) > pivot && j >= left + 1) { 
      j--; 
    } 
    if (i < j) { 
      std::swap(this->operator[](i), this->operator[](j)); 
    }
  } 
  std::swap(this->operator[](left), this->operator[](j)); 
  return j; 
}

/* ************************************************************************** */

}
