#include<iostream>
#include "Queue.h"

using namespace std;

template<typename T>
class ArrayQueue: public Queue <T> {
private:
	T* data;
	int head;
	int tail;
//	int len;
	int size;
public:
	~ArrayQueue() {
		delete[] data;
	}

	ArrayQueue():data(new T[10]), head(0), tail(0), size(10) {}

	ArrayQueue(const ArrayQueue<T> & otherArrayQueue) {
		data = new T[otherArrayQueue.size];

		head = otherArrayQueue.head;
		tail = otherArrayQueue.tail;
		size = otherArrayQueue.size;

//		data = new T[size];

		for (int a = 0; a < size; a++)
			data[a] = otherArrayQueue.data[a];
	}

	ArrayQueue<T> operator=(const ArrayQueue<T> & otherArrayQueue){
		head = otherArrayQueue.head;
		tail = otherArrayQueue.tail;
		size = otherArrayQueue.size;

		data = new T[otherArrayQueue.size];

		for (int a = 0; a < otherArrayQueue.size; a++)
			data[a] = otherArrayQueue.data[a];
//		return *this;
	}

	void enqueue(const T &t) override {
		if((tail+1)%size==head) {
			T* temp = new T[size*2];
			for(int a = 0; a < size - 1; a++) temp[a] = data[(a+head)%size];
		delete[] data;
		head = 0;
		tail = size - 1;
		data = temp;
		size = size * 2;
	}

	data[tail] = t;
	tail = (tail+1)%size;
	}

/*	if(head == len) {
		T* temp = new T[len*2];
		for(int a = 0; a < len; a++)
			temp[a] = data[(head + a) % len];
		data = temp;
		head = 0;
		}
	data[(head + len) % len] = t;
	len++;	
	}*/

	T dequeue() override{
		T temp = data[head];
		head = (head + 1) % size;
		return temp;
	}

	T peek() const override{
		return data[head];
	}

	bool isEmpty() const override{
		return (head == tail);
	}
};
