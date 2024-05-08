
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
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const BinaryTreeLnk<Data>::NodeLnk& other) {
    if (other.left != nullptr) {
        this->left = new NodeLnk(*other.left);
    }
    if (other.right != nullptr) {
        this->right = new NodeLnk(*other.right);
    }
    this->data = other.data;
}

// move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(BinaryTreeLnk<Data>::NodeLnk&& other) noexcept{
    std::swap(data, other.data);
    std::swap(left, other.left);
    std::swap(right, other.right);
}

// destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete left;
    delete right;
}

// copy assignment
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk BinaryTreeLnk<Data>::NodeLnk::operator=(const BinaryTreeLnk<Data>::NodeLnk& other){
    this->data = other.data;
    if (other.left != nullptr) {
        if (left == nullptr)
        {
            this->left = new NodeLnk(*other.left);
        }
        else
        {
            *this->left = *other.left;
        }
    }
    else if (left != nullptr) {
        delete left;
        left = nullptr;
    }

    if (other.right != nullptr) {
        if (right == nullptr)
        {
            this->right = new NodeLnk(*other.right);
        }
        else
        {
            *this->right = *other.right;
        }
    }
    else if (right != nullptr)
    {
        delete right;
        right = nullptr;
    }
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
    return *left;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const
{
    if (right == nullptr) throw std::out_of_range("NodeLnk has no right child");
    return *right;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild()
{
    if (left == nullptr) throw std::out_of_range("NodeLnk has no left child");
    return *left;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::RightChild()
{
    if (right == nullptr) throw std::out_of_range("NodeLnk has no right child");
    return *right;
}

template <typename Data>
inline const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return data;
}

template <typename Data>
inline Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return data;
}

//BinaryTreeLnk

// TODO controlla bene
// constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& traversable){
    if (traversable.Empty()) return;
    this->size = traversable.Size();
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
    this->size = mappable.Size();
    QueueLst<NodeLnk**> queue;
    queue.Enqueue(&root);
    mappable.Map([&queue](Data&& currentData){
        NodeLnk** currentNode = queue.HeadNDequeue();
        (*currentNode) = new NodeLnk(std::move(currentData));
        queue.Enqueue(&(*currentNode)->left);
        queue.Enqueue(&(*currentNode)->right);
    });
}

// come li fa il prof
// template <typename Data>
// BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& traversable){
//     if (traversable.Empty()) return;
//     size = traversable.Size();
//     QueueLst<NodeLnk**> queue;
//     queue.Enqueue(&root);
//     traversable.Traverse([&queue](const Data& currentData){
//         NodeLnk*&currentNode = *queue.HeadNDequeue();
//         currentNode = new NodeLnk(currentData);
//         queue.Enqueue(&currentNode->left);
//         queue.Enqueue(&currentNode->right);
//     });
// }

// template <typename Data>
// BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& mappable) noexcept{
//     if (mappable.Empty()) return;
//     size = mappable.Size();
//     QueueLst<NodeLnk**> queue;
//     queue.Enqueue(&root);
//     mappable.Map([&queue](Data& currentData){
//         NodeLnk*& currentNode = *queue.HeadNDequeue();
//         currentNode = new NodeLnk(currentData);
//         queue.Enqueue(&currentNode->left);
//         queue.Enqueue(&currentNode->right);
//     });
// }


// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& other) {
    if (other.root != nullptr) {
        this->root = new NodeLnk(*other.root);
        this->size = other.size;
    }
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->size, other.size);
}

// operator=
// copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& other) {
    this->Clear();
    root = new NodeLnk(*other.root);
    this->size = other.size;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->size, other.size);
    return *this;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& other) const noexcept {
    return BinaryTree<Data>::operator==(other);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& other) const noexcept {
    return BinaryTree<Data>::operator!=(other);
} 

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    delete root;
}

// from BinaryTree
template <typename Data>
const BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::Root() const{
    if (root == nullptr) throw std::length_error("BinaryTreeLnk is empty");
    return *root;
}

// from MutableBinaryTree
template <typename Data>
BinaryTreeLnk<Data>::MutableNode& BinaryTreeLnk<Data>::Root(){
    if (root == nullptr) throw length_error("BinaryTreeLnk is empty");
    return *root;
}

// from ClearableContainer
template <typename Data>
void BinaryTreeLnk<Data>::Clear(){
    delete root;
    this->root = nullptr;
    this->size = 0;   
}

/* ************************************************************************** */

}
