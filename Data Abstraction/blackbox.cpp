#include "BSTMap.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using std::map;
using std::make_pair;
using std::cout;
using std::vector;
using std::random_shuffle;
void runTests();
int main(int argc, char* argv[]){

	runTests();
	return 0;
}

void runTests(){
	int test_size = 1000000;
	cout << "\n--BSTMAP<INT,INT> TESTS BEGIN-------------------------------------\n\n";
    BSTMap<int, int> shark;
	map<int,int> dolphin;
	
	vector<int> randoms;
	for(int i = 0; i<test_size; ++i){
		randoms.push_back(i);
	}
	//cout << randoms[0] << "\n";
    random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";
	for(int i=0; i<test_size; ++i){
		//cout << "inserting " << randoms[i] << "\n";
	    shark.insert(make_pair(randoms[i],randoms[i]));
		dolphin.insert(make_pair(randoms[i],randoms[i]));
	}
	
	random_shuffle(randoms.begin(), randoms.end());
	
	for(int i=0; i<test_size; ++i){
		if(shark[randoms[i]]!=dolphin[randoms[i]]){
			cout << "insert failure: shark " << shark[randoms[i]] << " should be dolphin " << dolphin[randoms[i]] << "\n";
		}
	}	
	
	/*//shark.callInOrd();
	random_shuffle(randoms.begin(), randoms.end());
	for(int i = 0; i<test_size; ++i){
		//cout << "randoms " << randoms[i] << "\n";
		//shark.erase(randoms[i]);		
	}
	//shark.erase(0);
	
	*/
	cout << "\n--TESTS COMPLETE--------------------------------------------------\n";

}