
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

// List
// constructors
template <typename Data>
inline List<Data>::List(const TraversableContainer<Data>& traversable)
{
  this->InsertAll(traversable);
}

template <typename Data>
inline List<Data>::List(MappableContainer<Data>&& mappable)
{
  this->InsertAll(mappable);
}

template <typename Data>
List<Data>::List(const List & list) noexcept{

}

// destructor
template <typename Data>
List<Data>::~List(){
  delete head;
}

// TODO mog, why not noexcept
template <typename Data>
void List<Data>::Clear() noexcept{
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

}
