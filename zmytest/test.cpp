#include <iostream>
#include "test.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/stack/stack.hpp"
#include "../zlasdtest/queue/queue.hpp"

#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../bst/bst.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../zlasdtest/bst/bst.hpp"
#include "../zlasdtest/binarytree/binarytree.hpp"
#include "../zlasdtest/iterator/iterator.hpp"
#include "../binarytree/vec/binarytreevec.hpp"

#include "../hashtable/opnadr/htopnadr.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../zlasdtest/hashtable/hashtable.hpp"

using namespace std;

/*---------------------*/

template <typename Data>
void MyTestVectorData(uint &testnum, uint &testerr)
{
  uint localtestnum = 0, localtesterr = 0;
  try
  {
    {
      lasd::SortableVector<Data> vec(10);

      Empty(localtestnum, localtesterr, vec, false);

      for (int i = 9; i >= 0; i--)
      {
        SetAt(localtestnum, localtesterr, vec, true, 1, static_cast<Data>(i));
        GetAt(localtestnum, localtesterr, vec, true, 1, static_cast<Data>(i));
        Exists(localtestnum, localtesterr, vec, true, static_cast<Data>(i));
      }

      TraversePreOrder(localtestnum, localtesterr, vec, true, &TraversePrint<Data>);
      TraversePostOrder(localtestnum, localtesterr, vec, true, &TraversePrint<Data>);

      lasd::SortableVector<Data> vec2(vec);
      for (int i = 9; i >= 0; i--)
      {
        GetAt(localtestnum, localtesterr, vec2, true, i, Data(i));
      }

      vec2.Sort();

      TraversePreOrder(localtestnum, localtesterr, vec2, true, &TraversePrint<Data>);
      TraversePostOrder(localtestnum, localtesterr, vec2, true, &TraversePrint<Data>);
      vec2.Resize(0);
      Empty(localtestnum, localtesterr, vec2, true);

      NonEqualVector(localtestnum, localtesterr, vec, vec2, true);
    }

    {
      lasd::Vector<Data> vec{3};
      vec[0] = Data(10);
      vec[1] = Data(20);
      vec[2] = Data(30);
      Size(localtestnum, localtesterr, vec, true, 3);

      vec.Resize(5);
      Size(localtestnum, localtesterr, vec, true, 5);
      vec[3] = Data(40);
      vec[4] = Data(50);

      vec.Resize(1);
      Size(localtestnum, localtesterr, vec, true, 1);

      vec[0] = Data(11);

      GetFront(localtestnum, localtesterr, vec, true, Data(11));
      GetBack(localtestnum, localtesterr, vec, true, Data(11));
      SetFront(localtestnum, localtesterr, vec, true, Data(25));
      SetBack(localtestnum, localtesterr, vec, true, Data(25));

      vec.Resize(0);
      Size(localtestnum, localtesterr, vec, true, 0);

      GetFront(localtestnum, localtesterr, vec, false, Data(11));
      GetBack(localtestnum, localtesterr, vec, false, Data(11));
      SetFront(localtestnum, localtesterr, vec, false, Data(25));
      SetBack(localtestnum, localtesterr, vec, false, Data(25));

      lasd::SortableVector<Data> vec2;

      vec = vec2;

      vec2.Resize(3);
      vec2[0] = Data(1);
      vec2[1] = Data(2);
      vec2[2] = Data(3);

      vec = std::move(vec2);

      Size(localtestnum, localtesterr, vec, true, 3);
      GetFront(localtestnum, localtesterr, vec, true, Data(1));

      lasd::SortableVector<Data> vec3(std::move(vec));
      GetFront(localtestnum, localtesterr, vec3, true, Data(1));

      lasd::SortableVector<Data> vec4(vec3);
      GetFront(localtestnum, localtesterr, vec4, true, Data(1));

      vec4[0] = Data(3);
      vec4[1] = Data(2);
      vec4[2] = Data(1);

      vec4.Sort();

      GetAt(localtestnum, localtesterr, vec4, true, 0, Data(1));
      GetAt(localtestnum, localtesterr, vec4, true, 1, Data(2));
      GetAt(localtestnum, localtesterr, vec4, true, 2, Data(3));
    }

    {
      cout << "-- Sortable Vector --\n";
      lasd::SortableVector<Data> vec(3);
      vec[0] = Data(0);
      vec[1] = Data(1);
      vec[2] = Data(2);

      Size(localtestnum, localtesterr, vec, true, 3);
      vec.Resize(5);
      Size(localtestnum, localtesterr, vec, true, 5);
      vec[3] = Data(0);
      vec[4] = Data(1);

      vec.Resize(1);
      Size(localtestnum, localtesterr, vec, true, 1);
      vec[0] = Data(17);

      GetFront(localtestnum, localtesterr, vec, true, Data(17));
      GetBack(localtestnum, localtesterr, vec, true, Data(17));
      SetFront(localtestnum, localtesterr, vec, true, Data(25));
      SetBack(localtestnum, localtesterr, vec, true, Data(25));

      vec.Resize(0);

      GetFront(localtestnum, localtesterr, vec, false, Data(17));
      GetBack(localtestnum, localtesterr, vec, false, Data(17));
      SetFront(localtestnum, localtesterr, vec, false, Data(25));
      SetBack(localtestnum, localtesterr, vec, false, Data(25));

      lasd::List<Data> lst;
      lst.Insert(Data(5));
      lst.Insert(Data(7));
      lst.Insert(Data(8));

      lasd::Vector<Data> vec6(lst);
      Size(localtestnum, localtesterr, vec6, true, 3);
      TraversePreOrder(localtestnum, localtesterr, vec6, true, TraversePrint<Data>);
      TraversePostOrder(localtestnum, localtesterr, vec6, true, TraversePrint<Data>);
      MapPreOrder(localtestnum, localtesterr, vec6, true, MapDouble<Data>);
      MapPostOrder(localtestnum, localtesterr, vec6, true, MapDouble<Data>);
      TraversePreOrder(localtestnum, localtesterr, vec6, true, TraversePrint<Data>);
      FoldPreOrder(localtestnum, localtesterr, vec6, true, FoldAdd<Data>, 0, 80);
      FoldPostOrder(localtestnum, localtesterr, vec6, true, FoldAdd<Data>, 0, 80);

      lasd::SortableVector<Data> vec7(lst);
      Size(localtestnum, localtesterr, vec7, true, 3);
      TraversePreOrder(localtestnum, localtesterr, vec7, true, TraversePrint<Data>);
      TraversePostOrder(localtestnum, localtesterr, vec7, true, TraversePrint<Data>);
      MapPreOrder(localtestnum, localtesterr, vec7, true, MapDouble<Data>);
      MapPostOrder(localtestnum, localtesterr, vec7, true, MapDouble<Data>);
      TraversePreOrder(localtestnum, localtesterr, vec7, true, TraversePrint<Data>);
      FoldPreOrder(localtestnum, localtesterr, vec7, true, FoldAdd<Data>, 0, 80);
      FoldPostOrder(localtestnum, localtesterr, vec6, true, FoldAdd<Data>, 0, 80);
    }
  }
  catch (...)
  {
    localtestnum++;
    localtesterr++;
    cout << endl
         << "Unmanaged error! " << endl;
  }
  cout << "End of Test! (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
  testnum += localtestnum;
  testerr += localtesterr;
}

