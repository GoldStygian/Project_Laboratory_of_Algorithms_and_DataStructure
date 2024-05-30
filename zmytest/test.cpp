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
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
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
      
      htopn.Resize(1); // to min size
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
      Size(loctestnum2, loctesterr2, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, false, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum2, loctesterr2, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum2, loctesterr2, htopn, false, vc[i]);
      }
      
      lasd::HashTableClsAdr<int> htopn2;
      htopn2 = htopn;
      Size(loctestnum2, loctesterr2, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // htopn.debug(); //OK

      EqualHT(loctestnum2, loctesterr2, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum2, loctesterr2, htopn, vc[i]);
      }
      NonEqualHT(loctestnum2, loctesterr2, htopn, htopn2);
      
      htopn.Resize(1); // to min size
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
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
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
      
      htopn.Resize(1); // to min size
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
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }
      
      lasd::HashTableClsAdr<double> htopn2;
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
      
      htopn.Resize(1); // to min size
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
    cout << "\nBegin of HashMap -- OpnAdr<string> Test:\n\n";
    {
      
      lasd::Vector<string> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = static_cast<char>(i+97); //range [a, t]
      }

      vc.Traverse(
        [](const string& data){
          cout<<data<<" ";
        }
      );
      printf("\n");

      lasd::BST<string> bst(vc);

      lasd::HashTableOpnAdr<string> htopn(bst);

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
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      lasd::HashTableOpnAdr<string> htopn2;
      htopn2 = htopn;
      Size(loctestnum, loctesterr, htopn2, true, 0);
      // htopn2.debug(); //OK

      htopn = std::move(htopn2);
      // // htopn.debug(); //OK

      EqualHT(loctestnum, loctesterr, htopn, htopn2);

      for (ulong i = 0; i < 20; ++i) {
        InsertC(loctestnum, loctesterr, htopn, vc[i]);
      }
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn.Resize(1); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum, loctesterr, htopn, vc[i]);
      }
      Size(loctestnum, loctesterr, htopn, true, 0);
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

      lasd::HashTableOpnAdr<string> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum, loctesterr, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
      }

      lasd::HashTableOpnAdr<string> htopn4(htopn3);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);

      // cout<<"here\n\n\n";
      // lasd::Vector<string> vc2(120);
      // for (ulong i = 0; i <120; ++i) { //inserisco 99
      //   vc2[i] = static_cast<char>(i + 65);
      //   InsertC(loctestnum, loctesterr, htopn4, vc2[i]);
      // }
      // Size(loctestnum, loctesterr, htopn4, true, 120);
      // NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
      
      // htopn4.Resize(50);
      // // htopn4.debug();
      // for (ulong i = 0; i <120; ++i) { //inserisco 100
      //   Remove(loctestnum, loctesterr, htopn4, vc2[i]);
      // }

      // EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      cout << "End of HashMap -- OpnAdr<string>  (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      testnum += loctestnum;
      testerr += loctesterr;
    }

    loctestnum = 0, loctesterr = 0;
    cout << "\nBegin of HashMap -- ClsAdr<string> Test:\n\n";
    {
      
      lasd::Vector<string> vc(20);
      for(ulong i = 0; i<20; ++i){
        vc[i] = static_cast<char>(i + 97);
      }

      lasd::BST<string> bst(vc);

      lasd::HashTableClsAdr<string> htopn(bst);

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
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }

      htopn.Clear();
      Size(loctestnum, loctesterr, htopn, true, 0);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn, false, vc[i]);
      }
      
      lasd::HashTableClsAdr<string> htopn2;
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
      
      htopn.Resize(1); // to min size
      // htopn.debug(); //OK
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);
      
      htopn2 = htopn;
      for (ulong i = 0; i < 20; ++i) {
        Remove(loctestnum, loctesterr, htopn, vc[i]);
      }
      Size(loctestnum, loctesterr, htopn, true, 0);
      NonEqualHT(loctestnum, loctesterr, htopn, htopn2);

      lasd::HashTableClsAdr<string> htopn3;
      htopn3 = std::move(htopn2);
      Size(loctestnum, loctesterr, htopn3, true, 20);
      for(ulong i = 0; i<20; ++i){
        Exists(loctestnum, loctesterr, htopn3, true, vc[i]);
      }

      lasd::HashTableClsAdr<string> htopn4(htopn3);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      htopn4.Resize(4000);
      EqualHT(loctestnum, loctesterr, htopn3, htopn4);
      // for (ulong i = 20; i <120; ++i) { //inserisco 100
      //   string str(1, static_cast<char>(i + 97));
      //   InsertC(loctestnum, loctesterr, htopn4, str);
      // }
      // Size(loctestnum, loctesterr, htopn4, true, 120);
      // NonEqualHT(loctestnum, loctesterr, htopn3, htopn4);
      
      // htopn4.Resize(50);
      // // htopn4.debug();
      // for (ulong i = 20; i <120; ++i) { //inserisco 100
      //   string str(1, static_cast<char>(i + 97));
      //   Remove(loctestnum, loctesterr, htopn4, str);
      // }

      // EqualHT(loctestnum, loctesterr, htopn3, htopn4);

      cout << "End of HashMap -- ClsAdr<string>  (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      testnum += loctestnum;
      testerr += loctesterr;
    }

  }
  catch (const std::exception& e) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! "<< e.what() << endl;
  }
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

  MyTestHash(testnum, testerr);

  /***********************/

  // MyRowTest();

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