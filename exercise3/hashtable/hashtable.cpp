
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline unsigned long HashTable<Data>::HashKey(const Data& data) const noexcept {
    return encodingHash(data);
}

template <typename Data>
unsigned long HashTable<Data>::HashKey(const ulong key) const noexcept {
    // TODO use random
    return (coeff_a * key + coeff_b) % table_size;
}

/* ************************************************************************** */

}