void MyTestVectorString(uint &testnum, uint &testerr)
{
  uint localtestnum = 0, localtesterr = 0;
  try
  {
    {
      lasd::SortableVector<string> vec(20);

      Empty(localtestnum, localtesterr, vec, false);

      for (char i = 19; i >= 0; i--)
      {
        string letter(1, (char)i + 65);
        SetAt(localtestnum, localtesterr, vec, true, (ulong)i, letter);
        GetAt(localtestnum, localtesterr, vec, true, (ulong)i, letter);
        Exists(localtestnum, localtesterr, vec, true, letter);
      }

      TraversePreOrder(localtestnum, localtesterr, vec, true, &TraversePrint<string>);
      TraversePostOrder(localtestnum, localtesterr, vec, true, &TraversePrint<string>);

      lasd::SortableVector<string> vec2(vec);
      for (char i = 19; i >= 0; i--)
      {
        string letter(1, i + 65);
        GetAt(localtestnum, localtesterr, vec2, true, (ulong)i, letter);
      }

      vec2.Sort();

      TraversePreOrder(localtestnum, localtesterr, vec2, true, &TraversePrint<string>);
      TraversePostOrder(localtestnum, localtesterr, vec2, true, &TraversePrint<string>);
      vec2.Resize(0);
      Empty(localtestnum, localtesterr, vec2, true);

      NonEqualVector(localtestnum, localtesterr, vec, vec2, true);
    }
  }
  catch (...)
  {
    localtestnum++;
    localtesterr++;
    cout << endl
         << "Unmanaged error! " << endl;
  }
  cout << "End of Test! (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
  testnum += localtestnum;
  testerr += localtesterr;
}

void MyTestVector(uint &testnum, uint &testerr)
{
  uint localtestnum = 0, localtesterr = 0;

  cout << endl
       << "Begin of Vector<int> Test:\n"
       << endl;
  MyTestVectorData<int>(localtestnum, localtesterr);

  cout << endl
       << "Begin of Vector<float> Test:\n"
       << endl;
  MyTestVectorData<float>(localtestnum, localtesterr);

  cout << endl
       << "Begin of Vector<string> Test:\n"
       << endl;
  MyTestVectorString(localtestnum, localtesterr);

  testnum += localtestnum;
  testerr += localtesterr;
  cout << endl
       << "Test Vector (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
}

/*---------------------*/

