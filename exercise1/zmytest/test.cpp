#include <iostream>
#include <random>
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"
#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/queue.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"

#include "../zlasdtest/container/traversable.hpp"

/* ************************************************************************** */

using namespace std;
using namespace lasd;

/* ************************************************************************** */

unsigned long num_of_errors = 0;


// AUXILIARY FUNCTIONS
void FoundError(const char *message, const char *testTitle)
{
  cout << "ERROR CALLING : " << message << " IN TEST " << testTitle << endl;
  num_of_errors++;
}

void TellTest(const char *name)
{
  cout << endl << endl << "---STARTING TEST " << name << "---" << endl; 
}

// CONTAINER
void TestEmptyContainer(lasd::Container &container)
{
  const char *TEST_TITLE = "Empty Container";
  if (container.Empty() == false || container.Size() != 0) FoundError("Emtpy or Size", TEST_TITLE);
}
void TestFullContainer(lasd::Container &container)
{
  const char *TEST_TITLE = "Full Container";
  if (container.Empty() == true || container.Size() == 0) FoundError("Emtpy or Size", TEST_TITLE);
}

// RESIZABLE CONTAINER
void TestResizableContainer(lasd::ResizableContainer &resizable, unsigned int newsize)
{
  const char *TEST_TITLE = "Resizable Container";
  resizable.Resize(newsize);
  if (resizable.Size() != newsize) FoundError("Resize or Size", TEST_TITLE);
}

// CLEARABLE CONTAINER
void TestClearableContainer(lasd::ClearableContainer &clearable)
{
  const char *TEST_TITLE = "Clearable Container";
  clearable.Clear();
  if (clearable.Size() != 0) FoundError("Clear or Size", TEST_TITLE);
  if (clearable.Empty() == false) FoundError("Empty or Size", TEST_TITLE);
}

// TESTABLE
void TestTestable(TestableContainer<int> &testable, bool empty, unsigned long size, int num_in_container)
{
  const char *TEST_TITLE = "Testable";
  if (testable.Empty() != empty) FoundError("Empty", TEST_TITLE);
  if (testable.Size() != size) FoundError("Size", TEST_TITLE);
  if (!testable.Empty()){
    if (!testable.Exists(num_in_container)) FoundError("Exists", TEST_TITLE);
  }
}

// DICTIONARY
void TestDictionary(lasd::DictionaryContainer<int> &dictionary)
{
  const char *TEST_TITLE = "Dictionary";
  if (!dictionary.Exists(9999))
  {
    unsigned long curr_size = dictionary.Size();
    dictionary.Remove(9999);
    if (dictionary.Size() != curr_size) FoundError("Remove", TEST_TITLE);
    dictionary.Insert(9999);
    ++curr_size;
    if (dictionary.Size() != curr_size) FoundError("Insert", TEST_TITLE);
    dictionary.Remove(9999);
    --curr_size;
    if (dictionary.Size() != curr_size) FoundError("Remove", TEST_TITLE);
  }
}

// TRAVERSABLE
void TestTraversable(lasd::TraversableContainer<int> &traversable, string expected_concat)
{
  const char *TEST_TITLE = "Traversable";
  string tot = "";
  traversable.Traverse([&tot](const int &curr) {tot = tot + to_string(curr);});
  string tot2 = "";
  tot2 = traversable.Fold(std::function([](const int &curr, const string &acc) {return acc+to_string(curr);}), string());
  if (tot != expected_concat) FoundError("Traverse", TEST_TITLE);
  if (tot2 != expected_concat) FoundError("Fold", TEST_TITLE);
}

// MAPPABLE
void TestMappable(lasd::MappableContainer<int> &mappable, string expected_concat)
{
  TestTraversable(mappable, expected_concat);
  mappable.Map([](int &curr) {curr++;});
}

