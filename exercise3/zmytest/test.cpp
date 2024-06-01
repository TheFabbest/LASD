#include <iostream>
#include "../list/list.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

using namespace std;
using namespace lasd;

#define CONTAINER_SIZE_FOR_RANDOM_TESTING 10000
// todo incrementa
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

double GetDataNotInVector(Vector<double>& t){
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx;
  
  double candidate;
  do { 
    candidate = distx(genx) / 100;
  } while (t.Exists(candidate));

  return candidate;
}

string GetDataNotInVector(Vector<string>& t){
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx;
  
  string candidate;
  do { 
    candidate = to_string(distx(genx));
  } while (t.Exists(candidate));

  return candidate;
}

template <typename Data>
Data GetDataInVector(Vector<Data>& t) {
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(0, t.Size()-1);
  return t[distx(genx)];
}



// HASHTABLE

// general test for hashtables of any type, with given logical size and vector of elements belonging to the hashtable
template <typename Data>
void TestHashTable(HashTable<Data>& hashtable, unsigned long size, Vector<Data>& belonging) {
  const char* TEST_TITLE = "HashTable";
  const unsigned long RANDOM_TEST_SIZE = 10000;

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
    if (hashtable.Remove(element) == false) {
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

    Vector<Data> vec(2);
    vec[0] = element;
    vec[1] = absent;

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
    hashtable.RemoveAll(vec);
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
    if (hashtable.InsertSome(vec) == false) {
      FoundError("InsertSome (belonging: 1, absent: 1)", TEST_TITLE);
    }
    // remove of present element should be true
    if (hashtable.Remove(element) == false) {
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

  // after clear is called, hashtable should be empty
  hashtable.Clear();
  if (hashtable.Size() != 0) {
    FoundError("Clear (size is not 0)", TEST_TITLE);
  }
  if (hashtable.Empty() == false) {
    FoundError("Clear (is not empty)", TEST_TITLE);
  }

  unsigned long currentSize = size;
  if (size != 0) {
    // doing some random operations to check robustness
    hashtable.InsertAll(belonging);

    auto seed = random_device{}();
    
    cout << "Seed for random test: " << seed << endl;
    default_random_engine genx(seed);
    uniform_int_distribution<int> distx(0,1);

    // choosing other "size" objects that do not belong to the initial hashtable
    Vector<Data> domain = belonging;
    domain.Resize(belonging.Size()*2);
    for (unsigned long i = 0; i < belonging.Size(); ++i) {
      Data data = GetDataNotInVector(domain);
      domain[belonging.Size()+i] = data;
    }

    for (unsigned long i = 0; i < RANDOM_TEST_SIZE; ++i) {
      bool insert = distx(genx);
      
      // inserting random value
      if (insert) {
        Data data = GetDataInVector(domain);
        bool exists = hashtable.Exists(data);
        if (!exists) {
          ++currentSize;
        }
        // insert should return false if the data is present, false otherwise
        if (hashtable.Insert(data) == exists) {
          FoundError("Insert (random)", TEST_TITLE);
        }
      }
      // removing random value
      else {
        Data data = GetDataInVector(domain);
        bool exists = hashtable.Exists(data);
        if (exists) {
          --currentSize;
        }
        // remove should return true if the data is present, false otherwise
        if (hashtable.Remove(data) != exists) {
          FoundError("Remove (random)", TEST_TITLE);
        }
      }

      // size should be as expected
      if (currentSize != hashtable.Size()) {
        FoundError("Size (random)", TEST_TITLE);
      }
    }
  }

  // resize should not affect size in any way
  hashtable.Resize(1);
  if (currentSize != hashtable.Size()) {
    FoundError("Resize(1)", TEST_TITLE);
  }
  hashtable.Resize(100000);
  if (currentSize != hashtable.Size()) {
    FoundError("Resize(100000)", TEST_TITLE);
  }
  
  // rollback
  hashtable.Clear();
  hashtable.InsertSome(belonging);
}

void TestSpecificOpenAddressingInt(){
  // specific test

  // fast test to check what happens when a certain amount of cells are "removed"
  HashTableOpnAdr<int> table;
  Vector<int> emptyvec(0);

  // "26" is chosen because the minimum size of hashtables is known (23) but a higher value could be needed
  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < i; ++j) {
      table.Insert(j);
      table.Remove(j);
    }

    // at this point, in at least one case, all cells should be "removed" but the table is empty
    TestHashTable(table, 0, emptyvec);
  }
}

