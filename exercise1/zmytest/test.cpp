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

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

unsigned long num_of_tests = 0;
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

  num_of_tests++;
  if (sortablevec.Exists(2))
  {
    FoundError("Exists", "SortableVector");
  }
  
  num_of_tests++;
  if (!sortablevec.Empty())
  {
    FoundError("Empty", "SortableVector");
  }

  num_of_tests++;
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

  num_of_tests++;
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

void TestEmptyQueueVec(lasd::QueueVec<int> queuevec){
  bool error = false;
  
  num_of_tests++;
  if (!queuevec.Empty())
  {
    FoundError("Exists", "QueueVec");
  }

  num_of_tests++;
  if (queuevec.Size() != 0)
  {
    FoundError("Size", "QueueVec");
  }


  num_of_tests++;
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

  num_of_tests++;
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

  num_of_tests++;
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

  num_of_tests++;
  if (queuevec.Head() != 12)
  {
    FoundError("Head", "QueueVec");
  }

  num_of_tests++;
  if (queuevec.Size() != 1)
  {
    FoundError("Size", "QueueVec");
  }

  num_of_tests++;
  if (queuevec.HeadNDequeue() != 12)
  {
    FoundError("HeadNDequeue", "QueueVec");
  }
  cout << num_of_errors << endl;

  num_of_tests++;
  if (queuevec.Size() != 0)
  {
    FoundError("Size", "QueueVec");
  }

  num_of_tests++;
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
  lasd::SortableVector<int> sortablevec = lasd::SortableVector<int>();
  TestEmptySortableVector(sortablevec);
  sortablevec.Clear();
  TestEmptySortableVector(sortablevec);
}

void TestQueueVec(){
  TellTest("QueueVec");
  lasd::QueueVec<int> queuevec = lasd::QueueVec<int>();
  TestEmptyQueueVec(queuevec);
}

void PrintResults()
{
  cout << endl << "Errors: " << num_of_errors << "/" << num_of_tests << endl;
}

void mytest() {
  TestSortableVector();
  TestQueueVec();
  PrintResults();
  cout << "END" << endl;
}
