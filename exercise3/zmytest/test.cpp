#include <iostream>

#include "hashtable/hashtable.h"
#include "hashtable/clsadr/htclsadr.hpp"
#include "hashtable/opnadr/htopnadr.hpp"

using namespace std;

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

void TestEmptyHashTable(HashTable<int> hashtable) {
  const char* TEST_TITLE = "EmptyHashTable";
  if (hashtable.Empty() == false) {
    FoundError("Empty", TEST_TITLE);
  }
  if (hashtable.Size() != 0) {
    FoundError("Size", TEST_TITLE);
  }
  
}

void TestHashTable(HashTable<int> hashtable, unsigned long size) {
  if (size == 0) {
    TestEmptyHashTable(hashtable);
  }
  else {

  }
}

void TestClosedAddressing() {
  TellTest("ClosedAddressing");
  HashTable<int> hashtable;
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
