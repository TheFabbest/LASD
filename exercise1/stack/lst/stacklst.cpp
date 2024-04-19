
namespace lasd {

/* ************************************************************************** */

// constructors

// traversable
template <typename Data>
StackLst<Data>::StackLst(const TraversableContainer<Data>& traversable) : List<Data>::List(traversable){}

// mappable
template <typename Data>
StackLst<Data>::StackLst(MappableContainer<Data>&& mappable) : List<Data>::List(mappable){}

// copy
template <typename Data>
StackLst<Data>::StackLst(const StackLst& other) : List<Data>::List(other){}

// move
template <typename Data>
StackLst<Data>::StackLst(StackLst&& other) : List<Data>::List(other){}


template <typename Data>
bool StackLst<Data>::operator==(const StackLst& other) const noexcept{
    return List<Data>::operator==(other);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst& other) const noexcept{
  return !operator==(other);
}

// Copy assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& other) noexcept{
    List<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& other) noexcept{
    List<Data>::operator=(std::move(other));
    return *this;
}


// stack operations
template <typename Data>
const Data& StackLst<Data>::Top() const {
    if (tail == nullptr) throw std::length_error("Stack is empty");
    return head->data;
}

template <typename Data>
Data& StackLst<Data>::Top() {
    if (tail == nullptr) throw std::length_error("Stack is empty");
    return head->data;
}

template <typename Data>
void StackLst<Data>::Pop() {
    if (tail == nullptr) throw std::length_error("Stack is empty");
    Node* tmp = head;
    head = head->next;
    tmp->next = nullptr;
    delete[] tmp;
}

template <typename Data>
Data& StackLst<Data>::TopNPop() {
    if (tail == nullptr) throw std::length_error("Stack is empty");
    Node* tmp = head;
    head = head->next;
    Data &ret = tmp->data;
    tmp->next = nullptr;
    delete[] tmp;
    return ret;
}

template <typename Data>
void StackLst<Data>::Push(const Data& data){
    Node* tmp = head;
    head = new Node(data);
    head->next = tmp;
}

template <typename Data>
void StackLst<Data>::Push(Data&& data){
    Node* tmp = head;
    head = new Node(data);
    head->next = tmp;
}

template <typename Data>
void StackLst<Data>::Clear() noexcept{
    List<Data>::Clear();
    tail = 0;
    head = 0;
}

/* ************************************************************************** */

}
