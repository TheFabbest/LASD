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

#include <random>

/* ************************************************************************** */

#include <iostream>

using namespace std;
using namespace lasd;

/* ************************************************************************** */

unsigned long num_of_errors = 0;


// AUXILIARY FUNCTIONS
void FoundError(const char *message, const char *testTitle)
{
  cout << "Error when trying method: " << message << " in " << testTitle << endl;
  num_of_errors++;
}

void TellTest(const char *name)
{
  cout << endl << endl << "---STARTING TEST " << name << "---" << endl; 
}

// SORTABLE VECTOR
void TestEmptySortableVector(lasd::SortableVector<int> &sortablevec)
{
  bool error = false;

  cout << "Testing empty SortableVector" << endl;

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

  int tot = 100;
  sortablevec.Fold(std::function(FoldParity), tot);
  if (tot != 100) FoundError("Fold", "SortableVector");

  sortablevec.Traverse(
    [](const int& dat) {
      std::cout << "ERROR: READING " << dat << endl;
      FoundError("Traverse", "SortableVector");
    }
  );

  sortablevec.Map(
    [](int& dat) {
      cout << "ERROR: READING " << dat << endl;
      FoundError("Map", "SortableVector");
    }
  );
}

void TestSortableVector()
{
  TellTest("SortableVector");
  lasd::SortableVector<int> emptysortablevec = lasd::SortableVector<int>();
  TestEmptySortableVector(emptysortablevec);
  emptysortablevec.Clear();
  TestEmptySortableVector(emptysortablevec);
}

// LIST
void TestListInt(){
  List<int> lista = List<int>();
  lista.Remove(100);
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.Remove(100);
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.InsertAtBack(15);
  if (lista.Empty()) FoundError("InsertAtBack or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtBack or Size", "List");

  List<int> lista2 = lista;
  if (lista2 != lista) FoundError("Comparison", "List");

  lista.Insert(15);
  if (lista.Empty()) FoundError("Insert or Empty", "List");
  if (lista.Size() != 1) FoundError("Insert or Size", "List");
  
  lista.InsertAtFront(12);
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 2) FoundError("InsertAtFront or Size", "List");

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

  lista.Clear();
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 0) FoundError("Remove or Size", "List");

  List<int> lista3(lista2);
  if (lista2 != lista3) FoundError("Comparison", "List");

  lista3.Insert(123);
  List<int> lista4(std::move(lista3));
  if (lista4 == lista3) FoundError("Move", "List");
  if (lista3.Size() > 0) FoundError("Move", "List");
}

void TestList()
{
  TestListInt();
}

