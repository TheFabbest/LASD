#include <iostream>

#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

using namespace std;
using namespace lasd;

/* ************************************************************************** */

namespace fab{
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


// TODO same for double and string
int GetDataNotInVector(Vector<int>& t){
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx;
  
  int candidate;
  do { 
    candidate = distx(genx);
  } while (t.Exists(candidate));

  return candidate;
}



// HASHTABLE
template <typename Data>
void TestHashTable(HashTable<Data>& hashtable, unsigned long size, Vector<Data>& belonging) {
  const char* TEST_TITLE = "HashTable";
  if (hashtable.Size() != size) {
    FoundError("Size", TEST_TITLE);
  }
  if (hashtable.Empty() != (size == 0)) {
    FoundError("Empty", TEST_TITLE);
  }
  
  belonging.Traverse([&hashtable, TEST_TITLE](const Data& data){
    if (hashtable.Exists(data) == false) {
      FoundError("Exists (should exist)", TEST_TITLE);
    }
  });

  Data newdata = GetDataNotInVector(belonging);
  if (hashtable.Exists(newdata)) {
    FoundError("Exists (should not exist)", TEST_TITLE);
  }


}

void TestClosedAddressingINT() {
  TellTest("ClosedAddressing (INT)");

  Vector<int> belonging;
  HashTableClsAdr<int> hashtable;
  TestHashTable(hashtable, 0, belonging);
}

void TestClosedAddressing() {
  TellTest("ClosedAddressing");
  TestClosedAddressingINT();
}

void TestOpenAddressing() {
  // TODO
}

}

/* ************************************************************************** */



void mytest() {
  fab::TestClosedAddressing();
  fab::TestOpenAddressing();
  cout << endl << "END" << endl << "Errors: " << fab::num_of_errors << endl;
}
