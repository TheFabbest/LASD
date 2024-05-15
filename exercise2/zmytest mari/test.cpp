
// #include "..."
#include <iostream>
#include <random>

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/stack.hpp"
#include "../queue/queue.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../iterator/iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/stack/stack.hpp"
#include "../zlasdtest/queue/queue.hpp"
#include "../zlasdtest/iterator/iterator.hpp"
#include "../zlasdtest/binarytree/binarytree.hpp"
#include "../zlasdtest/bst/bst.hpp"

#include "../zmytest/test.hpp"

using namespace lasd;
using namespace std;

/* ************************************************************************** */

void mytest() {
  
  //TEST FUNZIONI/COMBINAZIONI NON TESTATE DAL PROF

  /* myDictionary();
  myLinear();
  myMappable();
  myTraversable();

  //TEST CASI PARTICOLARI

  mySortableVector();
  myList();
  myQueueList();
  myQueueVec();
  myQueue();
  myStack();
  myStackVec(); */

  //TEST BINARY TREE

  //myBinaryTreeLnk();
  //myBinaryTreeVec();
  myBST();

}

void myDictionary() {
  uint mytestnum = 0;
  uint mytesterr = 0;

  List<int> lst1;

  InsertC(mytestnum, mytesterr, lst1, true, 1);
  InsertC(mytestnum, mytesterr, lst1, true, 2);
  InsertC(mytestnum, mytesterr, lst1, false, 1);

  InsertM(mytestnum, mytesterr, lst1, true, 3);
  InsertM(mytestnum, mytesterr, lst1, true, 4);
  InsertM(mytestnum, mytesterr, lst1, false, 3);

  Remove(mytestnum, mytesterr, lst1, false, 5);
  Remove(mytestnum, mytesterr, lst1, true, 4);
  Remove(mytestnum, mytesterr, lst1, true, 2);
  Remove(mytestnum, mytesterr, lst1, true, 1);
  //lst1 contiene 3

  Vector<int> toinsert(3);
  SetAt(mytestnum, mytesterr, toinsert, true, 0, 1);
  SetAt(mytestnum, mytesterr, toinsert, true, 1, 2);
  SetAt(mytestnum, mytesterr, toinsert, true, 2, 3);
  InsertAllC(mytestnum, mytesterr, lst1, false, toinsert);
  //lst1 contiene 1 2 3

  SetAt(mytestnum, mytesterr, toinsert, true, 0, 4);
  SetAt(mytestnum, mytesterr, toinsert, true, 1, 5);
  SetAt(mytestnum, mytesterr, toinsert, true, 2, 6);
  InsertAllC(mytestnum, mytesterr, lst1, true, toinsert);
  
  Vector<int> toinsert2 = toinsert;
  Vector<int> toinsert3 = toinsert;
  SetAt(mytestnum, mytesterr, toinsert2, true, 2, 3);
  lst1.Clear();
  InsertAllM(mytestnum, mytesterr, lst1, true, move(toinsert));
  InsertAllM(mytestnum, mytesterr, lst1, false, move(toinsert2));
  //lst1 contiene 4 5 6 3
  
  Size(mytestnum, mytesterr, lst1, true, 4);
  RemoveAll(mytestnum, mytesterr, lst1, true, toinsert3);
  SetAt(mytestnum, mytesterr, toinsert3, true, 2, 3);
  RemoveAll(mytestnum, mytesterr, lst1, false, toinsert3);
  Empty(mytestnum, mytesterr, lst1, true);

  InsertSomeC(mytestnum, mytesterr, lst1, true, toinsert3);
  InsertSomeC(mytestnum, mytesterr, lst1, false, toinsert3);
  Vector<int> toinsert4(2);
  SetAt(mytestnum, mytesterr, toinsert4, true, 0, 1);
  SetAt(mytestnum, mytesterr, toinsert4, true, 1, 2);

  RemoveSome(mytestnum, mytesterr, lst1, false, toinsert4);
  SetAt(mytestnum, mytesterr, toinsert4, true, 0, 5);
  RemoveSome(mytestnum, mytesterr, lst1, false, toinsert4);
  //lst1 contiene 4 3

  InsertSomeM(mytestnum, mytesterr, lst1, false, move(toinsert3));
  SetAt(mytestnum, mytesterr, toinsert4, true, 1, 4);
  InsertSomeM(mytestnum, mytesterr, lst1, false, move(toinsert4));
  Size(mytestnum, mytesterr, lst1, true, 3);
  
  cout << endl << "End of functions inherited from Dictionary in List Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void myLinear() {
  uint mytestnum = 0;
  uint mytesterr = 0;
  
  Vector<int> vec;
  List<int> lst;

  EqualLinear(mytestnum, mytesterr, vec, lst, true);
  NonEqualLinear(mytestnum, mytesterr, vec, lst, false);
  EqualLinear(mytestnum, mytesterr, lst, vec, true);
  NonEqualLinear(mytestnum, mytesterr, lst, vec, false);

  Vector<int> vec2 = vec;
  List<int> lst2 = lst;
  EqualLinear(mytestnum, mytesterr, vec, vec2, true);
  EqualLinear(mytestnum, mytesterr, lst, lst2, true);

  vec.Resize(3);
  SetAt(mytestnum, mytesterr, vec, true, 0, 1);
  SetAt(mytestnum, mytesterr, vec, true, 1, 2);
  SetAt(mytestnum, mytesterr, vec, true, 2, 3);
  InsertAtBack(mytestnum, mytesterr, lst, true, 1);
  InsertAtBack(mytestnum, mytesterr, lst, true, 2);
  EqualLinear(mytestnum, mytesterr, vec, lst, false);

  InsertAtBack(mytestnum, mytesterr, lst, true, 3);
  EqualLinear(mytestnum, mytesterr, vec, lst, true);
  InsertAtBack(mytestnum, mytesterr, lst, true, 3);
  vec.Resize(4);
  EqualLinear(mytestnum, mytesterr, vec, lst, false);

  vec.Clear();
  SetAt(mytestnum, mytesterr, vec, false, 0, 1);
  SetFront(mytestnum, mytesterr, vec, false, 0);
  GetFront(mytestnum, mytesterr, vec, false, 0);

  lst.Clear();
  GetFront(mytestnum, mytesterr, lst, false, 0);
  SetFront(mytestnum, mytesterr, lst, false, 0);
  InsertAtFront(mytestnum, mytesterr, lst, true, 0);
  GetFront(mytestnum, mytesterr, lst, true, 0);

  cout << endl << "End of functions from Linear Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void myMappable() {
  
  uint mytestnum = 0;
  uint mytesterr = 0;
  
  Vector<int> vec;
  List<int> lst;

  MapPreOrder(mytestnum, mytesterr, vec, true, &MapIncrement<int>);
  MapPreOrder(mytestnum, mytesterr, lst, true, &MapIncrement<int>);
  MapPostOrder(mytestnum, mytesterr, vec, true, &MapIncrement<int>);
  MapPostOrder(mytestnum, mytesterr, lst, true, &MapIncrement<int>);

  vec.Resize(3);
  SetAt(mytestnum, mytesterr, vec, true, 0, 1);
  SetAt(mytestnum, mytesterr, vec, true, 1, 2);
  SetAt(mytestnum, mytesterr, vec, true, 2, 3);
  InsertAtBack(mytestnum, mytesterr, lst, true, 1);
  InsertAtBack(mytestnum, mytesterr, lst, true, 2);
  InsertAtBack(mytestnum, mytesterr, lst, true, 3);

  MapPreOrder(mytestnum, mytesterr, vec, true, &MapIncrement<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPreOrder(mytestnum, mytesterr, vec, true, &MapDecrement<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  Exists(mytestnum, mytesterr, vec, false, 4);

  MapPreOrder(mytestnum, mytesterr, vec, true, &MapDouble<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPreOrder(mytestnum, mytesterr, vec, true, &MapHalf<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPreOrder(mytestnum, mytesterr, vec, true, &MapInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);

  MapPreOrder(mytestnum, mytesterr, lst, true, &MapIncrement<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  MapPreOrder(mytestnum, mytesterr, lst, true, &MapDecrement<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  Exists(mytestnum, mytesterr, lst, false, 4);

  MapPreOrder(mytestnum, mytesterr, lst, true, &MapDouble<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  MapPreOrder(mytestnum, mytesterr, lst, true, &MapHalf<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  
  EqualLinear(mytestnum, mytesterr, vec, lst, false);
  MapPreOrder(mytestnum, mytesterr, lst, true, &MapInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  EqualLinear(mytestnum, mytesterr, vec, lst, true);

  MapPostOrder(mytestnum, mytesterr, vec, true, &MapDecrement<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, vec, true, &MapIncrement<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  Exists(mytestnum, mytesterr, vec, false, -4);

  MapPostOrder(mytestnum, mytesterr, vec, true, &MapDouble<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, vec, true, &MapHalf<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, vec, true, &MapInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);

  MapPostOrder(mytestnum, mytesterr, lst, true, &MapDecrement<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, lst, true, &MapIncrement<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  Exists(mytestnum, mytesterr, lst, false, -4);

  MapPostOrder(mytestnum, mytesterr, lst, true, &MapDouble<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, lst, true, &MapHalf<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  
  EqualLinear(mytestnum, mytesterr, vec, lst, false);
  MapPostOrder(mytestnum, mytesterr, lst, true, &MapInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  EqualLinear(mytestnum, mytesterr, vec, lst, true);
  
  MapPreOrder(mytestnum, mytesterr, lst, true, &MapParityInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, lst, true, &MapParityInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  
  MapPreOrder(mytestnum, mytesterr, vec, true, &MapParityInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  MapPostOrder(mytestnum, mytesterr, vec, true, &MapParityInvert<int>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);

  Vector<string> vec2(2);
  List<string> lst2;
  SetAt(mytestnum, mytesterr, vec2, true, 0, string("A"));
  SetAt(mytestnum, mytesterr, vec2, true, 1, string(""));
  InsertAtBack(mytestnum, mytesterr, lst2, true, string(""));
  InsertAtBack(mytestnum, mytesterr, lst2, true, string("A"));
  
  MapPostOrder(mytestnum, mytesterr, vec2, true, [](string & str) { MapStringNonEmptyAppend(str, string("!")); });
  TraversePreOrder(mytestnum, mytesterr, vec2, true, &TraversePrint<string>);
  MapPostOrder(mytestnum, mytesterr, lst2, true, [](string & str) { MapStringNonEmptyAppend(str, string("!")); });
  TraversePreOrder(mytestnum, mytesterr, lst2, true, &TraversePrint<string>);

  cout << endl << "End of functions from Mappable Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void myTraversable() {
  uint mytestnum = 0;
  uint mytesterr = 0;
  
  Vector<int> vec(3);
  List<int> lst;
  
  SetAt(mytestnum, mytesterr, vec, true, 0, 1);
  SetAt(mytestnum, mytesterr, vec, true, 1, 2);
  SetAt(mytestnum, mytesterr, vec, true, 2, 3);
  InsertAtBack(mytestnum, mytesterr, lst, true, 1);
  InsertAtBack(mytestnum, mytesterr, lst, true, 2);

  TraversePostOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  
  FoldPreOrder(mytestnum, mytesterr, vec, true, &FoldParity, 0, 0);
  FoldPreOrder(mytestnum, mytesterr, lst, true, &FoldParity, 0, 1);
  FoldPostOrder(mytestnum, mytesterr, vec, true, &FoldParity, 0, 0);
  FoldPostOrder(mytestnum, mytesterr, lst, true, &FoldParity, 0, 1);
  TraversePostOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);

  vec.Clear();
  lst.Clear();
  FoldPostOrder(mytestnum, mytesterr, vec, true, &FoldParity, 0, 0);
  FoldPostOrder(mytestnum, mytesterr, lst, true, &FoldParity, 0, 0);
  TraversePostOrder(mytestnum, mytesterr, vec, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, lst, true, &TraversePrint<int>);
  
  cout << endl << "End of functions from Traversable Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void mySortableVector() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  SortableVector<int> vec;
  Empty(mytestnum, mytesterr, vec, true);
  Exists(mytestnum, mytesterr, vec, false, 0);
  SetFront(mytestnum, mytesterr, vec, false, 0);
  GetFront(mytestnum, mytesterr, vec, false, 0);
  SetBack(mytestnum, mytesterr, vec, false, 0);
  GetBack(mytestnum, mytesterr, vec, false, 0);
  vec.Sort();

  List<int> lst;
  for (ulong i = 0; i < 10; i++) {
    lst.InsertAtBack(i);
  }
  vec.Resize(10);
  for (ulong i = 0; i < vec.Size(); i++) {
    vec[i] = i;
  }

  SortableVector<int> sortablevec = SortableVector<int>(lst);
  SortableVector<int> othersortable = SortableVector<int>(std::move(vec));
  EqualVector(mytestnum, mytesterr, sortablevec, othersortable, true);
  
  List<int> otherlst = List<int>(sortablevec);
  EqualLinear(mytestnum, mytesterr, sortablevec, otherlst, true);

  cout << endl << "End of functions from SortableVector Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void myList() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  List<int> lst;
  Remove(mytestnum, mytesterr, lst, false, 0);
  Remove(mytestnum, mytesterr, lst, false, 0);
  Empty(mytestnum, mytesterr, lst, true);
  Size(mytestnum, mytesterr, lst, true, 0);

  List<int> coplst = lst;
  EqualLinear(mytestnum, mytesterr, lst, coplst, true);
  EqualList(mytestnum, mytesterr, lst, coplst, true);

  InsertAtBack(mytestnum, mytesterr, lst, true, 1);
  coplst = lst;
  EqualLinear(mytestnum, mytesterr, lst, coplst, true);
  EqualList(mytestnum, mytesterr, lst, coplst, true);

  List<int> movlst = move(lst);
  EqualLinear(mytestnum, mytesterr, lst, movlst, false);
  EqualList(mytestnum, mytesterr, lst, movlst, false);

  List<int> copconstrlst(coplst);
  EqualLinear(mytestnum, mytesterr, coplst, copconstrlst, true);
  EqualList(mytestnum, mytesterr, coplst, copconstrlst, true);

  List<int> movconstrlst(std::move(copconstrlst));
  EqualLinear(mytestnum, mytesterr, movconstrlst, copconstrlst, false);
  EqualList(mytestnum, mytesterr, movconstrlst, copconstrlst, false);
  Size(mytestnum, mytesterr, copconstrlst, true, 0);
  EqualLinear(mytestnum, mytesterr, movconstrlst, coplst, true);
  EqualList(mytestnum, mytesterr, movconstrlst, coplst, true);

  cout << endl << "End of functions from List Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl;
}

void myQueueList() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  QueueLst<int> que;
  Empty(mytestnum, mytesterr, que, true);
  Size(mytestnum, mytesterr, que, true, 0);
  Dequeue(mytestnum, mytesterr, que, false);
  Head(mytestnum, mytesterr, que, false, 0);
  HeadNDequeue(mytestnum, mytesterr, que, false, 0);

  EnqueueC(mytestnum, mytesterr, que, 1);
  EnqueueC(mytestnum, mytesterr, que, 2);
  Size(mytestnum, mytesterr, que, true, 2);
  Empty(mytestnum, mytesterr, que, false);
  HeadNDequeue(mytestnum, mytesterr, que, true, 1);
  HeadNDequeue(mytestnum, mytesterr, que, true, 2);
  HeadNDequeue(mytestnum, mytesterr, que, false, 0);
  Empty(mytestnum, mytesterr, que, true);

  QueueLst<int> copque = que;
  EqualQueue(mytestnum, mytesterr, que, copque, true);
  EnqueueM(mytestnum, mytesterr, que, 1);
  EnqueueM(mytestnum, mytesterr, copque, 1);
  EqualQueue(mytestnum, mytesterr, que, copque, true);
  EnqueueM(mytestnum, mytesterr, que, 2);
  EnqueueM(mytestnum, mytesterr, que, 3);

  QueueLst<int> copconstrque(que);
  Vector<int> vec(que.Size());
  List<int> lst = List<int>();

  for (unsigned long i = 0; i < 3; i++)
  {
    vec[i] = que.Head();
    que.Enqueue(que.HeadNDequeue());
  }

  for (unsigned long i = 0; i < 3; i++)
  {
    lst.InsertAtBack(que.Head());
    que.Enqueue(que.HeadNDequeue());
  }

  QueueLst<int> travveconstrque(vec);
  QueueLst<int> travlstconstrque(lst);
  QueueLst<int> mapconstrque(std::move(vec));
  copque = que;
  
  Dequeue(mytestnum, mytesterr, que, true);
  int second = que.Head();
  HeadNDequeue(mytestnum, mytesterr, que, true, second);

  que.Enqueue(1);
  que.Enqueue(second);
  que.Enqueue(3);
  HeadNDequeue(mytestnum, mytesterr, que, true, 3);

  EqualQueue(mytestnum, mytesterr, copconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, travveconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, travlstconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, mapconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, copque, que, true);

  cout << endl << "End of functions from QueueList Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myQueueVec() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  QueueVec<int> que;
  Empty(mytestnum, mytesterr, que, true);
  Size(mytestnum, mytesterr, que, true, 0);
  Dequeue(mytestnum, mytesterr, que, false);
  Head(mytestnum, mytesterr, que, false, 0);
  HeadNDequeue(mytestnum, mytesterr, que, false, 0);

  EnqueueC(mytestnum, mytesterr, que, 1);
  EnqueueC(mytestnum, mytesterr, que, 2);
  Size(mytestnum, mytesterr, que, true, 2);
  Empty(mytestnum, mytesterr, que, false);
  HeadNDequeue(mytestnum, mytesterr, que, true, 1);
  HeadNDequeue(mytestnum, mytesterr, que, true, 2);
  HeadNDequeue(mytestnum, mytesterr, que, false, 0);
  Empty(mytestnum, mytesterr, que, true);

  QueueVec<int> copque = que;
  EqualQueue(mytestnum, mytesterr, que, copque, true);
  EnqueueM(mytestnum, mytesterr, que, 1);
  EnqueueM(mytestnum, mytesterr, copque, 1);
  EqualQueue(mytestnum, mytesterr, que, copque, true);
  EnqueueM(mytestnum, mytesterr, que, 2);
  EnqueueM(mytestnum, mytesterr, que, 3);

  QueueVec<int> copconstrque(que);
  Vector<int> vec(que.Size());
  List<int> lst = List<int>();

  for (unsigned long i = 0; i < 3; i++)
  {
    vec[i] = que.Head();
    que.Enqueue(que.HeadNDequeue());
  }

  for (unsigned long i = 0; i < 3; i++)
  {
    lst.InsertAtBack(que.Head());
    que.Enqueue(que.HeadNDequeue());
  }

  QueueVec<int> travveconstrque(vec);
  QueueVec<int> travlstconstrque(lst);
  QueueVec<int> mapconstrque(std::move(vec));
  copque = que;
  
  Dequeue(mytestnum, mytesterr, que, true);
  int second = que.Head();
  HeadNDequeue(mytestnum, mytesterr, que, true, second);

  que.Enqueue(1);
  que.Enqueue(second);
  que.Enqueue(3);
  HeadNDequeue(mytestnum, mytesterr, que, true, 3);

  EqualQueue(mytestnum, mytesterr, copconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, travveconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, travlstconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, mapconstrque, que, true);
  EqualQueue(mytestnum, mytesterr, copque, que, true);

  QueueVec<int> que2;
  for(int i = 1; i < 30; i++) {
    que2.Enqueue(i);
  }
  for(int i = 1; i < 30; i++) {
    que2.Dequeue();
  }

  que.Clear();
  for(int i = 1; i < 63; i++) {
    que.Enqueue(i);
    que2.Enqueue(i);
  }
  for(int i = 1; i < 20; i++) {
    que.Dequeue();
    que2.Dequeue();
  }
  for(int i = 1; i < 70; i++) {
    que.Enqueue(i);
    que2.Enqueue(i);
  }
  for(int i = 1; i < 30; i++) {
    que.Dequeue();
    que2.Dequeue();
  }

  EqualQueue(mytestnum, mytesterr, que, que2, true);
  Head(mytestnum, mytesterr, que, true, 49);
  HeadNDequeue(mytestnum, mytesterr, que, true, 49);
  Head(mytestnum, mytesterr, que, true, 50);
  Dequeue(mytestnum, mytesterr, que, true);
  
  Head(mytestnum, mytesterr, que2, true, 49);
  HeadNDequeue(mytestnum, mytesterr, que2, true, 49);
  Head(mytestnum, mytesterr, que2, true, 50);
  Dequeue(mytestnum, mytesterr, que2, true);
  EqualQueue(mytestnum, mytesterr, que, que2, true);

  cout << endl << "End of functions from QueueVec Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myQueue() {
  
  uint mytestnum = 0;
  uint mytesterr = 0;

  QueueVec<string> quevec = QueueVec<string>();
  QueueLst<string> quelst = QueueLst<string>();
  List<string> list = List<string>();
  SortableVector<string> vec = SortableVector<string>();

  EqualQueue(mytestnum, mytesterr, quevec, QueueVec<string>(list), true);
  EqualQueue(mytestnum, mytesterr, quelst, QueueLst<string>(list), true);
  EqualQueue(mytestnum, mytesterr, quevec, QueueVec<string>(vec), true);
  EqualQueue(mytestnum, mytesterr, quelst, QueueLst<string>(vec), true);

  list.InsertAtBack("prima");
  list.InsertAtBack("seconda");
  list.InsertAtBack("terza");
  list.InsertAtBack("quarta");
  list.InsertAtBack("quinta");
  EqualQueue(mytestnum, mytesterr, quevec, QueueVec<string>(list), false);
  EqualQueue(mytestnum, mytesterr, quelst, QueueLst<string>(list), false);

  quevec.Enqueue("prima");
  quevec.Enqueue("seconda");
  quevec.Enqueue("terza");
  quevec.Enqueue("quarta");
  quevec.Enqueue("quinta");
  quelst.Enqueue("prima");
  quelst.Enqueue("seconda");
  quelst.Enqueue("terza");
  quelst.Enqueue("quarta");
  quelst.Enqueue("quinta");
  EqualQueue(mytestnum, mytesterr, quevec, QueueVec<string>(list), true);
  EqualQueue(mytestnum, mytesterr, quelst, QueueLst<string>(list), true);

  vec = list;
  EqualQueue(mytestnum, mytesterr, quevec, QueueVec<string>(vec), true);
  EqualQueue(mytestnum, mytesterr, quelst, QueueLst<string>(vec), true);

  QueueVec<string> moved (move(quevec));
  EqualQueue(mytestnum, mytesterr, moved, QueueVec<string>(vec), true);
  moved = move(QueueVec<string>(vec));
  EqualQueue(mytestnum, mytesterr, moved, QueueVec<string>(vec), true);

  QueueLst<string> movedlst (move(quelst));
  EqualQueue(mytestnum, mytesterr, movedlst, QueueLst<string>(vec), true);
  movedlst = move(QueueLst<string>(list));
  EqualQueue(mytestnum, mytesterr, movedlst, QueueLst<string>(vec), true);

  cout << endl << "End of functions from Queue Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myStack() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  StackVec<string> stackvec = StackVec<string>();
  StackLst<string> stacklst = StackLst<string>();
  List<string> list = List<string>();
  SortableVector<string> vec = SortableVector<string>();

  EqualStack(mytestnum, mytesterr, stackvec, StackVec<string>(list), true);
  EqualStack(mytestnum, mytesterr, stacklst, StackLst<string>(list), true);
  EqualStack(mytestnum, mytesterr, stackvec, StackVec<string>(vec), true);
  EqualStack(mytestnum, mytesterr, stacklst, StackLst<string>(vec), true);

  list.InsertAtBack("prima");
  list.InsertAtBack("seconda");
  list.InsertAtBack("terza");
  list.InsertAtBack("quarta");
  list.InsertAtBack("quinta");
  EqualStack(mytestnum, mytesterr, stackvec, StackVec<string>(list), false);
  EqualStack(mytestnum, mytesterr, stacklst, StackLst<string>(list), false);

  stackvec.Push("prima");
  stackvec.Push("seconda");
  stackvec.Push("terza");
  stackvec.Push("quarta");
  stackvec.Push("quinta");
  stacklst.Push("quinta");
  stacklst.Push("quarta");
  stacklst.Push("terza");
  stacklst.Push("seconda");
  stacklst.Push("prima");
  EqualStack(mytestnum, mytesterr, stackvec, StackVec<string>(list), true);
  EqualStack(mytestnum, mytesterr, stacklst, StackLst<string>(list), true);

  vec = list;
  EqualStack(mytestnum, mytesterr, stackvec, StackVec<string>(vec), true);
  EqualStack(mytestnum, mytesterr, stacklst, StackLst<string>(vec), true);

  StackVec<string> moved (move(stackvec));
  EqualStack(mytestnum, mytesterr, moved, StackVec<string>(vec), true);
  moved = move(StackVec<string>(vec));
  EqualStack(mytestnum, mytesterr, moved, StackVec<string>(vec), true);

  StackLst<string> movedlst (move(stacklst));
  EqualStack(mytestnum, mytesterr, movedlst, StackLst<string>(vec), true);
  movedlst = move(StackLst<string>(list));
  EqualStack(mytestnum, mytesterr, movedlst, StackLst<string>(vec), true);
  
  cout << endl << "End of functions from Stack Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myStackVec() {

  uint mytestnum = 0;
  uint mytesterr = 0;
  
  StackVec<string> stack;
  string prima = "prima", seconda = "seconda", terza = "terza";
  Size(mytestnum, mytesterr, stack, true, 0);
  Empty(mytestnum, mytesterr, stack, true);

  PushM(mytestnum, mytesterr, stack, prima);
  Size(mytestnum, mytesterr, stack, true, 1);
  Empty(mytestnum, mytesterr, stack, false);
  PushC(mytestnum, mytesterr, stack, seconda);
  PushM(mytestnum, mytesterr, stack, terza);
  Size(mytestnum, mytesterr, stack, true, 3);
  Empty(mytestnum, mytesterr, stack, false);
  
  StackVec<string> copstack(stack);
  Vector<string> vec(stack.Size());
  List<string> lst = List<string>();
  StackLst<string> support = StackLst<string>();
  for (unsigned long i = 3; i > 0; --i)
  {
    vec[i-1] = stack.TopNPop();
    lst.InsertAtFront(vec[i-1]);
    support.Push(vec[i-1]);
  }

  TraversePreOrder(mytestnum, mytesterr, lst, true, &TraversePrint<string>);
  TraversePreOrder(mytestnum, mytesterr, vec, true, &TraversePrint<string>);

  for (unsigned long i = 0; i < 3; i++)
  {
    stack.Push(support.TopNPop());
  }

  StackVec<string> travvecconstrstack(vec);
  StackVec<string> travlstconstrstack(lst);
  StackVec<string> mapconstrstack(std::move(vec));

  StackVec<string> copstk;
  copstk = stack;
  
  stack.Pop();
  string second = stack.Top();
  TopNPop(mytestnum, mytesterr, stack, true, second);
  TopNPop(mytestnum, mytesterr, stack, true, prima);

  stack.Push(prima);
  stack.Push(seconda);
  stack.Push(terza);

  EqualStack(mytestnum, mytesterr, copstack, stack, true);
  EqualStack(mytestnum, mytesterr, travvecconstrstack, stack, true);
  EqualStack(mytestnum, mytesterr, travlstconstrstack, stack, true);
  EqualStack(mytestnum, mytesterr, mapconstrstack, stack, true);
  EqualStack(mytestnum, mytesterr, copstack, stack, true);

  StackVec<string> stk;
  Pop(mytestnum, mytesterr, stk, false);
  Size(mytestnum, mytesterr, stk, true, 0);
  PushC(mytestnum, mytesterr, stk, string("uno"));
  Size(mytestnum, mytesterr, stk, true, 1);
  TopNPop(mytestnum, mytesterr, stk, true, string("uno"));
  Size(mytestnum, mytesterr, stk, true, 0);

  cout << endl << "End of functions from StackVec Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myEmptyBinaryTree(BinaryTree<int> & bt) {

  uint mytestnum = 0;
  uint mytesterr = 0;
  
  Empty(mytestnum, mytesterr, bt, true);
  Size(mytestnum, mytesterr, bt, true, 0);
  Fold(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 0);
  FoldPreOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 0);
  FoldPostOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 0);
  FoldInOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 0);
  FoldBreadth(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 0);
  Root(mytestnum, mytesterr, bt, false, 0);
  Traverse(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraversePreOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraverseInOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraverseBreadth(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  // FAB exist, comparison
  cout << endl << "End of Empty Binary Tree Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myLargeBinaryTree(BinaryTree<int> & bt) {

  uint mytestnum = 0;
  uint mytesterr = 0;

  Empty(mytestnum, mytesterr, bt, false);
  Size(mytestnum, mytesterr, bt, true, 10000);
  Fold(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 49995000);
  FoldPreOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 49995000);
  FoldPostOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 49995000);
  FoldInOrder(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 49995000);
  FoldBreadth(mytestnum, mytesterr, bt, true, &FoldAdd<int>, 0, 49995000);
  Root(mytestnum, mytesterr, bt, true, 0);
  /* Traverse(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraversePreOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraverseInOrder(mytestnum, mytesterr, bt, true, &TraversePrint<int>);
  TraverseBreadth(mytestnum, mytesterr, bt, true, &TraversePrint<int>); */
  //commentati per troppo disordine...

  //TODO funzioni dei nodi???
  cout << endl << "End of Large Binary Tree Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 
}

void myBinaryTreeLnk() {
  
  BinaryTreeLnk<int> btlnk;
  myEmptyBinaryTree(btlnk);

  BinaryTreeLnk<int> btlnk2(btlnk);
  myEmptyBinaryTree(btlnk2);
  
  BinaryTreeLnk<int> btlnk3;
  btlnk = btlnk3;
  myEmptyBinaryTree(btlnk);

  btlnk2 = move(btlnk);
  myEmptyBinaryTree(btlnk2);


  Vector<int> vec(10000);
  for (int i = 0; i < 10000; ++i) {
    vec[i] = i;
  }

  BinaryTreeLnk<int> btlnk4(vec);
  myLargeBinaryTree(btlnk4);
  
  BinaryTreeLnk<int> btlnk5(move(vec));
  myLargeBinaryTree(btlnk4);

  BinaryTreeLnk<int> btlnk6(btlnk5);
  myLargeBinaryTree(btlnk6);
  
  BinaryTreeLnk<int> btlnk7(move(btlnk4));
  myLargeBinaryTree(btlnk7);

  btlnk3 = btlnk7;
  myLargeBinaryTree(btlnk6);

  btlnk2 = move(btlnk5);
  myLargeBinaryTree(btlnk2);

  if (btlnk2 == btlnk5) {
    cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }
  if (btlnk2 != btlnk3) {
    cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }

  //TODO ITERATORS....

  // FAB ordine di fold e traverse, exists, clear
}

void myBinaryTreeVec() {
  
  BinaryTreeVec<int> btlnk;
  myEmptyBinaryTree(btlnk);

  BinaryTreeLnk<int> btlnk2(btlnk);
  myEmptyBinaryTree(btlnk2);
  
  BinaryTreeLnk<int> btlnk3;
  btlnk = btlnk3;
  myEmptyBinaryTree(btlnk);

  btlnk2 = move(btlnk);
  myEmptyBinaryTree(btlnk2);


  List<int> lst;
  for (int i = 9999; i >= 0; --i) {
    lst.InsertAtFront(i);
  }

  BinaryTreeLnk<int> btlnk4(lst);
  myLargeBinaryTree(btlnk4);
  
  BinaryTreeLnk<int> btlnk5(move(lst));
  myLargeBinaryTree(btlnk4);

  BinaryTreeLnk<int> btlnk6(btlnk5);
  myLargeBinaryTree(btlnk6);
  
  BinaryTreeLnk<int> btlnk7(move(btlnk4));
  myLargeBinaryTree(btlnk7);

  btlnk3 = btlnk7;
  myLargeBinaryTree(btlnk6);

  btlnk2 = move(btlnk5);
  myLargeBinaryTree(btlnk2);

  if (btlnk2 == btlnk5) {
    cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }
  if (btlnk2 != btlnk3) {
    cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }
  //TODO ITERATORS....
  // FAB ordine di fold e traverse, exists, clear
}

void myEmptyBST(BST<int> & bst) {

  uint mytestnum = 0;
  uint mytesterr = 0;

  Min(mytestnum, mytesterr, bst, false, 0);
  MinNRemove(mytestnum, mytesterr, bst, false, 0);
  RemoveMin(mytestnum, mytesterr, bst, false);
  Max(mytestnum, mytesterr, bst, false, 0);
  MaxNRemove(mytestnum, mytesterr, bst, false, 0);
  RemoveMax(mytestnum, mytesterr, bst, false);
  Predecessor(mytestnum, mytesterr, bst, false, 0, 0);
  PredecessorNRemove(mytestnum, mytesterr, bst, false, 0, 0);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 0);
  Successor(mytestnum, mytesterr, bst, false, 0, 0);
  SuccessorNRemove(mytestnum, mytesterr, bst, false, 0, 0);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 0);
  InsertC(mytestnum, mytesterr, bst, true, 0);
  InsertC(mytestnum, mytesterr, bst, false, 0);
  InsertM(mytestnum, mytesterr, bst, true, 2);
  InsertM(mytestnum, mytesterr, bst, false, 2);
  Remove(mytestnum, mytesterr, bst, false, 3);
  Remove(mytestnum, mytesterr, bst, false, -1);
  Remove(mytestnum, mytesterr, bst, false, 1);
  Vector<int> vec(2);
  vec[0] = 2;
  vec[1] = 0;
  RemoveAll(mytestnum, mytesterr, bst, true, vec);
  Remove(mytestnum, mytesterr, bst, false, 0);
  Exists(mytestnum, mytesterr, bst, false, 0);
  
  cout << endl << "End of Empty BST Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 

  // FAB size
}

void myOnlyLeftChildrenBST() {
  
  uint mytestnum = 0;
  uint mytesterr = 0;

  Vector<int> vec(50);
  int i = 49;
  for (ulong idx = 0; idx < 50; idx++, --i) {
    vec[idx] = i * 2;
  }

  BST<int> bst(vec);

  Empty(mytestnum, mytesterr, bst, false);
  Size(mytestnum, mytesterr, bst, true, 50);
  Fold(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldPreOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldPostOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldInOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldBreadth(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  Root(mytestnum, mytesterr, bst, true, 98);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseBreadth(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  
  InsertSomeC(mytestnum, mytesterr, bst, false, vec);
  RemoveAll(mytestnum, mytesterr, bst, true, vec);
  RemoveSome(mytestnum, mytesterr, bst, false, vec);
  Empty(mytestnum, mytesterr, bst, true);
  Size(mytestnum, mytesterr, bst, true, 0);
  InsertAllC(mytestnum, mytesterr, bst, true, vec);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);

  Min(mytestnum, mytesterr, bst, true, 0);
  MinNRemove(mytestnum, mytesterr, bst, true, 0);
  RemoveMin(mytestnum, mytesterr, bst, true);
  Min(mytestnum, mytesterr, bst, true, 4);

  Max(mytestnum, mytesterr, bst, true, 98);
  MaxNRemove(mytestnum, mytesterr, bst, true, 98);
  RemoveMax(mytestnum, mytesterr, bst, true);
  Max(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, false, 4, 2);
  Predecessor(mytestnum, mytesterr, bst, false, 3, 2);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 3);
  Successor(mytestnum, mytesterr, bst, false, 94, 96);
  Successor(mytestnum, mytesterr, bst, false, 95, 96);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 95);

  Exists(mytestnum, mytesterr, bst, true, 4);
  Exists(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, true, 6, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, true, 6);
  Successor(mytestnum, mytesterr, bst, true, 92, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, true, 92);
  Root(mytestnum, mytesterr, bst, true, 92);

  InsertC(mytestnum, mytesterr, bst, true, 49);
  InsertC(mytestnum, mytesterr, bst, true, 4);
  InsertC(mytestnum, mytesterr, bst, true, 94);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  Remove(mytestnum, mytesterr, bst, true, 49);

  cout << endl << "End of BST with left children only Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 

  bst.Clear();
  myEmptyBST(bst);

}

void myOnlyRightChildrenBST() {
  
  uint mytestnum = 0;
  uint mytesterr = 0;

  Vector<int> vec(50);
  for (ulong i = 0; i < 50; ++i) {
    vec[i] = i * 2;
  }

  BST<int> bst(vec);

  Empty(mytestnum, mytesterr, bst, false);
  Size(mytestnum, mytesterr, bst, true, 50);
  Fold(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldPreOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldPostOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldInOrder(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  FoldBreadth(mytestnum, mytesterr, bst, true, &FoldAdd<int>, 0, 2450);
  Root(mytestnum, mytesterr, bst, true, 0);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseBreadth(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  
  InsertSomeC(mytestnum, mytesterr, bst, false, vec);
  RemoveAll(mytestnum, mytesterr, bst, true, vec);
  RemoveSome(mytestnum, mytesterr, bst, false, vec);
  Empty(mytestnum, mytesterr, bst, true);
  Size(mytestnum, mytesterr, bst, true, 0);
  InsertAllC(mytestnum, mytesterr, bst, true, vec);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);

  Min(mytestnum, mytesterr, bst, true, 0);
  MinNRemove(mytestnum, mytesterr, bst, true, 0);
  RemoveMin(mytestnum, mytesterr, bst, true);
  Min(mytestnum, mytesterr, bst, true, 4);

  Max(mytestnum, mytesterr, bst, true, 98);
  MaxNRemove(mytestnum, mytesterr, bst, true, 98);
  RemoveMax(mytestnum, mytesterr, bst, true);
  Max(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, false, 4, 2);
  Predecessor(mytestnum, mytesterr, bst, false, 3, 2);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 3);
  Successor(mytestnum, mytesterr, bst, false, 94, 96);
  Successor(mytestnum, mytesterr, bst, false, 95, 96);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 95);

  Exists(mytestnum, mytesterr, bst, true, 4);
  Exists(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, true, 6, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, true, 6);
  Successor(mytestnum, mytesterr, bst, true, 92, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, true, 92);
  Root(mytestnum, mytesterr, bst, true, 6);

  InsertC(mytestnum, mytesterr, bst, true, 49);
  InsertC(mytestnum, mytesterr, bst, true, 4);
  InsertC(mytestnum, mytesterr, bst, true, 94);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  Remove(mytestnum, mytesterr, bst, true, 49);

  cout << endl << "End of BST with right children only Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 

}

void myLeftAndRightBST() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  Vector<int> vec(50);
  for (ulong i = 0; i < 49; i+=2) {
    vec[i] = i;
    vec[i+1] = 98-i;
  }

  BST<int> bst(vec);

  Empty(mytestnum, mytesterr, bst, false);
  Size(mytestnum, mytesterr, bst, true, 50);
  Root(mytestnum, mytesterr, bst, true, 0);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePostOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraverseBreadth(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  
  InsertSomeC(mytestnum, mytesterr, bst, false, vec);
  RemoveAll(mytestnum, mytesterr, bst, true, vec);
  RemoveSome(mytestnum, mytesterr, bst, false, vec);
  Empty(mytestnum, mytesterr, bst, true);
  Size(mytestnum, mytesterr, bst, true, 0);
  InsertAllC(mytestnum, mytesterr, bst, true, vec);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);

  Min(mytestnum, mytesterr, bst, true, 0);
  MinNRemove(mytestnum, mytesterr, bst, true, 0);
  RemoveMin(mytestnum, mytesterr, bst, true);
  Min(mytestnum, mytesterr, bst, true, 4);

  Max(mytestnum, mytesterr, bst, true, 98);
  MaxNRemove(mytestnum, mytesterr, bst, true, 98);
  RemoveMax(mytestnum, mytesterr, bst, true);
  Max(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, false, 4, 2);
  Predecessor(mytestnum, mytesterr, bst, false, 3, 2);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, false, 3);
  Successor(mytestnum, mytesterr, bst, false, 94, 96);
  Successor(mytestnum, mytesterr, bst, false, 95, 96);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, false, 95);

  Exists(mytestnum, mytesterr, bst, true, 4);
  Exists(mytestnum, mytesterr, bst, true, 94);

  Predecessor(mytestnum, mytesterr, bst, true, 6, 4);
  RemovePredecessor(mytestnum, mytesterr, bst, true, 6);
  Successor(mytestnum, mytesterr, bst, true, 92, 94);
  RemoveSuccessor(mytestnum, mytesterr, bst, true, 92);
  Root(mytestnum, mytesterr, bst, true, 6);

  InsertC(mytestnum, mytesterr, bst, true, 49);
  InsertC(mytestnum, mytesterr, bst, true, 4);
  InsertC(mytestnum, mytesterr, bst, true, 94);
  TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  TraversePreOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  Remove(mytestnum, mytesterr, bst, true, 49);

  cout << endl << "End of BST with once left once right children Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 

}

void myRandomBST() {

  uint mytestnum = 0;
  uint mytesterr = 0;

  Vector<int> vec(1000);
  auto seed = random_device{}();
  cout << endl << "Seed: " << seed << endl;
  default_random_engine genx(seed);
  uniform_int_distribution<int> distx(1, 1000);
  for (int i = 0; i < 1000; ++i) {
    int num = distx(genx);
    vec[i] = num;
  }

  BST<int> bst(vec);

  Empty(mytestnum, mytesterr, bst, false);
  //todo root
  //TraverseInOrder(mytestnum, mytesterr, bst, true, &TraversePrint<int>);
  InsertSomeC(mytestnum, mytesterr, bst, false, vec);
  RemoveSome(mytestnum, mytesterr, bst, true, vec);
  RemoveSome(mytestnum, mytesterr, bst, false, vec);
  Empty(mytestnum, mytesterr, bst, true);
  Size(mytestnum, mytesterr, bst, true, 0);
  InsertSomeC(mytestnum, mytesterr, bst, true, vec);

  RemoveMin(mytestnum, mytesterr, bst, true);
  RemoveMax(mytestnum, mytesterr, bst, true);

  BST<int> bst2(move(vec));
  NonEqualBST(mytestnum, mytesterr, bst, bst2);

  BST<int> bst3(bst);
  EqualBT(mytestnum, mytesterr, bst, bst3);
  EqualBST(mytestnum, mytesterr, bst, bst3);
  
  bst2 = bst3;
  EqualBST(mytestnum, mytesterr, bst3, bst2);

  BST<int> bst4;
  bst4 = move(bst);
  NonEqualBST(mytestnum, mytesterr, bst, bst4);

  cout << endl << "End of random BST Test! (Errors/Tests: " << mytesterr << "/" << mytestnum << ")" << endl << endl; 

}

void myBST() {

  BST<int> bst;
  myEmptyBinaryTree(bst);
  myEmptyBST(bst);

  BST<int> bst2(bst);
  myEmptyBST(bst2);

  BST<int> bst3;
  bst = bst3;
  myEmptyBST(bst);

  bst2 = move(bst);
  myEmptyBST(bst2);

  myOnlyLeftChildrenBST();
  myOnlyRightChildrenBST();
  myLeftAndRightBST();
  myRandomBST();

}