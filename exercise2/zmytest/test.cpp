#include <iostream>
#include <random>
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"

using namespace std;
using namespace lasd;
string to_string(string str){return str;} // for templates

/* TEST
  BinaryTree
    = copy (done)
    = move (done)
    comparison (done)
    Root (done)
    Traverse (pre, post, in, breadth) (done)
  
  MutableBinaryTree
    (BinaryTree) + mutable (done)
    Map (pre, post, in, breadth) (done)
    Clear (done)

  BinaryTreeLnk
    (MutableBinaryTree)
    default constr (done)
    traversable constr (done)
    mappable constr TODO
    copy constr (done)
    move constr (done)
    = copy (done)
    = move (done)
    comparison (done)
    root (done)
    root (mutable) (done)
    clear (done)

  BinaryTreeVec
    (same as BinaryTreeLnk)

  BST
    default constr
    traversable constr
    mappable constr
    copy constr
    move constr
    = copy
    = move
    Min
    MinNRemove
    RemoveMax
    Predecessor
    PredecessorNRemove
    RemovePredecessor
    Successor
    SuccessorNRemove
    RemoveSuccessor
    Root
    Insert
    Insert (move)
    Remove
    Exists
    Clear
    protected methods (TODO)


  Iterator
    = copy
    = move
    comparison
    operator*
    Terminated
  
  MutableIterator
    (Iterator) + mutable

  ForwardIterator
    (Iterator)
    operator++

  ResettableIterator
    (Iterator)
    Reset

  BTPreOrderIterator
    (MutableIterator)
    constructor (binary tree)
    copy constr
    move constr
    operator++
    reset

  BTPreOrderMutableIterator
    (above) + mutable
  [Post, In, Breadth]

  
*/


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

void GetRandomBST(BST<int> &bst, unsigned long &size, int &min, int &max, int &num_for_tests,
                    int &prec, int &succ, int &root) {
  // initializing random device
  auto seed = random_device{}();
  if (min == 0) seed = 8433919; // for repeating
  // 2909141848
  cout << "Initializing random generator with seed " << seed << " for random BST" << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(1, 100);

  size = 0;
  min = 0;
  max = 0;
  root = 0;
  bst.Clear();
  int num = distx(genx);
  Vector<int> generated_numbers(num);
  for (int i = 0; i < num; ++i)
  {
    int generated = distx(genx);
    generated_numbers[i] = generated;

    bool inserted = bst.Insert(generated);
    if (inserted) {
      if (root == 0) {
        root = generated;
      }
      if (min == 0 || generated < min)
      {
        min = generated;
      }
      if (max == 0 || generated > max)
      {
        max = generated;
      }
      ++size;
    }
  }
  
  // TODO vedi se 3 va bene in testbst
  if (size < 3) {
    cout << "retrying..." << endl;
    GetRandomBST(bst, size, min, max, num_for_tests, 
                prec, succ, root);
    return;
  }

  do {
    num_for_tests = distx(genx);
  } while (num_for_tests <= min || num_for_tests >= max);

  prec = min;
  succ = max;
  for (int i = 0; i < num; i++) {
    int cur = generated_numbers[i];
    if (cur > prec && cur < num_for_tests) {
      prec = cur;
    }
    if (cur < succ && cur > num_for_tests) {
      succ = cur;
    }
  }
}

void GetRandomBST(BST<int> &bst) {
  unsigned long size;
  int min;
  int max;
  int num_for_tests;
  int prec;
  int succ;
  int root;
  GetRandomBST(bst, size, min, max, num_for_tests, prec, succ, root);
}

// BINARY TREE
template <class T>
void TestEmptyBinaryTree(BinaryTree<T> &tree){
  const char *TEST_TITLE = "Empty BinaryTree";
  TestEmptyContainer(tree);
  if (tree.Size() != 0) FoundError("size", TEST_TITLE);
  if (tree.Empty() == false) FoundError("empty", TEST_TITLE);
  if (tree.Exists(T{}) == true) FoundError("exists", TEST_TITLE);
  if (tree != tree) FoundError("Comparison", TEST_TITLE);

  bool error = false;
  try {
    tree.Root();
  }
  catch (length_error &e)
  {
    error = true;
  }
  if (!error) FoundError("Root", TEST_TITLE);


  int counter = 0;
  std::function increment = [&counter](const T&){++counter;};
  tree.Traverse(increment);
  tree.PreOrderTraverse(increment);
  tree.PostOrderTraverse(increment);
  tree.InOrderTraverse(increment);
  tree.BreadthTraverse(increment);
  if (counter != 0) FoundError("Traverse", TEST_TITLE);

  string empty = "";
  std::function concat = [](const T &curr, const string &acc) {return acc+to_string(curr);};
  empty = tree.Fold(concat, empty);
  empty = tree.PreOrderFold(concat, empty);
  empty = tree.PostOrderFold(concat, empty);
  empty = tree.InOrderFold(concat, empty);
  empty = tree.BreadthFold(concat, empty);
  if (empty != "") FoundError("Fold", TEST_TITLE);
}

