
namespace lasd {

/* ************************************************************************** */
// Node

//TODO mog chiedi
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


// TODO mog what??
template <typename Data>
struct Node * List<Data>::Node::Clone(Node* tail){
  if (next == nullptr)
  {
    return tail;
  } else {
    Node * node = new Node(data);
    node->next = next->Clone(tail);
    return node;
  }
}

// List
// constructors TODO controlla
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

// TODO mog what??
// copy constructor
template <typename Data>
List<Data>::List(const List & list) noexcept{
  if (list.tail != nullptr)
  {
    tail = new Node(*list.tail);
    head = lst.head->Clone(tail);
    size = list.size;
  }
}

// TODO mog
// move constructor
template <typename Data>
List<Data>::List(List && list) noexcept{
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
}

// TODO mog
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

// insert and remove

// copy
template <typename Data>
void List<Data>::InsertAtFront (const Data& data)
{
  Node *tmp = head;
  head = new Node(data);
  head->next = tmp;
  if (tail == nullptr)
  {
    tail = head;
  }
  ++size;
}

// move
template <typename Data>
void List<Data>::InsertAtFront (Data&& data)
{
  Node *tmp = head;
  head = new Node(std::move(data));
  head->next = tmp;
  if (tail == nullptr)
  {
    tail = head;
  }
  ++size;
}

// remove from front
template <typename Data>
void List<Data>::RemoveFromFront()
{
  if (tail == nullptr) throw std::length_error("List is empty");
  Node *tmp = head;
  head = head->next;
  tmp->next = nullptr;
  delete tmp;
}

// insert at back copy
template <typename Data>
void List<Data>::InsertAtBack (const Data& data){
  Node *tmp = new Node(data);
  if (tail != nullptr)
  {
    tail->next = tmp;
  }
  else
  {
    tail = tmp;
    head = tail;
  }
}

// insert at back move
template <typename Data>
void List<Data>::InsertAtBack (Data&& data){
  Node *tmp = new Node(data);
  if (tail != nullptr)
  {
    tail->next = tmp;
  }
  else
  {
    tail = tmp;
    head = tail;
  }
}


// TODO posso chiamare l'altro operatore?
template <typename Data>
const Data& List<Data>::operator[](const unsigned long index) const{
  unsigned long i;
  Node *curr = head;
  for (i = 0; i < index; ++i)
  {
    curr = curr->next;
  }
  return curr->data;
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index) {
  unsigned long i;
  Node *curr = head;
  for (i = 0; i < index; ++i)
  {
    curr = curr->next;
  }
  return curr->data;
}

/* ************************************************************************** */

}
