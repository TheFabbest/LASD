#include <iostream>
namespace lasd {
 
/* ************************************************************************** */

// TraversableContainer

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;
    Traverse (
        [data, &exists] (const Data &current){
            exists |= (data == current);
            std::cout << data << " " << current << std::endl;
        }
    );
    return exists;
}

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    Traverse(
        [function, &accumulator](const Data& current){
            accumulator = function(current, accumulator);
        }
    );
    return accumulator;
}

// PreOrderTraversableContainer

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const{
    this->PreOrderTraverse(function);
}


template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    PreOrderTraverse(
        [function, &accumulator] (const Data& current)
        {
            accumulator = function(current, accumulator);
        }
    );
    return accumulator;
}

// PostOrderTraversableContainer

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const{
    this->PostOrderTraverse(function);
}

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    PostOrderTraverse(
        [function, &accumulator] (const Data& current)
        {
            accumulator = function(current, accumulator);
        }
    );
    return accumulator;
}

// InOrderTraversableContainer

template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun function) const{
    this->InOrderTraverse(function);
}

template <typename Data>
template <typename Accumulator>
Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    InOrderTraverse(
        [function, &accumulator] (const Data& current)
        {
            accumulator = function(current, accumulator);
        }
    );
    return accumulator;
}

// BreadthTraversableContainer

template <typename Data>
inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun function) const{
    this->BreadthTraverse(function);
}

template <typename Data>
template <typename Accumulator>
Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    BreadthTraverse(
        [function, &accumulator] (const Data& current)
        {
            accumulator = function(current, accumulator);
        }
    );
    return accumulator;
}

/* ************************************************************************** */

}