// QUEUE LIST
void TestEmptyQueueLst(lasd::QueueLst<int> queuelist)
{
  const char *TEST_TITLE = "QueueLst";
  bool error = false;
  
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
  cout << "Size is " << curr_size << endl;

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
  for (unsigned long i = 0; i < curr_size; i++)
  {
    vec[i] = queuelist.Head();
    queuelist.Enqueue(queuelist.HeadNDequeue());
  }

  List<string> lst = List<string>();
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
  cout << "Size is " << curr_size << endl;

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
  for (unsigned long i = 0; i < curr_size; i++)
  {
    vec[i] = queuevec.Head();
    queuevec.Enqueue(queuevec.HeadNDequeue());
  }

  List<string> lst = List<string>();
  for (unsigned long i = 0; i < curr_size; i++)
  {
    lst.InsertAtBack(queuevec.Head());
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

  for (unsigned long i = 0; i < 50; i++)
  {
    queue.Enqueue("1");
    if(queue.Size() != i+1) FoundError("Enqueue", TEST_TITLE);
  }
  for (unsigned long i = 1; i <= 37; i++)
  {
    queue.Dequeue();
    if(queue.Size() != 50 - i) FoundError("Dequeue", TEST_TITLE);
  }
  for (unsigned long i = 13; i < 51; i++)
  {
    queue.Enqueue("1");
    if(queue.Size() != i+1) FoundError("Enqueue", TEST_TITLE);
  }
  queue.Clear();
  if (queue.Size() != 0) FoundError("Clear", TEST_TITLE);
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
  cout << "Size is " << curr_size << endl;

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
  StackLst<string> support;
  for (unsigned long i = 0; i < curr_size; i++)
  {
    vec[i] = stackvec.Top();
    lst.InsertAtBack(vec[i]);
    support.Push(stackvec.TopNPop());
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

  stackvec.Push(prima);
  stackvec.Push(seconda);
  stackvec.Push(terza);
  if (stackvec.TopNPop() != terza) FoundError("TopNPop", TEST_TITLE);

  cout << "Testing comparisons" << endl;
  if (copy_constr != stackvec) FoundError("Comparisons (copy)", TEST_TITLE);
  if (trav_vec_constr != stackvec) FoundError("Comparisons (trav)", TEST_TITLE);
  if (trav_lst_constr != stackvec) FoundError("Comparisons (trav)", TEST_TITLE);
  if (mapp_constr != stackvec) FoundError("Comparisons (map)", TEST_TITLE);
  if (copy_assign != stackvec) FoundError("Comparisons (assign)", TEST_TITLE);

  cout << "Testing correctness of size" << endl;
  StackVec<string> queue;
  bool error = false;
  try{
    queue.Pop();
  } catch (length_error &e){
    error = true;
  }
  if (!error) FoundError("Pop on empty", TEST_TITLE);

  if(queue.Size() != 0) FoundError("Size", TEST_TITLE);
  queue.Push("1");
  if(queue.Size() != 1) FoundError("Size", TEST_TITLE);
  if (queue.TopNPop() != "1") FoundError("TopNPop", TEST_TITLE);
  if(queue.Size() != 0) FoundError("Size", TEST_TITLE);

  for (unsigned long i = 0; i < 50; i++)
  {
    queue.Push("1");
    if(queue.Size() != i+1) FoundError("Push", TEST_TITLE);
  }
  for (unsigned long i = 1; i <= 37; i++)
  {
    queue.Pop();
    if(queue.Size() != 50 - i) FoundError("Pop", TEST_TITLE);
  }
  for (unsigned long i = 13; i < 51; i++)
  {
    queue.Push("1");
    if(queue.Size() != i+1) FoundError("Push", TEST_TITLE);
  }
  queue.Clear();
  if (queue.Size() != 0) FoundError("Clear", TEST_TITLE);
}

void TestStackVec()
{
  StackVec<string> stackvec;
  TestStackVecString(stackvec);
}

// results
void PrintResults()
{
  cout << endl << "Errors: " << num_of_errors << endl;
}

void TestMiscellaneus()
{
  cout << "Starting TestMiscellaneus" << endl;

  auto seed = random_device{}();
  cout << "Initializing random generator with seed " << seed << " for miscellaneus test." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned int> distx(0, 10);

  cout << "init list of random size and stack with random numbers" << endl;
  lasd::List<int> list = lasd::List<int>();
  StackVec<int> stack;
  unsigned int size = distx(genx);
  cout << "Size is " << size << endl;
  
  for(unsigned int i = 0; i < size; i++) {
    unsigned int num = distx(genx);
    cout << "Pushing " << num << endl;
    list.InsertAtBack(num);
    stack.Push(num);
  }

  cout << "convert to sortable vector to test costructors" << endl;
  lasd::SortableVector<int> sortablevec = lasd::SortableVector<int>(list);

  cout << "convert it back to List to test costructors" << endl;
  List<int> lst = List<int>(sortablevec);

  cout << "sort the vector" << endl;
  sortablevec.Sort();

  cout << "traverse the vector to check correctness" << endl;
  unsigned int last = 0;
  sortablevec.Traverse([lst, &last](const unsigned int&n){
    if (!lst.Exists(n)) cout << "ERROR (Exists)" << n << endl; // checking presence
    if (n < last) cout << "ERROR (order)" << endl; // checking order
    last = n;
  });

  cout << "convert list to stack" << endl;
  StackVec<int> second_stack = StackVec<int>(list);
  if (stack != second_stack){
    cout << "ERROR" << endl;
  }
  second_stack.Clear();

  cout << endl;
}

void mytest() {
  TestMiscellaneus();
  TestSortableVector();
  TestList();
  TestQueueVec();
  TestQueueList();
  TestQueue();
  TestStack();
  TestStackVec();
  PrintResults();
  //PureRandomTest(); TODO
  cout << "END" << endl;
}
