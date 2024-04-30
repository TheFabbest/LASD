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
void BinaryTree<Data>::PreOrderTraverse(TraverseFun function) const{
    // TODO iter?
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun function) const{
    // TODO iter?
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun function) const{
    // TODO iter?
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun function) const{
    // TODO iter?
}

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
void MutableBinaryTree<Data>::PreOrderMap(MapFun function) {
    // TODO iter?
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun function) {
    // TODO iter?
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun function) {
    // TODO iter?
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun function) {
    // TODO iter?
}

/* ************************************************************************** */

}