void TestEmptyBST(BST<string> &bst) {
  const char *TEST_TITLE = "BST (empty)";

  if (bst.Size() != 0){
    FoundError("Size", TEST_TITLE);
    cout << "You might have called TestEmptyBST on a non-empty BST" << endl;
  }

  Vector<string> vec(3);
  vec[0] = "";
  vec[1] = "0";
  vec[2] = "str";

  // Dictionary methods (traversable)
  cout << "Testing Dictionary methods on BST" << endl;
  if (bst.RemoveSome(vec)) {
    FoundError("RemoveSome", TEST_TITLE);
  }
  if (bst.RemoveAll(vec)) {
    FoundError("RemoveAll", TEST_TITLE);
  }

  if (!bst.InsertAll(vec)) {
    FoundError("InsertAll", TEST_TITLE);
  }
  if (!bst.RemoveAll(vec)) {
    FoundError("RemoveAll", TEST_TITLE);
  }

  if (!bst.InsertSome(vec)) {
    FoundError("InsertSome", TEST_TITLE);
  }
  if (!bst.RemoveSome(vec)) {
    FoundError("RemoveSome", TEST_TITLE);
  }

  // mappable
  cout << "Testing Dictionary methods on BST (mappable)" << endl;
  if (bst.RemoveSome(std::move(Vector(vec)))) {
    FoundError("RemoveSome", TEST_TITLE);
  }
  if (bst.RemoveAll(std::move(Vector(vec)))) {
    FoundError("RemoveAll", TEST_TITLE);
  }

  if (!bst.InsertAll(std::move(Vector(vec)))) {
    FoundError("InsertAll", TEST_TITLE);
  }
  if (!bst.RemoveAll(std::move(Vector(vec)))) {
    FoundError("RemoveAll", TEST_TITLE);
  }

  if (!bst.InsertSome(std::move(Vector(vec)))) {
    FoundError("InsertSome", TEST_TITLE);
  }
  if (!bst.RemoveSome(std::move(Vector(vec)))) {
    FoundError("RemoveSome", TEST_TITLE);
  }

  if (bst.Size() != 0){
    FoundError("Size", TEST_TITLE);
  }

  // exceptions
  cout << "Testing BST exceptions on min/max (and similar)" << endl;
  bool error = false;
  try{
    bst.Min();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("Min", TEST_TITLE);
  }

  error = false;
  try{
    bst.Max();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("Max", TEST_TITLE);
  }  

  error = false;
  try{
    bst.RemoveMin();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("RemoveMin", TEST_TITLE);
  }

  error = false;
  try{
    bst.RemoveMax();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("RemoveMax", TEST_TITLE);
  }

  error = false;
  try{
    bst.MinNRemove();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("MinNRemove", TEST_TITLE);
  }

  error = false;
  try{
    bst.MaxNRemove();
  }
  catch (std::length_error &e) {
    error = true;
  }
  if (error == false) {
    FoundError("MaxNRemove", TEST_TITLE);
  }

  cout << "Testing Exists" << endl;
  if (bst.Exists("")) {
    FoundError("Exists", TEST_TITLE);
  }
}

void TestEmptyBinaryTree(){
  TellTest ("BinaryTree (empty)");

  cout << "Testing default constructors" << endl;
  BinaryTreeVec<string> treeVec;
  BinaryTreeLnk<string> treeLnk;
  BST<string> bst;

  TestEmptyBinaryTree(treeVec);
  TestEmptyBinaryTree(treeLnk);
  TestEmptyBinaryTree(bst);
  TestEmptyBST(bst);

  cout << "Testing constructors from traversable/mappable" << endl;
  Vector<string> vector(0);
  BinaryTreeVec<string> treeVecFromVec(vector);
  BinaryTreeLnk<string> treeLnkFromVec(vector);
  BST<string> bstFromVec(vector);

  TestEmptyBinaryTree(treeVecFromVec);
  TestEmptyBinaryTree(treeLnkFromVec);
  TestEmptyBinaryTree(bstFromVec);
  TestEmptyBST(bstFromVec);

  cout << "Testing copy assignment" << endl;
  treeVecFromVec = treeVec;
  treeLnkFromVec = treeLnk;
  bstFromVec = bst;
  TestEmptyBinaryTree(treeVecFromVec);
  TestEmptyBinaryTree(treeLnkFromVec);
  TestEmptyBinaryTree(bstFromVec);
  TestEmptyBST(bstFromVec);

  cout << "Testing move assignment" << endl;
  treeVec = std::move(treeVecFromVec);
  treeLnk = std::move(treeLnkFromVec);
  bst = std::move(bstFromVec);
  TestEmptyBinaryTree(treeVec);
  TestEmptyBinaryTree(treeLnk);
  TestEmptyBinaryTree(bst);
  TestEmptyBST(bst);
  TestEmptyBinaryTree(treeVecFromVec);
  TestEmptyBinaryTree(treeLnkFromVec);
  TestEmptyBinaryTree(bstFromVec);

  cout << "Testing copy constructor" << endl;
  BinaryTreeLnk<string> treeLnkCopyConstructor(treeLnk);
  BinaryTreeVec<string> treeVecCopyConstructor(treeVec);
  BST<string> bstCopyConstructor(bst);
  TestEmptyBinaryTree(treeLnkCopyConstructor);
  TestEmptyBinaryTree(treeVecCopyConstructor);
  TestEmptyBinaryTree(bstCopyConstructor);
  TestEmptyBST(bstCopyConstructor);

  cout << "Testing move constructor" << endl;
  BinaryTreeLnk<string> treeLnkMoveConstructor(std::move(treeLnk));
  BinaryTreeVec<string> treeVecMoveConstructor(std::move(treeVec));
  BST<string> bstMoveConstructor(std::move(bst));
  TestEmptyBinaryTree(treeLnkMoveConstructor);
  TestEmptyBinaryTree(treeVecMoveConstructor);
  TestEmptyBinaryTree(bstMoveConstructor);
  TestEmptyBST(bstMoveConstructor);
  TestEmptyBinaryTree(treeVec);
  TestEmptyBinaryTree(treeLnk);
  TestEmptyBinaryTree(bst);
}

