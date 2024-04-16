
namespace lasd {

/* ************************************************************************** */

// PreOrderMappableContainer
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun function) const{
    this->PreOrderMap(function);
}

// PostOrderMappableContainer
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun function) const{
    this->PostOrderMap(function);
}

// InOrderMappableContainer
template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun function) const{
    this->InOrderMap(function);
}

// PostOrderMappableContainer
template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun function) const{
    this->BreadthMap(function);
}

/* ************************************************************************** */

}
