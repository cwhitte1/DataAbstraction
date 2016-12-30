#include <iostream>
#include "ArrayStack.h"
#include <string>
using namespace std;

int main() {
	ArrayStack<int> stack;

	stack.push(3);
	stack.push(7);
	stack.push(24);
	cout << stack.peek() << "\n";
	stack.pop();
	cout << stack.peek() << "\n";
	for(int a = 0; a < 100; a++)
	stack.push(a);

	ArrayStack<int> copy{stack};

	while(!stack.isEmpty()) {
		cout << stack.peek() << " ";
		stack.pop();
	}

	cout << copy.peek() << "\n";

	for(int a = 0; a < 1005; a++)
	stack.push(a);

	while(!stack.isEmpty()) {
		cout << stack.peek() << " ";
		stack.pop();
	}

	ArrayStack<char> charstack;
	charstack.push('a');
	charstack.push('b');
	charstack.push('c');

	while(!charstack.isEmpty()) {
		cout << charstack.peek() << "\n ";
		charstack.pop();
	}

	std:ArrayStack<std::string> stringStack;
	stringStack.push("Hey");
	stringStack.push("What's Up?");
	stringStack.push("Hello.");
	stringStack.push("Yara");
	stringStack.pop();
	stringStack.push("Emily");

//	while(!stringStack.isEmpty()){
//		cout << stringStack.pee
	
	while(!stringStack.isEmpty()){
		cout << stringStack.peek() << "\n";
		stringStack.pop();
	}

	stack.push(10000);
	stack.push(66666);
	stack.push(33333);
	stack.push(11111);

	cout << "is this fucking working ucnts";

	ArrayStack<int> copyStack = stack;
	
	while(!copyStack.isEmpty()) {
		cout << copyStack.peek() << "\n";
		copyStack.pop(); 
}	
}
