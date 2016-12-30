#include <iostream>
#include "FileArrayList.h"
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

  FileArrayList<int> flist { "testerTXT.txt" };
  flist.push_back(99);
  flist.push_back(89);
  /*
    for(int j = 0; j < flist.size(); j++) {
      cout << flist[j] << " ";
    }
  */

  //  flist.insert(1,73);
  flist.insert(flist.cbegin(), 73);

  for(int j = 0; j < flist.size(); j++) {
      cout << flist[j] << " ";
    }

 flist.clear();

  if(flist.size() == 0) cout << "the list is empty" << " \n";

  cout << " \n";

  for(int a = 0; a < 10000; ++a) {
    flist.push_back(a);
  }

  for(int j = 0; j < flist.size(); j++) {
    cout << flist[j] << " ";
  }

  flist.clear();

  cout << " \n";
  cout << " \n";

  if(flist.size() == 0) cout << "the list is still empty" << " \n";

  cout << " \n";

  flist.push_back(3);
  flist.push_back(6);
  flist.push_back(9);
  flist.push_back(12);
  flist.push_back(15);

  for(int j = 0; j < flist.size(); j++) {
    cout << flist[j] << " ";
  }

  cout << " \n" << " \n";

//  flist.erase(flist.cend());

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

  FileArrayList<char> clist { "testerTXTCHAR.txt" };

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

  FileArrayList<sexyChar> sexyW { "sexiest.txt" };

  sexyW.push_back(sexy[1]);     
  sexyW.push_back(sexy[0]);
  sexyW.push_back(sexy[2]);

  
//  (int i : sexy)
//  cout << i << " ";

/*  for(int j = 0; j < sexyW.size(); j++) {
      cout << sexyW[j] << " ";
  } */

  sexyW.pop_back();

  sexyW.clear();  // versus sexy.clear() and use of just sexy in general?

//  sexy.insert(sexy.cbegin(),

  
}
