#include <iostream>
#include "ArrayQueue.h"
#include <string>

using namespace std;

int main() {
	ArrayQueue<int> queue;

	for(int a = 0; a < 10000; a++)
	queue.enqueue(a);
	
	while(!queue.isEmpty()){
	cout << queue.peek() << "\n";
	queue.dequeue();
	}

	for(int a = 0; a < 10; a++)
	queue.enqueue(a);

	ArrayQueue<int> copy{queue};

	while(!copy.isEmpty()) {
		cout << copy.peek() << " ";
		copy.dequeue();
	}

	std:ArrayQueue<std::string> stringQueue;
	stringQueue.enqueue("Come");
	stringQueue.enqueue("Outside");
	stringQueue.enqueue("F");
	stringQueue.enqueue("It");
	stringQueue.enqueue("In");
	stringQueue.enqueue("The");
	stringQueue.enqueue("Benz");

	while(!stringQueue.isEmpty()) {
		cout << stringQueue.peek() << "\n";
		stringQueue.dequeue();
	}

/*	ArrayQueue<char> charQueue;

	charQueue.enqueue('c');
	charQueue.enqueue('b');
	charQueue.enqueue('a');

	while(!stringQueue.isEmpty()) {
		cout << charQueue.peek() << "\n";
		charQueue.dequeue();
	}*/
}
