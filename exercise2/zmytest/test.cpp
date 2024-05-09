#include <iostream>
#include <random>
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"

using namespace std;
using namespace lasd;

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

// BINARY TREE
void TestEmptyBinaryTree(BinaryTree<string> &tree){
  const char *TEST_TITLE = "Empty BinaryTree";
  if (tree.Size() != 0) FoundError("size", TEST_TITLE);
  if (tree.Empty() == false) FoundError("empty", TEST_TITLE);
  if (tree.Exists("") == true) FoundError("exists", TEST_TITLE);
  TestEmptyContainer(tree);
}

void TestEmptyBinaryTree(){
  TellTest ("BinaryTree (empty)");

  // TODO add BST to tests
  cout << "Testing default constructors" << endl;
  BinaryTreeVec<string> treeVec;
  BinaryTreeLnk<string> treeLnk;

  TestEmptyBinaryTree(treeVec);
  TestEmptyBinaryTree(treeLnk);


  cout << "Testing constructors from traversable/mappable" << endl;
  Vector<string> vector(0);
  BinaryTreeVec<string> treeVecFromVec(vector);
  BinaryTreeLnk<string> treeLnkFromVec(vector);

  TestEmptyBinaryTree(treeVecFromVec);
  TestEmptyBinaryTree(treeLnkFromVec);

  cout << "Testing copy assignment" << endl;
  treeVecFromVec = treeVec;
  cout << "here" << endl;
  treeLnkFromVec = treeLnk;
  cout << "here" << endl;
  TestEmptyBinaryTree(treeVecFromVec);
  cout << "here" << endl;
  TestEmptyBinaryTree(treeLnkFromVec);
  cout << "here" << endl;

  cout << "Testing copy constructor" << endl;
  BinaryTreeLnk<string> treeLnkCopyConstructor(treeLnk);
  BinaryTreeVec<string> treeVecCopyConstructor(treeVec);
  TestEmptyBinaryTree(treeLnkCopyConstructor);
  TestEmptyBinaryTree(treeVecCopyConstructor);
}

void TestBinaryTreeFull() {
  const char *TEST_TITLE = "BinaryTree (randomly populated)";

  // initializing random device
  auto seed = random_device{}();
  seed = 1599831501;
  cout << "Initializing random generator with seed " << seed << " for miscellaneus test." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(1, 10);

  // creating list of random size with random values
  cout << "init list of random size and stack with random numbers" << endl;
  int size = distx(genx);
  cout << "Size is " << size << endl;

  List<int> list = List<int>();
  string acc = "";
  int tot = 0;
  
  for(int i = 0; i < size; i++) {
    int num = distx(genx);
    cout << num << endl;
    list.InsertAtBack(num);
    acc += to_string(num);
    tot += num+5;
  }

  cout << "Building trees from list" << endl;
  // TODO add BST
  BinaryTreeVec<int> treeVecFromList(list);
  BinaryTreeLnk<int> treeLnkFromList(list);

  if (list.Size() != (unsigned long)size)
  {
    FoundError("InsertAtBack", "List");
  }
  if (treeVecFromList.Size() != list.Size()) {
    FoundError("traversable constructor", "BinaryTreeVec");
  }
  if (treeLnkFromList.Size() != list.Size()) {
    FoundError("traversable constructor", "BinaryTreeVec");
  }


  cout << "Checking BreadthFold correctness" << endl;
  string concatvec = treeVecFromList.BreadthFold(std::function([](const int &curr, const string &acc) {return acc+to_string(curr);}), string());
  string concatlnk = treeLnkFromList.BreadthFold(std::function([](const int &curr, const string &acc) {return acc+to_string(curr);}), string());

  if (concatlnk != concatvec || acc != concatlnk) FoundError("BreadthFold", TEST_TITLE);
  
  cout << "Checking Map and Fold correctness (for each \"order\")" << endl;

  int i = 0;
  auto incrementAndCount = [&i](int &curr){++curr; ++i;};
  treeVecFromList.Map(incrementAndCount);
  cout << i << "  " << size << endl;
  if (i != size) FoundError("Map", "BinaryTreeVec");
  treeVecFromList.InOrderMap(incrementAndCount);
  if (i != size*2) FoundError("InOrderMap", "BinaryTreeVec");
  treeVecFromList.PreOrderMap(incrementAndCount);
  if (i != size*3) FoundError("PreOrderMap", "BinaryTreeVec");
  treeVecFromList.PostOrderMap(incrementAndCount);
  if (i != size*4) FoundError("PostOrderMap", "BinaryTreeVec");
  treeVecFromList.BreadthMap(incrementAndCount);
  if (i != size*5) FoundError("BreadthMap", "BinaryTreeVec");


  i = 0;
  treeLnkFromList.Map(incrementAndCount);
  treeLnkFromList.InOrderMap(incrementAndCount);
  treeLnkFromList.PreOrderMap(incrementAndCount);
  treeLnkFromList.PostOrderMap(incrementAndCount);
  treeLnkFromList.BreadthMap(incrementAndCount);
  if (i != size*5) FoundError("Map", "BinaryTreeLnk");
  


  int vecTot = treeVecFromList.Fold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  int lnkTot = treeLnkFromList.Fold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (tot != vecTot) {
    FoundError("Fold or Map", "BinaryTreeVec");
  }
  if (tot != lnkTot) {
    FoundError("Fold or Map", "BinaryTreeLnk");
  }

  vecTot = treeVecFromList.InOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.InOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (tot != vecTot) {
    FoundError("InOrderFold or Map", "BinaryTreeVec");
  }
  if (tot != lnkTot) {
    FoundError("InOrderFold or Map", "BinaryTreeLnk");
  }

  vecTot = treeVecFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (tot != vecTot) {
    FoundError("PostOrderFold or Map", "BinaryTreeVec");
  }
  if (tot != lnkTot) {
    FoundError("PostOrderFold or Map", "BinaryTreeLnk");
  }

  vecTot = treeVecFromList.PreOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.PreOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (tot != vecTot) {
    FoundError("PreOrderFold or Map", "BinaryTreeVec");
  }
  if (tot != lnkTot) {
    FoundError("PreOrderFold or Map", "BinaryTreeLnk");
  }
}

void TestBinaryTree()
{
  TellTest ("BinaryTree");

  TestEmptyBinaryTree();
  TestBinaryTreeFull();
}
}


void mytest() {
  fab::TestBinaryTree();

  cout << endl << "END" << endl << "Errors: " << fab::num_of_errors << endl;
}