void MyTestList(uint &testnum, uint &testerr)
{
  cout << "\nBegin of List<int> / BTV<int> / Vector<int> Test:\n\n";
  uint localtestnum = 0, localtesterr = 0;
  try
  {
    {
      lasd::Vector<int> vec;
      Size(localtestnum, localtesterr, vec, true, 0);

      lasd::BinaryTreeVec<int> bt(vec);
      Size(localtestnum, localtesterr, bt, true, 0);
      Root(localtestnum, localtesterr, bt, false, 0);
      lasd::BinaryTreeVec<int> bt2(std::move(vec));
      Size(localtestnum, localtesterr, vec, true, 0);

      TraversePreOrder(localtestnum, localtesterr, vec, true, TraversePrint<int>); // true perche la traverse è void e viene confrontato un true con false sempre
      TraversePreOrder(localtestnum, localtesterr, bt, false, TraversePrint<int>);

      EqualBT(localtestnum, localtesterr, bt, bt2);

      lasd::BinaryTreeLnk<int> bt3;
      Root(localtestnum, localtesterr, bt3, false, 0);

      lasd::List<int> lista;
      RemoveFromFront(localtestnum, localtesterr, lista, false);
      FrontNRemove(localtestnum, localtesterr, lista, false, 0);

      InsertAtFront(localtestnum, localtesterr, lista, true, 5);
      InsertAtBack(localtestnum, localtesterr, lista, true, 12);

      lasd::List<int> lista2;

      EqualList(localtestnum, localtesterr, lista, lista2, false);
      NonEqualList(localtestnum, localtesterr, lista, lista2, true);

      lista.Clear();

      EqualList(localtestnum, localtesterr, lista, lista2, true);
      NonEqualList(localtestnum, localtesterr, lista, lista2, false);
    }

    {

      lasd::List<int> lista;

      lasd::Vector<int> vec{3};
      vec[0] = 0;
      vec[1] = 1;
      vec[2] = 2;

      Remove(localtestnum, localtesterr, lista, false, 5);
      RemoveAll(localtestnum, localtesterr, lista, false, vec);
      RemoveSome(localtestnum, localtesterr, lista, false, vec);

      InsertAllM(localtestnum, localtesterr, lista, true, std::move(vec));
      vec[0] = 0;
      vec[1] = 5;
      vec[2] = 2;
      InsertSomeM(localtestnum, localtesterr, lista, true, std::move(vec));
      vec[0] = 57;

      InsertM(localtestnum, localtesterr, lista, true, std::move(vec[0]));

      vec[0] = 0;
      vec[1] = 1;
      vec[2] = 2;

      lasd::List<int> lista2;

      InsertAllC(localtestnum, localtesterr, lista2, true, vec);
      vec[0] = 3;
      InsertSomeC(localtestnum, localtesterr, lista2, true, vec);
      vec[0] = 89;

      InsertC(localtestnum, localtesterr, lista2, true, vec[0]);

      lasd::List<int> lista3;

      NonEqualLinear(localtestnum, localtesterr, lista3, vec, true);
      vec.Clear();
      EqualLinear(localtestnum, localtesterr, lista3, vec, true);

      GetAt(localtestnum, localtesterr, lista3, false, 0, 0);
      GetFront(localtestnum, localtesterr, lista3, false, 0);
      GetBack(localtestnum, localtesterr, lista3, false, 0);

      SetAt(localtestnum, localtesterr, lista3, false, 0, 0);
      SetFront(localtestnum, localtesterr, lista3, false, 1);
      SetBack(localtestnum, localtesterr, lista3, false, 2);
    }

    {
      lasd::List<int> lst;
      lst.Insert(6);
      lst.Insert(22);
      lst.Insert(12);

      lasd::List<int> lst2(lst);

      lasd::List<int> lst3(std::move(lst));

      Size(localtestnum, localtesterr, lst2, true, 3);
      Size(localtestnum, localtesterr, lst3, true, 3);

      TraversePreOrder(localtestnum, localtesterr, lst2, true, TraversePrint<int>);
      TraversePostOrder(localtestnum, localtesterr, lst3, true, TraversePrint<int>);

      lasd::Vector<int> vec(3);
      vec[0] = 0;
      vec[1] = 1;
      vec[2] = 2;

      lasd::List<int> lst4(vec);
      lasd::List<int> lst5(std::move(vec));

      Size(localtestnum, localtesterr, lst4, true, 3);
      Size(localtestnum, localtesterr, lst5, true, 3);

      TraversePreOrder(localtestnum, localtesterr, lst4, true, TraversePrint<int>);
      TraversePostOrder(localtestnum, localtesterr, lst5, true, TraversePrint<int>);

      lasd::List<int> lst11;

      lst4 = lst11;
      Size(localtestnum, localtesterr, lst4, true, 0);
      TraversePreOrder(localtestnum, localtesterr, lst4, true, TraversePrint<int>);

      lst11 = lst5;

      Size(localtestnum, localtesterr, lst11, true, 3);
      TraversePreOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);

      lasd::List<int> lst12;
      lst12.Insert(60);
      lst12.Insert(70);
      lst12.Insert(80);
      lst12.Insert(90);
      lst12.Insert(689);

      lst11 = lst12;

      Size(localtestnum, localtesterr, lst11, true, 5);
      TraversePreOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);

      lst11.Insert(1234);

      lst11 = lst12;

      Size(localtestnum, localtesterr, lst11, true, 5);
      TraversePreOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);

      lst12.Clear();

      lst11 = std::move(lst12);

      Size(localtestnum, localtesterr, lst11, true, 0);
      TraversePreOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);
      TraversePostOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);
      MapPreOrder(localtestnum, localtesterr, lst11, true, MapDouble<int>);
      MapPostOrder(localtestnum, localtesterr, lst11, true, MapDouble<int>);

      FoldPreOrder(localtestnum, localtesterr, lst11, true, FoldAdd<int>, 0, 0);
      FoldPostOrder(localtestnum, localtesterr, lst11, true, FoldAdd<int>, 0, 0);

      lst11.Insert(1);
      lst11.Insert(2);

      TraversePreOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);
      TraversePostOrder(localtestnum, localtesterr, lst11, true, TraversePrint<int>);
      MapPreOrder(localtestnum, localtesterr, lst11, true, MapDouble<int>);
      MapPostOrder(localtestnum, localtesterr, lst11, true, MapDouble<int>);

      FoldPreOrder(localtestnum, localtesterr, lst11, true, FoldAdd<int>, 0, 12);
      FoldPostOrder(localtestnum, localtesterr, lst11, true, FoldAdd<int>, 0, 12);
    }
  }
  catch (...)
  {
    localtestnum++;
    localtesterr++;
    cout << endl
         << "Unmanaged error! " << endl;
  }
  cout << "End of Test! (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
  testnum += localtestnum;
  testerr += localtesterr;
}

