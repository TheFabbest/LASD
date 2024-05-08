
namespace lasd {

/* ************************************************************************** */

// NodeVec

// specific constructors
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(BinaryTreeVec<Data> &binarytree, const Data& data) : tree(binarytree)
{
    this->data = data;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(BinaryTreeVec<Data> &binarytree, Data&& data) noexcept : tree(binarytree)
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
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    const unsigned long address = 2*tree->vector + 1;
    if (address >= tree->vector + sizeof(tree->vector)) return false; // TODO controlla bene, >= ?, anche right
    return (NodeVec*)address->valid;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    const unsigned long address = 2*tree->vector + 2;
    if (address >= tree->vector + sizeof(tree->vector)) return false;
    return (NodeVec*)address->valid;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if (HasLeftChild() == false) throw std::out_of_range("NodeVec has no left child");
    const unsigned long address = 2*tree->vector + 1;
    return (NodeVec*) address;
}

template <typename Data>
const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if (HasRightChild() == false) throw std::out_of_range("NodeVec has no right child");
    const unsigned long address = 2*tree->vector + 2;
    return (NodeVec*) address;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if (HasLeftChild() == false) throw std::out_of_range("NodeVec has no left child");
    const unsigned long address = 2*tree->vector + 1;
    return (NodeVec*) address;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if (HasRightChild() == false) throw std::out_of_range("NodeVec has no right child");
    const unsigned long address = 2*tree->vector + 2;
    return (NodeVec*) address;
}

// BinaryTreeVec

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& traversable) {
    // QueueVec<typename NodeVec**> queue;
    // queue.Enqueue(&this->Root());
    // traversable.Traverse([this, queue](const Data& data){
    //     NodeVec** curr = queue.HeadNDequeue();
    //     (*curr) = new NodeVec(this, data);
    //     queue.Enqueue(&(*curr)->LeftChild());
    //     queue.Enqueue(&(*curr)->RightChild());
    // });
    // queue.Clear();

    unsigned long index = 0;
    traversable.Traverse([this, index](const Data& data){
        ++index;
        unsigned long size = this->vector->Size();
        if (index >= size) {
            this->vector->Resize(size*2);
        }
        this->vector[index] = data;
    });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mappable) noexcept {
    unsigned long index = 0;
    mappable.Map([this, index](Data& data){
        ++index;
        unsigned long size = this->vector->Size();
        if (index >= size) {
            this->vector->Resize(size*2);
        }
        this->vector[index] = data;
    });
}


// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& other) {
    this->vector = other.vector;
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept;


// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    // todo
}

// Copy assignment
template <typename Data>
BinaryTreeVec& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& other){

}

// Move assignment
template <typename Data>
BinaryTreeVec& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& other) noexcept;


// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& other) const noexcept;

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& other) const noexcept;


// Specific member functions (inherited from BinaryTree)

template <typename Data>
const NodeVec& BinaryTreeVec<Data>::Root() const override;

// Specific member function (inherited from MutableBinaryTree)

template <typename Data>
NodeVec& BinaryTreeVec<Data>::Root() override;

// Specific member function (inherited from ClearableContainer)

void Clear() {

}

// Specific member function (inherited from BreadthTraversableContainer)

template <typename Data>
virtual void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun function) const {

}

/* ************************************************************************ */

// Specific member function (inherited from BreadthMappableContainer)

template <typename Data>
virtual void BinaryTreeVec<Data>::BreadthMap(MapFun function) {

}

/* ************************************************************************** */

}
