
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

// HashTableOpnAdr
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    table = Vector<Pair>(primes[0]);
    SetCoeffs();
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long size) {
    table = Vector<Pair>(NextPrime(size));
    SetCoeffs();
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& traversable) {
    table = Vector<Pair>(NextPrime(traversable.Size() * 3));
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
    table = Vector<Pair>(NextPrime(mappable.Size() * 3));
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

// TODO RIGUARDA!!!!!!!!!!!!!!!
// todo riscrivi
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    unsigned long key = HashKey(data);
    unsigned long iteration = 0;
    
    // iterate until data is found or an empty cell is found todo find
    while (table[Probe(iteration, key)].state == Pair::TriState::Present && table[Probe(iteration, key)].data != data) {
        ++iteration;
    }

    // if data is found, Insert should do nothing and return false
    if (table[Probe(iteration, key)].state == Pair::TriState::Present && table[Probe(iteration, key)].data == data) {
        return false;
    }
    
    // insert the data at the first "logically" empty cell
    unsigned long position = Probe(iteration, key);
    typename Pair::TriState tmpStatus = table[position].state;
    table[position].data = data;
    table[position].state = Pair::TriState::Present;

    // if the cell was not "physically" empty, I might find the data later in the iteration
    if (tmpStatus == Pair::TriState::Removed) {
        ++iteration;
        position = Probe(iteration, key);
        while (table[position].state != Pair::TriState::Absent && iteration < TableSize()) {
            if (table[position].state == Pair::TriState::Present && table[position].data == data) {
                table[position].state = Pair::TriState::Removed;
                return false;
            }

            position = Probe(++iteration, key);
        }
    }

    ++size;
    if (size >= TableSize() * MAX_LOAD_FACTOR) {
        Resize(2*TableSize());
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat) {
    Data data = std::move(dat);
    unsigned long key = HashKey(data);
    unsigned long iteration = 0;
    
    // iterate until data is found or an empty cell is found todo find
    while (table[Probe(iteration, key)].state == Pair::TriState::Present && table[Probe(iteration, key)].data != data) {
        ++iteration;
    }

    // if data is found, Insert should do nothing and return false
    if (table[Probe(iteration, key)].state == Pair::TriState::Present && table[Probe(iteration, key)].data == data) {
        return false;
    }
    
    // insert the data at the first "logically" empty cell
    unsigned long position = Probe(iteration, key);
    typename Pair::TriState tmpStatus = table[position].state;
    table[position].data = data;
    table[position].state = Pair::TriState::Present;

    // if the cell was not "physically" empty, I might find the data later in the iteration
    if (tmpStatus == Pair::TriState::Removed) {
        ++iteration;
        position = Probe(iteration, key);
        while (table[position].state != Pair::TriState::Absent && iteration < TableSize()) {
            if (table[position].state == Pair::TriState::Present && table[position].data == data) {
                table[position].state = Pair::TriState::Removed;
                return false;
            }

            position = Probe(++iteration, key);
        }
    }

    ++size;
    if (size >= TableSize() * MAX_LOAD_FACTOR) {
        Resize(2*TableSize());
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    
    unsigned long index;
    bool found = Find(data, index); // todo CONTROLLA find, vedi se toglierla
    if (found) {
        table[index].state = Pair::TriState::Removed;
        --size;
        if (size < TableSize() / 8)
        {
            Resize(TableSize()/2);
        }
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
            Insert(curr.data);
        }
    });
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for (unsigned long i = 0; i < TableSize(); ++i)
    {
        table[i].state = Pair::TriState::Absent;
    }
    Resize(primes[0]);
    size = 0;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    
    for (unsigned long i = 0; i < TableSize(); ++i) {
        if (table[i].state == Pair::TriState::Present && other.Exists(table[i].data) == false) {
            return false;
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
    // usando tablesize prima:
    // i problemi con il probing quadratico sono stati discussi a ricevimento, si e' concluso che era preferibile un altro metodo
    // il probing random e' stato solo accennato a lezione e per questo, nonostante avesse proprieta' interessanti, ho preferito evitare
    // interessante era anche l'Hopscotch Hashing che si dista troppo pero' dall'implementazione descritta durante il corso
    // la scelta si e' ridotta al probing lineare o al double hashing
    return (key + iteration) % TableSize();
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(const Data& data, unsigned long &position) const noexcept {
    unsigned long key = HashKey(data);
    position = key;

    typename Pair::TriState state = table[position].state;
    Data current_data = table[position].data;
    unsigned long i = 0;

    while (state != Pair::TriState::Absent && i < TableSize()) {
        if (state == Pair::TriState::Present && current_data == data) {
            return true;
        }
        // could check state == Pair::TriState::Removed && current_data == data if "data" is simple enough, personal test found it not useful
        ++i;
        position = Probe(i, key);
        state = table[position].state;
        current_data = table[position].data;
    }
    return false;
}

/* ************************************************************************** */

}
