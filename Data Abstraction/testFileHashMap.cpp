#include "FileHashMap.h"
#include <string>
#include<vector>
#include <functional>
#include<unordered_map>

using std::pair;
using std::string;
using std::cout;
using std::hash;


int main() {
  hash<char> hash_fn;
  FileHashMap<char,int,hash<char>> fmap("sexyAlice.txt",hash_fn);

  fmap.insert(std::make_pair('a',1));
  fmap.insert(std::make_pair('b',2));
  fmap.insert(std::make_pair('c',3));
  fmap.insert(std::make_pair('d',4));
  fmap.insert(std::make_pair('e',5));
  fmap.insert(std::make_pair('f',6));
  fmap.insert(std::make_pair('g',7));
  fmap.insert(std::make_pair('h',8));
  fmap.insert(std::make_pair('i',9));
  fmap.insert(std::make_pair('j',10));
  fmap.insert(std::make_pair('k',11));
  fmap.insert(std::make_pair('l',12));

/*  fmap.insert(std::make_pair('a',4));
  fmap.insert(std::make_pair('b',1));

  FileHashMap<char,int,hash<char>> fmap2("sexyAlice2.txt",hash_fn);

  fmap2.insert(std::make_pair('a',4));
  fmap2.insert(std::make_pair('b',1));

  if(fmap == fmap2) {
    cout << "EQUALITY TEST PASSED";
    cout << "\n";
  }

  fmap2.insert(std::make_pair('c',6));

  if(fmap != fmap2) {
    cout << "INEQUALITY TEST PASSED";
    cout << "\n";
  }

  auto findTester = fmap.insert(std::make_pair('d',6));

  if(findTester.first == fmap.find('d')) {
    cout << "FIND TEST PASSED";
    cout << "\n";
  }

  fmap.set(std::make_pair('d',2));

  if(fmap.count('d') == 1) {
    cout << "SET AND COUNT PASSED";
    cout << "\n";
  }

  if(fmap['d'] == 2) {
    cout << "BRACKET OPERATOR PASSED";
    cout << "\n";
  }

  fmap.clear();
  fmap2.clear(); */

  hash<int> hash_fnINT;
  FileHashMap<int,int,hash<int>> fINT("sexyInt.txt",hash_fnINT);

  std::unordered_map<int,int> sexy;

  for(int i = 0; i < 200000; ++i) {
    fINT.insert(std::make_pair(i, i));
    sexy.insert(std::make_pair(i,i));
  }

  for(int i = 0; i < 200000; ++i) {
    if(fINT[i] == sexy[i]) {
     // cout << "WERK IT THEN TWERK IT" << "\n";
    }
    if(fINT[i] != sexy[i]) {
      cout << "YOU LUCKED UP: " << i << "\n";
    }
  }

  //fINT.clear();

  //for(int i = 0; i < 10001; ++i) {
  //  fINT.insert(std::make_pair(i, 8));
  //}
/*
  struct sexyChar {
  char a;
  int b;
  };

  hash<sexyChar> hash_fnALICE;
  FileHashMap<int,int,hash<sexyChar>> alice("alice.txt",hash_fnALICE;

  vector<sexyChar> sexy = {{'c',1},{'a',33},{'t',4}};

  alice.insert(sexy[1]);  


hash<char> hash_fn;
  FileHashMap<char,int,hash<char>> fmap("sexyAlice.txt",hash_fn);

  fmap.insert(std::make_pair('a',1));
  fmap.insert(std::make_pair('b',2));
  fmap.insert(std::make_pair('c',3));
  fmap.insert(std::make_pair('d',4));
  fmap.insert(std::make_pair('e',5));
  fmap.insert(std::make_pair('f',6));
  fmap.insert(std::make_pair('g',7));
  fmap.insert(std::make_pair('h',8));
  fmap.insert(std::make_pair('i',9));
  fmap.insert(std::make_pair('j',10));
  fmap.insert(std::make_pair('k',11));
  fmap.insert(std::make_pair('l',12)); */

/*  fmap.insert(std::make_pair('a',4));
     fmap.insert(std::make_pair('b',1));
 */
}