// LINEAR
void TestLinear(lasd::LinearContainer<int> &linear, unsigned long size, int tot, int front, int back){
  const char *TEST_TITLE = "Linear";
  if (linear.Size() != size) FoundError("Size", TEST_TITLE);
  if (linear.Size() > 0)
  {
    if (linear.Front() != front) FoundError("Front", TEST_TITLE);
    if (linear.Back() != back) FoundError("Back", TEST_TITLE);
  }
  else
  {
    bool err = false;
    try{
      linear.Front();
    }
    catch (std::length_error &e){
      err = true;
    }
    if (err == false) FoundError("Front (when empty)", TEST_TITLE);
    err = false;
    try{
      linear.Back();
    }
    catch (std::length_error &e){
      err = true;
    }
    if (err == false) FoundError("Back (when empty)", TEST_TITLE);
  }
  
  int acc = 0;
  acc = linear.Fold(std::function([](const int &curr, const int &tot) {return tot+curr;}), acc);
  if (acc != tot) FoundError("Fold", TEST_TITLE);
}

// SORTABLE VECTOR
void TestEmptySortableVector(lasd::SortableVector<int> &sortablevec)
{
  bool error = false;
  TestEmptyContainer(sortablevec);

  if (sortablevec.Exists(2))
  {
    FoundError("Exists", "SortableVector");
  }
  
  if (!sortablevec.Empty())
  {
    FoundError("Empty", "SortableVector");
  }

  try{
    sortablevec.Back();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Back", "SortableVector");
  }

  try{
    sortablevec.Front();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Front", "SortableVector");
  }

  sortablevec.Sort();

  cout << "Testing Fold, Traverse and Map" << endl;
  int tot = 100;
  int res = sortablevec.Fold(std::function(FoldParity), tot);
  if (res != 100) FoundError("Fold", "SortableVector");

  sortablevec.Traverse(
    [](const int& dat) {
      FoundError("Traverse", "SortableVector");
    }
  );

  sortablevec.Map(
    [](int& dat) {
      FoundError("Map", "SortableVector");
    }
  );
}

void TestMiscellaneusUsageOfSortableVector()
{
  auto seed = random_device{}();
  cout << "Initializing random generator with seed " << seed << " for miscellaneus test." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned int> distx(0, 10);

  cout << "init list of random size and stack with random numbers" << endl;
  lasd::List<int> list = lasd::List<int>();
  unsigned int size = distx(genx);
  Vector<int> vec(size);
  cout << "Size is " << size << endl;
  
  for(unsigned int i = 0; i < size; i++) {
    unsigned int num = distx(genx);
    cout << "Pushing " << num << endl;
    list.InsertAtBack(num);
    vec[i] = num;
  }

  cout << "convert to sortable vector to test costructors" << endl;
  lasd::SortableVector<int> sortablevec = lasd::SortableVector<int>(list);
  lasd::SortableVector<int> othersortable = lasd::SortableVector<int>(std::move(vec));

  if (sortablevec != othersortable) FoundError("Comparison or Constructors", "Miscellaneus");

  cout << "convert it back to List to test costructors" << endl;
  List<int> lst = List<int>(sortablevec);

  cout << "sort the vector" << endl;
  sortablevec.Sort();

  cout << "traverse the vector to check correctness" << endl;
  unsigned int last = 0;
  sortablevec.Traverse([lst, &last](const unsigned int&n){
    if (!lst.Exists(n)) FoundError("Exists", "Miscellaneus"); // checking presence
    if (n < last) FoundError("Checking Order", "Miscellaneus"); // checking order
    last = n;
  });
  cout << endl;
}

void TestSortableVector()
{
  TellTest("SortableVector");
  cout << "Testing empty SortableVector" << endl;
  lasd::SortableVector<int> emptysortablevec = lasd::SortableVector<int>();
  TestEmptySortableVector(emptysortablevec);
  emptysortablevec.Clear();
  TestEmptySortableVector(emptysortablevec);
  TestMiscellaneusUsageOfSortableVector();
}

