#include <iostream>
using namespace std;
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>((unsigned long) MIN_SIZE){}

template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data>& traversable){
    unsigned long argument_size = traversable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;

    // TODO vedi se allocare di piu, inoltre se devo togliere +1 chiama direttamente costruttore di Vector
    Elements = new Data[new_size+1]();
    
    unsigned long i = 0;
    traversable.Traverse(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
        }
    );
    // end

    top = argument_size;
    size = new_size+1;
}


template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data>&& mappable){
    unsigned long argument_size = mappable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;

    // TODO vedi se allocare di piu, inoltre se devo togliere +1 chiama direttamente costruttore di Vector
    Elements = new Data[new_size+1]();
    
    unsigned long i = 0;
    mappable.Map(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
        }
    );
    // end

    top = argument_size;
    size = new_size+1;
}

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& other) : Vector<Data>(other){
    top = other.top;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& other) noexcept: Vector<Data>::Vector(std::move(other)){
    std::swap(top, other.top);
}

// Operators

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& other){
    Clear();

    // TODO reimplementare traverse in StackVec? se usavo traverse mi scorreva vettore per intero
    unsigned long index;
    for (index = 0; index < other.top; ++index)
    {
        Push(other[index]);
    }
    
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& other) noexcept{
    std::swap(size, other.size);
    std::swap(top, other.top);
    std::swap(Elements, other.Elements);
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec& other) const noexcept
{
    if (top != other.Size()) return false;
    
    unsigned long index;
    for (index = 0; index < top; ++index){
        if (this->operator[](index) != other[index]) return false;
    }

    return true;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec& other) const noexcept
{
    return !(this->operator==(other));
}

// stack operations
template <typename Data>
const Data& StackVec<Data>::Top() const {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top-1);
}

template <typename Data>
Data& StackVec<Data>::Top() {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top-1);
}

template <typename Data>
void StackVec<Data>::Pop() {
    if (top == 0) throw std::length_error("Stack is empty");
    top--;
    AdjustSizeAfterPop();
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
    Data ret = Top();
    Pop();
    return ret;
}

template <typename Data>
void StackVec<Data>::Push(const Data& data){
    AdjustSizeBeforePush();
    this->operator[](top++) = data;
}

template <typename Data>
void StackVec<Data>::Push(Data&& data){
    AdjustSizeBeforePush();
    this->operator[](top++) = std::move(data);
}

template <typename Data>
inline unsigned long StackVec<Data>::Size() const noexcept{
    return top;
}

template <typename Data>
inline bool StackVec<Data>::Empty() const noexcept{
    return top == 0;
}

template <typename Data>
void StackVec<Data>::Clear(){
    Resize(MIN_SIZE);
    top = 0;
}

// auxiliary
template <typename Data>
void StackVec<Data>::AdjustSizeBeforePush(){
    if (top >= size){
        Resize(size*2);
    }
}

template <typename Data>
void StackVec<Data>::AdjustSizeAfterPop(){
    if (top == size/2){
        if (size > MIN_SIZE) Resize(size/2);
        else Resize(MIN_SIZE);
    }
}

template <typename Data>
void StackVec<Data>::Resize(const unsigned long newsize) {
    if (size == newsize) return;
    Vector<Data>::Resize(newsize);
    if (top > newsize) top = newsize;
}

/* ************************************************************************** */

}
