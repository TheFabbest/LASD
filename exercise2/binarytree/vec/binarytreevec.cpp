#include <iostream>
using namespace std;
namespace lasd {

/* ************************************************************************** */

// NodeVec
// default constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec()
{
    tree = nullptr; // TODO chiedi a mog se puoi usare tree==nullptr come controllo che il nodo sia valido o meno
    // eliminare valid
    // quando creo il vettore di NodeVec, ogni nodo viene creato con costruttore di default, quindi non so che albero dargli
    // 1) immediatamente dopo aver creato o ridimensionato il vettore devo settare il tree
    // 2) come dico sopra
}

// specific constructors
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(BinaryTreeVec<Data> &binarytree, const Data& data) : tree(&binarytree)
{
    this->data = data;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(BinaryTreeVec<Data> &binarytree, Data&& data) noexcept : tree(&binarytree)
{
    this->data = std::move(data);
}

// copy constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& other){
    this->tree = other.tree;
    this->data = other.data;
    this->valid = other.valid;
}

// move constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& other) noexcept {
    this->tree = std::move(other.tree);
    this->data = std::move(other.data);
    this->valid = std::move(other.valid);
}

// operator=

template <typename Data>
BinaryTreeVec<Data>::NodeVec BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& other){
    this->tree = other.tree;
    this->data = other.data;
    this->valid = other.valid;
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& other) noexcept {
    std::swap(tree, other.tree);
    std::swap(data, other.data);
    std::swap(valid, other.valid);
    return *this;
}

template <typename Data>
inline const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return data;
}

template <typename Data>
inline Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return data;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    const unsigned long childIndex = 2 * Index() + 1;
    const unsigned long address = BaseAddress() + childIndex;
    if (childIndex >= this->tree->vector.Size()) {
        return false;
    }
    return ((NodeVec*)address)->valid;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    const unsigned long childIndex = 2 * Index() + 2;
    const unsigned long address = BaseAddress() + childIndex;
    if (childIndex >= this->tree->vector.Size()) {
        return false;
    }
    return ((NodeVec*)address)->valid;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if (HasLeftChild() == false) throw std::out_of_range("NodeVec has no left child");
    const unsigned long address = 2 * Index() + 1;
    return this->tree->vector[address];
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if (HasRightChild() == false) throw std::out_of_range("NodeVec has no right child");
    const unsigned long address = 2 * Index() + 2;
    return this->tree->vector[address];
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if (HasLeftChild() == false) throw std::out_of_range("NodeVec has no left child");
    const unsigned long address = 2 * Index() + 1;
    return this->tree->vector[address];
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if (HasRightChild() == false) throw std::out_of_range("NodeVec has no right child");
    const unsigned long address = 2 * Index() + 2;
    return this->tree->vector[address];
}

template <typename Data>
inline unsigned long BinaryTreeVec<Data>::NodeVec::BaseAddress() const noexcept {
    return (unsigned long) &(this->tree->Root());
}

template <typename Data>
inline unsigned long BinaryTreeVec<Data>::NodeVec::Index() const noexcept {
    return ((unsigned long)this - BaseAddress()) / sizeof(NodeVec);
}

// BinaryTreeVec

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& traversable) {
    this->size = traversable.Size();
    this->vector.Resize(this->size);
    unsigned long index = 0;
    traversable.Traverse([this, &index](const Data& data){
        this->vector[index++] = NodeVec(*this, data);
    });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mappable) noexcept {
    this->size = mappable.Size();
    this->vector.Resize(this->size);
    unsigned long index = 0;
    mappable.Map([this, &index](Data& data){
        this->vector[index++] = NodeVec(*this, data);
    });
}


// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& other) {
    this->size = other.size;
    this->vector = other.vector;
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
        this->vector[i].tree = this;
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept{
    std::swap(this->size, other.size);
    std::swap(this->vector, other.vector);
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
        this->vector[i].tree = this;
    }
}

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& other){
    this->size = other.size;
    this->vector = other.vector;
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
        this->vector[i].tree = this;
    }
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& other) noexcept{
    std::swap(this->size, other.size);
    std::swap(this->vector, other.vector);
    unsigned long i;
    for (i = 0; i < this->size; ++i)
    {
        this->vector[i].tree = this;
    }
    return *this;
}


// Comparison operators
template <typename Data>
inline bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& other) const noexcept {
    return BinaryTree<Data>::operator==(other);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& other) const noexcept {
    return BinaryTree<Data>::operator!=(other);
}


// Specific member functions (inherited from BinaryTree)

template <typename Data>
const BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (this->Empty()) throw std::length_error("BinaryTreeVec is empty");
    return this->vector[0];
}

// Specific member function (inherited from MutableBinaryTree)

template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if (this->Empty()) throw std::length_error("BinaryTreeVec is empty");
    return this->vector[0];
}

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    this->size = 0;
    this->vector.Clear();
}

// Specific member function (inherited from BreadthTraversableContainer)

template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun function) const {
    for (unsigned long i = 0; i < this->Size(); ++i)
    {
        function (vector[i].Element());
    }
}

/* ************************************************************************ */

// Specific member function (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun function) {
    for (unsigned long i = 0; i < this->Size(); ++i)
    {
        function (vector[i].Element());
    }
}

/* ************************************************************************** */

}
