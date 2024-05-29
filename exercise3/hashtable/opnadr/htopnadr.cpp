
namespace lasd {

/* ************************************************************************** */

// PAIR
template <typename Data>
inline bool HashTableOpnAdr<Data>::Pair::operator==(const HashTableOpnAdr<Data>::Pair& other) const noexcept {
    return state == other.state && data == other.data;
}

template <typename Data>
inline bool HashTableOpnAdr<Data>::Pair::operator!=(const HashTableOpnAdr<Data>::Pair& other) const noexcept {
    return !(this->operator==(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    table = Vector<Pair>(primes[0]);
    SetCoeffs();
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long size) {
    table = Vector<Pair>(NextPrime(size));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& traversable) {
    table = Vector<Pair>(NextPrime(traversable.Size() * 3)); // todo MULTIPLY
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, const TraversableContainer<Data>& traversable) {
    table = Vector<Pair>(NextPrime(size));
    SetCoeffs();
    InsertAll(traversable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& mappable) {
    table = Vector<Pair>(NextPrime(mappable.Size()));
    SetCoeffs();
    InsertAll(mappable);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, MappableContainer<Data>&& mappable) {
    table = Vector<Pair>(NextPrime(size));
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
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    unsigned long index;

    if (Exists(data)) {
        return false;
    }

    bool found = FindEmpty(data, index);

    if (!found) {
        Resize(2*TableSize());
        FindEmpty(data, index);
    }

    table[index].state = Pair::TriState::Present;
    table[index].data = data;
    ++size;

    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    unsigned long index;
    Data d = std::move(data);

    if (Exists(d)) {
        return false;
    }

    bool found = FindEmpty(d, index);

    if (!found) {
        Resize(2*TableSize());
        FindEmpty(d, index);
    }

    table[index].state = Pair::TriState::Present;
    table[index].data = d;
    ++size;

    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    unsigned long index;
    bool found = Find(data, index);
    if (found) {
        table[index].state = Pair::TriState::Removed;
        --size;
    }
    
    return found;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long l;
    return Find(data, l);
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long tablesize) {
    tablesize = NextPrime(tablesize);

    Vector<Pair> new_table = Vector<Pair>(tablesize);
    std::swap(new_table, table);
    SetCoeffs();
    size = 0;
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
    size = 0;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    
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
inline unsigned long HashTableOpnAdr<Data>::Probe(unsigned long iteration, unsigned long key) const noexcept {
    return (key + iteration * iteration * coeff_a + coeff_b) % TableSize();
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
            else if (state == Pair::TriState::Removed) {
                return false;
            }
        }
        ++i;
        position = Probe(i, key);
        state = table[position].state;
        current_data = table[position].data;
    }
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::FindEmpty(const Data& data, unsigned long &position) const noexcept {
    unsigned long key = HashKey(data);
    position = key;

    typename Pair::TriState state = table[position].state;
    unsigned long i = 0;

    while (state == Pair::TriState::Present && i < TableSize()) {
        if (table[position].data == data) {
            return false; // TODO vedi se va bene
        }
        ++i;
        position = Probe(i, key);
        state = table[position].state;
    }
    return i < TableSize();
}

/* ************************************************************************** */

}
