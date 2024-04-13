
namespace lasd {

/* ************************************************************************** */

// TraversableContainer

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;
    Traverse (
        [data, &exists] (const Data &current){
            exists |= (data == current);
        }
    );
    return exists;
}

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator accumulator) const{
    Traverse(
        [fun, &acc](const Data& current){
            acc = fun(current, acc);
        }
    );
    return acc;
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
    )
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
    )
    return accumulator;
}

// InOrderTraversableContainer

/* ************************************************************************** */

}
