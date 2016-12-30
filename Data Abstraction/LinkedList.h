#ifndef LINKEDLIST
#define LINKEDLIST

#include<iostream>

template<typename T>
class LinkedList {
  struct Node {
    Node *prev;
    Node *next;
    T nodeData;
    Node() {
      prev = this;
      next = this;
    }
    Node(Node *previousNode, Node *nextNode,const T dataNode):nodeData(dataNode) {
      prev = previousNode;
      next = nextNode;
    }
    Node(const Node &that) {
      nodeData = that.nodeData;
      next = that.next;
      prev = that.prev;
    }
    bool operator==(const Node &n) const {
      return (next = n.next && prev == n.next);
    }
  };
  int lenList;
  Node sentinel;
  public:
    typedef T value_type;

    class iterator {
    private:
      Node *iRover;
    public:
      iterator(Node *l):iRover(l) {}
      iterator():iRover(nullptr) {} // maybe wrong
      iterator(const iterator &i) { iRover = i.iRover; }
      T &operator*() { return iRover -> nodeData;  }
      bool operator==(const iterator &i) const { return (iRover == i.iRover); }
      bool operator!=(const iterator &i) const { return (iRover != i.iRover); }
      iterator &operator=(const iterator &i) { iRover = i.iRover; return *this; }
      iterator &operator++() { iRover = iRover -> next; return *this; }
      iterator &operator--() { iRover = iRover -> prev; return *this; }
      iterator operator++(int) {
        iterator temp = *this;
        iRover = iRover -> next;
        return temp;
      }
      iterator operator--(int) {
        iterator temp = *this;        
        iRover = iRover -> prev;
        return temp;
      }
      friend class const_iterator;
      friend class LinkedList;
  };
  class const_iterator {
    private:
      const Node *cRover;
    public:
      // TODO - Constructors
     // TODO - Include a constructor that converts from a regular iterator.<- what does this mean?
     const_iterator(const Node *l):cRover(l) {}
     const_iterator(const iterator &i) { cRover = i.iRover; } //FINISH HIM
     const_iterator():cRover(nullptr) {}
     const_iterator(const const_iterator &i) { cRover = i.cRover; }
     const T &operator*() { return cRover -> nodeData; }
     bool operator==(const const_iterator &i) const { return (cRover == i.cRover); }
     bool operator!=(const const_iterator &i) const { return (cRover != i.cRover); }
     const_iterator &operator=(const const_iterator &i) { cRover = i.cRover; return *this; }
     const_iterator &operator++() { cRover = cRover -> next; return *this; }
     const_iterator &operator--() { cRover = cRover -> prev; return *this; }
     const_iterator operator++(int) {
        const_iterator temp = *this;
        cRover = cRover -> next;
        return temp;
     }
     const_iterator operator--(int) {
        const_iterator temp = *this;
        cRover = cRover -> prev;
        return temp;
     }
};

// General Methods

LinkedList():lenList(0) {
  sentinel.prev = &sentinel;
  sentinel.next = &sentinel;
}

LinkedList(const LinkedList &that) {
  for(const T &d : that) {
    push_back(d);
  }
  lenList = that.lenList;
}

LinkedList &operator=(const LinkedList &al) {
  clear();
  for(const T &d : al) {
    push_back(d);
  }
  lenList = al.lenList;
  return *this;
}

~LinkedList() {
  clear();
}

void push_back(const T &t) {           // add to the end.
  Node *temp = new Node(sentinel.prev, &sentinel, t);
  sentinel.prev -> next = temp;
  sentinel.prev = temp;
  ++lenList;
}

void pop_back() {                      // remove last element. CHANGE
  Node *temp = sentinel.prev;
  sentinel.prev -> prev -> next = &sentinel;
  sentinel.prev = sentinel.prev -> prev;
  delete temp;
  --lenList;
}

int size() const { return lenList; }

void clear() {
for(Node *rover = sentinel.next; rover != &sentinel;) {
  Node *temp = rover -> next;
  delete rover;
  rover = temp;
}
sentinel.prev = &sentinel;
sentinel.next = &sentinel;
lenList = 0;
}

iterator insert(iterator position,const T &t) {    // insert this element before the given index.
  Node *temp = new Node(position.iRover -> prev, position.iRover, t);
  position.iRover -> prev = temp;
  temp -> prev -> next = temp;
  ++lenList;
  return iterator(temp);
}

const T &operator[](int index) const {             // get the element at index.
   const Node *rov = sentinel.next;
    for(int a = 0; a < index; ++a) {
      rov = rov -> next;
    }
    return rov -> nodeData;
}

T &operator[](int index) {                         // get the element at index.
    Node *rov = sentinel.next;
    for(int a = 0; a < index; ++a) {
      rov = rov -> next;
    }
    return rov -> nodeData;
}

iterator erase(iterator position) {               // remove the item at the given index.
  iterator temp = position;
  position.iRover -> prev -> next = position.iRover -> next;
  position.iRover -> next -> prev = position.iRover -> prev;
  delete position.iRover;
  --lenList;
  return ++temp;
}

iterator begin() { return iterator(sentinel.next); } 
const_iterator begin() const { return const_iterator(sentinel.next); }
iterator end() { return iterator(&sentinel); }
const_iterator end() const { return const_iterator(&sentinel); }
const_iterator cbegin() const { return const_iterator(sentinel.next); }
const_iterator cend() const { return const_iterator(&sentinel); }
};

#endif
