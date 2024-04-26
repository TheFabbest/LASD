#include <iostream>
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>((unsigned long) MIN_SIZE){}

template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data>& traversable){
    cout << "traversable constructor" << endl;
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
    tail = i;
    size = new_size;
}

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>&& mappable){
    cout << "mappable constructor" << endl;
    unsigned long argument_size = mappable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;
    ++new_size;

    Elements = new Data[new_size](); // TODO vedi se allocare di piu
    
    unsigned long i = 0;
    mappable.Map(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
            cout << i-1 << "<-" << curr << endl;
        }
    );

    head = 0;
    tail = i;
    size = new_size;
}

// Copy constructor
// TODO vedi
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& other) : Vector<Data>(other){
    cout << "Calling copy constructor queuevec" << endl;
    head = other.head;
    tail = other.tail;
}

// Move constructor
// TODO vedi
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& other) : Vector<Data>::Vector(std::move(other)){
    cout << "Calling move constructor queuevec" << endl;
    std::swap(head, other.head);
    cout << "Err..." << endl;
    std::swap(tail, other.tail);
    cout << "uh..." << endl;
}

// operators

// Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec& other){
    cout << "Calling operator= & queuevec" << endl;
    Vector<Data>::operator=(other);
    head = other.head;
    tail = other.tail;
    return *this;
}

// Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec&& other) noexcept{
    cout << "Calling operator= && queuevec" << endl;
    Vector<Data>::operator=(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec& other) const noexcept{
    unsigned long num_of_elements = Size();
        cout << num_of_elements << " vs " << other.Size() << endl;
    if (other.Size() != num_of_elements) return false;
    unsigned long index1, index2, i;
    for (i = 0; i < num_of_elements; ++i)
    {
        index1 = (head + i) % size;
        index2 = (other.head + i) % other.size;
        cout << this->operator[](index1) << "==" << other[index2] << endl;
        if (this->operator[](index1) != other[index2]) return false;
    }
    return true;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec& other) const noexcept{
    return !(this->operator==(other));
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
    ++head;
    head %= size;
    AdjustSizeAfterDequeue();
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    Data ret = Head();
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
    Elements[tail++] = std::move(data);
    tail %= size;
}

// TODO controlla
template <typename Data>
void QueueVec<Data>::Resize(const unsigned long newsize){
    if (size == newsize) return;
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
    if (Size() == size-1){
        Resize(size*2);
    }
}

template <typename Data>
void QueueVec<Data>::AdjustSizeAfterDequeue(){
    unsigned long newsize = size/2;
    if (Size() == size/4){
        if (newsize >= MIN_SIZE) Resize(newsize);
        else Resize(MIN_SIZE);
    }
}

/* ************************************************************************** */

}
