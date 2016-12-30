#include <iostream>
#include "FileLinkedList.h"
#include <string>
#include<cstdio>
#include<vector>

using std::vector;

using namespace std;

struct sexyChar {
  char a;
  int b;
};


int main() {

  FileLinkedList<int> flist { "testerTXTLinked.txt" };

  for(int a = 0; a < 10000; ++a) {
    flist.push_back(a);
  }

  for(int a = 0; a < 10000; ++a) {
    if(flist[a] != a) {
      cout << "Big Test Failed";
    }
  }

  for(int a = 0; a < 10000; ++a) {
   flist.pop_back();
  }

  if(flist.size() != 0) { cout << "List not empty."; }





/*
  for(int a = 0; a <= 5; ++a) {
    flist.push_back(a);
  }*/
/*
  flist.insert(flist.begin(), 66);

  flist.insert(flist.end(), 69);

  flist.erase(flist.begin()++);
  flist.erase(--flist.end());
*/
/*  flist.push_back(1);

  for(int a = 2; a < 101; ++a) {
    flist.push_back(a);
  }

//  flist.push_back(10000);
*//*
  for(int j = 0; j < flist.size(); j++) {
   cout << flist[j] << " ";
  }
*/
//  cout << "\n";

//  FileLinkedList<int> copyl {flist.cbegin(), flist.cend(), "testercopyTXT.txt" };
/*
  for(int j = 0; j < copyl.size(); j++) {
     cout << copyl[j] << " ";
  }
*/
//  copyl.erase(copyl.begin());

//  copyl.erase(copyl.end()--);

  cout << "\n";
/*
  for(int j = 0; j < copyl.size(); j++) {
    cout << copyl[j] << " ";
  }
*/
 

//  FileLinkedList<int> copyl {flist.begin(), flist.end(), "testercopyTXT.txt" };

//   for(int j = 0; j < flist.size(); j++) {
//     cout << copyl[j] << " ";
//   }
    cout << "\n";



/*  flist.push_back(99);
  flist.push_back(89);

  for(int a = 0; a < 100000; a++) {
    flist.push_back(a);
  }

  for(int j = 0; j < flist.size(); j++) {
   cout << flist[j] << " ";
  }

  flist.clear();

  if(flist.size() == 0) cout << "the list is empty" << " \n";

  cout << "\n";

  cout << "\n";

  cout << "\n";

  for(int h = 0; h < 13; h++) {
    flist.push_back(h);
  }

  for(int j = 0; j < flist.size(); j++) {
    cout << flist[j] << " ";
  }

  for(int i : flist) {
    cout << i << " ";
  }

  cout << "\n"; */
/*
  flist.pop_back();
  flist.pop_back();
  flist.pop_back();

  for(int j = 0; j < flist.size(); j++) {
    cout << flist[j] << " ";
  }

  FileLinkedList<int> copyl {flist.cbegin(), flist.cend(), "testercopyTXT.txt" };

  cout << "\n";

  for(int j = 0; j < copyl.size(); j++) {
    cout << copyl[j] << " ";
  }
*/

/*

  flist.insert(flist.cend(), 77);

  for(int j = 0; j < flist.size(); j++) {
      cout << flist[j] << " ";
  }

  cout << " \n" << " \n";

  flist.erase(flist.cbegin());
  flist.erase(flist.cend());

  for(int j = 0; j < flist.size(); j++) {
      cout << flist[j] << " ";
  }

  cout << " \n" << " \n";

  flist.pop_back();

  cout << "after pop_back" << " \n";

  for(int j = 0; j < flist.size(); j++) {
      cout << flist[j] << " ";
  }

cout << " \n" << " \n";


  flist.clear();

  cout << " \n" << " \n";

  if(flist.size() == 0) cout << "the list is still empty" << " \n";

  cout << " \n" << " \n";

  cout << "char test" << " \n";

  FileLinkedList<char> clist { "testerTXTCHAR.txt" };

  clist.push_back('c');
  clist.push_back('a');
  clist.push_back('t');

  for(int j = 0; j < clist.size(); j++) {
      cout << clist[j] << " ";
  }

  cout << " \n" << " \n";

  clist.pop_back();

  for(int j = 0; j < clist.size(); j++) {
      cout << clist[j] << " ";
  }

  cout << " \n" << " \n";

  clist.clear();

  cout << " \n";

  for(int i : clist)
  cout << i << " ";

  cout << " \n";

  vector<sexyChar> sexy = {{'c',1},{'a',33},{'t',4}};

  FileLinkedList<sexyChar> sexyW { "sexiest.txt" };

  sexyW.push_back(sexy[1]);

  clist.push_back('c');
  clist.push_back('a');
  clist.push_back('t');

  for(int j = 0; j < clist.size(); j++) {
      cout << clist[j] << " ";
  }

  cout << " \n" << " \n";

  clist.pop_back();

  for(int j = 0; j < clist.size(); j++) {
      cout << clist[j] << " ";
  }

  cout << " \n" << " \n";

  clist.clear();

  cout << " \n";

  for(int i : clist)
  cout << i << " ";

  cout << " \n";

  vector<sexyChar> sexy = {{'c',1},{'a',33},{'t',4}};

  FileLinkedList<sexyChar> sexyW { "sexiest.txt" };

  sexyW.push_back(sexy[1]);
  sexyW.push_back(sexy[0]);
  sexyW.push_back(sexy[2]);


//  (int i : sexy)
//  //  cout << i << " ";
//
//  /*  for(int j = 0; j < sexyW.size(); j++) {
//        cout << sexyW[j] << " ";
//          } */
//
// sexyW.pop_back();
//
// sexyW.clear();  // versus sexy.clear() and use of just sexy in general?
//
//  sexy.insert(sexy.cbegin(),
//


}
