
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = Vector<List<Data>()>(MIN_SIZE);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& traversable) {
    table = Vector<List<Data>()>(traversable.Size()); // todo MULTIPLY
    traversable.Traverse([this](const Data& curr){
        this->Insert(curr);
    });
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& traversable, unsigned long size) {
    table = Vector<List<Data>()>(size);
    traversable.Traverse([this](const Data& curr){
        this->Insert(curr);
    });
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mappable) {
    table = Vector<List<Data>()>(mappable.Size());
    mappable.Mappable([this](Data&& curr){
        this->Insert(curr);
    });
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mappable, unsigned long size) {
    table = Vector<List<Data>()>(size);
    mappable.Mappable([this](Data&& curr){
        this->Insert(curr);
    });
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = Vector<List<Data>>(other.table.Size());
    this->table_size = other.table_size;
    this->size = other.size;
    for (unsigned long i = 0; i < table.size; ++i) {
        this->table[i] = other.table[i];
    }
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->table_size, other.table_size);
    std::swap(this->size, other.size);
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = Vector<List<Data>>(other.table.Size());
    this->table_size = other.table_size;
    this->size = other.size;
    for (unsigned long i = 0; i < table.size; ++i) {
        this->table[i] = other.table[i];
    }
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->table_size, other.table_size);
    std::swap(this->size, other.size);
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long size) {
    table = Vector<List<Data>()>((size >= MIN_SIZE) ? size : MIN_SIZE);
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if (table[HashKey(data)].Insert(data)) {
        ++size;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) {
    if (table[HashKey(data)].Insert(std::move(data))) {
        ++size;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data) {
    if (table[HashKey(data)].Remove(data)) {
        --size;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return table[HashKey(data)].Exists(data);
}

template <typename Data>
void HashTableClsAdr<Data>::Resize(unsigned long size) {
    if (size == table_size) return;

    Vector<List<Data>> oldtable = Vector<List<Data>>(size);
    std::swap(oldtable, table);

    this->table_size = size;
    oldtable.Traverse([this](const List<Data>& curr) {
        curr.Traverse([this](const Data& data){
            this->Insert(data);
        });
    });
}

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
    // TODO keep size?
    table.Traverse([](const List<Data>& curr){
        curr.Clear();
    });
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
