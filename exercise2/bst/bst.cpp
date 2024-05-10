#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& traversable){
    traversable.Traverse([](const Data& data){
        this->Insert(data);
    });
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& mappable) noexcept{
    mappable.Map([](Data& data){
        this->Insert(data);
    });
}

// copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data>& other) : BinaryTreeLnk<Data>(other) {}

// move constructor
template <typename Data>
BST<Data>::BST(BST<Data>&& other) noexcept : BinaryTreeLnk<Data>(std::move(other)) {}

// destructor
template <typename Data>
BST<Data>::~BST() {
    delete root;
}


// Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& other) {
    BinaryTreeLnk<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& other) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(other));
    return *this;
}

// Comparison operators
template <typename Data>
inline bool BST<Data>::operator==(const BST<Data>& other) const noexcept {
    return BinaryTreeLnk<Data>::operator==(other);
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& other) const noexcept {
    return BinaryTreeLnk<Data>::operator!=(other);
}


template <typename Data>
const Data& BST<Data>::Min() const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }
    return FindPointerToMin(root)->Element();
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk * min = DetachMin(root);
    Data ret = DataNDelete(min);
    return ret;
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk * min = DetachMin(root);
    delete min;
}

template <typename Data>
const Data& BST<Data>::Max() const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }
    return FindPointerToMax(root)->Element();
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk * max = DetachMax(root);
    Data ret = DataNDelete(max);
    return ret;
}

template <typename Data>
void BST<Data>::RemoveMax() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk * max = DetachMax(root);
    delete max;
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToPredecessor(root, data);
    if (*ptr == nullptr) {
        throw std::length_error("input has no predecessor");
    }
    NodeLnk * pre = Detach(*ptr);
    Data ret = DataNDelete(pre);
    return ret;
}

template <typename Data>
const Data& BST<Data>::PredecessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToPredecessor(root, dat);
    if (*ptr == nullptr) {
        throw std::length_error("No predecessor");
    }
    NodeLnk * pre = Detach(*ptr);
    Data rem = DataNDelete(pre);
    return rem;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToPredecessor(root, dat);
    if (*ptr == nullptr) {
        throw std::length_error("input has no predecessor");
    }
    NodeLnk * pre = Detach(*ptr);
    delete pre;
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToSuccessor(root, data);
    if (*ptr == nullptr) {
        throw std::length_error("input has no successor");
    }
    NodeLnk * pre = Detach(*ptr);
    Data ret = DataNDelete(pre);
    return ret;
}

template <typename Data>
const Data& BST<Data>::SuccessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToSuccessor(root, dat);
    if (*ptr == nullptr) {
        throw std::length_error("No successor");
    }
    NodeLnk * pre = Detach(*ptr);
    Data rem = DataNDelete(pre);
    return rem;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** ptr = FindPointerToSuccessor(root, dat);
    if (*ptr == nullptr) {
        throw std::length_error("input has no successor");
    }
    NodeLnk * pre = Detach(*ptr);
    delete pre;
}


template<typename Data>
bool BST<Data>::Insert(const Data & dat) {
    NodeLnk * & ptr = FindPointerTo(root, dat);
    if (ptr != nullptr) {
        return false;
    }
    ptr = new NodeLnk(dat);
    if (root == nullptr) {
        root = ptr;
    }
    ++size;
    return true;
}

template<typename Data>
bool BST<Data>::Insert(Data && dat) {
    NodeLnk * & ptr = FindPointerTo(root, dat);
    if (ptr != nullptr) {
        return false;
    }
    ptr = new NodeLnk(std::move(dat));
    if (root == nullptr) {
        root = ptr;
    }
    ++size;
    return true;
}

template<typename Data>
bool BST<Data>::Remove(const Data & dat) {
    NodeLnk * & ptr = FindPointerTo(root, dat);
    if (ptr != nullptr) {
        return false;
    }
    NodeLnk * nod = Detach(ptr);
    delete nod;
    return true;
}

template<typename Data>
bool BST<Data>::Exists(const Data & data) const noexcept {
    const NodeLnk * const & node = FindPointerTo(root, data);
    return node != nullptr;
}

// aux functions
template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk * node) {
    Data ret = node->Element();
    delete node;
    return ret;
}

