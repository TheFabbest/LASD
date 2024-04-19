#include <iostream>
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>((unsigned long) MIN_SIZE){}

template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data>& traversable){
    unsigned long argument_size = traversable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;
    ++new_size;

    // TODO vedi se allocare di piu, inoltre se devo togliere +1 chiama direttamente costruttore di Vector
    Elements = new Data[new_size]();
    
    unsigned long i = 0;
    traversable.Traverse(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
        }
    );
    // end

    head = 0;
    tail = new_size;
    size = new_size;
}

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>&& mappable){
    unsigned long argument_size = mappable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;
    ++new_size;

    Elements = new Data[new_size](); // TODO vedi se allocare di piu
    
    unsigned long i = 0;
    mappable.Map(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
        }
    );

    head = 0;
    tail = new_size;
    size = new_size;
}

// Copy constructor
// TODO vedi
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& other) : Vector<Data>(other){
    head = other.head;
    tail = other.tail;
}

// Move constructor
// TODO vedi
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& other){
    Vector<Data>::Vector(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

// operators

// Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec& other){
    Vector<Data>();
    head = other.head;
    tail = other.tail;
}

// Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec&& other) noexcept{
    Vector<Data>(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec& other) const noexcept{
    unsigned long num_of_elements = Size();
    if (other.Size() != num_of_elements) return false;

    unsigned long index1, index2, i;
    for (i = 0; i < num_of_elements; ++i)
    {
        index1 = (head + i) % size;
        index2 = (other.head + i) % other.size;
        if (this->operator[](index1) != other[index2]) return false;
    }
    return true;
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec& other) const noexcept{
    unsigned long num_of_elements = Size();
    if (other.Size() != num_of_elements) return true;

    unsigned long index1, index2, i;
    for (i = 0; i < num_of_elements; ++i)
    {
        index1 = (head + i) % size;
        index2 = (other.head + i) % other.size;
        if (this->operator[](index1) != other[index2]) return true;
    }
    return false;
}


// operations on queues
template <typename Data>
const Data& QueueVec<Data>::Head() const{
    if (head == tail) throw std::length_error("Emtpy queue");
    return Elements[head];
}

template <typename Data>
Data& QueueVec<Data>::Head(){
    if (head == tail) throw std::length_error("Emtpy queue");
    return Elements[head];
}

template <typename Data>
void QueueVec<Data>::Dequeue(){
    if (head == tail) throw std::length_error("Emtpy queue");
    if (tail == 0) tail = size;
    --tail;
    AdjustSizeAfterDequeue();
}

template <typename Data>
Data& QueueVec<Data>::HeadNDequeue(){
    Data &ret = Head();
    Dequeue();
    return ret;
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data &data){
    AdjustSizeBeforeEnqueue();
    Elements[tail++] = data;
    tail %= size;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data &&data){
    AdjustSizeBeforeEnqueue();
    Elements[tail++] = data;
    tail %= size;
}

// TODO controlla
template <typename Data>
void QueueVec<Data>::Resize(const unsigned long newsize){
    unsigned long num_of_elements = Size();
    unsigned long min_size = (num_of_elements >= newsize) ? newsize : num_of_elements;
    unsigned long index_old, index_new;

    Data *newElements =  new Data[newsize];
    for (index_old = head, index_new = 0; index_new < min_size; index_old = (index_old+1)%size, ++index_new){
        std::swap(Elements[index_old], newElements[index_new]);
    }
    head = 0;
    tail = min_size;
    size = newsize;

    std::swap(newElements, Elements);
    delete[] newElements;
}


// overrides of container
template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept{
    return tail == head;
}

template <typename Data>
inline unsigned long QueueVec<Data>::Size() const noexcept{
    return ((size + tail) - head) % size;
}

template <typename Data>
void QueueVec<Data>::Clear() noexcept{
    Resize(MIN_SIZE);
    tail = 0;
    head = 0;
}


// auxiliary
template <typename Data>
void QueueVec<Data>::AdjustSizeBeforeEnqueue(){
    if (size > MIN_SIZE && Size() == size){
        Resize(size*2);
    }
}

template <typename Data>
void QueueVec<Data>::AdjustSizeAfterDequeue(){
    if (size > MIN_SIZE && Size() == size/2){
        Resize(size/2);
    }
}

/* ************************************************************************** */

}
