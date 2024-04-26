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

void FoundError(const char *message, const char *testTitle)
{
  cout << "Error when trying method: " << message << " in " << testTitle << endl;
  num_of_errors++;
}

void TellTest(const char *name)
{
  cout << endl << endl << "---STARTING TEST " << name << "---" << endl; 
}

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
    [](const int& dat) {
      cout << "ERROR: READING " << dat << endl;
      FoundError("Map", "SortableVector");
    }
  );
}

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

void TestListString()
{
  List<string> lista = List<string>();

  cout << "Removing on empty" << endl;
  lista.Remove(string());
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.Remove("Albero");
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.Remove("Albero");
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  cout << "InsertAtBack(\"C\")" << endl;
  lista.InsertAtBack("C");
  if (lista.Empty()) FoundError("InsertAtBack or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtBack or Size", "List");

  cout << "Copy Assignment" << endl;
  List<string> lista2;
  lista2 = lista;
  if (lista2 != lista) FoundError("Comparison", "List");

  cout << "Insert and Remove" << endl;
  lista.Insert("C");
  if (lista.Empty()) FoundError("Insert or Empty", "List");
  if (lista.Size() != 1) FoundError("Insert or Size", "List");
  
  lista.InsertAtFront("B");
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 2) FoundError("InsertAtFront or Size", "List");
  if (lista.Front() != "B" || lista.Back() != "C") FoundError("Front or Back", "List");

  lista.Remove("B");
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");
  if (lista.Front() != "C" || lista.Back() != "C") FoundError("Front or Back", "List");

  lista.Remove("B");
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");
  if (lista.Front() != "C" || lista.Back() != "C") FoundError("Front or Back", "List");

  lista.Remove("C");
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 0) FoundError("Remove or Size", "List");

  lista.InsertAtFront("C");
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtFront or Size", "List");
  if (lista != lista2) FoundError("InsertAtFront or Comparison", "List");

  lista.Clear();
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 0) FoundError("Remove or Size", "List");

  cout << "Copy Constructor" << endl;
  List<string> lista3(lista2);
  if (lista2 != lista3) FoundError("Comparison", "List");

  lista3.Insert("ABC");

  cout << "Move Constructor" << endl;
  List<string> lista4(std::move(lista3));
  if (lista4 == lista3) FoundError("Move", "List");
  if (lista3.Size() > 0 || !lista3.Empty()) FoundError("Move", "List");

  std::swap(lista4, lista3);
  if (lista4.Size() > 0 || lista3.Size() == 0) FoundError("swap", "List");
}

void TestList()
{
  TellTest("List");
  cout << "Test on List<int>" << endl;
  TestListInt();
  cout << "Deeper test on List<string>" << endl;
  TestListString();
}

void TestEmptyQueueVec(lasd::QueueVec<int> queuevec){
  bool error = false;
  
  if (!queuevec.Empty())
  {
    FoundError("Exists", "QueueVec");
  }

  if (queuevec.Size() != 0)
  {
    FoundError("Size", "QueueVec");
  }

  try{
    queuevec.Dequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Dequeue", "QueueVec");
  }

  try{
    queuevec.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", "QueueVec");
  }

  try{
    queuevec.HeadNDequeue();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("HeadNDequeue", "QueueVec");
  }

  queuevec.Enqueue(12);

  if (queuevec.Head() != 12)
  {
    FoundError("Head", "QueueVec");
  }

  if (queuevec.Size() != 1)
  {
    FoundError("Size", "QueueVec");
  }

  if (queuevec.HeadNDequeue() != 12)
  {
    FoundError("HeadNDequeue", "QueueVec");
  }
  cout << num_of_errors << endl;

  if (queuevec.Size() != 0)
  {
    FoundError("Size", "QueueVec");
  }

  try{
    queuevec.Head();
  }
  catch(length_error &err){
    error = true;
  }
  if (!error)
  {
    FoundError("Head", "QueueVec");
  }
}

void TestQueueVecString(QueueVec<string> &queuevec)
{
  string prima = "Stringa di Prova", seconda = "Seconda Stringa", terza = "Terza";

  unsigned long curr_size = queuevec.Size();
  cout << "Size is " << curr_size << endl;

  cout << "Populating" << endl;
  queuevec.Enqueue(prima);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", "QueueVec");

  queuevec.Enqueue(seconda);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", "QueueVec");

  queuevec.Enqueue(terza);
  curr_size++;
  if (queuevec.Size() != curr_size) FoundError("Enqueue or Size", "QueueVec");
  
  cout << "Testing constructors" << endl;
  QueueVec<string> copy_constr(queuevec);
  Vector<string> vec(3); 
  vec[1] = seconda;
  vec[0] = prima;
  vec[2] = terza;

  cout << "trav" << endl;
  QueueVec<string> trav_constr(vec);
  cout << "map" << endl;
  QueueVec<string> mapp_constr(std::move(vec));

  cout << trav_constr.Size() << "   " << mapp_constr.Size() << endl;

  cout << "Testing assignements" << endl;
  QueueVec<string> copy_assign;
  copy_assign = queuevec;
  
  cout << "Testing Enqueue and Dequeue" << endl;
  queuevec.Dequeue();
  string second = queuevec.Head();
  if (second != queuevec.HeadNDequeue()) FoundError("HeadNDequeue", "QueueVec");

  queuevec.Enqueue(prima);
  queuevec.Enqueue(seconda);
  queuevec.Enqueue(terza);
  if (queuevec.HeadNDequeue() != terza) FoundError("HeadNDequeue", "QueueVec");

  cout << "Testing comparisons" << endl;
  if (copy_constr != queuevec) FoundError("Comparisons (copy)", "QueueVec");
  if (trav_constr != queuevec) FoundError("Comparisons (trav)", "QueueVec");
  if (mapp_constr != queuevec) FoundError("Comparisons (map)", "QueueVec");
  if (copy_assign != queuevec) FoundError("Comparisons (assign)", "QueueVec");
}

void TestSortableVector()
{
  TellTest("SortableVector");
  lasd::SortableVector<int> emptysortablevec = lasd::SortableVector<int>();
  TestEmptySortableVector(emptysortablevec);
  emptysortablevec.Clear();
  TestEmptySortableVector(emptysortablevec);
}

void TestQueueVec(){
  TellTest("QueueVec");
  lasd::QueueVec<int> queuevec = lasd::QueueVec<int>();
  TestEmptyQueueVec(queuevec);
  lasd::QueueVec<string> queuevecstring = lasd::QueueVec<string>();
  TestQueueVecString(queuevecstring);

  cout << "MOVE CONSTR!!!!!!!!!!!!!!!" << endl;
  QueueVec<string> move_constr(std::move(queuevecstring));
  TestQueueVecString(move_constr);
  /*cout << "MOVE ASSIGN!!!!!!!!!!!!!!!" << endl;
  QueueVec<string> move_assign = std::move(move_constr);
  TestQueueVecString(move_assign);*/
}

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
  
  for(unsigned int i = 0; i < size; i++) {
    unsigned int num = distx(genx);
    list.InsertAtFront(num);
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
  // TestMiscellaneus();
  // TestSortableVector();
  // TestList();
  TestQueueVec();
  PrintResults();
  //PureRandomTest(); TODO
  cout << "END" << endl;
}
