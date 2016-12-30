#include <iostream>
#include "ArrayList.h"
#include <string>

using namespace std;

int main() {

  ArrayList<int> list;
  ArrayList<int> copyList;
//  copyList = list;

//  list.push_back(4);

/*  for(int a = 0; a < 10000; a++)
    list.push_back(a);

  for(int j = 0; j < list.size(); j++) {
    cout << list[j] << " ";
  }

  for(int a = 0; a < 10000; a++)
    list.pop_back();

  cout << (list.size() == 0) << "\n";

  cout << true << "\n";

  for(int a = 0; a < 10; a++)
    list.push_back(a);

  list.insert(5,5);

  for(int j = 0; j < list.size(); j++) {
    cout << list[j] << " ";
  }

  copyList = list;
  
  for(int j = 0; j < copyList.size(); j++) {
    cout << copyList[j] << " ";
  }

  copyList.remove(5);

  for(int j = 0; j < copyList.size(); ++j) {
    cout << copyList[j] << "\n";
  } */

/*  ArrayList<string> stringList;
  stringList.push_back("hello");
  stringList.push_back("whats up");
  stringList.push_back("turn up the base");
  stringList.push_back("to the next round");
  stringList.push_back("to the next base");
  stringList.push_back("turn the base up");

  for(int j = 0; j < stringList.size(); j++) {
    cout << stringList[j] << "\n";
  }

  stringList.clear();

  cout << (stringList.size() == 0) << " ";

  stringList.push_back("mic");
  stringList.push_back("this");
  stringList.push_back("mother");
  stringList.push_back("up");

  for(string i : stringList){
    cout << i << "  ";
  }

  ArrayList<int> intList;

  for(int a = 0; a < 20; a++) {
    intList.push_back(a);
  }

  for(int i : intList) {
    cout << i << "\n";
  } */

  ArrayList<int> removeList;

/*  removeList.push_back(3);
  removeList.push_back(7);
  removeList.push_back(9);
  removeList.push_back(2);
  removeList.push_back(4);

  removeList.remove(2);

  for(int i : removeList)
  cout << i << " ";

  cout << removeList.size() << " ";

  removeList.remove(3);

  for(int i : removeList)
  cout << i << " "; */

  for(int a = 0; a < 10; a++)
    removeList.push_back(a);

  cout << removeList.size() << "      ";

  removeList.remove(9);

  for(int i : removeList)
  cout << i << " "; 

}
