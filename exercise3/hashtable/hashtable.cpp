
namespace lasd {

/* ************************************************************************** */

// Hashable
template<>
class Hashable<int> {
    public:
        unsigned long operator() (const int& data) const noexcept {
            return data*data;
        }
};

template<>
class Hashable<double> {
    public:
        unsigned long operator() (const double& data) const noexcept {
            long int_part = floor(data);
            long frac = pow(2,24) * (data-int_part);
            return int_part * frac;
        }
};

template<>
class Hashable<string> {
    public:
        unsigned long operator() (const string& data) const noexcept {
            unsigned long hash = 5381;
            for (unsigned long i = 0; i < data.length(); ++i)
            {
                hash = (hash << 5) + data[i];
            }
            return hash;
        }
};

// HashTable
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