/*---------------------*/

void MyTestBinaryTree(uint &testnum, uint &testerr)
{
  cout << "\nBegin of BinaryTreeLnk<int>:\n\n";
  uint localtestnum = 0;
  uint localtesterr = 0;
  try
  {

    lasd::Vector<int> vec{3};

    SetAt(localtestnum, localtesterr, vec, true, 0, 0);
    SetAt(localtestnum, localtesterr, vec, true, 1, 1);
    SetAt(localtestnum, localtesterr, vec, true, 2, 2);

    Exists(localtestnum, localtesterr, vec, true, 0);
    Exists(localtestnum, localtesterr, vec, true, 1);
    Exists(localtestnum, localtesterr, vec, true, 2);

    lasd::BinaryTreeLnk<int> btl(vec);
    TraverseInOrder(localtestnum, localtesterr, btl, true, &TraversePrint<int>);
    Root(localtestnum, localtesterr, btl, true, 0);

    lasd::BinaryTreeLnk<int> btl2(btl);
    EqualBT(localtestnum, localtesterr, btl, btl2);

    MapPreOrder(localtestnum, localtesterr, btl, true, MapDoubleNPrint<int>);
    MapPostOrder(localtestnum, localtesterr, btl, true, MapDoubleNPrint<int>);
    MapInOrder(localtestnum, localtesterr, btl, true, MapDoubleNPrint<int>);
    MapBreadth(localtestnum, localtesterr, btl, true, MapDoubleNPrint<int>);

    NonEqualBT(localtestnum, localtesterr, btl, btl2);

    TraverseBreadth(localtestnum, localtesterr, btl, true, &TraversePrint<int>);
    FoldPreOrder(localtestnum, localtesterr, btl, true, FoldAdd<int>, 0, 48);
    FoldPostOrder(localtestnum, localtesterr, btl, true, FoldAdd<int>, 0, 48);
    FoldInOrder(localtestnum, localtesterr, btl, true, FoldAdd<int>, 0, 48);
    FoldBreadth(localtestnum, localtesterr, btl, true, FoldAdd<int>, 0, 48);
  }catch (...)
    {
      localtestnum++;
      localtesterr++;
      cout << endl
           << "Unmanaged error! " << endl;
    }
    cout << "End of Test! (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
    testnum += localtestnum;
    testerr += localtesterr;
}

