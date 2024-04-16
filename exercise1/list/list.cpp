
namespace lasd {

/* ************************************************************************** */
// Node

//TODO chiedi
// operators
template <typename Data>
bool List<Data>::Node::operator==(const struct Node& other) const noexcept
{
  return this->data == other->data \
    && ((next == nullptr && other.next == nullptr) || (next != nullptr && other.next != nullptr));
}

template <typename Data>
bool List<Data>::Node::operator!=(const struct Node& other) const noexcept
{
  return !operator==(other);
}


// constructors
// TODO noexcept?
template <typename Data>
List<Data>::Node::Node(const Data & data) {
  this->data = data;
}

template <typename Data>
List<Data>::Node::Node(Data && data){
  std::swap(this->data, data);
}

// TODO mog ma why swap
template <typename Data>
List<Data>::Node::Node(const struct Node & node) noexcept{
  data = node.data;
  std::swap(next, node.next);
}

// TODO mog ma why swap
template <typename Data>
List<Data>::Node::Node(struct Node && node) noexcept{
  std::swap(data, node.data);
  std::swap(next, node.next);
}

// destructors
template <typename Data>
List<Data>::Node::~Node(){
  delete next;
}

/* ************************************************************************** */

}
