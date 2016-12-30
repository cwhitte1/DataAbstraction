#include<iostream>
#include "Stack.h"

using namespace std;

template<typename T>
class ArrayStack: public Stack <T> {
private:
	T* data;
	int size;
	int top;
public:
	~ArrayStack() {
		delete[] data;
	}

	ArrayStack():data(new T[10]), size(10), top(0) {}

	ArrayStack(const ArrayStack<T> & otherArrayStack) {
//		data = NULL;
//		delete[] data;
		size = otherArrayStack.size;
		top = otherArrayStack.top;

		data = new T[size];

		for (int a = 0; a < top; a++)
			data[a] = otherArrayStack.data[a];
	}

	ArrayStack<T> operator=(const ArrayStack<T> & otherArrayStack){
		delete[] data;
		size = otherArrayStack.size;
		top = otherArrayStack.top;

		data = new T[size];

		for (int a = 0; a < top; a++)
			data[a] = otherArrayStack.data[a];
		return *this;
 }
	
	void push(const T &t) override {
	if(top >= size) {
		T* temp = new T[size*2];
		for(int a = 0; a < top; a++)
			temp[a] = data[a];
		
		delete[] data;
		data = temp;
		size = size * 2;
		}

		data[top] = t;
		top++;
	}

	bool isEmpty() const override{
		return(top == 0);
	}

	T peek() const override {
		return data[top - 1];
	}

	 T pop() override {
		if(!isEmpty()){
			T ret = data[top-1];
			--top;
		return ret;
		}
	}
};	
