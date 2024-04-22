
namespace lasd {

/* ************************************************************************** */
// constructors

// traversable
template <typename Data>
QueueLst<Data>::QueueLst(const TraversableContainer<Data>& traversable) : List<Data>::List(traversable){}

// mappable
template <typename Data>
QueueLst<Data>::QueueLst(MappableContainer<Data>&& mappable) : List<Data>::List(mappable){}

// copy
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst& other) : List<Data>::List(other){}

// move
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst&& other) : List<Data>::List(other){}

// operators
// TODO mog prossimi 5
template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst& other){
    List<Data>::operator=(other);
    return *this;
}

template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(QueueLst&& other) noexcept{
    List<Data>::operator=(std::move(other)); // TODO controlla operator = se e di move o copy
    return *this;
}

template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst& other) const noexcept{
    return List<Data>::operator==(other);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst& other) const noexcept{
  return List<Data>::operator!=(other);
}

// operations on queue
template <typename Data>
inline const Data& QueueLst<Data>::Head() const {
    return List<Data>::Front();
}

template <typename Data>
inline Data& QueueLst<Data>::Head(){
    return List<Data>::Front();
}

template <typename Data>
inline void QueueLst<Data>::Dequeue(){
    List<Data>::RemoveFromFront();
}

template <typename Data>
inline Data QueueLst<Data>::HeadNDequeue(){
    return List<Data>::FrontNRemove();
}

template <typename Data>
inline void QueueLst<Data>::Enqueue(const Data &data){
    List<Data>::InsertAtBack(data);
}

template <typename Data>
inline void QueueLst<Data>::Enqueue(Data &&data){
    List<Data>::InsertAtBack(std::move(data));
}


/* ************************************************************************** */

}
