#include <iostream>
#include "OrderStat.h"
#include <string>
#include <map>

using namespace std;

int main() {

  cout << "\n" << "\n";

  // SMALL AND NON-PRIMITIVE TEST
  
  OrderStat<string> tester;
  auto circuit = true;

  tester.push_front("a");

  if(tester.size() != 1) {
    circuit = false;
    cout << "Initial Size Test Failed\n";
  }
  if(tester[0] != "a") {
    circuit = false;
    cout << "Initial Bracket Test Failed\n";
  }
  if(tester.returnRootData() != "a") {
    circuit = false;
    cout << "Initial Root Test Failed\n";
  }

  tester.push_front("b");
  tester.push_front("c");
  tester.push_front("d");
  tester.push_front("e");

  if(tester.size() != 5) {
    circuit = false;
    cout << "Final Size Test Failed\n";
  } 

  //tester.printPreOrder(tester.returnRoot());

  if(tester[0] != "e") {
    circuit = false;
    cout << "Bracket 0 Incorrect\n";
  } else if(tester[1] != "d") {
    circuit = false;
    cout << "Bracket 1 Incorrect\n";
  } else if(tester[2] != "c") {
    circuit = false;
    cout << "Bracket 2 Incorrect\n";
  } else if(tester[3] != "b") {
    circuit = false;
    cout << "Bracket 3 Incorrect\n";
  } else if(tester[4] != "a") {
    circuit = false;
    cout << "Bracket 4 Incorrect\n";
  } else if(tester.returnRootData() != "b") {
    circuit = false;
    cout << "Final Root Incorrect\n";
  } else {
    cout << "Completed Pushing and Balanced\nProcessing\n";
  }

  // Manual Balance Check
  //tester.printPreOrder(tester.returnRoot());

  tester.pop_front();

  if(tester[0] != "d") {
    cout << "Pop_Front Failed\n";
    circuit = false;
  }
  
  tester.pop_back();

  if(tester.returnRootData() != "c") {
    cout << "Root incorrect after pop_back\n";
    circuit = false;
  }

  //tester.insert(tester.cbegin(), "z"); Ignore
  //tester.insert(tester.cbegin(), "q"); Ignore
  
  // Manual Balance Check
  //tester.printPreOrder(tester.returnRoot());

  OrderStat<string> testerCopy(tester);

  //cout << "\n";

  //testerCopy.printPreOrder(testerCopy.returnRoot());

  if(tester != testerCopy) {
    cout << "Equality Check after copy failed\n";
    circuit = false;
  } else {
    cout << "Completed Equality Check and simple pop\n";
  }

  //Check contents manually
  //tester.printPreOrder(tester.returnRoot());

  tester.insert(tester.cbegin(), "z");

  if(tester[0] != "z") {
    cout << "Insert at begin failed\n";
    circuit = false;
  }

  tester.insert(tester.cbegin()++, "p");

  // POSSIBLY TEST MORE WITH INSERT HERE

  //tester.printPreOrder(tester.returnRoot());

  tester.push_back("l");

  if(tester[5] != "l") {
    cout << "Failed push_back\n";
    circuit = false;
  }

  tester.erase(tester.cbegin());

  //tester.printPreOrder(tester.returnRoot());
  
  if(tester[0] != "z" || tester[4] != "l") {
    cout << tester[0];
    cout << tester[1];
    //cout << tester[2];
    cout << tester[3];
    cout << tester[4];    
cout << "Failed erase\n";
    circuit = false;
  }

  //tester.printPreOrder(tester.returnRoot());

  tester.clear();

  if(tester.size() != 0) {
    cout << "Size after clear failed\n";
    circuit = false;
  }

  tester.insert(tester.cbegin(), "a");

  if(tester.returnRootData() != "a" || tester[0] != "a") {
    cout << "Insert failed after clear\n";
    circuit = false;
  }

  if(circuit) {
    cout << "--- SIMPLE TEST PASSED ---\n";
  } else {
    cout << "--- SIMPLE TEST FAILED ---\n";
    circuit = true;
  }

  cout << "\n" << "\n";

  OrderStat<int> lst1;

  lst1.push_back(4);
  lst1.push_back(5);
  lst1.push_back(99);
  lst1.push_back(7);
  lst1.push_back(8);

  lst1.printPreOrder(lst1.returnRoot());

  OrderStat<int> lst2(lst1);
   lst2.insert(++++++lst2.begin(),98);
   lst2.printPreOrder(lst2.returnRoot());
   cout << "\n";
   cout << "LIST2 " << lst2[1] << " LIST2\n";
   if(lst2[0]!=4) { cout << "After insert lst2[0]." << endl; return false; }
   if(lst2[1]!=5) { cout << "After insert lst2[1]." << endl; return false; }
   if(lst2[2]!=99) { cout << "After insert lst2[2]." << endl; return false; }
   if(lst2[3]!=98) { cout << "After insert lst2[3]. " << lst2[3] << endl; return false; }
   if(lst2[4]!=7) { cout << "After insert lst2[4]." << endl; return false; }
   if(lst2[5]!=8) { cout << "After insert lst2[5]." << endl; return false; }

  lst2.clear();
/*
  for(int i = 0; i < 2000000; ++i) {
    lst2.push_back(i);
  }

  if(lst2.size() == 2000000) {
    cout << "You win.";
  } */
}
