
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

    head = new_size;
    tail = 0;
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

    head = new_size;
    tail = 0;
    size = new_size;
}

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& other) : Vector<Data>(other){
    head = other.head;
    tail = other.tail;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& other){
    Vector<Data>::Vector(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

// Operators

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& other){
    Vector<Data>();
    head = other.head;
    tail = other.tail;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& other) noexcept{
    Vector<Data>(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

/* ************************************************************************** */

}
