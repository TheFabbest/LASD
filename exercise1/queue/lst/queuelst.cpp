
namespace lasd {

/* ************************************************************************** */
// constructors

// traversable
template <typename Data>
QueueLst<Data>::QueueLst(const TraversableContainer<Data>& traversable){
    List<Data>::List(traversable);
}

// mappable
template <typename Data>
QueueLst<Data>::QueueLst(MappableContainer<Data>&& mappable){
    List<Data>::List(mappable);
}

// copy
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst& other){
    List<Data>::List(other);
}

// move
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst&& other){
    List<Data>::List(other);
}


// destructor
template <typename Data>
QueueLst<Data>::~QueueLst(){
    //TODO
}

template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst& other) const noexcept{
    return List<Data>::operator==(other);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst& other) const noexcept{
  return !operator==(other);
}

// operations on queue
// TODO chiedi quale delle due e meglio (poi const e non sono uguali)
template <typename Data>
inline const Data& QueueLst<Data>::Head() const {
    return List<Data>::Front();
}

template <typename Data>
Data& QueueLst<Data>::Head() {
    if (tail == nullptr) throw std::length_error("Queue is empty");
    return head->data;
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
    if (tail == nullptr) throw std::length_error("Queue is empty");
    struct Node* tmp = head;
    head = tmp->next;
    tmp->next = nullptr;
    delete[] tmp;
}

template <typename Data>
Data& QueueLst<Data>::HeadNDequeue() {
    if (tail == nullptr) throw std::length_error("Queue is empty");
    struct Node* tmp = head;
    head = tmp->next;
    Data &ret = tmp->data;
    tmp->next = nullptr;
    delete[] tmp;
    return ret;
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& data) {
    struct Node* newnode = new struct Node(data);
    newnode->next = tail;
    tail = newnode;
}



/* ************************************************************************** */

}
