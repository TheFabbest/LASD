#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;
using namespace lasd;

/* ************************************************************************** */
void TestBinaryTree()
{
  cout << "Testing BinaryTree" << endl;
  Vector<int> vector(4);
  vector[0] = 1;
  vector[1] = 2;
  vector[2] = 3;
  vector[3] = 4;
  BinaryTreeVec<int> treevec(vector);
  BinaryTreeLnk<int> treelnk(vector);
}


void mytest() {
  TestBinaryTree();
}