void TestClosedAddressingINT() {
  const char* addressing = "closed";
  const char* datatype = "int";
  const char* TEST_TITLE = "TestClosedAddressingINT";
  TellTest("ClosedAddressing (INT)");

  // empty, size=1, size=8 (same hash), size=5 from vector with repetitions, random

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<int> belonging;
  HashTableClsAdr<int> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = 0;
  hashtable = HashTableClsAdr<int> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = 0;
  belonging[1] = 1;
  belonging[2] = -1;
  belonging[3] = 23;
  belonging[4] = 24;
  belonging[5] = -24;
  belonging[6] = -23;
  belonging[7] = 46;
  hashtable = HashTableClsAdr<int> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = 1;
  belonging [4] = 1;
  belonging [7] = -23;
  hashtable = HashTableClsAdr<int> (belonging);
  belonging.Resize(5);
  belonging[0] = 0;
  belonging[1] = 1;
  belonging[2] = -1;
  belonging[3] = -24;
  belonging[4] = -23;
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestClosedAddressingINT is " << seed << endl;

  // init tree
  BST <int> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(distx(genx));
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<int>(tree);
  hashtable = HashTableClsAdr<int> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<int> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableClsAdr<int> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableClsAdr<int> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);// TODO

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableClsAdr<int> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableClsAdr<int> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }


  // specific test
  // todo TestSpecificClosedAddressingInt();
}

void TestClosedAddressingDOUBLE() {
  const char* addressing = "closed";
  const char* datatype = "double";
  const char* TEST_TITLE = "TestClosedAddressingDOUBLE";
  TellTest("ClosedAddressing (DOUBLE)");

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<double> belonging;
  HashTableClsAdr<double> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = 0;
  hashtable = HashTableClsAdr<double> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = 0;
  belonging[1] = 1.5;
  belonging[2] = -1.5;
  belonging[3] = 23.1;
  belonging[4] = 24;
  belonging[5] = -24;
  belonging[6] = -23.1;
  belonging[7] = 46;
  hashtable = HashTableClsAdr<double> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = 1.5;
  belonging [4] = 1.5;
  belonging [7] = -23.1;
  hashtable = HashTableClsAdr<double> (belonging);
  belonging.Resize(5);
  belonging[0] = 0;
  belonging[1] = 1.5;
  belonging[2] = -1.5;
  belonging[3] = -24;
  belonging[4] = -23.1;
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestClosedAddressingDOUBLE is " << seed << endl;

  // init tree
  BST <double> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(distx(genx) / 100);
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<double>(tree);
  hashtable = HashTableClsAdr<double> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<double> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableClsAdr<double> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableClsAdr<double> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableClsAdr<double> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableClsAdr<double> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }
}

void TestClosedAddressingSTRING() {
  const char* addressing = "closed";
  const char* datatype = "string";
  const char* TEST_TITLE = "TestClosedAddressingSTRING";
  TellTest("ClosedAddressing (STRING)");

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<string> belonging;
  HashTableClsAdr<string> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = "0";
  hashtable = HashTableClsAdr<string> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = "0";
  belonging[1] = "aaaaaaaaaaaaaaaaaaa"; // some of the strings have the same hash
  belonging[2] = "oaaaaaaaaaaaaa";
  belonging[3] = "123";
  belonging[4] = "Z1A";
  belonging[5] = "Xpa";
  belonging[6] = "0Ps";
  belonging[7] = "stringa";
  hashtable = HashTableClsAdr<string> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = "aaaaaaaaaaaaaaaaaaa";
  belonging [4] = "aaaaaaaaaaaaaaaaaaa";
  belonging [7] = "0Ps";
  hashtable = HashTableClsAdr<string> (belonging);
  belonging.Resize(5);
  belonging[0] = "0";
  belonging[1] = "aaaaaaaaaaaaaaaaaaa";
  belonging[2] = "oaaaaaaaaaaaaa";
  belonging[3] = "Xpa";
  belonging[4] = "0Ps";
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestClosedAddressingSTRING is " << seed << endl;

  // init tree
  BST <string> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(to_string(distx(genx)));
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<string>(tree);
  hashtable = HashTableClsAdr<string> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<string> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableClsAdr<string> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableClsAdr<string> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableClsAdr<string> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableClsAdr<string> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }
}

