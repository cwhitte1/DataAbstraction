#include <iostream>
#include "HashMap.h"
#include <string>
#include <functional>
#include <utility>

using std::pair;
using std::string;
using std::cout;


int main() {
  std::hash<int> hf;
  HashMap<int, int, std::function<int(int)>> hm(hf);

  hm.insert(std::make_pair(4,6));

  hm.printHash();

  cout << "\n What is at 4 maybe?" << hm[4];

//  cout << " \n What is happening at 19 tho?" << hm[19] << "\n";

  hm[19] = 666;

  hm.printHash();

  hm.erase(19);

  cout << "\n";

  hm.printHash();

/*  cout<<hm.insert(std::make_pair(4,6)).second;

  cout << hm.count(4);

  //cout << hm[4,666];

  hm.printHash();

  cout << hm.empty() << " :Is empty\n";

  cout << hm.size() << " :Size\n";

  return 0; */
  /*
  hm.insert(std::make_pair(5,78));

  cout << "\n";

  hm.printHash();

  hm.clear();

  cout << "\n";

  hm.printHash();

  for(int a = 0; a < 10000; ++a) {
    hm.insert(std::make_pair(a,a));
  }

  hm.printHash(); */

  //cout << hm.find(std::make_pair(///////);

  std::hash<int> hfS;
  HashMap<int, string, std::function<int(int)>> hmS(hfS);

  hmS.insert(std::make_pair(4,"hey"));
  hmS.insert(std::make_pair(4,"wassup"));
  hmS.insert(std::make_pair(5,"heyO"));
  hmS.insert(std::make_pair(6,"heyA"));
  hmS.insert(std::make_pair(7,"heySexy"));
  hmS.insert(std::make_pair(99,"heyMarcus"));
  hmS.insert(std::make_pair(1,"heySexyBOIIII"));
  hmS.insert(std::make_pair(2,"heywassuphello"));

  hmS.printHash();

//  for(auto x: hmS) {
//    hmS.erase(x);
//  }

  std::hash<int> hfSS;
  HashMap<int, string, std::function<int(int)>> hmSS(hfSS);


  hmSS.insert(std::make_pair(4,"hey"));
  hmSS.insert(std::make_pair(4,"wassup"));
  hmSS.insert(std::make_pair(5,"heyO"));
  hmSS.insert(std::make_pair(6,"heyA"));
  hmSS.insert(std::make_pair(7,"heySexy"));
  hmSS.insert(std::make_pair(99,"heyMarcus"));
  hmSS.insert(std::make_pair(1,"heySexyBOIIII"));
  hmSS.insert(std::make_pair(2,"heywassuphello"));

  hmSS.printHash();

  cout << "\n";

  if(hmS == hmSS) {
    cout << "THEY EQUAL PRAISE";
  }

  hmSS.insert(std::make_pair(3,"yesdaddyimabiggirlnow"));

  cout << "\n";

  if(hmS != hmSS) {
    cout << "THEY AINT EQUAL PRAISE";
  }

  cout << "\n";

   
}