// LIST
void TestListInt(){
  List<int> lista = List<int>();

  TestEmptyContainer(lista);
  TestDictionary(lista);

  cout << "Remove on empty" << endl;
  lista.Remove(100);
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.Remove(100);
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");


  cout << "InsertAtBack" << endl;
  lista.InsertAtBack(15);
  if (lista.Empty()) FoundError("InsertAtBack or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtBack or Size", "List");

  cout << "Copy Assignment" << endl;
  List<int> lista2 = lista;
  if (lista2 != lista) FoundError("Comparison or Assignment", "List");

  cout << "Insert and Remove" << endl;
  lista.Insert(15);
  if (lista.Empty()) FoundError("Insert or Empty", "List");
  if (lista.Size() != 1) FoundError("Insert or Size", "List");
  
  lista.InsertAtFront(12);
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 2) FoundError("InsertAtFront or Size", "List");

  TestFullContainer(lista);

  lista.Remove(12);
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");

  lista.Remove(12);
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");

  lista.Remove(15);
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 0) FoundError("Remove or Size", "List");

  lista.InsertAtFront(15);
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtFront or Size", "List");
  if (lista != lista2) FoundError("InsertAtFront or Comparison", "List");

  cout << "Clearing" << endl;
  TestClearableContainer(lista);
  TestTestable(lista, true, 0, 0);

  cout << "Testing Constructors and Comparisons" << endl;
  List<int> lista3(lista2);
  if (lista2 != lista3) FoundError("Comparison", "List");

  lista3.Insert(123);
  List<int> lista4(std::move(lista3));
  if (lista4 == lista3) FoundError("Move", "List");
  if (lista3.Size() > 0) FoundError("Move", "List");

  cout << "Testing InsertAll and InsertSome" << endl;
  lista4.Insert(1);
  lista4.Insert(2);
  lista4.Insert(3);
  lista4.Insert(4);
  if (lista4.InsertSome(lista4)) FoundError("InsertSome", "List");
  if (lista4.InsertAll(lista4)) FoundError("InsertAll", "List");
  TestTestable(lista4, false, 6, 15);
  TestMappable(lista4, "432112315");
}

void TestList()
{
  TellTest("List");
  TestListInt();

  cout << "Testing List (mappable, traversable, linear)" << endl;
  List<int> lista = List<int>();
  lista.Insert(1);
  lista.Insert(2);
  lista.Insert(3);
  lista.Insert(4);
  TestMappable(lista, "4321"); // increments by one
  TestTraversable(lista, "5432");
  TestLinear(lista, 4, 14, 5, 2);
}

// QUEUE LIST
void TestEmptyQueueLst(lasd::QueueLst<int> queuelist)
{
  const char *TEST_TITLE = "QueueLst";
  bool error = false;
  TestEmptyContainer(queuelist);
  
  if (!queuelist.Empty())
  {
    FoundError("Exists", TEST_TITLE);
  }

  if (queuelist.Size() != 0)
  {
    FoundError("Size", TEST_TITLE);
  }

  try{
    queuelist.Dequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Dequeue", TEST_TITLE);
  }

  try{
    queuelist.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", TEST_TITLE);
  }

  try{
    queuelist.HeadNDequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("HeadNDequeue", TEST_TITLE);
  }

  queuelist.Enqueue(12);

  if (queuelist.Head() != 12)
  {
    FoundError("Head", TEST_TITLE);
  }

  if (queuelist.Size() != 1)
  {
    FoundError("Size", TEST_TITLE);
  }

  if (queuelist.HeadNDequeue() != 12)
  {
    FoundError("HeadNDequeue", TEST_TITLE);
  }

  if (queuelist.Size() != 0)
  {
    FoundError("Size", TEST_TITLE);
  }

  try{
    queuelist.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", TEST_TITLE);
  }
}

