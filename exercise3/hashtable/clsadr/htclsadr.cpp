
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = Vector<BST<Data>>(MIN_SIZE);
    SetCoeffs();
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& traversable) {
    table = Vector<BST<Data>>(traversable.Size()*2);
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long size, const TraversableContainer<Data>& traversable) {
    table = Vector<BST<Data>>(size);
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mappable) {
    table = Vector<BST<Data>>(mappable.Size());
    SetCoeffs();
    InsertAll(mappable);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long size, MappableContainer<Data>&& mappable) {
    table = Vector<BST<Data>>(size);
    SetCoeffs();
    InsertAll(mappable);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = other.table;
    this->size = other.size;
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->size, other.size);
}


template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
    table.Map([](BST<Data>& curr){
        curr.Clear();
    });
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = other.table;
    this->size = other.size;
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->size, other.size);
    return *this;
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long size) {
    table = Vector<BST<Data>>((size >= MIN_SIZE) ? size : MIN_SIZE);
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
    if (size == TableSize()) return;

    this->size = 0;
    Vector<BST<Data>> oldtable = Vector<BST<Data>>(size);
    std::swap(oldtable, table);

    oldtable.Traverse([this](const BST<Data>& curr) {
        curr.Traverse([this](const Data& data){
            this->Insert(data);
        });
    });
}

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
    // TODO keep size? open addr? 1/4
    table.Map([](BST<Data>& curr){
        curr.Clear();
    });
    this->size = 0;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& other) const noexcept {
    if (size != other.size) return false;
    for (unsigned long i = 0; i < TableSize(); ++i) {
        BTPreOrderIterator iter(table[i]);
        while (iter.Terminated() == false) {
            if (other.Exists(*iter) == false) {
                return false;
            }
            ++iter;
        }
    }
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& other) const noexcept {
    return !(this->operator==(other));
}

template <typename Data>
inline unsigned long HashTableClsAdr<Data>::TableSize() const noexcept {
    return table.Size();
}




/* ************************************************************************** */

}
