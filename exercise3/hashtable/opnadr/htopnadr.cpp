
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    table = Vector<Pair>(MIN_SIZE);
    SetCoeffs();
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& traversable) {
    table = Vector<Pair>(traversable.Size() * 4); // todo MULTIPLY
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, const TraversableContainer<Data>& traversable) {
    table = Vector<Pair>(size);
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& mappable) {
    table = Vector<Pair>(mappable.Size());
    SetCoeffs();
    InsertAll(mappable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, MappableContainer<Data>&& mappable) {
    table = Vector<Pair>((size >= MIN_SIZE) ? size : MIN_SIZE);
    SetCoeffs();
    InsertAll(mappable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = other.table;
    this->size = other.size;
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->size, other.size);
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& other) {
    this->coeff_a = other.coeff_a;
    this->coeff_b = other.coeff_b;
    this->table = other.table;
    this->size = other.size;
    return *this;
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& other) noexcept {
    std::swap(this->coeff_a, other.coeff_a);
    std::swap(this->coeff_b, other.coeff_b);
    std::swap(this->table, other.table);
    std::swap(this->size, other.size);
    return *this;
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long size) {
    table = Vector<Pair>((size >= MIN_SIZE) ? size : MIN_SIZE);
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    unsigned long index;
    bool found = Find(data, index);
    if (found) {
        table[index].state = Pair::TriState::Removed;
    }
    return found;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long l;
    return Find(data, l);
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long size) {
    if (size < MIN_SIZE) {
        size = MIN_SIZE;
    }
    if (size == TableSize()) {
        return;
    }

    Vector<Pair> new_table = Vector<Pair>(size);
    std::swap(new_table, table);
    new_table.Traverse([this](const Pair& curr) {
        if (curr.state == Pair::TriState::Present) {
            this->Insert(curr.data);
        }
    });
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for (unsigned long i = 0; i < TableSize(); ++i)
    {
        table[i].state = Pair::TriState::Absent;
    }
    Resize(MIN_SIZE);
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
    for (unsigned long i = 0; i < TableSize(); ++i) {
        if (table[i].state == Pair::TriState::Present) {
            if (other.Exists(table[i].data) == false) {
                return false;
            }
        }
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& other) const noexcept {
    return !(this->operator==(other));
}

template <typename Data>
inline unsigned long HashTableOpnAdr<Data>::TableSize() const noexcept {
    return table.Size();
}

// aux
template <typename Data>
inline unsigned long HashTableOpnAdr<Data>::Probe(unsigned long iteration, unsigned long current, unsigned long key) const noexcept {
    default_random_engine genx(key);
    uniform_int_distribution<int> distx(1, TableSize()-iteration);
    return (distx(genx) + current) % TableSize();
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(const Data& data, unsigned long &position) const noexcept {
    unsigned long key = HashKey(data);
    position = key;

    typename Pair::TriState state = table[position].state;
    Data current_data = table[position].data;
    unsigned long i = 0;

    while (state != Pair::TriState::Absent && i < TableSize()) {
        if (current_data == data) {
            if (state == Pair::TriState::Present) {
                return true;
            }
            if (state == Pair::TriState::Removed) {
                return false;
            }
        }
        ++i;
        Probe(i, position, key);
    }
}

template <typename Data>
bool HashTableOpnAdr<Data>::FindEmpty(const Data& data, unsigned long &position) const noexcept {
    return false; // TODO
}

/* ************************************************************************** */

}