void TestClosedAddressing() {
  TellTest("ClosedAddressing");
  TestClosedAddressingINT();
  TestClosedAddressingDOUBLE();
  TestClosedAddressingSTRING();
}

void TestOpenAddressingINT() {
  const char* addressing = "open";
  const char* datatype = "int";
  const char* TEST_TITLE = "TestOpenAddressingINT";
  TellTest("OpenAddressing (INT)");

  // empty, size=1, size=8 (same hash), size=5 from vector with repetitions, random

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<int> belonging;
  HashTableOpnAdr<int> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = 0;
  hashtable = HashTableOpnAdr<int> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = 0;
  belonging[1] = 1;
  belonging[2] = -1;
  belonging[3] = 23;
  belonging[4] = 24;
  belonging[5] = -24;
  belonging[6] = -23;
  belonging[7] = 46;
  hashtable = HashTableOpnAdr<int> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = 1;
  belonging [4] = 1;
  belonging [7] = -23;
  hashtable = HashTableOpnAdr<int> (belonging);
  belonging.Resize(5);
  belonging[0] = 0;
  belonging[1] = 1;
  belonging[2] = -1;
  belonging[3] = -24;
  belonging[4] = -23;
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestClosedAddressingINT is " << seed << endl;

  // init tree
  BST <int> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(distx(genx));
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<int>(tree);
  hashtable = HashTableOpnAdr<int> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<int> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableOpnAdr<int> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableOpnAdr<int> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);// TODO

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableOpnAdr<int> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableOpnAdr<int> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }


  // specific test
  TestSpecificOpenAddressingInt();
}

void TestOpenAddressingDOUBLE() {
  const char* addressing = "open";
  const char* datatype = "double";
  const char* TEST_TITLE = "TestOpenAddressingDOUBLE";
  TellTest("OpenAddressing (DOUBLE)");

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<double> belonging;
  HashTableOpnAdr<double> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = 0;
  hashtable = HashTableOpnAdr<double> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = 0;
  belonging[1] = 1.5;
  belonging[2] = -1.5;
  belonging[3] = 23.1;
  belonging[4] = 24;
  belonging[5] = -24;
  belonging[6] = -23.1;
  belonging[7] = 46;
  hashtable = HashTableOpnAdr<double> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = 1.5;
  belonging [4] = 1.5;
  belonging [7] = -23.1;
  hashtable = HashTableOpnAdr<double> (belonging);
  belonging.Resize(5);
  belonging[0] = 0;
  belonging[1] = 1.5;
  belonging[2] = -1.5;
  belonging[3] = -24;
  belonging[4] = -23.1;
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestOpenAddressingDOUBLE is " << seed << endl;

  // init tree
  BST <double> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(distx(genx) / 100);
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<double>(tree);
  hashtable = HashTableOpnAdr<double> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<double> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableOpnAdr<double> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableOpnAdr<double> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableOpnAdr<double> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableOpnAdr<double> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }
  // specific test
  // TODO TestSpecificOpenAddressingDouble();
}