void MyTestIterator(uint &testnum, uint &testerr)
{
  cout << "\nBegin of Iterators:\n\n";
  uint localtestnum = 0;
  uint localtesterr = 0;
  try
  {
  {
  cout << "\n--- Pre Order Iterator ---\n";
  lasd::Vector<int> vec{5};

  SetAt(localtestnum, localtesterr, vec, true, 0, 0);
  SetAt(localtestnum, localtesterr, vec, true, 1, 1);
  SetAt(localtestnum, localtesterr, vec, true, 2, 2);
  SetAt(localtestnum, localtesterr, vec, true, 3, 3);
  SetAt(localtestnum, localtesterr, vec, true, 4, 4); //5

  Exists(localtestnum, localtesterr, vec, true, 0);
  Exists(localtestnum, localtesterr, vec, true, 1);
  Exists(localtestnum, localtesterr, vec, true, 2);
  Exists(localtestnum, localtesterr, vec, true, 3);
  Exists(localtestnum, localtesterr, vec, true, 4); //5

  lasd::Vector<int> vecM(std::move(vec));
  TraversePreOrder(localtestnum, localtesterr, vecM, true, &TraversePrint<int>);

  lasd::BinaryTreeVec btVec(vecM);
  TraversePreOrder(localtestnum, localtesterr, btVec, true, &TraversePrint<int>); // 0 1 3 4 2

  lasd::BTPreOrderMutableIterator<int> itr(btVec);

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 0);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 1);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 3);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 4);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 2);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);

  itr.Reset();
  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);
  }
  {
  cout << "\n--- Post Order Iterator ---\n";
  
  lasd::Vector<int> vec{5};

  SetAt(localtestnum, localtesterr, vec, true, 0, 0);
  SetAt(localtestnum, localtesterr, vec, true, 1, 1);
  SetAt(localtestnum, localtesterr, vec, true, 2, 2);
  SetAt(localtestnum, localtesterr, vec, true, 3, 3);
  SetAt(localtestnum, localtesterr, vec, true, 4, 4); //5

  Exists(localtestnum, localtesterr, vec, true, 0);
  Exists(localtestnum, localtesterr, vec, true, 1);
  Exists(localtestnum, localtesterr, vec, true, 2);
  Exists(localtestnum, localtesterr, vec, true, 3);
  Exists(localtestnum, localtesterr, vec, true, 4); //5

  lasd::Vector<int> vecM(std::move(vec));

  lasd::BinaryTreeVec btVec(vecM);
  TraversePostOrder(localtestnum, localtesterr, btVec, true, &TraversePrint<int>); // 3 4 1 2 0
  lasd::BTPostOrderMutableIterator<int> itr2(btVec);

  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 3);
  SetItrValue(localtestnum, localtesterr, itr2, true, 100);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;

  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 4);
  SetItrValue(localtestnum, localtesterr, itr2, true, 100);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;

  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 1);
  SetItrValue(localtestnum, localtesterr, itr2, true, 100);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;

  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 2);
  SetItrValue(localtestnum, localtesterr, itr2, true, 100);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;

  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 0);
  SetItrValue(localtestnum, localtesterr, itr2, true, 100);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  Terminated(localtestnum, localtesterr, itr2, true);

  itr2.Reset();
  Terminated(localtestnum, localtesterr, itr2, false);
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  GetItrValue(localtestnum, localtesterr, itr2, true, 100);
  ++itr2;
  Terminated(localtestnum, localtesterr, itr2, true);
  }
  {
  cout << "\n--- In Order Iterator ---\n";
  lasd::Vector<int> vec{5};

  SetAt(localtestnum, localtesterr, vec, true, 0, 0);
  SetAt(localtestnum, localtesterr, vec, true, 1, 1);
  SetAt(localtestnum, localtesterr, vec, true, 2, 2);
  SetAt(localtestnum, localtesterr, vec, true, 3, 3);
  SetAt(localtestnum, localtesterr, vec, true, 4, 4); //5

  Exists(localtestnum, localtesterr, vec, true, 0);
  Exists(localtestnum, localtesterr, vec, true, 1);
  Exists(localtestnum, localtesterr, vec, true, 2);
  Exists(localtestnum, localtesterr, vec, true, 3);
  Exists(localtestnum, localtesterr, vec, true, 4); //5

  lasd::Vector<int> vecM(std::move(vec));

  lasd::BinaryTreeVec btVec(vecM);
  TraverseInOrder(localtestnum, localtesterr, btVec, true, &TraversePrint<int>); // 3 1 4 0 2

  lasd::BTInOrderMutableIterator<int> itr(btVec);

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 3);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 1);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 4);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 0);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 2);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);

  itr.Reset();
  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);
  }
  {
  cout << "\n--- Breadth Iterator ---\n";
  lasd::Vector<int> vec{5};

  SetAt(localtestnum, localtesterr, vec, true, 0, 0);
  SetAt(localtestnum, localtesterr, vec, true, 1, 1);
  SetAt(localtestnum, localtesterr, vec, true, 2, 2);
  SetAt(localtestnum, localtesterr, vec, true, 3, 3);
  SetAt(localtestnum, localtesterr, vec, true, 4, 4); //5

  Exists(localtestnum, localtesterr, vec, true, 0);
  Exists(localtestnum, localtesterr, vec, true, 1);
  Exists(localtestnum, localtesterr, vec, true, 2);
  Exists(localtestnum, localtesterr, vec, true, 3);
  Exists(localtestnum, localtesterr, vec, true, 4); //5

  lasd::Vector<int> vecM(std::move(vec));

  lasd::BinaryTreeVec btVec(vecM);
  TraverseBreadth(localtestnum, localtesterr, btVec, true, &TraversePrint<int>); // 0 1 2 3 4

  lasd::BTBreadthMutableIterator<int> itr(btVec);

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 0);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 1);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 2);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 3);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;

  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 4);
  SetItrValue(localtestnum, localtesterr, itr, true, 100);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);

  itr.Reset();
  Terminated(localtestnum, localtesterr, itr, false);
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  GetItrValue(localtestnum, localtesterr, itr, true, 100);
  ++itr;
  Terminated(localtestnum, localtesterr, itr, true);
  }

}
catch (...)
{
  localtestnum++;
  localtesterr++;
  cout << endl
       << "Unmanaged error! " << endl;
}
cout << "End of Test! (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
testnum += localtestnum;
testerr += localtesterr;
}

