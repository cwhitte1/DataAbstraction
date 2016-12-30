#include <iostream>
#include "AVLMap.h"
#include <string>
#include <map>

using namespace std;

int main() {
  
  cout << "\n" << "\n";
  
  map<int, int> test;
  AVLMap<int, int> bsttest;

  bsttest.insert(std::make_pair(1,1));
  //cout << bsttest[1] << "\n";

  bsttest.insert(std::make_pair(2,2));
  bsttest.insert(std::make_pair(3,3));
  bsttest.insert(std::make_pair(4,4));
  bsttest.insert(std::make_pair(5,5));
  bsttest.insert(std::make_pair(7,7));
  bsttest.insert(std::make_pair(24,24));
  bsttest.insert(std::make_pair(12,12));
  bsttest.insert(std::make_pair(17,17));
  bsttest.insert(std::make_pair(6,6));
  bsttest.insert(std::make_pair(99,99));

  // SIMPLE ITERATOR AND BRACKET TEST START
  bool tester = true;
  for(auto i : bsttest) {
    //bool tester = true;
    if(i.first != bsttest[i.first]) { 
      tester = false; 
    }
  }

  if(tester == false) { cout << "TEST 1: SIMPLE ITERATOR AND BRACKET TEST --- FAILED ---\n"; }
  else { cout << "TEST 1: SIMPLE ITERATOR AND BRACKET TEST --- PASSED ---\n"; }
    //cout << bsttest[i.first] << "\n";

  // SIMPLE ITERATOR AND BRACKET TEST END


  //cout << "Min: " << (bsttest.findMin(bsttest.returnRoot())) -> key  << " Max: " << (bsttest.findMax(bsttest.returnRoot())) -> key << "\n";


  // SIMPLE INT ERASE AND COUNT TEST START

  bsttest.erase(17);
  bsttest.erase(12);
  bsttest.erase(7);
  bsttest.erase(1);
  bsttest.erase(99);

  bool found = true;

  if(bsttest.count(17) != 0) { found = false; }
  if(bsttest.count(12) != 0) { found = false; }
  if(bsttest.count(7) != 0) { found = false; }
  if(bsttest.count(1) != 0) { found = false; }
  if(bsttest.count(99) != 0) { found = false; }
  if(bsttest.count(2) != 1) { found = false; }
  if(bsttest.count(6) != 1) { found = false; }

  if(found) { cout << "TEST 2: SIMPLE INT ERASE AND COUNT TEST --- PASSED ---\n"; }
  else { cout << "TEST 2: SIMPLE INT ERASE AND COUNT TEST --- FAILED ---\n"; }

  // SIMPLE INT ERASE AND COUNT TEST END

  // SIMPLE SIZE TEST START @ size = 6

  if(bsttest.size() == 6) { cout << "TEST 3: SIMPLE SIZE TEST --- PASSED ---\n"; }
  else { cout << "TEST 3: SIMPLE SIZE TEST --- FAILED ---\n"; }

  // SIMPLE SIZE TEST FAILED

  // SIMPLE ITERATOR ERASE, ITERATOR FIND, AND ITERATOR == TEST START

  bsttest.erase(bsttest.cbegin());

  if(bsttest.find(2) == bsttest.end()) { cout << "TEST 4: SIMPLE ITERATOR ERASE, ITERATOR FIND, AND ITERATOR == TEST --- PASSED ---\n"; }
  else { cout << "TEST 4: SIMPLE ITERATOR ERASE, ITERATOR FIND, AND ITERATOR == TEST --- FAILED ---\n"; }

  // SIMPLE ITERATOR ERASE, ITERATOR FIND, AND ITERATOR == TEST END
  
  // SIMPLE CLEAR TEST START
  
  bsttest.clear();

  if(bsttest.begin() == bsttest.end()) { cout << "TEST 5: CLEAR TEST --- PASSED ---\n"; }
  else { cout << "TEST 5: CLEAR TEST --- FAILED ---\n"; }

  //cout << "TEST 5: CLEAR TEST --- INCOMPLETE ---\n";

  // SIMPLE CLEAR TEST END

  // SPECIAL REINSERTION AND DOUBLE INSERTION TEST START

  bsttest.insert(std::make_pair(1,4));
  bsttest.insert(std::make_pair(1,5));
  bsttest.insert(std::make_pair(1,6));

  if(bsttest.size() == 1 && bsttest[1] == 4) {
    cout << "TEST 6: SPECIAL REINSERTION AND DOUBLE INSERTION TEST --- PASSED ---\n";
  } else {
    cout << "TEST 6: SPECIAL REINSERTION AND DOUBLE INSERTION TEST --- FAILED ---\n";
  }

  // SPECIAL REINSERTION AND DOUBLE INSERTION TEST END

  // == TEST AND LARGE TEST START

  AVLMap<int, int> twin1;
  AVLMap<int, int> twin2;

  for(auto a = 0; a < 2000; ++a) {
    twin1.insert(std::make_pair(a, a));
    twin2.insert(std::make_pair(a, a));
  }

  if(twin1 == twin2) { cout << "TEST 7: == TEST AND LARGE TEST --- PASSED ---\n"; }
  else { cout << "TEST 7: == TEST AND LARGE TEST --- FAILED ---\n"; }

  // == TEST AND LARGE TEST END

  // != TEST START

  twin1.erase(twin1.cbegin());

  if(twin1 != twin2) { cout << "TEST 8: != TEST --- PASSED ---\n"; }
  else { cout << "TEST 8: != TEST --- FAILED ---\n"; }

  // != TEST END

  // COPY CONSTRUCTOR TEST START

  AVLMap<int, int> twin3(twin1);

  if(twin3 == twin1) { cout << "TEST 9: COPY CONSTRUCTOR TEST --- PASSED ---\n"; }
  else { cout << "TEST 9: COPY CONSTRUCTOR TEST --- FAILED ---\n"; }

  // COPY CONSTRUCTOR TEST END

  // EQUALS OPERATOR TEST START

  twin3 = twin2;

  if(twin3 == twin2) { cout << "TEST 10: EQUALS OPERATOR TEST --- PASSED ---\n"; }
  else { cout << "TEST 10: EQUALS OPERATOR TEST --- FAILED ---\n"; }

  // EQUALS OPERATOR TEST END

  // SPECIAL BRACKETS OPERATOR ASSIGNMENT AND NON-PRIMITIVE TEST START

  AVLMap<int, string> brackie;
  
  bool brackTest = true;

  brackie[4] = "test";

  if(brackie[4] != "test") {
    brackTest = false;
  }

  brackie[4] = "changed";

  if(brackie[4] != "changed") {
    brackTest = false;
  }

  if(brackTest) { cout << "TEST 11: SPECIAL BRACKETS OPERATOR ASSIGNMENT AND NON-PRIMITIVE TEST --- PASSED ---\n"; }
  else { cout << "TEST 11: SPECIAL BRACKETS OPERATOR ASSIGNMENT AND NON-PRIMITIVE TEST --- FAILED ---\n"; }

  // SPECIAL BRACKETS OPERATOR ASSIGNMENT AND NON-PRIMITIVE TEST START

  cout << "\n" << "\n";

  //bsttest.treePrint(bsttest.returnRoot());
  
  // MANUAL BALANCE CHECK BELOW

  AVLMap<int, int> bal;
  
  for(int i = 10; i > 6; --i) {
    bal.insert(std::make_pair(i,i));
  }
  //bal.erase(7);
  
  //bal.insert(std::make_pair(10,10));
  //bal.insert(std::make_pair(9,9));
  //bal.insert

  bal.printPreOrder(bal.returnRoot());

}

