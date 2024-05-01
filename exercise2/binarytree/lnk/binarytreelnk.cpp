
namespace lasd {

/* ************************************************************************** */

//BinaryTreeLnk

// constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& traversable){
    if (traversable.Empty()) return;
    root = new BinaryTree<Data>::Node();
    traversable.Traverse([](const Data& curr){
        
    });
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    delete root;
}

/* ************************************************************************** */

}
