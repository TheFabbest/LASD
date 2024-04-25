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
  cout << endl << endl << "Starting test " << name << endl; 
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

  // todo test fold and traverse and sort
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
  lista.Remove("Albero");
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.Remove("Albero");
  if (!lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() > 0) FoundError("Remove or Size", "List");

  lista.InsertAtBack("C");
  if (lista.Empty()) FoundError("InsertAtBack or Empty", "List");
  if (lista.Size() != 1) FoundError("InsertAtBack or Size", "List");

  List<string> lista2 = lista;
  if (lista2 != lista) FoundError("Comparison", "List");

  lista.Insert("C");
  if (lista.Empty()) FoundError("Insert or Empty", "List");
  if (lista.Size() != 1) FoundError("Insert or Size", "List");
  
  lista.InsertAtFront("B");
  if (lista.Empty()) FoundError("InsertAtFront or Empty", "List");
  if (lista.Size() != 2) FoundError("InsertAtFront or Size", "List");

  lista.Remove("B");
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");

  lista.Remove("B");
  if (lista.Empty()) FoundError("Remove or Empty", "List");
  if (lista.Size() != 1) FoundError("Remove or Size", "List");

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

  List<string> lista3(lista2);
  if (lista2 != lista3) FoundError("Comparison", "List");

  lista3.Insert("ABC");
  List<string> lista4(std::move(lista3));
  if (lista4 == lista3) FoundError("Move", "List");
  if (lista3.Size() > 0) FoundError("Move", "List");

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
  TestMiscellaneus();
  TestSortableVector();
  TestQueueVec();
  TestList();
  PrintResults();
  //PureRandomTest(); TODO
  cout << "END" << endl;
}