void TestQueueLstString(QueueLst<string> &queuelist)
{
  const char *TEST_TITLE = "QueueLst";
  string prima = "Stringa di Prova", seconda = "Seconda Stringa", terza = "Terza";

  unsigned long curr_size = queuelist.Size();

  cout << "Populating" << endl;
  queuelist.Enqueue(prima);
  curr_size++;
  if (queuelist.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);

  queuelist.Enqueue(seconda);
  curr_size++;
  if (queuelist.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);

  queuelist.Enqueue(terza);
  curr_size++;
  if (queuelist.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);
  
  cout << "Testing constructors" << endl;
  QueueLst<string> copy_constr(queuelist);
  Vector<string> vec(queuelist.Size());
  List<string> lst = List<string>();
  for (unsigned long i = 0; i < curr_size; i++)
  {
    vec[i] = queuelist.Head();
    queuelist.Enqueue(queuelist.HeadNDequeue());
  }

  for (unsigned long i = 0; i < curr_size; i++)
  {
    lst.InsertAtBack(queuelist.Head());
    queuelist.Enqueue(queuelist.HeadNDequeue());
  }

  QueueLst<string> trav_vec_constr(vec);
  QueueLst<string> trav_lst_constr(lst);
  QueueLst<string> mapp_constr(std::move(vec));

  cout << "Testing assignements" << endl;
  QueueLst<string> copy_assign;
  copy_assign = queuelist;
  
  cout << "Testing Enqueue and Dequeue" << endl;
  queuelist.Dequeue();
  string second = queuelist.Head();
  if (second != queuelist.HeadNDequeue()) FoundError("HeadNDequeue", TEST_TITLE);

  queuelist.Enqueue(prima);
  queuelist.Enqueue(seconda);
  queuelist.Enqueue(terza);
  if (queuelist.HeadNDequeue() != terza) FoundError("HeadNDequeue", TEST_TITLE);

  cout << "Testing comparisons" << endl;
  if (copy_constr != queuelist) FoundError("Comparisons (copy)", TEST_TITLE);
  if (trav_vec_constr != queuelist) FoundError("Comparisons (trav)", TEST_TITLE);
  if (trav_lst_constr != queuelist) FoundError("Comparisons (trav)", TEST_TITLE);
  if (mapp_constr != queuelist) FoundError("Comparisons (map)", TEST_TITLE);
  if (copy_assign != queuelist) FoundError("Comparisons (assign)", TEST_TITLE);
}

void TestQueueList()
{
  TellTest("QueueLst");
  lasd::QueueLst<int> queuelist = lasd::QueueLst<int>();
  TestEmptyQueueLst(queuelist);
  lasd::QueueLst<string> queueliststring = lasd::QueueLst<string>();
  TestQueueLstString(queueliststring);

  cout << "Testing Move Constructor" << endl;
  QueueLst<string> move_constr(std::move(queueliststring));
  TestQueueLstString(move_constr);
  
  cout << "Testing Move Assignment" << endl;
  QueueLst<string> move_assign = std::move(move_constr);
  TestQueueLstString(move_assign);
}

// QUEUE VEC
void TestEmptyQueueVec(lasd::QueueVec<int> queuevec){
  const char *TEST_TITLE = "QueueVec";
  bool error = false;
  
  if (!queuevec.Empty())
  {
    FoundError("Exists", TEST_TITLE);
  }

  if (queuevec.Size() != 0)
  {
    FoundError("Size", TEST_TITLE);
  }

  try{
    queuevec.Dequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Dequeue", TEST_TITLE);
  }

  try{
    queuevec.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", TEST_TITLE);
  }

  try{
    queuevec.HeadNDequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("HeadNDequeue", TEST_TITLE);
  }

  queuevec.Enqueue(12);

  if (queuevec.Head() != 12)
  {
    FoundError("Head", TEST_TITLE);
  }

  if (queuevec.Size() != 1)
  {
    FoundError("Size", TEST_TITLE);
  }

  if (queuevec.HeadNDequeue() != 12)
  {
    FoundError("HeadNDequeue", TEST_TITLE);
  }

  if (queuevec.Size() != 0)
  {
    FoundError("Size", TEST_TITLE);
  }

  try{
    queuevec.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", TEST_TITLE);
  }
}