void TestBinaryTree(BinaryTree<int> &tree, unsigned long size, int root, int expected_tot) {
  const char *TEST_TITLE = "BinaryTree (with parameters)";
  if (tree.Size() != size) {
    FoundError("Size or Constructor", TEST_TITLE);
  }
  if (tree.Empty() && size != 0) {
    FoundError("Empty", TEST_TITLE);
  }
  if (tree.Size() != 0 && tree.Root().Element() != root) {
    FoundError("Root", TEST_TITLE);
  }

  unsigned long counter = 0;
  std::function increment = [&counter](const int&){++counter;};
  tree.Traverse(increment);
  tree.PreOrderTraverse(increment);
  tree.PostOrderTraverse(increment);
  tree.InOrderTraverse(increment);
  tree.BreadthTraverse(increment);
  if (counter != size * 5) {
    FoundError("Traverse", TEST_TITLE);
  }

  int tot = 0;
  std::function sum = [](const int &curr, const int &acc) {return acc+curr;};
  tot = tree.Fold(sum, tot);
  tot = tree.PreOrderFold(sum, tot);
  tot = tree.PostOrderFold(sum, tot);
  tot = tree.InOrderFold(sum, tot);
  tot = tree.BreadthFold(sum, tot);
  if (tot != expected_tot*5) {
    FoundError("Fold", TEST_TITLE);
  }
}

