#include <iostream>
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
List<Data>::Node::Node(const Node & node) noexcept{
  data = node.data;
  //std::swap(next, node.next); // TODO se faccio cosi ovviamente non funziona perche const ma mi pare mog
  next = node.next;
}

// TODO mog ma why swap
template <typename Data>
List<Data>::Node::Node(Node && node) noexcept{
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
// constructors
template <typename Data>
inline List<Data>::List(const TraversableContainer<Data>& traversable)
{
  traversable.Traverse(
    [this] (const Data& data){
      this->Insert(data);
  });
}

template <typename Data>
inline List<Data>::List(MappableContainer<Data>&& mappable)
{
  mappable.Map(
    [this] (const Data& data){
      this->Insert(data);
  });
}

// TODO mog what??
// copy constructor
template <typename Data>
List<Data>::List(const List & other) noexcept{
  if (other.tail != nullptr)
  {
    tail = new Node(*other.tail);
    head = other.head->Clone(tail);
    size = other.size;
  }
}

// TODO mog
// move constructor
template <typename Data>
List<Data>::List(List && other) noexcept{
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& other) {
  if (other.tail != nullptr)
  {
    tail = new Node(*other.tail);
    head = other.head->Clone(tail);
    size = other.size;
  }
  return *this;
}

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  return *this;
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
    newnode->next = head;
    head = newnode;
  }
  ++size;
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
    newnode->next = head;
    head = newnode;
  }
  ++size;
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
      if (prec->next == nullptr) tail = prec;
    }
    --size;
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
  --size;
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
  ++size;
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
  ++size;
}


// TODO posso chiamare l'altro operatore?
template <typename Data>
const Data& List<Data>::operator[](const unsigned long index) const{
  if (index >= size) throw std::out_of_range("index out of range for this list");
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
  if (index >= size) throw std::out_of_range("index out of range for this list");
  unsigned long i;
  Node *curr = head;
  for (i = 0; i < index; ++i)
  {
    curr = curr->next;
  }
  return curr->data;
}

template <typename Data>
bool List<Data>::operator==(const List<Data>& other) const noexcept{
  bool are_equal = true;
  unsigned long counter = 0;
  other.Traverse([&are_equal, this, &counter](const Data& curr){
    are_equal &= curr == this->operator[](counter++);
  });
  return are_equal;
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data>& other) const noexcept{
  return !this->operator==(other);
}

// front non mutable
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
  Node *curr = head;
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
  Node *curr = head;
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