void TestQueueVecString(QueueVec<string> &queuevec)
{
  const char *TEST_TITLE = "QueueVec";
  string prima = "Stringa di Prova", seconda = "Seconda Stringa", terza = "Terza";

  unsigned long curr_size = queuevec.Size();

  cout << "Populating" << endl;
  queuevec.Enqueue(prima);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);

  queuevec.Enqueue(seconda);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);

  queuevec.Enqueue(terza);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", TEST_TITLE);
  
  cout << "Testing constructors" << endl;
  QueueVec<string> copy_constr(queuevec);
  Vector<string> vec(queuevec.Size());
  List<string> lst = List<string>();
  for (unsigned long i = 0; i < curr_size; i++)
  {
    vec[i] = queuevec.Head();
    lst.InsertAtBack(vec[i]);
    queuevec.Enqueue(queuevec.HeadNDequeue());
  }

  QueueVec<string> trav_vec_constr(vec);
  QueueVec<string> trav_lst_constr(lst);
  QueueVec<string> mapp_constr(std::move(vec));

  cout << "Testing assignements" << endl;
  QueueVec<string> copy_assign;
  copy_assign = queuevec;
  
  cout << "Testing Enqueue and Dequeue" << endl;
  queuevec.Dequeue();
  string second = queuevec.Head();
  if (second != queuevec.HeadNDequeue()) FoundError("HeadNDequeue", TEST_TITLE);

  queuevec.Enqueue(prima);
  queuevec.Enqueue(seconda);
  queuevec.Enqueue(terza);
  if (queuevec.HeadNDequeue() != terza) FoundError("HeadNDequeue", TEST_TITLE);

  cout << "Testing comparisons" << endl;
  if (copy_constr != queuevec) FoundError("Comparisons (copy)", TEST_TITLE);
  if (trav_vec_constr != queuevec) FoundError("Comparisons (trav)", TEST_TITLE);
  if (trav_lst_constr != queuevec) FoundError("Comparisons (trav)", TEST_TITLE);
  if (mapp_constr != queuevec) FoundError("Comparisons (map)", TEST_TITLE);
  if (copy_assign != queuevec) FoundError("Comparisons (assign)", TEST_TITLE);

  cout << "Testing correctness of size" << endl;
  QueueVec<string> queue;
  bool error = false;
  try{
    queue.Dequeue();
  } catch (length_error &e){
    error = true;
  }
  if (!error) FoundError("Dequeue on empty", TEST_TITLE);

  if(queue.Size() != 0) FoundError("Size", TEST_TITLE);
  queue.Enqueue("1");
  if(queue.Size() != 1) FoundError("Size", TEST_TITLE);
  if (queue.HeadNDequeue() != "1") FoundError("HeadNDequeue", TEST_TITLE);
  if(queue.Size() != 0) FoundError("Size", TEST_TITLE);

  auto seed = random_device{}();
  cout << "Initializing random generator with seed " << seed << " for QueueVec population." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned int> distx(10, 30);

  cout << "Populating" << endl;
  List<string> inserted;
  unsigned long curr_s = 0;
  for (unsigned long i = 0; i < 500; i++)
  {
    unsigned int num = distx(genx);
    if (num < 20)
    {
      queue.Enqueue(to_string(num));
      inserted.InsertAtBack(to_string(num));
      ++curr_s;
      if(queue.Size() != curr_s) FoundError("Enqueue", TEST_TITLE);
    }
    else
    {
      try{
        queue.Dequeue();
        inserted.RemoveFromFront();
        --curr_s;
      }
      catch(length_error &e)
      {
        if (curr_s != 0) FoundError("Enqueue or Dequeue", TEST_TITLE);
      }
    }
  }
  if (queue != QueueVec<string>(inserted)) FoundError("Enqueue or Dequeue", TEST_TITLE);
  cout << "Clearing" << endl;
  TestClearableContainer(queue);
}

void TestQueueVec(){
  TellTest("QueueVec");
  lasd::QueueVec<int> queuevec = lasd::QueueVec<int>();
  TestEmptyQueueVec(queuevec);
  lasd::QueueVec<string> queuevecstring = lasd::QueueVec<string>();
  TestQueueVecString(queuevecstring);

  cout << "Retrying after move constructor" << endl;
  QueueVec<string> move_constr(std::move(queuevecstring));
  TestQueueVecString(move_constr);
  
  cout << "Retrying after move assignment" << endl;
  QueueVec<string> move_assign = std::move(move_constr);
  TestQueueVecString(move_assign);
}

