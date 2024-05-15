
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = Vector<List<Data>()>(MIN_SIZE);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long size) {
    table = Vector<List<Data>()>((size >= MIN_SIZE) ? size : MIN_SIZE);
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if (table[HashKey(data)].Insert(data)) {
        ++size;
    }
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) {
    if (table[HashKey(data)].Insert(std::move(data))) {
        ++size;
    }
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& other) const noexcept {
    if (size != other.size) return false;
    for (unsigned long i = 0; i < table.size; ++i) {
        auto& current_container = table[i];
        auto& other_container = other.table[i];
        if (current_container.size != other_container.size) {
            return false;
        }

        for (unsigned long j = 0; j < current_container.size; ++j) {
            if (current_container.Exists(other_container[j]) == false) {
                return false;
            }
        }
    }
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& other) const noexcept {
    return !(this->operator==(other));
}


/* ************************************************************************** */

}
