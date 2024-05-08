#include <iostream>
#include <stdexcept>
using namespace std;
namespace lasd {

/* ************************************************************************** */

// Node

// TODO chiedi se uguaglianza controlla solo presenza o anche posizione (perche questo controlla anche posizione)
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& other) const noexcept{
    return Element() == other.Element() &&
        ((HasLeftChild() && other.HasLeftChild() && LeftChild() == other.LeftChild()) || (!HasLeftChild() && !other.HasLeftChild())) && 
        ((HasRightChild() && other.HasRightChild() && RightChild() == other.RightChild()) || (!HasRightChild() && !other.HasRightChild()));
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node& other) const noexcept{
    return !(this->operator==(other));
}

template <typename Data>
inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return !HasLeftChild() && !HasRightChild();
}


// BinaryTree
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& other) const noexcept{
    if (size == 0 && other.size == 0) return true;
    if (size != other.size) return false;
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


template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun function) const{
    if (size == 0) return;
    QueueLst<const Node*> queue;
    queue.Enqueue(&Root());
    while (!queue.Empty()) {
        const Node * curr = queue.HeadNDequeue();
        function (curr->Element());
        if (curr->HasLeftChild())
        {
            queue.Enqueue(&curr->LeftChild());
        }
        if (curr->HasRightChild())
        {
            queue.Enqueue(&curr->RightChild());
        }
    }
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun function, const Node& curr) const{
    function(curr.Element());
    if (curr.HasLeftChild()) PreOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PreOrderTraverse(function, curr.RightChild());
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun function, const Node& curr) const{
    if (curr.HasLeftChild()) PostOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PostOrderTraverse(function, curr.RightChild());
    function(curr.Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun function, const Node& curr) const{
    if (curr.HasLeftChild()) InOrderTraverse(function, curr.LeftChild());
    function(curr.Element());
    if (curr.HasRightChild()) InOrderTraverse(function, curr.RightChild());
}

// MutableNode

// MutableBinaryTree

// TODO check if preorder
template <typename Data>
inline void MutableBinaryTree<Data>::Map(MapFun function) {
    this->PreOrderMap(function);
}

template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun function) {
    if (size > 0) PreOrderMap(function, Root());
}

template <typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(MapFun function) {
    if (size > 0) PostOrderMap(function, Root());
}

template <typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(MapFun function) {
    if (size > 0) InOrderMap(function, Root());
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun function) {
    if (size == 0) return;
    QueueLst<MutableNode*> queue;
    queue.Enqueue(&Root());
    while (!queue.Empty()) {
        MutableNode * curr = queue.HeadNDequeue();
        function (curr->Element());
        if (curr->HasLeftChild())
        {
            queue.Enqueue(&curr->LeftChild());
        }
        if (curr->HasRightChild())
        {
            queue.Enqueue(&curr->RightChild());
        }
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun function, MutableNode& curr) const{
    function(curr.Element());
    if (curr.HasLeftChild()) PreOrderMap(function, curr.LeftChild());
    if (curr.HasRightChild()) PreOrderMap(function, curr.RightChild());
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun function, MutableNode& curr) const{
    if (curr.HasLeftChild()) PostOrderMap(function, curr.LeftChild());
    if (curr.HasRightChild()) PostOrderMap(function, curr.RightChild());
    function(curr.Element());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun function, MutableNode& curr) const{
    if (curr.HasLeftChild()) InOrderMap(function, curr.LeftChild());
    function(curr.Element());
    if (curr.HasRightChild()) InOrderMap(function, curr.RightChild());
}

// BTPreOrderIterator

// constructors
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &binarytree){
    this->tree = &binarytree;
    this->stack.Push(&tree->Root());
}

// copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& other) : tree(other.tree), stack(other.stack) {}

// move constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& other) noexcept
{
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& other){
    this->tree = other.tree;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& other) noexcept {
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& other) const noexcept{
    return this->tree == other.tree && this->stack == other.stack;
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
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if (stack.Empty()) throw std::out_of_range("BTPreOrderIterator was empty");
    const typename BinaryTree<Data>::Node* curr = stack.TopNPop();
    if (curr->HasRightChild()) {
        stack.Push(&curr->RightChild());
    }
    if (curr->HasLeftChild()) {
        stack.Push(&curr->LeftChild());
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept{
    if (tree == nullptr) return;
    stack.Clear();
    stack.Push(&tree->Root());
}

// BTPreOrderMutableIterator
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BinaryTree<Data> &binarytree) : BTPreOrderIterator<Data>(binarytree) {}

// copy constructor
template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& other) : BTPreOrderIterator<Data>(other) {}

template <typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& other) noexcept : BTPreOrderIterator<Data>(std::move(other)) {}

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
    if (binarytree.Size() > 0)
    {
        this->tree = &binarytree;
        FillToLeftMostLeaf(binarytree.Root());
    }
}

// copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& other) : tree(other.tree), stack(other.stack) {}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& other) noexcept
{
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& other){
    this->tree = other.tree;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& other) noexcept {
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& other) const noexcept{
    return this->tree == other.tree && this->stack == other.stack; // TODO stesso PUNTATORE a radice, se sono due alberi uguali ma non lo stesso albero allora gli iteratori sono diversi
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
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if (stack.Empty()) throw std::out_of_range("BTPostOrderIterator was empty");

    const typename BinaryTree<Data>::Node* old = stack.TopNPop();
    if (!stack.Empty())
    {
        const typename BinaryTree<Data>::Node * curr = stack.Top();
        if (curr->HasLeftChild() && &curr->LeftChild() == old && curr->HasRightChild()){
            FillToLeftMostLeaf(curr->RightChild());
        }
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept{
    if (this->tree == nullptr || this->tree->Empty()) return;
    stack.Clear();
    FillToLeftMostLeaf(this->tree->Root());
}

// aux functions
template <typename Data>
void BTPostOrderIterator<Data>::FillToLeftMostLeaf(const typename BinaryTree<Data>::Node& curr) {
    stack.Push(&curr);
    if (curr.HasLeftChild()) FillToLeftMostLeaf(curr.LeftChild());
    else if (curr.HasRightChild()) FillToLeftMostLeaf(curr.RightChild());
}


// BTPostOrderMutableIterator
template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BinaryTree<Data> &binarytree) : BTPostOrderIterator<Data>(binarytree) {}

// copy constructor
template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& other) : BTPostOrderIterator<Data>(other) {}

template <typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& other) noexcept : BTPostOrderIterator<Data>(std::move(other)) {}

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
    if (Terminated()) throw std::out_of_range("BTPostOrderIterator terminated");
    return stack.Top()->Element();
}

// BTInOrderIterator
// constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &binarytree){
    this->tree = &binarytree;
    if (binarytree.Empty()) return;

    const typename BinaryTree<Data>::Node *curr = &binarytree.Root();
    this->stack.Push(curr);
    while (curr->HasLeftChild())
    {
        curr = &curr->LeftChild();
        this->stack.Push(curr);
    }
}

// copy constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& other) : tree(other.tree), stack(other.stack) {}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& other) noexcept
{
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
}

// operator=
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& other){
    this->tree = other.tree;
    this->stack = other.stack;
    return this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& other) noexcept {
    std::swap(this->tree, other.tree);
    std::swap(this->stack, other.stack);
    return this;
}

// comparisons operator
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& other) const noexcept{
    return this->tree == other.tree && this->stack == other.stack; // TODO stesso PUNTATORE a radice
}

template <typename Data>
inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from Iterator
template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const{
    if (Terminated()) throw std::out_of_range("BTPreOrderIterator terminated");
    return stack.Top()->Element();
}

template <typename Data>
inline bool BTInOrderIterator<Data>::Terminated() const noexcept{
    return stack.Empty();
}

// inherited from ForwardIterator
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if (stack.Empty()) throw std::out_of_range("BTInOrderIterator was empty");

    const typename BinaryTree<Data>::Node* curr = stack.TopNPop();
    if (curr->HasRightChild()) {
        curr = &curr->RightChild();
        stack.Push(curr);
        while (curr->HasLeftChild())
        {
            curr = &curr->LeftChild();
            stack.Push(curr);
        }
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept{
    if (tree == nullptr || tree->Empty()) return;
    stack.Clear();
    const typename BinaryTree<Data>::Node* curr = &tree->Root();
    while (curr->HasLeftChild()) {
        curr = &curr->LeftChild();
        stack.Push(curr);
    }
}

// BTBreadthIterator
// constructors
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &binarytree){
    if (binarytree.Size() == 0) return;
    this->tree = &binarytree;
    this->queue.Enqueue(&binarytree.Root());
}

// copy constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& other) : tree(other.tree), queue(other.queue) {}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& other) noexcept
{
    std::swap(this->tree, other.tree);
    std::swap(this->queue, other.queue);
}

// operator=
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& other){
    this->tree = other.tree;
    this->queue = other.queue;
    return this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& other) noexcept {
    std::swap(this->tree, other.tree);
    std::swap(this->queue, other.queue);
    return this;
}

// comparisons operator
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& other) const noexcept{
    return (*this->tree) == (*other.tree) && this->queue == other.queue; // TODO controlla *tree o tree, eventualmente cambia o correggi gli altri
}

template <typename Data>
inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from Iterator
template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const{
    if (Terminated()) throw std::out_of_range("BTBreadthIterator terminated");
    return queue.Head()->Element();
}

template <typename Data>
inline bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return queue.Empty();
}

// inherited from ForwardIterator
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if (queue.Empty()) throw std::out_of_range("BTBreadthIterator was empty");
    const typename BinaryTree<Data>::Node& curr = *queue.HeadNDequeue();
    if (curr.HasLeftChild()){
        queue.Enqueue(&curr.LeftChild());
    }
    if (curr.HasRightChild()){
        queue.Enqueue(&curr.RightChild());
    }
    return *this;
}

// inherited from ResettableIterator
template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept{
    if (this->tree == nullptr || this->tree->Empty()) return;
    queue.Clear();
    queue.Enqueue(&this->tree->Root());
}


// BTBreadthMutableIterator
template <typename Data>
BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const MutableBinaryTree<Data> &binarytree) : BTBreadthIterator<Data>(binarytree) {}

// copy constructor
template <typename Data>
BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& other) : BTBreadthIterator<Data>(other) {}

template <typename Data>
BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& other) noexcept : BTBreadthIterator<Data>(std::move(other)) {}

// operator=
template <typename Data>
inline BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& other){
    return BTPostOrderIterator<Data>::operator=(other);
}

template <typename Data>
inline BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& other) noexcept{
    return BTPostOrderIterator<Data>::operator=(std::move(other));
}

// comparisons operator
template <typename Data>
bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data>& other) const noexcept{
    return BTPostOrderIterator<Data>::operator==(other);
}

template <typename Data>
inline bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data>& other) const noexcept{
    return !(this->operator==(other));
}

// inherited from MutableIterator

template <typename Data>
Data& BTBreadthMutableIterator<Data>::operator*() {
    if (this->Terminated()) throw std::out_of_range("BTBreadthMutableIterator terminated");
    return this->queue.Front()->Element();
}

/* ************************************************************************** */

}
