
namespace lasd {

/* ************************************************************************** */

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container){
    bool inserted = true;
    container.Traverse(
        [this, &inserted] (const Data& data){
            inserted &= this->Insert(data);
        }
    );
    return inserted;
}

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&container){
    bool inserted = true;
    container.Map(
        [this, &inserted] (Data& data){
            inserted &= this->Insert(std::move(data));
        }
    );
    return inserted;
}

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container){
    bool removed = true;
    container.Traverse(
        [this, &removed] (const Data& data){
            removed &= this->Remove(data);
        }
    );
    return removed;
}

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container){
    bool inserted = false;
    container.Traverse(
        [this, &inserted] (const Data& data){
            inserted |= this->Insert(data);
        }
    );
    return inserted;
}

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&container){
    bool inserted = false;
    container.Map(
        [this, &inserted] (Data& data){
            inserted |= this->Insert(std::move(data));
        }
    );
    return inserted;
}

// TODO mog
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container){
    bool removed = false;
    container.Traverse(
        [this, &removed] (const Data& data){
            removed |= this->Remove(data);
        }
    );
    return removed;
}

/* ************************************************************************** */

}
