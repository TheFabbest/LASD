
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>((unsigned long) MIN_SIZE){}

template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data>& traversable){
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

    top = new_size;
    size = new_size;
}


template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data>&& mappable){
    unsigned long argument_size = mappable.Size();
    unsigned long new_size = (argument_size > MIN_SIZE) ? argument_size : MIN_SIZE;
    ++new_size;

    // TODO vedi se allocare di piu, inoltre se devo togliere +1 chiama direttamente costruttore di Vector
    Elements = new Data[new_size]();
    
    unsigned long i = 0;
    mappable.Map(
        [this, &i](const Data& curr){
            this->Elements[i++] = curr;
        }
    );
    // end

    top = new_size;
    size = new_size;
}

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& other) : Vector<Data>(other){
    top = other.top;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& other){
    Vector<Data>::Vector(std::move(other));
    std::swap(top, other.top);
}

// Operators

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& other){
    Vector<Data>();
    top = other.top;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& other) noexcept{
    Vector<Data>(std::move(other));
    std::swap(top, other.top);
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec& other) const noexcept
{
    unsigned long num_of_elements = Size();
    if (num_of_elements != other.Size()) return false;
    
    unsigned long index;
    for (index = 0; index < num_of_elements; ++index){
        if (this->operator[](index) != other[index]) return false;
    }

    return true;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec& other) const noexcept
{
    return !(this == other);
}

// stack operations
template <typename Data>
const Data& StackLst<Data>::Top() const {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top);
}

template <typename Data>
Data& StackLst<Data>::Top() {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top);
}

template <typename Data>
void StackLst<Data>::Pop() {
    if (top == 0) throw std::length_error("Stack is empty");
    top--;
    //TODO Resize
}

template <typename Data>
Data& StackLst<Data>::TopNPop() {
    Data &ret = Top();
    Pop();
    return ret;
}

template <typename Data>
void StackLst<Data>::Push(const Data& data){
    // TODO resize
    this->operator[](++top) = data;
}

template <typename Data>
void StackLst<Data>::Push(Data&& data){
    // TODO resize
    this->operator[](++top) = std::move(data);
}

template <typename Data>
inline unsigned long StackVec<Data>::Size() const noexcept{
    return top;
}

/* ************************************************************************** */

}
