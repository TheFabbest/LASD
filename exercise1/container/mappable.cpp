
namespace lasd {

/* ************************************************************************** */

// PreOrderMappableContainer
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun function) {
    this->PreOrderMap(function);
}

// PostOrderMappableContainer
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun function) {
    this->PostOrderMap(function);
}

// InOrderMappableContainer
template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun function) {
    this->InOrderMap(function);
}

// BreadthMappableContainer
template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun function) {
    this->BreadthMap(function);
}

/* ************************************************************************** */

}
