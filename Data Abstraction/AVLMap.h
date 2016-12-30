#ifndef AVLMAP
#define AVLMAP

#include<iostream>

template<typename K,typename V>
class AVLMap {
  struct Node {
    Node *right;
    Node *left;
    Node *parent;
    int height;

    std::pair<K,V> nodePair;

    Node(Node *r, Node *l, Node *p, K k, V v, int h) {
      right = r;
      left = l;
      parent = p;
      nodePair = std::make_pair(k,v);
      height = h;
    }
  };

  unsigned elems;
  Node *root;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
      Node* loc;
      bool atEnd;
    public:
        friend class const_iterator;
        iterator(Node* l, bool a):loc(l),atEnd(a){
          if(loc == nullptr) {
            atEnd = true;
          }
        }

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
            return AVLMap<K,V>::findMin(x -> right);
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
            return AVLMap<K,V>::findMax(x -> left);
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
      Node* loc;
      bool atEnd;
    public:
        friend class AVLMap<K,V>;
        const_iterator(Node* l, bool a):loc(l),atEnd(a){
          if(loc == nullptr) {
            atEnd = true;
          }
        }
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
          return loc -> nodePair; 
        }
        Node* findSuccessor(Node* x) {
          if(x -> right != nullptr) {
            return AVLMap<K,V>::findMin(x -> right);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> right) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        const_iterator &operator++() {
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
            return AVLMap<K,V>::findMax(x -> left);
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

    AVLMap() {
      root = nullptr;
      elems = 0;
    }

    ~AVLMap() {
      clear();
    }

    void helpCopier(Node *x) {
      if(x != nullptr) {
        insert(x -> nodePair);
        helpCopier(x -> left);
        helpCopier(x -> right);
      }
    }

    AVLMap(const AVLMap<K,V> &that) {
      root = nullptr;
      elems = 0;
      helpCopier(that.root);
    }

    AVLMap &operator=(const AVLMap<K,V> &that) {
      clear();
      root = nullptr;
      elems = 0;
      helpCopier(that.root);
      return *this;                       
    }

    bool empty() const { return (elems == 0); }

    unsigned size() const { return elems; }

    Node* search(Node* x, const key_type& k) const {
      if((x == nullptr) || (k == x -> nodePair.first)){ 
        return x;
      }
      
      if(k < x -> nodePair.first) {
        return search(x -> left, k);
      } else {
        return search(x -> right, k);
      }
    }

    iterator find(const key_type& k) {
      Node* temp = root;
      while((temp != nullptr) && (k != (temp -> nodePair).first)) {
        if(k < (temp -> nodePair).first) {
          temp = temp -> left;
        } else {
          temp = temp -> right;
        }
      }
      if(temp == nullptr) {
        return end();
      } else {
        return iterator(temp, false);
      }
   }
    

    /*  Node* temp = search(root, k);
      if(temp == nullptr) {
        return end();
      } else {
      return iterator(temp, false);
      } */
  

    const_iterator find(const key_type& k) const {
      Node* temp = root;
      while((temp != nullptr) && (k != (temp -> nodePair).first)) {
        if(k < (temp -> nodePair).first) {
          temp = temp -> left;
        } else {
          temp = temp -> right;
        }
      }
      if(temp == nullptr) {
        return cend();
      } else {
        return const_iterator(temp, false);
      }
    }

     /* Node* temp = search(root, k);
      if(temp == nullptr) {
        return cend();
      } else {
      return const_iterator(temp, false);
      }
    } */

    unsigned int count(const key_type& k) const {
      if(find(k) == end()) {
        return 0;
      } else {
        return 1;
      }
    }

    std::pair<iterator,bool> insert(const value_type& val) {
      

      Node* y = nullptr;
      Node* x = root;
      
      while(x != nullptr) {
        y = x;
        if(x -> nodePair.first == val.first) {
          return std::make_pair(iterator(x, false), false);
        }
        if(val.first < x -> nodePair.first) {
          x = x -> left;
        } else {
          x = x -> right;
        }
      }
      Node* z = new Node(nullptr, nullptr, nullptr, val.first, val.second, 1);
      z -> parent = y;
      if(y == nullptr) {
        root = z;
      } else if(z -> nodePair.first < y -> nodePair.first) {
        y -> left = z;
      } else {
        y -> right = z;
      }

      updateHeight(z);
      balance(z);
      ++elems;
      return std::make_pair(iterator(z, false), true);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position) {
      Node* z = position.loc;
      if(z -> left == nullptr) {
        iterator temp = find((z -> nodePair).first);
        ++temp;
        Node* ret = z -> right;
        transplant(z, z -> right);
        delete z;
        updateHeight(findMax(ret));
        balance(ret);
        --elems;
        return temp;
      }
      else if(z -> right == nullptr) {
        iterator temp = find((z -> nodePair).first);
        ++temp;
        Node* ret = z -> left;
        transplant(z, z -> left);
        delete z;
        updateHeight(findMin(ret));
        balance(ret);
        --elems;
        return temp;
      } else {
        iterator temp = find((z -> nodePair).first);
        ++temp;
        Node* y = findMin(z -> right);
        if(y -> parent != z) {
          transplant(y, y -> right);
          y -> right = z -> right;
          y -> right -> parent = y;
        }
        transplant(z,y);
        y -> left = z -> left;
        y -> left -> parent = y;
        delete z;
        updateHeight(findMin(y -> right));
        balance(findMin(y -> right));
        --elems;
        return temp;
      }
   }
  



    /*  Node* temp = position.loc;
      iterator afterNode = find(temp -> nodePair.first);
      ++afterNode;

      if(count(temp -> nodePair.first) == 0) {
        return end();
      }

      erase(temp -> nodePair.first);
      return afterNode;
    } */

    unsigned int erase(const key_type& k) {
      auto iter = find(k);
      if(iter == end()) {
        return 0;
      } else {
        erase(iter);
        return 1;
      }
    }







/*      if(count(k) == 0) {
        return 0;
      }
      Node* z = search(root,k);
      Node* temp = z;
      if(z -> left == nullptr) {
        transplant(z, z -> right);
        updateHeight(findMax(z -> right));
        balance(z -> right);
      } else if(z -> right == nullptr) {
        transplant(z, z -> left);
        updateHeight(findMin(z -> left));
        balance(z -> left);
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
        updateHeight(findMin(y -> right));
        balance(findMin(y -> right));
      }
      delete temp;
      --elems;
      return 1;
    } */

    void clearTree(Node* x) {
      if(x != nullptr) {
        if(x -> left != nullptr) {
          clearTree(x -> left);
        }
        if(x -> right != nullptr) {
          clearTree(x -> right);
        }
        delete x; //erase(x -> nodePair.first);
      }
    }
    
    void clear() {
      clearTree(root);
      elems = 0;
      root = nullptr;
    }

    mapped_type &operator[](const K &key) {
      auto ret = find(key);
      if(ret != end()) {
        return (*ret).second;
      }
      std::pair <K,V> p;
      p.first = key;
      insert(p);
      return (*find(key)).second;
    }
      



    /*  if(count(key) == 1) {
        return (*find(key)).second;
      }
      std::pair<K,V> tempPair;
      tempPair.first = key;
      insert(tempPair);
      return (*find(key)).second;
    } */

    static Node* findMin(Node* x) {
      if(x != nullptr) {
        while(x -> left != nullptr) {
          x = x -> left;
        }
      }
      return x;
    }

    static Node* findMax(Node* x) {
      if(x != nullptr) {
        while(x -> right != nullptr) {
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

    void leftRotate(Node* x) {
      Node* pivot = x -> right;
      transplant(x, pivot);
      x -> right = pivot -> left;
      if(pivot -> left != nullptr) {
        pivot -> left -> parent = x;
      }
      pivot -> left = x;
      x -> parent = pivot;

    }

    void rightRotate(Node* x) {
      Node* pivot = x -> left;
      transplant(x, pivot);
      x -> left = pivot -> right;
      if(pivot -> right != nullptr) {
        pivot -> right -> parent = x;
      }
      pivot -> right = x;
      x -> parent = pivot;
    }

    void balance(Node* n) {
      Node* rover = n;
      while((rover != nullptr) && (std::abs(getHeight(rover -> right) - getHeight(rover -> left)) < 2)) {
        rover = rover -> parent;
      }
      if(rover != nullptr) {
        if(getHeight(rover -> left) > getHeight(rover -> right)) {
          if(getHeight(rover -> left -> left) < getHeight(rover -> left -> right)) {
            leftRotate(rover -> left);
            rightRotate(rover);
            rover -> height = 1 + std::max(getHeight(rover -> left), getHeight(rover -> right));
            updateHeight(rover -> parent -> left);
          } else {
            rightRotate(rover);
            updateHeight(rover);
          }
        } else {
          if(getHeight(rover -> right -> right) < getHeight(rover -> right -> left)) {
            rightRotate(rover -> right);
            leftRotate(rover);
            rover -> height = 1 + std::max(getHeight(rover -> right), getHeight(rover -> left));
            updateHeight(rover -> parent -> right);
          } else {
            leftRotate(rover);
            updateHeight(rover);
          }
        }
      }
    }

    int getHeight(Node* n) {
      if(n == nullptr) {
        return 0; //-1;
      } else {
        return n -> height;
      }
    }

    void updateHeight(Node* n) {
      while(n != nullptr) {
        n -> height = 1 + (std::max (getHeight(n -> left), getHeight(n -> right)));
        n = n -> parent;
      }
    }
      /*
      if(n != nullptr) {
        int hr = getHeight(n -> right);
        int hl = getHeight(n -> left);
        int maxHeight = -1;
        if(hr > hl) {
          maxHeight = hr + 1;
        } else {
          maxHeight = hl + 1;
        }      
        n -> height = maxHeight;
        updateHeight(n -> parent);
      } */
    //}

    void treePrint(Node* x) const {
      if(x != nullptr) {
        //std:: cout << getHeight(x);
        treePrint(x -> left);
        std::cout << x -> nodePair.first << " ";
        treePrint(x -> right);
      }
      std::cout << "\n";
    }

    Node* returnRoot() const {
      return root;
    }

    bool operator==(const AVLMap<K,V>& rhs) const {
      if(size() != rhs.size()) {
        return false;
      }

      for(auto x = rhs.begin(); x != rhs.end(); ++x) {
        auto temp = find((*x).first); //.loc -> nodePair.first;
        if(temp == end() || (*temp).second != (*x).second){  //rhs.count(temp) == 0) {
          return false;
        }
      }
      return true;
    }

    bool operator!=(const AVLMap<K,V>& rhs) const {
      return !(*this == rhs);
    }

    void printPreOrder(Node* x) {
      if (x == nullptr) {
        std::cout << "NONE ";
        return;
      }
      //std::cout << x -> nodePair.first << "'s height : ";
      //std::cout << getHeight(x) << "| ";
      std::cout << x -> nodePair.first << "\n";
      std::cout << x -> nodePair.first << "'s left : ";
      printPreOrder(x -> left);
      std::cout << x -> nodePair.first << "'s right : ";
      printPreOrder(x -> right);
    }

    iterator begin() { return iterator(findMin(root), false); }

    const_iterator begin() const { return const_iterator(findMin(root), false); }

    iterator end() { return iterator(findMax(root), true); }

    const_iterator end() const { return const_iterator(findMax(root), true); }

    const_iterator cbegin() const { return const_iterator(findMin(root), false); }

    const_iterator cend() const { return const_iterator(findMax(root), true); }

};

#endif
