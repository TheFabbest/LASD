#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// constructors
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& traversable){
    traversable.Traverse([this](const Data& data){
        this->Insert(data);
    });
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& mappable) noexcept{
    mappable.Map([this](Data& data){
        this->Insert(data);
    });
}

// copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data>& other) : BinaryTreeLnk<Data>(other) {}

// move constructor
template <typename Data>
BST<Data>::BST(BST<Data>&& other) noexcept : BinaryTreeLnk<Data>(std::move(other)) {}

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
    if (size != other.Size()) {
        return false;
    }
    BTInOrderIterator<Data> iter1(*this);
    BTInOrderIterator<Data> iter2(other);
    while (!iter1.Terminated()) {
        if (*iter1 != *iter2) {
            return false;
        }
        ++iter1;
        ++iter2;
    }
    return true;
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& other) const noexcept {
    return !this->operator==(other);
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

    const NodeLnk * const & node = FindPointerToPredecessor(root, data);
    if (node == nullptr) {
        throw std::length_error("input has no predecessor");
    }
    return node->Element();
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** node = &FindPointerToPredecessor(root, data);
    if (*node == nullptr) {
        throw std::length_error("No predecessor");
    }

    NodeLnk * pre = Detach(*node);
    Data rem = DataNDelete(pre);
    return rem;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** node = &FindPointerToPredecessor(root, data);
    if (*node == nullptr) {
        throw std::length_error("input has no predecessor");
    }
    NodeLnk * pre = Detach(*node);
    delete pre;
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    const NodeLnk * const & node = FindPointerToSuccessor(root, data);
    if (node == nullptr) {
        throw std::length_error("input has no successor");
    }
    return node->Element();
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** node = &FindPointerToSuccessor(root, data);
    if (*node == nullptr) {
        throw std::length_error("No successor");
    }
    NodeLnk * pre = Detach(*node);
    Data rem = DataNDelete(pre);
    return rem;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    NodeLnk ** node = &FindPointerToSuccessor(root, data);
    if (*node == nullptr) {
        throw std::length_error("input has no successor");
    }
    NodeLnk * pre = Detach(*node);
    delete pre;
}


template<typename Data>
bool BST<Data>::Insert(const Data & data) {
    NodeLnk * & ptr = FindPointerTo(root, data);
    if (ptr != nullptr) {
        return false;
    }
    ptr = new NodeLnk(data);
    if (root == nullptr) {
        root = ptr;
    }
    ++size;
    return true;
}

template<typename Data>
bool BST<Data>::Insert(Data && data) {
    NodeLnk * & ptr = FindPointerTo(root, data);
    if (ptr != nullptr) {
        return false;
    }
    ptr = new NodeLnk(std::move(data));
    if (root == nullptr) {
        root = ptr;
    }
    ++size;
    return true;
}

template<typename Data>
bool BST<Data>::Remove(const Data & data) {
    NodeLnk * & ptr = FindPointerTo(root, data);
    if (ptr == nullptr) {
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
BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->left == nullptr) {
        return Skip2Right(node);
    } else if (node->right == nullptr) {
        return Skip2Left(node);
    } else {
        NodeLnk * max = DetachMax(node->left);
        std::swap(node->data, max->data);
        return max;
    }
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMin(NodeLnk *& node) noexcept {
    return Skip2Right(FindPointerToMin(node));
}

template<typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMax(NodeLnk *& node) noexcept {
    return Skip2Left(FindPointerToMax(node));
}

// TODO decidi!
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
    NodeLnk *right = nullptr;
    if (node != nullptr)
    {
        std::swap(right, node->right);
        std::swap(right, node);
        --size;
    }
    return right;

    // non funziona
    // if (node != nullptr) {
    //     NodeLnk *right = node->right;
    //     node->right = nullptr;
    //     node = right;
    //     --size;
    // }
    // return node;
}

template <typename Data>
BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& root) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(root));
}

// TODO vedi why prof diverso
template <typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMin(const NodeLnk * const & root) const noexcept {
    const NodeLnk * const * curr = &root;
    if (*curr != nullptr) {
        while ((*curr)->HasLeftChild())
        {
            curr = &((*curr)->left);
        }
    } 
    cout << (*curr)->Element();
    return *curr;
}

template <typename Data>
BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& root) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(root));
}

// TODO vedi why prof diverso
template <typename Data>
const BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMax(const NodeLnk * const & root) const noexcept {
    const NodeLnk * const * curr = &root;
    if (*curr != nullptr) {
        while ((*curr)->HasRightChild())
        {
            curr = &((*curr)->right);
        }
    } 
    return *curr;
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
            return FindPointerTo(root->left, data);
        }
        else {
            return root->left;
        }
    }
    else if (data > curr) {
        if (root->HasRightChild()) {
            return FindPointerTo(root->right, data);
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
        return pred;
    }
    else if (data < curr) {
        return FindPointerToPredecessor(node->left, data);
    }
    else
    {
        const NodeLnk * const & pred = FindPointerToPredecessor(node->right, data);
        if (pred == nullptr) {
            return node;
        }
        return (curr > pred->data) ? node : pred;
    }
}


template<typename Data>
BST<Data>::NodeLnk *& BST<Data>::FindPointerToSuccessor(NodeLnk *& node, const Data & data) noexcept {
    return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, data));
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
        const NodeLnk * const & succ = FindPointerToMin(node->right);
        return succ;
    }
    else if (data > curr) {
        return FindPointerToSuccessor(node->right, data);
    }
    else
    {
        const NodeLnk * const & succ = FindPointerToSuccessor(node->left, data);
        if (succ == nullptr) {
            return node;
        }
        return (curr < succ->data) ? node : succ;
    }
}
/* ************************************************************************** */

}
