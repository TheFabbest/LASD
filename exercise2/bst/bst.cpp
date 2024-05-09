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
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& other) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(other));
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

    const NodeLnk* curr = &root;
    while (curr->HasLeftChild())
    {
        curr = curr->LeftChild();
    }
    return curr->Element();
}

template <typename Data>
const Data BST<Data>::MinNRemove() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    // TODO semplificando ma con overhead?
    const NodeLnk* curr = &root;
    const NodeLnk* prec = nullptr;
    while (curr->HasLeftChild())
    {
        prec = curr;
        curr = curr->LeftChild();
    }
    Data ret = curr->Element(); // TODO no ref perche se no quando elimino perdo
    if (prec == nullptr) {
        const NodeLnk* oldroot = root;
        root = root->right;
        oldroot->right = nullptr;
        delete oldroot;
    }
    else {
        if (curr->HasRightChild())
        {
            if (prec->Element() > curr->RightChild().Element()) {
                prec->left = curr->right;
            }
            else {
                prec->right = curr->right;
            }
            curr->right = nullptr;
        }
        delete curr;
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

    const NodeLnk* curr = &root;
    const NodeLnk* prec = nullptr;
    while (curr->HasLeftChild())
    {
        prec = curr;
        curr = curr->LeftChild();
    }

    if (prec == nullptr) {
        const NodeLnk* oldroot = root;
        root = root->right;
        oldroot->right = nullptr;
        delete oldroot;
    }
    else {
        if (curr->HasRightChild())
        {
            if (prec->Element() > curr->RightChild().Element()) {
                prec->left = curr->right;
            }
            else {
                prec->right = curr->right;
            }
            curr->right = nullptr;
        }
        delete curr;
    }
}

template <typename Data>
const Data& BST<Data>::Max() const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
const Data& BST<Data>::MaxNRemove() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
void BST<Data>::RemoveMax() {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
const Data& BST<Data>::PredecessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
const Data& BST<Data>::SuccessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("BST is empty");
    }

}

// aux functions
template <typename Data>
void BST<Data>::Detach(const NodeLnk& node) {
    
}

/* ************************************************************************** */

}
