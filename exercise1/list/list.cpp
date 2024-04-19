
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
typename List<Data>::Node * List<Data>::Node::Clone(Node* tail){
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
    head = list.head->Clone(tail);
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
template <typename Data>
bool List<Data>::Insert(const Data& data){
  Node *curr = head;
  while (curr != nullptr && curr->data != data)
  {
    curr = curr->next;
  }
  if (curr == nullptr) {
    Node *newnode = new Node(data);
    curr->next = newnode;
  }
  return curr==nullptr;
}

template <typename Data>
bool List<Data>::Insert(Data&& data){
  Node *curr = head;
  while (curr != nullptr && curr->data != data)
  {
    curr = curr->next;
  }
  if (curr == nullptr) {
    Node *newnode = new Node(data);
    curr->next = newnode;
  }
  return curr==nullptr;
}

template <typename Data>
bool List<Data>::Remove(const Data& data) noexcept{
  Node *curr = head;
  Node *prec = nullptr;
  while (curr != nullptr && curr->data != data)
  {
    prec = curr;
    curr = curr->next;
  }
  if (curr != nullptr) {
    if (prec == nullptr)
    {
      RemoveFromFront();
    }
    else
    {
      prec->next = curr->next;
      curr->next = nullptr;
      delete curr;
    }
    return true;
  }
  return false;
}

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

template <typename Data>
Data& List<Data>::FrontNRemove(){
  Data& ret = Front();
  RemoveFromFront();
  return ret;
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

// front non mutable
// WHY THE FUCK "does not override" ???
template <typename Data>
const Data& List<Data>::Front() const{
  if (head == nullptr) throw std::length_error("List is empty");
  return head->data;
}

// front mutable
template <typename Data>
Data& List<Data>::Front() {
  if (head == nullptr) throw std::length_error("List is empty");
  return head->data;
}

// back non mutable
template <typename Data>
const Data& List<Data>::Back() const {
  if (tail == nullptr) throw std::length_error("List is empty");
  return tail->data;
}

// front non mutable
template <typename Data>
Data& List<Data>::Back() {
  if (tail == nullptr) throw std::length_error("List is empty");
  return tail->data;
}

// traverse
template <typename Data>
inline void List<Data>::Traverse(TraverseFun function) const {
  PreOrderTraverse(function);
}

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun function) const {
  struct Node *curr = head;
  while (curr != nullptr)
  {
    function(curr->data);
    curr = curr->next;
  }
}

template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun function) const {
  PostOrderTraverse(function, head);
}

// aux function for postorder
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun function, Node* curr) const {
  if (curr != nullptr)
  {
    PostOrderTraverse(function, curr->next);
    function(curr->data);
  }
}

// map
template <typename Data>
inline void List<Data>::Map(MapFun function){
  PreOrderMap(function);
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun function){
  struct Node *curr = head;
  while (curr != nullptr)
  {
    function(curr->data);
    curr = curr->next;
  }
}

template <typename Data>
inline void List<Data>::PostOrderMap(MapFun function) {
  PostOrderMap(function, head);
}

// aux function for postorder
template <typename Data>
void List<Data>::PostOrderMap(MapFun function, Node* curr) {
  if (curr != nullptr)
  {
    PostOrderMap(function, curr->next);
    function(curr->data);
  }
}


/* ************************************************************************** */

}
