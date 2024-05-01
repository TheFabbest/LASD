#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// Node

// TODO chiedi se altri hanno fatto cosi + chiedi se uguaglianza controlla solo presenza o anche posizione (perche questo controlla anche posizione)
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
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return !HasLeftChild() && !HasRightChild();
}


// BinaryTree
template <typename Data>
BinaryTree<Data>::~BinaryTree(){
    delete root;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTree<Data>::Root() const{
    if (root == nullptr) throw std::length_error("Binary Tree is Empty");
    return *root;
}

// TODO check if preorder
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
void BinaryTree<Data>::PreOrderTraverse(TraverseFun function, Node& curr) const{
    function(curr);
    if (curr.HasLeftChild()) PreOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PreOrderTraverse(function, curr.RightChild());
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun function, Node& curr) const{
    if (curr.HasLeftChild()) PostOrderTraverse(function, curr.LeftChild());
    if (curr.HasRightChild()) PostOrderTraverse(function, curr.RightChild());
    function(curr);
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun function, Node& curr) const{
    if (curr.HasLeftChild()) InOrderTraverse(function, curr.LeftChild());
    function(curr);
    if (curr.HasRightChild()) InOrderTraverse(function, curr.RightChild());
}

// template <typename Data>
// void BinaryTree<Data>::BreadthTraverse(TraverseFun function, Node& curr) const{
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

template <typename Data>
const MutableBinaryTree<Data>::MutableNode& MutableBinaryTree<Data>::Root() const{
    if (root == nullptr) throw std::length_error("Binary Tree is Empty");
    return *root;
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

/* ************************************************************************** */

}
