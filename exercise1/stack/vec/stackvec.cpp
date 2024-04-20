
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
StackVec<Data>::StackVec(StackVec<Data>&& other) : Vector<Data>::Vector(std::move(other)){
    std::swap(top, other.top);
}

// Operators

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& other){
    Vector<Data>();
    top = other.top;
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& other) noexcept{
    Vector<Data>(std::move(other));
    std::swap(top, other.top);
    return *this;
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
    return !(this->operator==(other));
}

// stack operations
template <typename Data>
const Data& StackVec<Data>::Top() const {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top);
}

template <typename Data>
Data& StackVec<Data>::Top() {
    if (top == 0) throw std::length_error("Stack is empty");
    return this->operator[](top);
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
void StackVec<Data>::Clear() noexcept{
    Vector<Data>::Clear();
    top = 0;
}

// auxiliary
template <typename Data>
void StackVec<Data>::AdjustSizeBeforePush(){
    if (Size() >= size){
        Resize(size*2);
    }
}

template <typename Data>
void StackVec<Data>::AdjustSizeAfterPop(){
    if (Size() == size/2){
        if (size > MIN_SIZE) Resize(size/2);
        else Resize(MIN_SIZE);
    }
}

template <typename Data>
void StackVec<Data>::Resize(const unsigned long newsize) {
    Vector<Data>::Resize(newsize);
    if (top >= newsize) top = newsize-1;
}

/* ************************************************************************** */

}
