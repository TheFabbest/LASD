
namespace lasd {

/* ************************************************************************** */
// Node

//TODO chiedi
// operators
template <typename Data>
bool List<Data>::Node::operator==(const Node& other) const noexcept
{
  return this->data == other->data \
    && ((next == nullptr && other.next == nullptr) || (next != nullptr && other.next != nullptr));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& other) const noexcept
{
  return !operator==(other);
}


// constructors
template <typename Data>
void List<Data>::Node::Node(const Data & data) noexcept{
  this->data = data;
}

template <typename Data>
void List<Data>::Node::Node(Data && data) noexcept{
  std::swap(this->data, data);
}

// TODO mog ma why swap
template <typename Data>
void List<Data>::Node::Node(Node & node) noexcept{
  data = node.data;
  std::swap(next, node.next);
}

// TODO mog ma why swap
template <typename Data>
void List<Data>::Node::Node(Node && node) noexcept{
  std::swap(data, node.data);
  std::swap(next, node.next);
}

// destructors
template <typename Data>
void List<Data>::Node::~Node(){
  delete next;
}

/* ************************************************************************** */

}