void TestBinaryTreeLnk() {
  const char *TEST_TITLE = "BinaryTreeLnk";
  const unsigned long size = 18;

  TellTest(TEST_TITLE);

  cout << "Testing constructors and assignments" << endl;
  List<int> list;
  int tot = 0;
  for (unsigned long i = 0; i < size; ++i) {
    BinaryTreeLnk<int> tree(list);
    TestBinaryTree(tree, i, 0, tot);

    BinaryTreeLnk<int> assignment_tree = tree;
    TestBinaryTree(assignment_tree, i, 0, tot);

    tree = assignment_tree;
    TestBinaryTree(tree, i, 0, tot);

    BinaryTreeLnk<int> move_tree = std::move(tree);
    TestEmptyBinaryTree(tree);
    TestBinaryTree(move_tree, i, 0, tot);

    BinaryTreeLnk<int> move_constr_tree(std::move(assignment_tree));
    TestEmptyBinaryTree(assignment_tree);
    TestBinaryTree(move_constr_tree, i, 0, tot);

    list.InsertAtBack(i);
    tot += i;
  }

  list.Clear();
  const unsigned long size2 = 9;
  for (unsigned long i = 0; i < size2; ++i) {
    list.InsertAtBack(i);
  }

  BinaryTreeLnk<int> tree(list);
  
  for (unsigned long i = 0; i < size2; ++i) {
    if (!tree.Exists(i)) {
      FoundError("Exists", TEST_TITLE);
    }
  }

  cout << "Testing traverse (pre/in/post order and breadth) and fold (pre/in/post order and breadth)" << endl;
  string result;
  string traverse_result = "";
  std::function concat = [](const int &curr, const string &acc) {return acc+to_string(curr);};
  std::function concatForTraverse = [&traverse_result](const int &curr) {traverse_result += to_string(curr);};
  result = tree.BreadthFold(concat, string());
  tree.BreadthTraverse(concatForTraverse);
  if (result != "012345678") {
    FoundError("BreadthFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("BreadthTraverse", TEST_TITLE);
  }
  traverse_result = "";

  result = tree.PreOrderFold(concat, string());
  tree.PreOrderTraverse(concatForTraverse);
  if (result != "013784256") {
    FoundError("PreOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("PreOrderTraverse", TEST_TITLE);
  }
  traverse_result = "";

  result = tree.PostOrderFold(concat, string());
  tree.PostOrderTraverse(concatForTraverse);
  if (result != "783415620") {
    FoundError("PostOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("PostOrderTraverse", TEST_TITLE);
  }
  traverse_result = "";
  
  result = tree.InOrderFold(concat, string());
  tree.InOrderTraverse(concatForTraverse);
  if (result != "738140526") {
    FoundError("InOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("InOrderTraverse", TEST_TITLE);
  }
  
  cout << "Testing Root" << endl;
  if (tree.Root().Element() != 0) FoundError("Root", TEST_TITLE);

  cout << "Testing comparison (better tests are done in TestBinaryTreeRandom)" << endl;
  BinaryTreeLnk<int> other_tree(tree);
  if (tree != tree) FoundError("Comparison", TEST_TITLE);
  if (tree != other_tree) FoundError("Comparison", TEST_TITLE);
  other_tree.Root().Element() = -1;
  if (tree == other_tree) FoundError("Comparison", TEST_TITLE);

  list.InsertAtBack(1);
  BinaryTreeLnk<int> yet_another_tree(list);
  if (tree == yet_another_tree) FoundError("Comparison", TEST_TITLE);

  cout << "Testing Clear" << endl;
  tree.Clear();
  TestEmptyBinaryTree(tree);
}

void TestBinaryTreeVec() {
  const char *TEST_TITLE = "BinaryTreeVec";
  const unsigned long size = 18;

  TellTest(TEST_TITLE);

  cout << "Testing constructors and assignments" << endl;
  List<int> list;
  int tot = 0;
  for (unsigned long i = 0; i < size; ++i) {
    BinaryTreeLnk<int> tree(list);
    TestBinaryTree(tree, i, 0, tot);

    BinaryTreeLnk<int> assignment_tree = tree;
    TestBinaryTree(assignment_tree, i, 0, tot);

    tree = assignment_tree;
    TestBinaryTree(tree, i, 0, tot);

    BinaryTreeLnk<int> move_tree = std::move(tree);
    TestEmptyBinaryTree(tree);
    TestBinaryTree(move_tree, i, 0, tot);

    BinaryTreeLnk<int> move_constr_tree(std::move(assignment_tree));
    TestEmptyBinaryTree(assignment_tree);
    TestBinaryTree(move_constr_tree, i, 0, tot);

    list.InsertAtBack(i);
    tot += i;
  }

  list.Clear();
  const unsigned long size2 = 9;
  for (unsigned long i = 0; i < size2; ++i) {
    list.InsertAtBack(i);
  }

  BinaryTreeVec<int> tree(list);
  
  for (unsigned long i = 0; i < size2; ++i) {
    if (!tree.Exists(i)) {
      FoundError("Exists", TEST_TITLE);
    }
  }

  cout << "Testing traverse (pre/in/post order and breadth) and fold (pre/in/post order and breadth)" << endl;
  string result;
  string traverse_result = "";
  std::function concat = [](const int &curr, const string &acc) {return acc+to_string(curr);};
  std::function concatForTraverse = [&traverse_result](const int &curr) {traverse_result += to_string(curr);};
  result = tree.BreadthFold(concat, string());
  tree.BreadthTraverse(concatForTraverse);
  if (result != "012345678") {
    FoundError("BreadthFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("BreadthTraverse", TEST_TITLE);
  }
  traverse_result = "";

  result = tree.PreOrderFold(concat, string());
  tree.PreOrderTraverse(concatForTraverse);
  if (result != "013784256") {
    FoundError("PreOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("PreOrderTraverse", TEST_TITLE);
  }
  traverse_result = "";

  result = tree.PostOrderFold(concat, string());
  tree.PostOrderTraverse(concatForTraverse);
  if (result != "783415620") {
    FoundError("PostOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("PostOrderTraverse", TEST_TITLE);
  }
  traverse_result = "";
  
  result = tree.InOrderFold(concat, string());
  tree.InOrderTraverse(concatForTraverse);
  if (result != "738140526") {
    FoundError("InOrderFold", TEST_TITLE);
  }
  if (traverse_result != result) {
    FoundError("InOrderTraverse", TEST_TITLE);
  }
  
  cout << "Testing Root" << endl;
  if (tree.Root().Element() != 0) FoundError("Root", TEST_TITLE);

  cout << "Testing comparison (better tests are done in TestBinaryTreeRandom)" << endl;
  BinaryTreeVec<int> other_tree(tree);
  if (tree != tree) FoundError("Comparison", TEST_TITLE);
  if (tree != other_tree) FoundError("Comparison", TEST_TITLE);
  other_tree.Root().Element() = -1;
  if (tree == other_tree) FoundError("Comparison", TEST_TITLE);

  list.InsertAtBack(1);
  BinaryTreeVec<int> yet_another_tree(list);
  if (tree == yet_another_tree) FoundError("Comparison", TEST_TITLE);

  cout << "Testing Clear" << endl;
  tree.Clear();
  TestEmptyBinaryTree(tree);
}

void TestBinaryTreeRandom() {
  const char *TEST_TITLE = "BinaryTree (randomly populated)";

  // initializing random device
  auto seed = random_device{}();
  seed = 413063144; // TODO remove
  cout << "Initializing random generator with seed " << seed << " for TestBinaryTreeRandom." << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(1, 100);

  // creating list of random size with random values
  cout << "init list of random size and stack with random numbers" << endl;
  int size = distx(genx);
  cout << "Size is " << size << endl;

  List<int> list = List<int>();
  string acc = "";
  int totAfterIncrement = 0;
  unsigned long num_of_different_numbers = 0;
  int totForBST = 0;
  
  for(int i = 0; i < size; i++) {
    int num = distx(genx);

    if (list.Exists(num) == false) {
      ++num_of_different_numbers;
      totForBST += num;
    }

    list.InsertAtBack(num);
    acc += to_string(num);
    totAfterIncrement += num+5;
  }

  cout << "Building trees from list" << endl;
  BinaryTreeVec<int> treeVecFromList(list);
  BinaryTreeLnk<int> treeLnkFromList(list);
  BST<int> BSTFromList(list);

  if (list.Size() != (unsigned long)size)
  {
    FoundError("InsertAtBack", "List");
  }
  if (treeVecFromList.Size() != list.Size()) {
    FoundError("traversable constructor", "BinaryTreeVec");
  }
  if (treeLnkFromList.Size() != list.Size()) {
    FoundError("traversable constructor", "BinaryTreeLnk");
  }
  if (BSTFromList.Size() != num_of_different_numbers) {
    FoundError("traversable constructor", "BST");
  }


  cout << "Checking BreadthFold correctness" << endl;
  string concatvec = treeVecFromList.BreadthFold(std::function([](const int &curr, const string &acc) {return acc+to_string(curr);}), string());
  string concatlnk = treeLnkFromList.BreadthFold(std::function([](const int &curr, const string &acc) {return acc+to_string(curr);}), string());

  if (concatlnk != acc || acc != concatlnk) FoundError("BreadthFold", TEST_TITLE);
  
  cout << "Checking Map and Fold correctness (for each \"order\")" << endl;

  int i = 0;
  auto incrementAndCount = [&i](int &curr){++curr; ++i;};
  treeVecFromList.Map(incrementAndCount);
  treeVecFromList.InOrderMap(incrementAndCount);
  treeVecFromList.PreOrderMap(incrementAndCount);
  treeVecFromList.PostOrderMap(incrementAndCount);
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
  int bstTot = BSTFromList.Fold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (totAfterIncrement != vecTot) {
    FoundError("Fold or Map", "BinaryTreeVec");
  }
  if (totAfterIncrement != lnkTot) {
    FoundError("Fold or Map", "BinaryTreeLnk");
  }
  if (totForBST != bstTot) {
    FoundError("Fold or Map", "BST");
  }

  vecTot = treeVecFromList.InOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.InOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  bstTot = BSTFromList.InOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (totAfterIncrement != vecTot) {
    FoundError("InOrderFold or Map", "BinaryTreeVec");
  }
  if (totAfterIncrement != lnkTot) {
    FoundError("InOrderFold or Map", "BinaryTreeLnk");
  }
  if (totForBST != bstTot) {
    FoundError("InOrderFold or Map", "BST");
  }

  vecTot = treeVecFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  bstTot = BSTFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (totAfterIncrement != vecTot) {
    FoundError("PostOrderFold or Map", "BinaryTreeVec");
  }
  if (totAfterIncrement != lnkTot) {
    FoundError("PostOrderFold or Map", "BinaryTreeLnk");
  }
  if (totForBST != bstTot) {
    FoundError("PostOrderFold or Map", "BST");
  }

  vecTot = treeVecFromList.PreOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  lnkTot = treeLnkFromList.PreOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  bstTot = BSTFromList.PostOrderFold(std::function([](const int &curr, const int &acc) {return acc+curr;}), 0);
  if (totAfterIncrement != vecTot) {
    FoundError("PreOrderFold or Map", "BinaryTreeVec");
  }
  if (totAfterIncrement != lnkTot) {
    FoundError("PreOrderFold or Map", "BinaryTreeLnk");
  }
  if (totForBST != bstTot) {
    FoundError("PreOrderFold or Map", "BST");
  }

  cout << "Trying comparisons after random insert ";
  bool inserted = list.Insert(distx(genx));
  if (inserted) {
    cout << "(the number was inserted)" << endl;
  }
  else {
    cout << "(the number was not inserted)" << endl;
  }

  list.Map([](int& curr) {
    curr += 5;
  });

  BinaryTreeVec<int> newBTVec(list);
  BinaryTreeLnk<int> newBTLnk(list);
  if (inserted == (newBTVec == treeVecFromList)) {
    FoundError("Comparison", "BinaryTreeVec");
  }
  if (inserted == (newBTLnk == treeLnkFromList)) {
    FoundError("Comparison", "BinaryTreeLnk");
  }
}

void TestBST(BST<int> bst, unsigned long size, int min, int max, int num_for_test, int succ, int prec, int root) {
  const char* TEST_TITLE = "BST (with arguments)";

  BST<int> restore(bst);
  BST<int> copy = bst;

  cout << "Testing Size" << endl;
  if (bst.Size() != size) {
    FoundError("Size", TEST_TITLE);
  }

  cout << "Testing Min" << endl;
  if (bst.Min() != min) {
    FoundError("Min", TEST_TITLE);
  }
  if (copy.MinNRemove() != min || copy.Size() != --size) {
    FoundError("MinNRemove", TEST_TITLE);
  }
  bst.RemoveMin();
  if (bst.Min() <= min || bst != copy) {
    FoundError("RemoveMin", TEST_TITLE);
  }

  cout << "Testing Max" << endl;
  if (bst.Max() != max) {
    FoundError("Max", TEST_TITLE);
  }
  if (copy.MaxNRemove() != max || copy.Size() != --size) {
    FoundError("MaxNRemove", TEST_TITLE);
  }
  bst.RemoveMax();
  if (bst.Max() > max || bst != copy) {
    FoundError("RemoveMax", TEST_TITLE);
  }

  cout << "Testing Predecessor" << endl;
  bst = restore;
  copy = restore;
  if (bst.Predecessor(num_for_test) != prec) { // todo error
    cout << bst.Predecessor(num_for_test) << " diff " << prec << endl;
    FoundError("Predecessor", TEST_TITLE);
  }
  if (copy.PredecessorNRemove(num_for_test) != prec) {
    FoundError("PredecessorNRemove", TEST_TITLE);
  }
  bst.RemovePredecessor(num_for_test);
  
  // tries to find another predecessor after removal but there could be none
  try {
    int new_prec = bst.Predecessor(num_for_test);
    if (new_prec >= prec) {
      FoundError("RemovePredecessor", TEST_TITLE);
    }
  } catch (std::length_error &err) {
    if (prec != min) {
      FoundError("RemovePredecessor (in this case prec should be = min but is not)", TEST_TITLE);
    }
  }
  
  if (bst != copy) {
    FoundError("RemovePredecessor", TEST_TITLE);
  }


  cout << "Testing Successor" << endl;
  bst = restore;
  copy = restore;
  if (bst.Successor(num_for_test) != succ) {
    FoundError("Successor", TEST_TITLE);
  }
  if (copy.SuccessorNRemove(num_for_test) != succ) {
    FoundError("SuccessorNRemove", TEST_TITLE);
  }

  bst.RemoveSuccessor(num_for_test);
  // tries to find another successor after removal but there could be none
  try {
    int new_succ = bst.Successor(num_for_test);
    if (new_succ <= succ) {
      FoundError("RemoveSuccessor", TEST_TITLE);
    }
  } catch (std::length_error &err) {
    if (succ != max) {
      FoundError("RemoveSuccessor (in this case succ should be = max but is not)", TEST_TITLE);
    }
  }
  if (bst != copy) {
    FoundError("RemoveSuccessor", TEST_TITLE);
  }

  cout << "Testing Root" << endl;

  bst = restore;
  if (bst.Root().Element() != root) {
    FoundError("Root", TEST_TITLE);
  }


  cout << "Testing Exists and dictionary functions" << endl;
  int tests [3] {max, min, prec};
  for (int i = 0; i < 3; i++)
  {
    int curr = tests[i];
    if (bst.Exists(curr) == false) {
      FoundError("Exists", TEST_TITLE);
    }

    if (bst.Insert(curr)) {
      FoundError("Insert (existing value)", TEST_TITLE);
    }
  
    if (bst.Remove(curr) == false) {
      FoundError("Remove (existing value)", TEST_TITLE);
    }

    if (bst.Remove(curr)) {
      FoundError("Remove (non present value)", TEST_TITLE);
    }

    if (bst.Insert(curr) == false) {
      FoundError("Insert (non present value)", TEST_TITLE);
    }
  }

  cout << "Testing comparisons" << endl;
  if (bst != restore) {
    FoundError("Comparisons", TEST_TITLE);
  }

  cout << "Testing Clear" << endl;
  bst.Clear();
  TestEmptyBinaryTree(bst);
}

void TestBST(){
  const char* TEST_TITLE = "BST";
  TellTest(TEST_TITLE);

  cout << "Creating List" << endl;
  List<int> list = List<int>();
  list.InsertAtBack(10);
  list.InsertAtBack(2);
  list.InsertAtBack(1);
  list.InsertAtBack(3);
  list.InsertAtBack(6);
  list.InsertAtBack(1);
  int tot = 22;

  cout << "Testing Constructors" << endl;
  BST<int> bst_trav(list);
  TestBinaryTree(bst_trav, 5, 10, tot);
  
  BST<int> bst_copy = bst_trav;
  TestBinaryTree(bst_copy, 5, 10, tot);

  BST<int> bst_map(std::move(bst_trav));
  TestBinaryTree(bst_trav, 0, 10, 0);
  TestBinaryTree(bst_map, 5, 10, tot);

  BST<int> bst = std::move(bst_copy);
  TestBinaryTree(bst_trav, 0, 10, 0);
  TestBinaryTree(bst, 5, 10, tot);

  bst_copy = bst;
  TestBinaryTree(bst_copy, 5, 10, tot);

  BST<int> bst_copy_constr(bst);
  TestBinaryTree(bst_copy_constr, 5, 10, tot);

  TestBST(bst, 5, 1, 10, 3, 6, 2, 10);

  cout << "Building random BST" << endl;
  unsigned long size;
  int min;
  int max;
  int num_for_tests;
  int prec;
  int succ;
  int root;
  BST<int> random_bst;
  GetRandomBST(random_bst, size, min, max, num_for_tests, 
                prec, succ, root);
  
  cout << "BST created with: " << endl;
  cout << "size = " << size << endl;
  cout << "min = " << min << endl;
  cout << "max = " << max << endl;
  cout << "num for tests = " << num_for_tests << endl;
  cout << "prec = " << prec << endl;
  cout << "succ = " << succ << endl;
  cout << "root = " << root << endl;

  TestBST(random_bst, size, min, max, num_for_tests, succ, prec, root);
}

void TestBinaryTree()
{
  TellTest ("BinaryTree");

  TestEmptyBinaryTree();
  TestBinaryTreeLnk();
  TestBinaryTreeVec();
  TestBST();
  TestBinaryTreeRandom();
}

template <typename T>
void TestBTIterator (Iterator<T> &iterator, BinaryTree<T> &bt) {
  const char* TEST_TITLE = "BTIterator";
  cout << "Testing Iterator as a Iterator" << endl;

  if (bt.Empty()) {
    cout << "Binary tree was empty" << endl;
    cout << "Checking if iterator is terminated" << endl;
    if (iterator.Terminated() == false) {
      FoundError("Terminated", TEST_TITLE);
    }
    
    cout << "Testing operator*" << endl;
    bool err = false;
    try {
      (*iterator);
    }
    catch (std::out_of_range &e) {
      err = true;
    }
    if (err == false) {
      FoundError("operator* (no exception was thrown)", TEST_TITLE);
    }
  }
  else 
  {
    cout << "BTIterator skipped because binary tree was not empty" << endl;
  }
}

template <typename T>
void TestBTMutableIterator(MutableIterator<T> &mutableiterator, BinaryTree<T> &bt) {
  const char* TEST_TITLE = "MutableIterator";
  cout << "Testing Iterator as a MutableIterator" << endl;
  TestBTIterator(mutableiterator, bt);
  if (bt.Empty()) {
    if (mutableiterator.Terminated() == false) {
      FoundError("Terminated", TEST_TITLE);
    }
  }
  else
  {
    T old = bt.Root().Element();
    ++(*mutableiterator);
    if (bt.Root().Element() != old+1) {
      FoundError("Mutable", TEST_TITLE);
    }
  }
}

template <typename T>
void TestBTForwardIterator(ForwardIterator<T> &forwarditerator, BinaryTree<T> &bt) {
  const char *TEST_TITLE = "ForwardIterator";
  cout << "Testing Iterator as a ForwardIterator" << endl;
  unsigned long count = 0;
  while (!forwarditerator.Terminated()) {
    ++count;
    ++forwarditerator;
  }
  if (count != bt.Size()) {
    cout << count << "  " << bt.Size() << endl;
    FoundError("Terminated or ++", TEST_TITLE);
  }
  
  bool error = false;
  try {
    *forwarditerator;
  }
  catch (std::out_of_range &e)
  {
    error = true;
  }
  if (error == false) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }
}

template <typename T>
void TestBTPreOrderIterator(BTPreOrderIterator<T> &iterator, BinaryTree<T> &bt)
{
  const char* TEST_TITLE = "BTPreOrderIterator";
  TestBTIterator(iterator, bt);
  iterator.Reset();
  TestBTForwardIterator(iterator, bt);
  iterator.Reset();

  BTPreOrderIterator<T> copy = iterator;
  if (copy != iterator) {
    FoundError("Comparison", TEST_TITLE);
  }

  if (bt.Size() > 2) {
    ++iterator;
    ++iterator;
    iterator.Reset();

    cout << "Testing Comparison" << endl;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }
    ++iterator;
    ++copy;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }

    copy.Reset();
    iterator.Reset();
  }

  cout << "Testing order" << endl;
  bt.PreOrderTraverse([&iterator, &TEST_TITLE](const T& curr){
    if (curr != (*iterator)) {
      FoundError("Increment", TEST_TITLE);
    }
    ++iterator;
  });

  cout << "Testing out_of_range" << endl;

  bool error = false;
  try {
    *iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  error = false;
  try {
    ++iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  iterator.Reset();
}

template <typename T>
void TestBTInOrderIterator(BTInOrderIterator<T> &iterator, BinaryTree<T> &bt)
{
  const char* TEST_TITLE = "BTInOrderIterator";
  // TODO mutable
  TestBTIterator(iterator, bt);
  iterator.Reset();
  TestBTForwardIterator(iterator, bt);
  iterator.Reset();

  BTInOrderIterator<T> copy = iterator;
  if (copy != iterator) {
    FoundError("Comparison", TEST_TITLE);
  }

  if (bt.Size() > 2) {
    ++iterator;
    ++iterator;
    iterator.Reset();

    cout << "Testing Comparison" << endl;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }
    ++iterator;
    ++copy;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }

    copy.Reset();
    iterator.Reset();
  }

  cout << "Testing order" << endl;
  bt.InOrderTraverse([&iterator, &TEST_TITLE](const T& curr){
    if (curr != (*iterator)) {
      FoundError("Increment", TEST_TITLE);
    }
    ++iterator;
  });
  
  cout << "Testing out_of_range" << endl;

  bool error = false;
  try {
    *iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  error = false;
  try {
    ++iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  iterator.Reset();
}

template <typename T>
void TestBTPostOrderIterator(BTPostOrderIterator<T> &iterator, BinaryTree<T> &bt)
{
  const char* TEST_TITLE = "BTPostOrderIterator";
  TestBTIterator(iterator, bt);
  iterator.Reset();
  TestBTForwardIterator(iterator, bt);
  iterator.Reset();

  BTPostOrderIterator<T> copy = iterator;
  if (copy != iterator) {
    FoundError("Comparison", TEST_TITLE);
  }

  if (bt.Size() > 2) {
    ++iterator;
    ++iterator;
    iterator.Reset();

    cout << "Testing Comparison" << endl;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }
    ++iterator;
    ++copy;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }

    copy.Reset();
    iterator.Reset();
  }

  cout << "Testing order" << endl;
  bt.PostOrderTraverse([&iterator, &TEST_TITLE](const T& curr){
    if (curr != (*iterator)) {
      FoundError("Increment", TEST_TITLE);
    }
    ++iterator;
  });

  cout << "Testing out_of_range" << endl;

  bool error = false;
  try {
    *iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  error = false;
  try {
    ++iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  iterator.Reset();
}

template <typename T>
void TestBTBreadthIterator(BTBreadthIterator<T> &iterator, BinaryTree<T> &bt)
{
  const char* TEST_TITLE = "BTBreadthIterator";
  TestBTIterator(iterator, bt);
  iterator.Reset();
  TestBTForwardIterator(iterator, bt);
  iterator.Reset();

  BTBreadthIterator<T> copy = iterator;
  if (copy != iterator) {
    FoundError("Comparison", TEST_TITLE);
  }

  if (bt.Size() > 2) {
    ++iterator;
    ++iterator;
    iterator.Reset();

    cout << "Testing Comparison" << endl;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }
    ++iterator;
    ++copy;
    if (copy != iterator) {
      FoundError("Comparison", TEST_TITLE);
    }

    copy.Reset();
    iterator.Reset();
  }

  cout << "Testing order" << endl;
  bt.BreadthTraverse([&iterator, &TEST_TITLE](const T& curr){
    if (curr != (*iterator)) {
      FoundError("Increment", TEST_TITLE);
    }
    ++iterator;
  });

  cout << "Testing out_of_range" << endl;

  bool error = false;
  try {
    *iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  error = false;
  try {
    ++iterator;
  }
  catch (std::out_of_range &e) {
    error = true;
  }
  if (!error) {
    FoundError("operator* (terminated)", TEST_TITLE);
  }

  iterator.Reset();
}

void TestPreOrderIteratorsBST(BST<int> &bst) {
  cout << " - Testing iterator(bst) - " << endl;
  BTPreOrderIterator<int> iterator(bst);
  TestBTPreOrderIterator(iterator, bst);

  cout << " - Testing iterator created with copy assignment - " << endl;
  BTPreOrderIterator<int> copy_assign(bst);
  copy_assign = iterator;
  TestBTPreOrderIterator(copy_assign, bst);
  
  cout << " - Testing iterator created with move assignment - " << endl;
  BTPreOrderIterator<int> move_assign(bst);
  move_assign = std::move(iterator);
  TestBTPreOrderIterator(move_assign, bst);

  cout << " - Testing iterator created with copy constructor - " << endl;
  BTPreOrderIterator<int> copy_constr(move_assign);
  TestBTPreOrderIterator(copy_constr, bst);

  cout << " - Testing iterator created with move constructor - " << endl;
  BTPreOrderIterator<int> move_constr(std::move(move_assign));
  TestBTPreOrderIterator(move_constr, bst);
}

void TestInOrderIteratorsBST(BST<int> &bst) {
  cout << " - Testing iterator(bst) - " << endl;
  BTInOrderIterator<int> iterator(bst);
  TestBTInOrderIterator(iterator, bst);

  cout << " - Testing iterator created with copy assignment - " << endl;
  BTInOrderIterator<int> copy_assign(bst);
  copy_assign = iterator;
  TestBTInOrderIterator(copy_assign, bst);

  cout << " - Testing iterator created with move assignment - " << endl;
  BTInOrderIterator<int> move_assign(bst);
  move_assign = std::move(iterator);
  TestBTInOrderIterator(move_assign, bst);

  cout << " - Testing iterator created with copy constructor - " << endl;  
  BTInOrderIterator<int> copy_constr(move_assign);
  TestBTInOrderIterator(copy_constr, bst);

  cout << " - Testing iterator created with move constructor - " << endl;
  BTInOrderIterator<int> move_constr(std::move(move_assign));
  TestBTInOrderIterator(move_constr, bst);
}

void TestPostOrderIteratorsBST(BST<int> &bst) {
  cout << " - Testing iterator(bst) - " << endl;
  BTPostOrderIterator<int> iterator(bst);
  TestBTPostOrderIterator(iterator, bst);

  cout << " - Testing iterator created with copy assignment - " << endl;
  BTPostOrderIterator<int> copy_assign(bst);
  copy_assign = iterator;
  TestBTPostOrderIterator(copy_assign, bst);

  cout << " - Testing iterator created with move assignment - " << endl;
  BTPostOrderIterator<int> move_assign = std::move(iterator);
  TestBTPostOrderIterator(move_assign, bst);

  cout << " - Testing iterator created with copy constructor - " << endl;
  BTPostOrderIterator<int> copy_constr(move_assign);
  TestBTPostOrderIterator(copy_constr, bst);

  cout << " - Testing iterator created with move constructor - " << endl;
  BTPostOrderIterator<int> move_constr(std::move(move_assign));
  TestBTPostOrderIterator(move_constr, bst);
}

void TestBreadthIteratorsBST(BST<int> &bst) {
  cout << " - Testing iterator(bst) - " << endl;
  BTBreadthIterator<int> iterator(bst);
  TestBTBreadthIterator(iterator, bst);

  cout << " - Testing iterator created with copy assignment - " << endl;
  BTBreadthIterator<int> copy_assign(bst);
  copy_assign = iterator;
  TestBTBreadthIterator(copy_assign, bst);

  cout << " - Testing iterator created with move assignment - " << endl;
  BTBreadthIterator<int> move_assign(bst);
  move_assign = std::move(iterator);
  TestBTBreadthIterator(move_assign, bst);

  cout << " - Testing iterator created with copy constructor - " << endl;
  BTBreadthIterator<int> copy_constr(move_assign);
  TestBTBreadthIterator(copy_constr, bst);

  cout << " - Testing iterator created with move constructor - " << endl;
  BTBreadthIterator<int> move_constr(std::move(move_assign));
  TestBTBreadthIterator(move_constr, bst);
}

void TestIteratorsBST(BST<int> &bst) {
  TellTest("PreOrderIterator (BST)");
  TestPreOrderIteratorsBST(bst);
  TellTest("InOrderIterator (BST)");
  TestInOrderIteratorsBST(bst);
  TellTest("PostOrderIterator (BST)");
  TestPostOrderIteratorsBST(bst);
  TellTest("BreadthIterator (BST)");
  TestBreadthIteratorsBST(bst);
}

void TestIteratorsBST()
{
  TellTest("Iterators in BST");

  BST<int> empty_bst;
  TestIteratorsBST(empty_bst);

  BST<int> random_bst;
  GetRandomBST(random_bst);
  TestIteratorsBST(random_bst);

  BST<int> degenerate_bst;
  degenerate_bst.Insert(100);
  degenerate_bst.Insert(0);
  TestIteratorsBST(degenerate_bst);

  degenerate_bst.Insert(50);
  degenerate_bst.Insert(25);
  degenerate_bst.Insert(12);
  degenerate_bst.Insert(6);
  TestIteratorsBST(degenerate_bst);
}

void TestIterators()
{
  TellTest ("Iterator");
  TestIteratorsBST();
}

} // end of namespace "fab"


void mytest() {
  fab::TestBinaryTree();
  fab::TestIterators();
  cout << endl << "END" << endl << "Errors: " << fab::num_of_errors << endl;
}
