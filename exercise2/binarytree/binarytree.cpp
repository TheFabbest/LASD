#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// Node

// TODO chiedi se uguaglianza controlla solo presenza o anche posizione (perche questo controlla anche posizione)
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& other) const noexcept{
    return data == other.data &&
        ((HasLeftChild() && other.HasLeftChild() && LeftChild() == other.LeftChild()) || (!HasLeftChild() && !other.HasLeftChild())) && 
        ((HasRightChild() && other.HasRightChild() && RightChild() == other.RightChild()) || (!HasRightChild() && !other.HasRightChild()));
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node& other) const noexcept{
    return !(this->operator==(other));
}

template <typename Data>
const Data& BinaryTree<Data>::Node::Element() const noexcept {
    return data;
}

template <typename Data>
inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return !HasLeftChild() && !HasRightChild();
}


// BinaryTree
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& other) const noexcept{
    if (size == 0 && other.size == 0) return true;
    if (size == 0 || other.size == 0) return false;
    return Root() == other.Root();
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& other) const noexcept{
    return !(this->operator==(other));
}

template <typename Data>
inline void BinaryTree<Data>::Traverse(TraverseFun function) const{
    this->PreOrderTraverse(function);
}

template <typename Data>
inline void BinaryTree<Data>::PreOrderTraverse(TraverseFun function) const{
    if (size == 0) return;
    PreOrderTraverse(function, Root());
}

template <typename Data>
inline void BinaryTree<Data>::PostOrderTraverse(TraverseFun function) const{
    if (size == 0) return;
    PostOrderTraverse(function, Root());
}

template <typename Data>
inline void BinaryTree<Data>::InOrderTraverse(TraverseFun function) const{
    if (size == 0) return;
    InOrderTraverse(function, Root());
}

// TODO
// template <typename Data>
// void BinaryTree<Data>::BreadthTraverse(TraverseFun function) const{
//     if (size == 0) return;
//     BreadthTraverse(function, Root());
// }

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun function, const Node& curr) const{
    function(curr);
    if (curr.HasLeftChild()) PreOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PreOrderTraverse(function, curr.RightChild());
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun function, const Node& curr) const{
    if (curr.HasLeftChild()) PostOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PostOrderTraverse(function, curr.RightChild());
    function(curr);
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun function, const Node& curr) const{
    if (curr.HasLeftChild()) InOrderTraverse(function, curr.LeftChild());
    function(curr);
    if (curr.HasRightChild()) InOrderTraverse(function, curr.RightChild());
}

// template <typename Data>
// void BinaryTree<Data>::BreadthTraverse(TraverseFun function, const Node& curr) const{
//     function(curr);
//     if (curr.HasLeftChild()) PreOrderTraverse(function, curr.LeftChild());
//     if (curr.HasRightChild()) PreOrderTraverse(function, curr.RightChild());
// }

// MutableNode
template <typename Data>
Data& MutableBinaryTree<Data>::MutableNode::Element() noexcept {
    return data;
}

// MutableBinaryTree
template <typename Data>
MutableBinaryTree<Data>::~MutableBinaryTree(){
    delete root;
}

// TODO check if preorder
template <typename Data>
inline void MutableBinaryTree<Data>::Map(MapFun function) {
    this->PreOrderMap(function);
}

template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun function) {
    PreOrderMap(function, Root());
}

template <typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(MapFun function) {
    PostOrderMap(function, Root());
}

template <typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(MapFun function) {
    InOrderMap(function, Root());
}

// TODO
// template <typename Data>
// void MutableBinaryTree<Data>::BreadthMap(MapFun function) {
//     BreadthMap(function, Root());
// }

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun function, Node& curr) const{
    function(curr);
    if (curr.HasLeftChild()) PreOrderMap(function, curr.LeftChild());
    if (curr.HasRightChild()) PreOrderMap(function, curr.RightChild());
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun function, Node& curr) const{
    if (curr.HasLeftChild()) PostOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PostOrderTraverse(function, curr.RightChild());
    function(curr);
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun function, Node& curr) const{
    if (curr.HasLeftChild()) InOrderTraverse(function, curr.LeftChild());
    function(curr);
    if (curr.HasRightChild()) InOrderTraverse(function, curr.RightChild());
}

// BTPreOrderIterator

// constructors
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &binarytree){
    this->root = binarytree.Root();
    this->stack.Push(root);
}

// copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& other) : root(other.root), stack(other.stack) {}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& other) noexcept
{
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& other){
    this->root = other.root;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& other) const noexcept{
    return this->stack == other.stack && this->root == other.root; // TODO stesso PUNTATORE a radice
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from Iterator
template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const{
    if (Terminated()) throw std::out_of_range("BTPreOrderIterator terminated");
    return stack.Top()->Element();
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return stack.Empty();
}

// inherited from ForwardIterator
template <typename Data>
BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator++() {
    const Node* curr = stack.TopNPop();
    if (curr.HasLeftChild()) {
        stack.Push(curr.LeftChild());
    }
    if (curr.HasRightChild()) {
        stack.Push(curr.RightChild());
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept{
    if (root == nullptr) return;
    stack.Clear();
    stack.Push(root);
}

// BTPreOrderMutableIterator
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BinaryTree<Data> &binarytree) : BTPreOrderIterator(binarytree) {}

// copy constructor
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& other) : BTPreOrderIterator(other) {}

template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& other) : BTPreOrderIterator(std::move(other)) noexcept

// operator=
template <typename Data>
inline BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& other){
    return BTPreOrderIterator<Data>::operator=(other);
}

template <typename Data>
inline BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& other) noexcept{
    return BTPreOrderIterator<Data>::operator=(std::move(other));
}

// comparisons operator
template <typename Data>
bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator<Data>& other) const noexcept{
    return BTPreOrderIterator<Data>::operator==(other);
}

template <typename Data>
inline bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from MutableIterator

template <typename Data>
Data& BTPreOrderMutableIterator<Data>::operator*() {
    if (Terminated()) throw std::out_of_range("BTPreOrderIterator terminated");
    return stack.Top()->Element();
}

// BTPostOrderIterator
// constructors
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &binarytree){
    this->root = binarytree.Root();
    this->stack = StackLst<Node*>(binarytree); // TODO controlla ordine ma da codice ok
}

// copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& other) : root(other.root), stack(other.stack) {}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& other) noexcept
{
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& other){
    this->root = other.root;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& other) const noexcept{
    return this->stack == other.stack && this->root == other.root; // TODO stesso PUNTATORE a radice, se sono due alberi uguali ma non lo stesso albero allora gli iteratori sono diversi
}

template <typename Data>
inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from Iterator
template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const{
    if (Terminated()) throw std::out_of_range("BTPostOrderIterator terminated");
    return stack.Top()->Element();
}

template <typename Data>
inline bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    return stack.Empty();
}

// inherited from ForwardIterator
template <typename Data>
BTPostOrderIterator<Data> BTPostOrderIterator<Data>::operator++() {
    stack.Pop();
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept{
    stack.Clear();
    //stack = tree; // TODO UUU
}


// BTPostOrderMutableIterator
template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BinaryTree<Data> &binarytree) : BTPostOrderIterator(binarytree) {}

// copy constructor
template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& other) : BTPostOrderIterator(other) {}

template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& other) : BTPostOrderIterator(std::move(other)) noexcept

// operator=
template <typename Data>
inline BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator<Data>& other){
    return BTPostOrderIterator<Data>::operator=(other);
}

template <typename Data>
inline BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator<Data>&& other) noexcept{
    return BTPostOrderIterator<Data>::operator=(std::move(other));
}

// comparisons operator
template <typename Data>
bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator<Data>& other) const noexcept{
    return BTPostOrderIterator<Data>::operator==(other);
}

template <typename Data>
inline bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from MutableIterator

template <typename Data>
Data& BTPostOrderMutableIterator<Data>::operator*() {
    if (Terminated()) throw std::out_of_range("BTPreOrderIterator terminated");
    return stack.Top()->Element();
}

// BTInOrderIterator
// TODO solo copiato
// constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &binarytree){
    this->root = binarytree.Root();
    this->stack.Push(root);
}

// copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& other) : root(other.root), stack(other.stack) {}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& other) noexcept
{
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& other){
    this->root = other.root;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& other) const noexcept{
    return this->stack == other.stack && this->root == other.root; // TODO stesso PUNTATORE a radice
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from Iterator
template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const{
    if (Terminated()) throw std::out_of_range("BTPreOrderIterator terminated");
    return stack.Top()->Element();
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return stack.Empty();
}

// inherited from ForwardIterator
template <typename Data>
BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator++() {
    const Node* curr = stack.TopNPop();
    if (curr.HasLeftChild()) {
        stack.Push(curr.LeftChild());
    }
    if (curr.HasRightChild()) {
        stack.Push(curr.RightChild());
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept{
    if (root == nullptr) return;
    stack.Clear();
    stack.Push(root);
}

/* ************************************************************************** */

}
