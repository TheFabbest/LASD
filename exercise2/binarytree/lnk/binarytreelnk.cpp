
namespace lasd {

/* ************************************************************************** */

// NodeLnk
// specific constructors
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dat) {
    this->data = dat;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& dat) noexcept {
    std::swap(data, dat);
}

// copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const BinaryTreeLnk<Data>::NodeLnk& other) : left(other.left), right(other.right){
    this->data = other.data;
}

// move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(BinaryTreeLnk<Data>::NodeLnk&& other) noexcept{
    std::swap(data, other.data);
    std::swap(left, other.left);
    std::swap(right, other.right);
}

// copy assignment
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk BinaryTreeLnk<Data>::NodeLnk::operator=(const BinaryTreeLnk<Data>::NodeLnk& other){
    this->data = other.data;
    this->left = other.left;
    this->right = other.right;
    return *this;
}

// move assignment
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk BinaryTreeLnk<Data>::NodeLnk::operator=(BinaryTreeLnk<Data>::NodeLnk&& other) noexcept{
    std::swap(data, other.data);
    std::swap(left, other.left);
    std::swap(right, other.right);
    return *this;
}


template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept
{
    return left != nullptr;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept
{
    return right != nullptr;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
{
    if (left == nullptr) throw std::out_of_range("NodeLnk has no left child");
    return left;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const
{
    if (right == nullptr) throw std::out_of_range("NodeLnk has no right child");
    return right;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild()
{
    if (left == nullptr) throw std::out_of_range("NodeLnk has no left child");
    return left;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::RightChild()
{
    if (right == nullptr) throw std::out_of_range("NodeLnk has no right child");
    return right;
}

//BinaryTreeLnk

// TODO controlla bene
// constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& traversable){
    if (traversable.Empty()) return;
    QueueLst<NodeLnk**> queue;
    queue.Enqueue(&root);
    traversable.Traverse([&queue](const Data& currentData){
        NodeLnk** currentNode = queue.HeadNDequeue();
        (*currentNode) = new NodeLnk(currentData);
        queue.Enqueue(&(*currentNode)->left);
        queue.Enqueue(&(*currentNode)->right);
    });
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& mappable) noexcept{
    if (mappable.Empty()) return;
    QueueLst<NodeLnk**> queue;
    queue.Enqueue(&root);
    mappable.Map([&queue](Data&& currentData){
        NodeLnk** currentNode = queue.HeadNDequeue();
        (*currentNode) = new NodeLnk(std::move(currentData));
        queue.Enqueue(&(*currentNode)->left);
        queue.Enqueue(&(*currentNode)->right);
    });
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    delete root;
}

// from BinaryTree
template <typename Data>
const BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    if (root == nullptr) throw length_error("BinaryTreeLnk is empty");
    return root;
}

// from MutableBinaryTree
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root(){
    if (root == nullptr) throw length_error("BinaryTreeLnk is empty");
    return root;
}

// from ClearableContainer
template <typename Data>
void BinaryTreeLnk<Data>::Clear(){
    delete root;
    root = nullptr;
    size = 0;
    
}

/* ************************************************************************** */

}