void TestOpenAddressingSTRING() {
  const char* addressing = "open";
  const char* datatype = "string";
  const char* TEST_TITLE = "TestOpenAddressingSTRING";
  TellTest("OpenAddressing (STRING)");

  cout << "Empty " << addressing << " " << datatype << endl;
  Vector<string> belonging;
  HashTableOpnAdr<string> hashtable;
  TestHashTable(hashtable, 0, belonging);

  cout << "from vector of size=1 " << addressing << " " << datatype << endl;
  belonging.Resize(1);
  belonging[0] = "0";
  hashtable = HashTableOpnAdr<string> (belonging);
  TestHashTable(hashtable, 1, belonging);

  cout << "from vector of 8 different values " << addressing << " " << datatype << endl;
  belonging.Resize(8);
  belonging[0] = "0";
  belonging[1] = "ABC"; // some of the strings have the same hash
  belonging[2] = "AAc";
  belonging[3] = "123";
  belonging[4] = "Z1A";
  belonging[5] = "Xpa";
  belonging[6] = "0Ps";
  belonging[7] = "stringa";
  hashtable = HashTableOpnAdr<string> (belonging);
  TestHashTable(hashtable, 8, belonging);

  cout << "from vector of 5 repeated values " << addressing << " " << datatype << endl;
  belonging [3] = "ABC";
  belonging [4] = "ABC";
  belonging [7] = "0Ps";
  hashtable = HashTableOpnAdr<string> (belonging);
  belonging.Resize(5);
  belonging[0] = "0";
  belonging[1] = "ABC";
  belonging[2] = "AAc";
  belonging[3] = "Xpa";
  belonging[4] = "0Ps";
  TestHashTable(hashtable, 5, belonging);

  // random
  auto seed = random_device{}();
  seed = 289431; // todo remove
  default_random_engine genx(seed);
  uniform_int_distribution<unsigned long> distx(1, CONTAINER_SIZE_FOR_RANDOM_TESTING); // todo fai piu piccolo
  cout << "seed for TestClosedAddressingSTRING is " << seed << endl;

  // init tree
  BST <string> tree;
  unsigned long randomSize = distx(genx);
  for (unsigned long i = 0; i < randomSize; ++i) {
    tree.Insert(to_string(distx(genx)));
  }
  
  // start test
  cout << "from bst of random values " << addressing << " " << datatype << endl;
  belonging = Vector<string>(tree);
  hashtable = HashTableOpnAdr<string> (belonging);
  unsigned long effectiveSize = tree.Size();
  TestHashTable(hashtable, effectiveSize, belonging);

  // constructors and assignments
  Vector<string> empty(0);

  // copy constr
  cout << "copy constructor" << endl;
  HashTableOpnAdr<string> copy_constr (hashtable);
  TestHashTable(copy_constr, effectiveSize, belonging);

  // move constr
  cout << "move constructor" << endl;
  HashTableOpnAdr<string> move_constr (std::move(hashtable));
  TestHashTable(move_constr, effectiveSize, belonging);
  cout << "moved with move constructor" << endl;
  TestHashTable(hashtable, 0, empty);

  // copy assignment
  cout << "copy assignment" << endl;
  HashTableOpnAdr<string> copy_assignment;
  copy_assignment = copy_constr;
  TestHashTable(copy_assignment, effectiveSize, belonging);

  // move assignment
  cout << "move assignment" << endl;
  HashTableOpnAdr<string> move_assignment;
  move_assignment = std::move(move_constr);
  TestHashTable(move_assignment, effectiveSize, belonging);
  cout << "moved with move assignment" << endl;
  TestHashTable(move_constr, 0, empty);

  // testing comparisons
  cout << "comparisons" << endl;
  if (copy_constr != copy_assignment) {
    FoundError("Comparison (should be equal", TEST_TITLE);
  }
  move_assignment.Resize(800000);
  if (move_assignment != copy_assignment) {
    FoundError("Comparison (resized but should be equal)", TEST_TITLE);
  }
  if (hashtable != move_constr) {
    FoundError("Comparison (empty should be equal)", TEST_TITLE);
  }
  if (hashtable == copy_constr) {
    FoundError("Comparison (empty should be different from non-empty)", TEST_TITLE);
  }
  if (copy_constr == move_constr) {
    FoundError("Comparison (non-empty should be different from empty)", TEST_TITLE);
  }

  // todo specific
}

void TestOpenAddressing() {
  TellTest("OpenAddressing");
  TestOpenAddressingINT();
  TestOpenAddressingDOUBLE();
  TestOpenAddressingSTRING();
}

}

/* ************************************************************************** */



void mytest() {
  fab::TestClosedAddressing();
  fab::TestOpenAddressing();
  cout << endl << "END" << endl << "Errors: " << fab::num_of_errors << endl;
}
