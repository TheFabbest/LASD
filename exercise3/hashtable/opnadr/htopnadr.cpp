
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
    table = Vector<List<Data>()>((size >= MIN_SIZE) ? size : MIN_SIZE);
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    
}

template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long size) {
    if (size < MIN_SIZE) {
        size = MIN_SIZE;
    }
    if (size == TableSize()) {
        return;
    }

    Array<Pair> new_table = Array<Pair>(size);
    std::swap(new_table, table);
    new_table.Traverse([this](const Pair& curr) {
        if (curr.state == Present) {
            this->Insert(curr.data);
        }
    });
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for (unsigned long i = 0; i < TableSize(); ++i)
    {
        table[i].state = Absent; // TODO absent o removed
    }
    Resize(MIN_SIZE);
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
    for (unsigned long i = 0; i < TableSize(); ++i) {
        if (table[i].state == Present) {
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
inline unsigned long HashTableOpnAdr<Data>::Probe(unsigned long iteration, unsigned long current, unsigned long key) {
    default_random_engine genx(key);
    uniform_int_distribution<int> distx(1, TableSize()-iteration);
    return (distx(genx) + current) % TableSize();
}

template <typename Data>
unsigned long HashTableOpnAdr<Data>::Find(const Data& data) const noexcept {
    unsigned long curr = HashKey(data);
    TriState state = table[curr].state;
    Data current_data = table[curr].data;

    while (state != Absent && curr TODO ) {
        if (current_data == data) {
            if (state == Present) {
                return curr;
            }
            if (state == Removed) {

            }
        }
    }
}

/* ************************************************************************** */

}