/*---------------------*/

void MyRowTest(){

  // lasd::HashTableOpnAdr<int> test;
  // test.debug();

  // cout<<"\n------------\n";
  // lasd::HashTableOpnAdr<int> test2(50);
  // test2.debug();
  
  // cout<<"\n------------\n";
  // lasd::Vector<int> vec(6);
  // vec[0]= 10;
  // vec[1]= 20;
  // vec[2]= 30;
  // vec[3]= 40;
  // vec[4]= 50;
  // vec[5]= 50;

  // lasd::HashTableOpnAdr<int> test3(vec);

  // std::cout<<test3.Find(10)<<"\n";
  // std::cout<<test3.Find(20)<<"\n";
  // std::cout<<test3.Find(30)<<"\n";
  // std::cout<<test3.Find(40)<<"\n";
  // std::cout<<test3.Find(50)<<"\n";
  // std::cout<<test3.Exists(10)<<"\n";
  // test3.debug();

  // cout<<"\n------------\n";
  // lasd::Vector<int> vec2;
  // lasd::HashTableOpnAdr<int> test4(vec2);

  // test4.debug();
  // test4.Insert(10);
  // test4.Insert(10);
  // test4.Insert(1);
  // test4.Insert(1);
  // test4.Insert(12);
  // test4.Insert(12);
  // test4.Insert(20);
  // test4.Insert(20);
  // test4.Insert(30);
  // test4.debug();

  // std::cout<<test4.Find(10)<<"\n";
  // std::cout<<test4.Find(12)<<"\n";
  // std::cout<<test4.Find(200)<<"\n";

  // test4.Remove(12);
  // test4.debug();

  // test4.Resize(1);
  // test4.debug();

  // test4.Insert(12);
  // test4.debug();

}

// template <typename T>
// T convert(ulong value) {
//     if constexpr (std::is_integral_v<T>) {
//         return static_cast<T>(value);
//     } else if constexpr (std::is_floating_point_v<T>) {
//         return static_cast<T>(value);
//     } else if constexpr (std::is_same_v<T, std::string>) {
//         return std::to_string(value);
//     } 
//     // else {
//     //     static_assert(always_false<T>::value, "Unsupported type");
//     // }
// }

// template <typename Data>
// void OpnAdrTest(uint &testnum, uint &testerr){

//   uint loctestnum = 0, loctesterr = 0;

//     lasd::Vector<Data> vc(20);
//     for(ulong i = 0; i<20; ++i){
//       vc[i] = i;
//     }

//     lasd::BST<Data> bst(vc);

//     lasd::HashTableOpnAdr<Data> htopn(bst);

//     Size(loctestnum, loctesterr, htopn, true, 20);
//     for(ulong i = 0; i<20; ++i){
//       Exists(loctestnum, loctesterr, htopn, true, vc[i]);
//     }

//     htopn.Resize(200);
//     Size(loctestnum, loctesterr, htopn, true, 20);
//     for(ulong i = 0; i<20; ++i){
//       Exists(loctestnum, loctesterr, htopn, true, vc[i]);
//     }

//     htopn.Resize(0);
//     Size(loctestnum, loctesterr, htopn, true, 20);
//     for(ulong i = 0; i<20; ++i){
//       Exists(loctestnum, loctesterr, htopn, true, vc[i]);
//     }

//     htopn.Clear();
//     Size(loctestnum, loctesterr, htopn, true, 0);
//     for(ulong i = 0; i<20; ++i){
//       Exists(loctestnum, loctesterr, htopn, false, vc[i]);
//     }

//     lasd::HashTableOpnAdr<Data> htopn2;
//     htopn2 = htopn;
//     Size(loctestnum, loctesterr, htopn2, true, 0);
//     // htopn2.debug(); //OK

//     htopn = std::move(htopn2);
//     // htopn.debug(); //OK

//     EqualHT(loctestnum, loctesterr, htopn, htopn2);

//     for (ulong i = 0; i < 20; ++i) {
//       InsertC(loctestnum, loctesterr, htopn, vc[i]);
//     }
//     NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
    
//     htopn.Resize(0); // to min size
//     // htopn.debug(); //OK
//     NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
    
//     htopn2 = htopn;
//     for (ulong i = 0; i < 20; ++i) {
//       Remove(loctestnum, loctesterr, htopn, vc[i]);
//     }
//     Size(loctestnum, loctesterr, htopn, true, 0);
//     NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

//     lasd::HashTableOpnAdr<Data> htopn3;
//     htopn3 = std::move(htopn2);
//     Size(loctestnum, loctesterr, htopn3, true, 20);
//     for(ulong i = 0; i<20; ++i){
//       Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
//     }

