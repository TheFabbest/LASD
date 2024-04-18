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

void TestEmptySortableVector()
{
  bool error = false;
  lasd::SortableVector<int> sortablevec = lasd::SortableVector<int>();

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

  sortablevec.Clear();
  // todo test fold and traverse
}

void TestSortableVector()
{
  TellTest("SortableVector");

  TestEmptySortableVector();



}

void mytest() {
  printf("END\n");
}