template <typename Data>
void BST<Data>::Detach(const NodeLnk& node) {
    if (nod == nullptr) {
        return nullptr;
    }

    if (nod->left == nullptr) {
        return Skip2Right(nod);
    } else if (nod->right == nullptr) {
        return Skip2Left(nod);
    } else {
        NodeLnk * max = DetachMax(node->left);
        std::swap(node->data, max->data);
        return max;
    }
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMin(NodeLnk *& nod) noexcept {
    return Skip2Right(FindPointerToMin(nod));
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMax(NodeLnk *& nod) noexcept {
    return Skip2Left(FindPointerToMax(nod));
}

template <typename Data>
BST<Data>::NodeLnk * BST<Data>::Skip2Left(NodeLnk *& node) noexcept {
    NodeLnk *left = nullptr;
    if (node != nullptr)
    {
        std::swap(left, node->left); // node->left is nullptr, left = node->left
        std::swap(left, node); // node = left (old node->left), left = node
        --size;
    }
    return left;
}

// TODO vedi why return e why diverso dal prof
template <typename Data>
BST<Data>::NodeLnk * BST<Data>::Skip2Right(NodeLnk *& node) noexcept {
    // NodeLnk *right = nullptr;
    // if (node != nullptr)
    // {
    //     std::swap(right, node->right);
    //     std::swap(right, node);
    //     --size;
    // }
    // return right;

    if (node != nullptr) {
        NodeLnk *right = node->right;
        node->right = nullptr;
        node = right;
        --size;
    }
    return node;
}

template <typename Data>
BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& root) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(root));
}

// TODO vedi why prof diverso
template <typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMin(const NodeLnk * const & root) const noexcept {
    const NodeLnk *& curr = root;
    if (curr != nullptr) {
        while (curr->HasLeftChild())
        {
            curr = curr->LeftChild();
        }
    } 
    return &curr;
}

template <typename Data>
BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& root) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(root));
}

// TODO vedi why prof diverso
template <typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMax(const NodeLnk * const & root) const noexcept {
    const NodeLnk *& curr = root;
    if (curr != nullptr) {
        while (curr->HasRightChild())
        {
            curr = curr->RightChild();
        }
    } 
    return &curr;
}

template <typename Data>
BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& root, const Data& data) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(root, data));
}

// TODO vedi why prof diverso
template <typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerTo(const NodeLnk * const & root, const Data& data) const noexcept {
    if (root == nullptr) {
        return root;
    }

    const Data& curr = root->Element();
    if (data < curr) {
        if (root->HasLeftChild()) {
            return FindPointerTo(root->LeftChild(), data);
        }
        else {
            return root->left;
        }
    }
    else if (data > curr) {
        if (root->HasRightChild()) {
            return FindPointerTo(root->RightChild(), data);
        }
        else {
            return root->right;
        }
    }
    else {
        return root;
    }
}

template<typename Data>
BST<Data>::NodeLnk *& BST<Data>::FindPointerToPredecessor(NodeLnk *& node, const Data & data) noexcept {
    return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, data));
}

// TODO Messo *&, also e diverso
template<typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToPredecessor(const NodeLnk * const & node, const Data & data) const noexcept {
    if (node == nullptr)
    {
        return node;
    }

    const Data& curr = node->Element();
    if (data == curr)
    {
        const NodeLnk * const & pred = FindPointerToMax(node->left);
        return (pred == nullptr) ? node : pred;
    }
    else if (data < curr) {
        return FindPointerToPredecessor(node->left, data);
    }
    else
    {
        const NodeLnk * const & pred = FindPointerToPredecessor(node->left, data);
        if (pred == nullptr) {
            return node;
        }
        return (curr > pred->data) ? curr : pred->data;
    }
}

// TODO Messo *&, also e diverso
template<typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToSuccessor(const NodeLnk * const & node, const Data & data) const noexcept {
    if (node == nullptr)
    {
        return node;
    }

    const Data& curr = node->Element();
    if (data == curr)
    {
        const NodeLnk * const & pred = FindPointerToMin(node->right);
        return (pred == nullptr) ? node : pred;
    }
    else if (data > curr) {
        return FindPointerToSuccessor(node->right, data);
    }
    else
    {
        const NodeLnk * const & pred = FindPointerToSuccessor(node->right, data);
        if (pred == nullptr) {
            return node;
        }
        return (curr < pred->data) ? curr : pred->data;
    }
}
/* ************************************************************************** */

}