// QUEUE
void TestQueue()
{
  const char *TEST_TITLE = "Queue"; 

  cout << "Comparison between empty structures" << endl;
  QueueVec<string> quevec = QueueVec<string>();
  QueueLst<string> quelst = QueueLst<string>();
  List<string> list = List<string>();
  SortableVector<string> vec = SortableVector<string>();
  if(quevec != QueueVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quelst != QueueLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quevec != QueueVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quelst != QueueLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);


  cout << "Comparison between empty and full structures" << endl;
  list.InsertAtBack("prima");
  list.InsertAtBack("seconda");
  list.InsertAtBack("terza");
  list.InsertAtBack("quarta");
  list.InsertAtBack("quinta");
  if(quevec == QueueVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quelst == QueueLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);


  cout << "Comparison between full structures" << endl;
  quevec.Enqueue("prima");
  quevec.Enqueue("seconda");
  quevec.Enqueue("terza");
  quevec.Enqueue("quarta");
  quevec.Enqueue("quinta");
  quelst.Enqueue("prima");
  quelst.Enqueue("seconda");
  quelst.Enqueue("terza");
  quelst.Enqueue("quarta");
  quelst.Enqueue("quinta");
  if(quevec != QueueVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quelst != QueueLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);

  vec = list;
  if(quevec != QueueVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(quelst != QueueLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);

  cout << "Comparison on moved queue" << endl;  
  QueueVec<string> moved (move(quevec));
  if (moved != QueueVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  moved = move(QueueVec<string>(vec));
  if (moved != QueueVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);

  QueueLst<string> movedlst (move(quelst));
  if (movedlst != QueueLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  movedlst = move(QueueLst<string>(list));
  if (movedlst != QueueLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
}

// STACK
void TestStack()
{
  const char *TEST_TITLE = "Stack"; 

  cout << "Comparison between empty structures" << endl;
  StackVec<string> stackvec = StackVec<string>();
  StackLst<string> stacklst = StackLst<string>();
  List<string> list = List<string>();
  SortableVector<string> vec = SortableVector<string>();
  if(stackvec != StackVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stacklst != StackLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stackvec != StackVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stacklst != StackLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  
  TestEmptyContainer(stackvec);
  TestEmptyContainer(stacklst);
  TestEmptyContainer(list);
  TestEmptyContainer(vec);


  cout << "Comparison between empty and full structures" << endl;
  list.InsertAtBack("prima");
  list.InsertAtBack("seconda");
  list.InsertAtBack("terza");
  list.InsertAtBack("quarta");
  list.InsertAtBack("quinta");
  if(stackvec == StackVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stacklst == StackLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);


  cout << "Comparison between full structures" << endl;
  stackvec.Push("prima");
  stackvec.Push("seconda");
  stackvec.Push("terza");
  stackvec.Push("quarta");
  stackvec.Push("quinta");
  stacklst.Push("quinta");
  stacklst.Push("quarta");
  stacklst.Push("terza");
  stacklst.Push("seconda");
  stacklst.Push("prima");
  if(stackvec != StackVec<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stacklst != StackLst<string>(list)) FoundError("Comparison or Constructor", TEST_TITLE);

  vec = list;
  if(stackvec != StackVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  if(stacklst != StackLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);

  cout << "Comparison on moved queue" << endl;  
  StackVec<string> moved (move(stackvec));
  if (moved != StackVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  moved = move(StackVec<string>(vec));
  if (moved != StackVec<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);

  StackLst<string> movedlst (move(stacklst));
  if (movedlst != StackLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
  movedlst = move(StackLst<string>(list));
  if (movedlst != StackLst<string>(vec)) FoundError("Comparison or Constructor", TEST_TITLE);
}

void TestStackVecString(StackVec<string> stackvec)
{
  const char *TEST_TITLE = "StackVec";
  string prima = "Stringa di Prova", seconda = "Seconda Stringa", terza = "Terza";

  unsigned long curr_size = stackvec.Size();
  if (curr_size == 0) TestEmptyContainer(stackvec);

  cout << "Populating" << endl;
  stackvec.Push(prima);
  curr_size++;
  if (stackvec.Size() != curr_size) FoundError("Push or Size", TEST_TITLE);

  stackvec.Push(seconda);
  curr_size++;
  if (stackvec.Size() != curr_size) FoundError("Push or Size", TEST_TITLE);

  stackvec.Push(terza);
  curr_size++;
  if (stackvec.Size() != curr_size) FoundError("Push or Size", TEST_TITLE);
  
  cout << "Testing constructors" << endl;
  StackVec<string> copy_constr(stackvec);
  Vector<string> vec(stackvec.Size());
  List<string> lst = List<string>();
  StackLst<string> support = StackLst<string>();
  for (unsigned long i = curr_size; i >= 1; --i)
  {
    vec[i-1] = stackvec.TopNPop();
    lst.InsertAtFront(vec[i-1]);
    support.Push(vec[i-1]);
  }

  for (unsigned long i = 0; i < curr_size; i++)
  {
    stackvec.Push(support.TopNPop());
  }

  StackVec<string> trav_vec_constr(vec);
  StackVec<string> trav_lst_constr(lst);
  StackVec<string> mapp_constr(std::move(vec));

  cout << "Testing assignements" << endl;
  StackVec<string> copy_assign;
  copy_assign = stackvec;
  
  cout << "Testing Push and Pop" << endl;
  stackvec.Pop();
  string second = stackvec.Top();
  if (second != stackvec.TopNPop()) FoundError("TopNPop", TEST_TITLE);
  if (stackvec.TopNPop() != prima) FoundError("TopNPop", TEST_TITLE);

  stackvec.Push(prima);
  stackvec.Push(seconda);
  stackvec.Push(terza);

  cout << "Testing comparisons" << endl;
  if (copy_constr != stackvec) FoundError("Comparisons (copy)", TEST_TITLE);
  if (trav_vec_constr != stackvec) FoundError("Comparisons (trav vec)", TEST_TITLE);
  if (trav_lst_constr != stackvec) FoundError("Comparisons (trav lst)", TEST_TITLE);
  if (mapp_constr != stackvec) FoundError("Comparisons (map)", TEST_TITLE);
  if (copy_assign != stackvec) FoundError("Comparisons (assign)", TEST_TITLE);

  cout << "Testing correctness of size" << endl;
  StackVec<string> stack;
  bool error = false;
  try{
    stack.Pop();
  } catch (length_error &e){
    error = true;
  }
  if (!error) FoundError("Pop on empty", TEST_TITLE);

  if(stack.Size() != 0) FoundError("Size", TEST_TITLE);
  stack.Push("1");
  if(stack.Size() != 1) FoundError("Size", TEST_TITLE);
  if (stack.TopNPop() != "1") FoundError("TopNPop", TEST_TITLE);
  if(stack.Size() != 0) FoundError("Size", TEST_TITLE);


  auto seed = random_device{}();
  cout << "Initializing random generator with seed " << seed << " for StackVec population." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned int> distx(0, 20);

  cout << "Populating" << endl;
  unsigned long curr_s = 0;
  for (unsigned long i = 0; i < 500; i++)
  {
    unsigned int num = distx(genx);
    if (num < 10)
    {
      stack.Push(to_string(num));
      ++curr_s;
      if(stack.Size() != curr_s) FoundError("Push", TEST_TITLE);
    }
    else
    {
      try{
        stack.Pop();
        --curr_s;
      }
      catch(length_error &e)
      {
        if (curr_s != 0) FoundError("Pop or Push", TEST_TITLE);
      }
    }
  }
  cout << "Clearing" << endl;
  TestClearableContainer(stack);
}

void TestStackVec()
{
  TellTest("StackVec");
  StackVec<string> stackvec;
  TestStackVecString(stackvec);
}

// results
void PrintResults()
{
  cout << endl << "END" << endl << "Errors: " << num_of_errors << endl;
}

void mytest() {
  TestSortableVector();
  TestList();
  TestQueueVec();
  TestQueueList();
  TestQueue();
  TestStack();
  TestStackVec();
  PrintResults();
}