//     lasd::HashTableOpnAdr<Data> htopn4(htopn3);
//     EqualHT(loctestnum, loctesterr, htopn3, htopn4);
//     htopn4.Resize(4000);
//     EqualHT(loctestnum, loctesterr, htopn3, htopn4);
//     for (ulong i = 20; i <120; ++i) { //inserisco 100
//       InsertC(loctestnum, loctesterr, htopn4, convert<Data>(i));
//     }
//     Size(loctestnum, loctesterr, htopn4, true, 120);
//     NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
    
//     htopn4.Resize(50);
//     // htopn4.debug();
//     for (ulong i = 20; i <120; ++i) { //inserisco 100
//       Remove(loctestnum, loctesterr, htopn4, convert<Data>(i));
//     }

//     EqualHT(loctestnum, loctesterr, htopn3, htopn4);

//     testnum += loctestnum;
//     testerr += loctesterr;

// }

// OpnAdrTest<int>(loctestnum, loctesterr);
// OpnAdrTest<double>(loctestnum, loctesterr);
// OpnAdrTest<string>(loctestnum, loctesterr);

void MyTestHashInt(uint &testnum, uint &testerr){ // OK
  uint loctestnum = 0, loctesterr = 0;
  uint loctestnum2 = 0, loctesterr2 = 0;
  try{

    uint loctestnum = 0, loctesterr = 0;
    cout << "\nBegin of HashMap -- OpnAdr<int> Test:\n\n";
    {

      lasd::Vector<int> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = i;
      }

      lasd::BST<int> bst(vc);

      lasd::HashTableOpnAdr<int> htopn(bst);

      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(200);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(0);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      lasd::HashTableOpnAdr<int> htopn2;
      htopn2 = htopn;
      Size(loctestnum, loctesterr, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // htopn.debug(); //OK

      EqualHT(loctestnum, loctesterr, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum, loctesterr, htopn, vc[i]);
      }
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn.Resize(0); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum, loctesterr, htopn, vc[i]);
      }
      Size(loctestnum, loctesterr, htopn, true, 0);
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

      lasd::HashTableOpnAdr<int> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum, loctesterr, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
      }

      lasd::HashTableOpnAdr<int> htopn4(htopn3);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        InsertC(loctestnum, loctesterr, htopn4, static_cast<int>(i));
      }
      Size(loctestnum, loctesterr, htopn4, true, 120);
      NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
      
      htopn4.Resize(50);
      // htopn4.debug();
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        Remove(loctestnum, loctesterr, htopn4, static_cast<int>(i));
      }

      EqualHT(loctestnum, loctesterr, htopn3, htopn4);

      cout << "End of HashMap -- OpnAdr<int>  (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      testnum += loctestnum;
      testerr += loctesterr;
    }

    cout << "\nBegin of HashMap -- ClsAdr<int> Test:\n\n";
    {
      
      lasd::Vector<int> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = i;
      }

      lasd::BST<int> bst(vc);

      lasd::HashTableClsAdr<int> htopn(bst);

      Size(loctestnum2, loctesterr2, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, true, vc[i]);
      }

      htopn.Resize(200);
      Size(loctestnum2, loctesterr2, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, true, vc[i]);
      }

      htopn.Resize(0);
      Size(loctestnum2, loctesterr2, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, true, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum2, loctesterr2, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, false, vc[i]);
      }
      
      cout<<"debug1\n";
      lasd::HashTableClsAdr<int> htopn2;
      cout<<"debug2\n";
      htopn2 = htopn;
      cout<<"debug3\n";
      Size(loctestnum2, loctesterr2, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // htopn.debug(); //OK

      EqualHT(loctestnum2, loctesterr2, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum2, loctesterr2, htopn, vc[i]);
      }
      NonEqualHT(loctestnum2, loctesterr2, htopn, htopn2);
      
      htopn.Resize(0); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum2, loctesterr2, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum2, loctesterr2, htopn, vc[i]);
      }
      Size(loctestnum2, loctesterr2, htopn, true, 0);
      NonEqualHT(loctestnum2, loctesterr2, htopn, htopn2);

      lasd::HashTableClsAdr<int> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum2, loctesterr2, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn3, true, vc[i]);
      }

      lasd::HashTableClsAdr<int> htopn4(htopn3);
      EqualHT(loctestnum2, loctesterr2, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum2, loctesterr2, htopn3, htopn4);
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        InsertC(loctestnum2, loctesterr2, htopn4, static_cast<int>(i));
      }
      Size(loctestnum2, loctesterr2, htopn4, true, 120);
      NonEqualHT(loctestnum2, loctesterr2, htopn3, htopn4);
      
      htopn4.Resize(50);
      // htopn4.debug();
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        Remove(loctestnum2, loctesterr2, htopn4, static_cast<int>(i));
      }

      EqualHT(loctestnum2, loctesterr2, htopn3, htopn4);
      
      cout << "End of HashMap -- ClsAdr<int>  (Errors/Tests: " << loctesterr2 << "/" << loctestnum2 << ")" << endl;
      testnum += loctestnum2;
      testerr += loctesterr2;
    }

  }
  catch (const std::exception& e) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! "<< e.what() << endl;
  }
  // cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr+loctesterr2 << "/" << loctestnum+loctestnum2 << ")" << endl;
  // testnum += loctestnum;
  // testerr += loctesterr;
}

