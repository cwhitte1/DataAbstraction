#ifndef BSTMAP
#define BSTMAP

#include<iostream>

template<typename K,typename V>
class BSTMap {
    // TODO: Define your Node
  struct Node {
    Node *right;
    Node *left;
    Node *parent;
    
    //K key;
    //V value;

    std::pair<K,V> nodePair;

    Node(Node *r, Node *l, Node *p, K k, V v) {
      right = r;
      left = l;
      parent = p;
      //key = k;
      //value = v;

      nodePair = std::make_pair(k,v);
    }
  };
    // TODO: specify whatever member data you need.

  unsigned elems;
  Node *root;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
      Node* loc;
      bool atEnd;
    public:
        friend class const_iterator;
        iterator(Node* l, bool a):loc(l),atEnd(a){
          if(loc == nullptr) {
            atEnd = true;
          }
        }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const {
          return ((loc == i.loc) && (atEnd == i.atEnd));
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() {
          //return (std::make_pair(loc -> key, loc -> value));
          return loc -> nodePair;
        }
        Node* findSuccessor(Node* x) {
          if(x -> right != nullptr) {
            return BSTMap<K,V>::findMin(x -> right);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> right) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        iterator &operator++() {
          Node* temp = findSuccessor(loc);
          if(temp != nullptr) {
            atEnd = false;
            loc = temp;
          } else {
            atEnd = true;
          }
          return *this;
        }
        Node* findPredecessor(Node* x) {
          if(x -> left != nullptr) {
            return BSTMap<K,V>::findMax(x -> left);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> left) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        iterator &operator--() {
          Node* temp = findPredecessor(loc);
          if(atEnd) {
            atEnd = false;
            return *this;
          }
          loc = temp;
          return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
        // TODO: iterator data
      Node* loc;
      bool atEnd;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* l, bool a):loc(l),atEnd(a){
          if(loc == nullptr) {
            atEnd = true;
          }
        }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter):loc(iter.loc),atEnd(iter.atEnd){
          if(loc == nullptr) {
            atEnd = true;
          }
        }

        bool operator==(const const_iterator &i) const {
          return ((loc == i.loc) && (atEnd == i.atEnd));
        }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() { 
          //return (std::make_pair(loc -> key, loc -> value));
          return loc -> nodePair; 
        }
        Node* findSuccessor(Node* x) {
          if(x -> right != nullptr) {
            return BSTMap<K,V>::findMin(x -> right);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> right) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        const_iterator &operator++() {
            // TODO next largest element / right
          Node* temp = findSuccessor(loc);
          if(temp != nullptr) {
            atEnd = false;
            loc = temp;
          } else {
            atEnd = true;
          }
          return *this;
        }
        Node* findPredecessor(Node* x) {
          if(x -> left != nullptr) {
            return BSTMap<K,V>::findMax(x -> left);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> left) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        const_iterator &operator--() {
          Node* temp = findPredecessor(loc);
          if(atEnd) {
            atEnd = false;
            return *this;
          }
          loc = temp;
          return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };



    BSTMap() {
        // TODO
      root = nullptr;
      elems = 0;
    }
    ~BSTMap() {
      clear();
    }
    BSTMap(const BSTMap<K,V> &that) {
      root = nullptr;
      elems = 0;
      for(auto a = that.begin(); a != that.end(); ++a) {
        // std::cout << "Succ: " << a.loc -> nodePair.first << "\n";
        auto temp = a.loc -> nodePair;
        insert(temp);
      }
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
      clear();
      root = nullptr;
      elems = 0;
      for(auto a = that.begin(); a != that.end(); ++a) {
        auto temp = a.loc -> nodePair;
        insert(temp);
      }                       
    }

    bool empty() const { return (elems == 0); }

    unsigned size() const { return elems; }

    Node* search(Node* x, const key_type& k) const {
      if((x == nullptr) || (k == x -> nodePair.first)) { //key)) {
        return x;
      }
      
      /*
      if(x != nullptr) {
        std::cout << "nullptr succ\n";
        if(k == x -> nodePair.first) {
          std::cout << "key compare succ\n";
          return x;
        }
      } */

      if(k < x -> nodePair.first) { //if(k < x -> key) {
        return search(x -> left, k);
      } else {
        return search(x -> right, k);
      }
    }

    iterator find(const key_type& k) {
      Node* temp = search(root, k);
      if(temp == nullptr) {
        return end();
      } else {
      return iterator(temp, false);
      }
    }

    const_iterator find(const key_type& k) const {
      Node* temp = search(root, k);
      if(temp == nullptr) {
        return cend();
      } else {
      return const_iterator(temp, false);
      }
    }

    unsigned int count(const key_type& k) const {
      if(search(root, k) == nullptr) {
        return 0;
      } else {
        return 1;
      }
    }

    std::pair<iterator,bool> insert(const value_type& val) {
      if(count(val.first) == 1) {
        return std::make_pair(find(val.first), false);
      } 

      Node* y = nullptr;
      Node* x = root;
      Node* z = new Node(nullptr, nullptr, nullptr, val.first, val.second);
      while(x != nullptr) {
        y = x;
        if(z -> nodePair.first < x -> nodePair.first) { //if(z -> key < x -> key) {
          x = x -> left;
        } else {
          x = x -> right;
        }
      }
      z -> parent = y;
      if(y == nullptr) {
        root = z;
      } else if(z -> nodePair.first < y -> nodePair.first) { //else if (z -> key < y -> key) {
        y -> left = z;
      } else {
        y -> right = z;
      }

      ++elems;
      return std::make_pair(find(val.first), true);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position) {
      Node* temp = position.loc;
      iterator afterNode = find(temp -> nodePair.first);
      ++afterNode;

      if(count(temp -> nodePair.first) == 0) {
        return end();
      }

      erase(temp -> nodePair.first);
      return afterNode; // returning false correct?
    }

    unsigned int erase(const key_type& k) {
      if(count(k) == 0) {
        return 0;
      }
      Node* z = search(root,k);
      Node* temp = z;
      if(z -> left == nullptr) {
        transplant(z, z -> right);
      } else if(z -> right == nullptr) {
        transplant(z, z -> left);
      } else {
        Node* y = findMin(z -> right);
        if(y -> parent != z) {
          transplant(y, y -> right);
          y -> right = z -> right;
          y -> right -> parent = y;
        }
        transplant(z, y);
        y -> left = z -> left;
        y -> left -> parent = y;
      }
      delete temp;
      --elems;
      return 1;
    }

    void clearTree(Node* x) {
      if(x != nullptr) {
        if(x -> left != nullptr) {
          clearTree(x -> left);
        }
        //erase(x -> nodePair.first);
        if(x -> right != nullptr) {
          clearTree(x -> right);
        }
        erase(x -> nodePair.first);
      }
    }
    
    void clear() {
      clearTree(root);
      elems = 0;
      //root = nullptr; // Should I do this here?
    }

    mapped_type &operator[](const K &key) {
      if(count(key) == 1) {
        return (*find(key)).second;
      }
      std::pair<K,V> tempPair;
      tempPair.first = key;
      insert(tempPair);
      return (*find(key)).second;
    }

    static Node* findMin(Node* x) {
      if(x != nullptr) {
        while(x -> left != nullptr) {
          x = x -> left;
        }
      }
      return x;
    }

    static Node* findMax(Node* x) {
      if(x != nullptr) { // May be not correct, put in to stop from seg fault
        while(x -> right != nullptr) { // Causing seg fault?
          x = x -> right;
        }
      }
      return x;
    }

    void transplant(Node* u, Node* v) {
      if(u -> parent == nullptr) {
        root = v;
      } else if (u == u -> parent -> left) {
        u -> parent -> left = v;
      } else {
        u -> parent -> right = v;
      }
      if (v != nullptr) {
        v -> parent = u -> parent;
      }
    }

    void treePrint(Node* x) const {
      if(x != nullptr) {
        treePrint(x -> left);
        std::cout << x -> nodePair.first << " ";
        treePrint(x -> right);
      }
      std::cout << "\n";
    }

    Node* returnRoot() const {
      return root;
    }

    bool operator==(const BSTMap<K,V>& rhs) const {
      if(size() != rhs.size()) {
        return false;
      }

      for(auto x = begin(); x != end(); ++x) {
        auto temp = x.loc -> nodePair.first;
        if(rhs.count(temp) == 0) {
          return false;
        }
      }
      return true;
    }

    bool operator!=(const BSTMap<K,V>& rhs) const {
      return !(*this == rhs);
    }

    iterator begin() { return iterator(findMin(root), false); }

    const_iterator begin() const { return const_iterator(findMin(root), false); }

    iterator end() { return iterator(findMax(root), true); }

    const_iterator end() const { return const_iterator(findMax(root), true); }

    const_iterator cbegin() const { return const_iterator(findMin(root), false); }

    const_iterator cend() const { return const_iterator(findMax(root), true); }

};

#endif
