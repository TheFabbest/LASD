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

template <typename Data>
Data GetDataInVector(Vector<Data>& t) {
  unsigned long size = sizeof(t) / sizeof(Data);
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(0, size-1);
  return t[distx(genx)];
}



// HASHTABLE

// general test for hashtables of any type, with given logical size and vector of elements belonging to the hashtable
template <typename Data>
void TestHashTable(HashTable<Data>& hashtable, unsigned long size, Vector<Data>& belonging) {
  const char* TEST_TITLE = "HashTable";

  // size and empty
  if (hashtable.Size() != size) {
    FoundError("Size", TEST_TITLE);
  }
  if (hashtable.Empty() != (size == 0)) {
    FoundError("Empty", TEST_TITLE);
  }
  
  // all elements in vector "belonging" should belong to the hashtable
  belonging.Traverse([&hashtable, TEST_TITLE](const Data& data){
    if (hashtable.Exists(data) == false) {
      FoundError("Exists (should exist)", TEST_TITLE);
    }
  });

  // element that is not in belonging should not belong to the hashtable
  Data newdata = GetDataNotInVector(belonging);
  if (hashtable.Exists(newdata)) {
    FoundError("Exists (should not exist)", TEST_TITLE);
  }

  // insert remove resize clear insertall removeall removesome insertsome TODO!!!!!!!!

  
  // TODO in specific test check if removeall removes only present data
  
  // RemoveAll should return true...
  if (!hashtable.RemoveAll(belonging)){
    FoundError("RemoveAll", TEST_TITLE);
  }

  // ...and make the hashtable empty
  if (hashtable.Size() != 0) {
    FoundError("Size (should be 0)", TEST_TITLE);
  }
  if (hashtable.Empty() == false) {
    FoundError("Empty (should be empty)", TEST_TITLE);
  }

  // Remove of absent value should return false
  if (hashtable.Remove(newdata)) {
    FoundError("Remove (of absent value)", TEST_TITLE);
  }
  if (hashtable.Size() != 0) {
    FoundError("Size (should be 0)", TEST_TITLE);
  }

  // insert of absent value should return true
  if (hashtable.Insert(newdata) == false) {
    FoundError("Insert (of absent value)", TEST_TITLE);
  }
  if (hashtable.Size() != 1) {
    FoundError("Size (should be 1)", TEST_TITLE);
  }
  // inserted value should belong to the hashtable
  if (hashtable.Exists(newdata) == false) {
    FoundError("Exists (size = 1, value should be present)", TEST_TITLE);
  }

  // insert of present value should return false
  if (hashtable.Insert(newdata)) {
    FoundError("Insert (of present value)", TEST_TITLE);
  }
  if (hashtable.Size() != 1) {
    FoundError("Size (should be 1)", TEST_TITLE);
  }

  // remove of present value should return true
  if (hashtable.Remove(newdata) == false) {
    FoundError("Remove (of present value)", TEST_TITLE);
  }
  // removed value should not belong to the hashtable
  if (hashtable.Exists(newdata)) {
    FoundError("Exists (size = 0)", TEST_TITLE);
  }

  // hashtable should be empty at this point
  if (hashtable.Size() != 0) {
    FoundError("Size (should be 0)", TEST_TITLE);
  }
  if (hashtable.Empty() == false) {
    FoundError("Empty (should be empty)", TEST_TITLE);
  }

  // insertall on empty hashtable should return true
  if (hashtable.InsertAll(belonging) == false) {
    FoundError("InsertAll (empty hashtable)", TEST_TITLE);
  }

  // specific test for non-empty hashtables
  if (belonging.Size() != 0) {

    Data element = GetDataInVector(belonging);
    Data absent = GetDataNotInVector(belonging);

    // remove of present value should return true
    if (hashtable.Remove(element)) {
      FoundError("Remove (present value)", TEST_TITLE);
    }
    // size should be decremented
    if (hashtable.Size() != size-1) {
      FoundError("Size (after removal of one element)", TEST_TITLE);
    }
    // removed element should not belong to the hashtable
    if (hashtable.Exists(element)) {
      FoundError("Exists (removed element)", TEST_TITLE);
    }

    // insertsome should restore previous state
    if (hashtable.InsertSome(belonging) == false) {
      FoundError("InsertSome (only one value absent)", TEST_TITLE);
    }
    hashtable.Remove(element); //already tested

    Vector<Data> vec(2);
    vec[0] = element;
    vec[1] = absent;

    //removesome 1/1-2/0-0/2
    //insertall 0/2-2/0-1/1
    //insertsome 2/0-0/2-1/1
    //remove absent/present
    //insert absent/present
    //removeall 0/2-2/0-1/1
    //insertsome (map) 0/2-2/0-1/1
    //insertall (map) 2/0-1/1-0/2
    //removesome (map) 2/0-0/2-1/1
    //removeall (map) 2/0-0/2-1/1


    // removesome of vec should be true ("element" belongs to vec, "absent" does not)
    if (hashtable.RemoveSome(vec) == false) {
      FoundError("RemoveSome (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // insertall of vec should be true
    if (hashtable.InsertAll(vec) == false) {
      FoundError("InsertAll (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // insertall of vec should be false
    if (hashtable.InsertAll(vec)) {
      FoundError("InsertAll (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // insertsome of vec should be false
    if (hashtable.InsertSome(vec)) {
      FoundError("InsertSome (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // removesome of vec should be true
    if (hashtable.RemoveSome(vec) == false) {
      FoundError("RemoveSome (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // removesome of vec should be false
    if (hashtable.RemoveSome(vec)) {
      FoundError("RemoveSome (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // removeall of vec should be false
    if (hashtable.RemoveAll(vec)) {
      FoundError("RemoveAll (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // insertsome of vec should be true
    if (hashtable.InsertSome(vec) == false) {
      FoundError("InsertSome (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // remove of absent elements should be false
    if (hashtable.Remove(element)) {
      FoundError("Remove (absent)", TEST_TITLE);
    }
    // remove of absent elements should be false
    if (hashtable.Remove(absent)) {
      FoundError("Remove (absent)", TEST_TITLE);
    }
    // insert of absent elements should be true
    if (hashtable.Insert(element) == false) {
      FoundError("Insert (absent)", TEST_TITLE);
    }
    // insert of present elements should be false
    if (hashtable.Insert(element)) {
      FoundError("Insert (present)", TEST_TITLE);
    }
    // insertsome of vec should be true
    if (hashtable.InsertSome(vec)) {
      FoundError("InsertSome (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // remove of present element should be true
    if (hashtable.Remove(element)) {
      FoundError("Remove (present)", TEST_TITLE);
    }
    // insertall of vec should be false
    if (hashtable.InsertAll(vec)) {
      FoundError("InsertAll (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // removeall of vec should be true
    if (hashtable.RemoveAll(vec) == false) {
      FoundError("RemoveAll (belonging: 2, absent: 0)", TEST_TITLE);
    }
    hashtable.Insert(element);
    // removeall of vec should be false
    if (hashtable.RemoveAll(vec)) {
      FoundError("RemoveAll (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // insertsome of vec should be true
    if (hashtable.InsertSome(std::move(Vector<Data>(vec))) == false) {
      FoundError("InsertSome map (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // insertsome of vec should be false
    if (hashtable.InsertSome(std::move(Vector<Data>(vec)))) {
      FoundError("InsertSome map (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // insertall of vec should be false
    if (hashtable.InsertAll(std::move(Vector<Data>(vec)))) {
      FoundError("InsertAll map (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // removesome of vec should be true
    if (hashtable.RemoveSome(std::move(Vector<Data>(vec))) == false) {
      FoundError("RemoveSome map (belonging: 2, absent: 0)", TEST_TITLE);
    }
    hashtable.Insert(element); //insert already tested
    // insertsome of vec should be true
    if (hashtable.InsertSome(std::move(Vector<Data>(vec))) == false) {
      FoundError("InsertSome map (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // removeall of vec should be true
    if (hashtable.RemoveAll(std::move(Vector<Data>(vec))) == false) {
      FoundError("RemoveAll map (belonging: 2, absent: 0)", TEST_TITLE);
    }
    // removesome of vec should be false
    if (hashtable.RemoveSome(std::move(Vector<Data>(vec)))) {
      FoundError("RemoveSome map (belonging: 0, absent: 2)", TEST_TITLE);
    }
    // removeall of vec should be false
    if (hashtable.RemoveAll(std::move(Vector<Data>(vec)))) {
      FoundError("RemoveAll map (belonging: 0, absent: 2)", TEST_TITLE);
    }
    hashtable.Insert(absent); //insert already tested
    // insertall of vec should be false
    if (hashtable.InsertAll(std::move(Vector<Data>(vec)))) {
      FoundError("InsertAll map (belonging: 1, absent: 1)", TEST_TITLE);
    }
    hashtable.Remove(element);
    // removesome of vec should be true
    if (hashtable.RemoveSome(std::move(Vector<Data>(vec))) == false) {
      FoundError("RemoveSome map (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // insertall of vec should be true
    if (hashtable.InsertAll(std::move(Vector<Data>(vec))) == false) {
      FoundError("InsertAll map (belonging: 0, absent: 2)", TEST_TITLE);
    }
    hashtable.Remove(element);
    // removeall of vec should be false
    if (hashtable.RemoveAll(std::move(Vector<Data>(vec)))) {
      FoundError("RemoveAll map (belonging: 1, absent: 1)", TEST_TITLE);
    }


    if (belonging.Size() == 1) {
      if (hashtable.RemoveSome(belonging)) {
        FoundError("RemoveSome (was true on empty hashtable)", TEST_TITLE);
      }
    }
    else {
      if (hashtable.RemoveSome(belonging) == false) {
        FoundError("RemoveSome (one element missing)", TEST_TITLE);
      }
    }
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

void TestOpenAddressingINT() {
  TellTest("OpenAddressing (INT)");

  Vector<int> belonging;
  HashTableOpnAdr<int> hashtable;
  TestHashTable(hashtable, 0, belonging);
}

void TestOpenAddressing() {
  TellTest("OpenAddressing");
  TestOpenAddressingINT();
}

}

/* ************************************************************************** */



void mytest() {
  fab::TestClosedAddressing();
  fab::TestOpenAddressing();
  cout << endl << "END" << endl << "Errors: " << fab::num_of_errors << endl;
}