void MyTestHashDouble(uint &testnum, uint &testerr){
  uint loctestnum = 0, loctesterr = 0;
  try{

    cout << "\nBegin of HashMap -- OpnAdr<double> Test:\n\n";
    {
      
      lasd::Vector<double> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = (i+0.5678);
      }

      lasd::BST<double> bst(vc);

      lasd::HashTableOpnAdr<double> htopn(bst);

      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(200);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(0);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      lasd::HashTableOpnAdr<double> htopn2;
      htopn2 = htopn;
      Size(loctestnum, loctesterr, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // htopn.debug(); //OK

      EqualHT(loctestnum, loctesterr, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum, loctesterr, htopn, vc[i]);
      }
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn.Resize(0); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum, loctesterr, htopn, vc[i]);
      }
      Size(loctestnum, loctesterr, htopn, true, 0);
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

      lasd::HashTableOpnAdr<double> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum, loctesterr, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
      }

      lasd::HashTableOpnAdr<double> htopn4(htopn3);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        InsertC(loctestnum, loctesterr, htopn4, static_cast<double>(i));
      }
      Size(loctestnum, loctesterr, htopn4, true, 120);
      NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
      
      htopn4.Resize(50);
      // htopn4.debug();
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        Remove(loctestnum, loctesterr, htopn4, static_cast<double>(i));
      }

      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      cout << "End of HashMap -- OpnAdr<double>  (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      testnum += loctestnum;
      testerr += loctesterr;
    }

    loctestnum = 0, loctesterr = 0;
    cout << "\nBegin of HashMap -- ClsAdr<double> Test:\n\n";
    {
      
      lasd::Vector<double> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = (i+0.58448);
      }

      lasd::BST<double> bst(vc);

      lasd::HashTableClsAdr<double> htopn(bst);

      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(200);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Resize(0);
      Size(loctestnum, loctesterr, htopn, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, true, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }
      
      cout<<"debug1\n";
      lasd::HashTableClsAdr<double> htopn2;
      cout<<"debug2\n";
      htopn2 = htopn;
      cout<<"debug3\n";
      Size(loctestnum, loctesterr, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // htopn.debug(); //OK

      EqualHT(loctestnum, loctesterr, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum, loctesterr, htopn, vc[i]);
      }
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn.Resize(0); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum, loctesterr, htopn, vc[i]);
      }
      Size(loctestnum, loctesterr, htopn, true, 0);
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

      lasd::HashTableClsAdr<double> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum, loctesterr, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
      }

      lasd::HashTableClsAdr<double> htopn4(htopn3);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        InsertC(loctestnum, loctesterr, htopn4, static_cast<double>(i));
      }
      Size(loctestnum, loctesterr, htopn4, true, 120);
      NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
      
      htopn4.Resize(50);
      // htopn4.debug();
      for (ulong i = 20; i <120; ++i) { //inserisco 100
        Remove(loctestnum, loctesterr, htopn4, static_cast<double>(i));
      }

      EqualHT(loctestnum, loctesterr, htopn3, htopn4);

      cout << "End of HashMap -- ClsAdr<double>  (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      testnum += loctestnum;
      testerr += loctesterr;
    }

  }
  catch (const std::exception& e) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! "<< e.what() << endl;
  }
  // cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  // testnum += loctestnum;
  // testerr += loctesterr;
}


void MyTestHashString(uint &testnum, uint &testerr){
  uint loctestnum = 0, loctesterr = 0;
  try{

  }
  catch (const std::exception& e) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! "<< e.what() << endl;
  }
  cout << "End of HashTable Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;

}

void MyTestHash(uint testnum, uint testerr){

  uint localtestnum = 0, localtesterr = 0;

  cout << "\nBegin of HashMap<int> Test:\n\n";
  MyTestHashInt(localtestnum, localtesterr);

  cout << "\nBegin of HashMap<double> Test:\n\n";
  MyTestHashDouble(localtestnum, localtesterr);

  cout << "\nBegin of HashMap<string> Test:\n\n";
  MyTestHashString(localtestnum, localtesterr);

  cout<< "\nTest HashMap (Errors/Tests: " << localtesterr << "/" << localtestnum << ")" << endl;
  testnum += localtestnum;
  testerr += localtesterr;
}

void MyTest(uint &testnum, uint &testerr)
{
  
  // MyTestVector(testnum, testerr);

  // MyTestList(testnum, testerr);

  // MyTestBinaryTree(testnum, testerr);

  // MyTestIterator(testnum, testerr);

  /***********************/

  MyTestHash(testnum, testerr);

  // MyRowTest();

  cout << "\nMyTest (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

void mytest()
{

  std::cout << std::endl
            << "~*~#~*~ Welcome to my test (Raffaele Raia N8600456) ~*~#~*~ " << std::endl;

  uint localtestnum, localtesterr;

  localtestnum = 0;
  localtesterr = 0;
  MyTest(localtestnum, localtesterr);

  cout << endl
       << "-- FINE --" << endl;
}