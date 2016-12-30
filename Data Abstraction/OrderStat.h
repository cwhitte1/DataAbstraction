#ifndef ORDERSTAT
#define ORDERSTAT

#include<iostream>

template<typename T>
class OrderStat {
    struct Node {
      Node *right;
      Node *left;
      Node *parent;
      int height; // HEIGHT USES THE LOGIC OF SIZE; IN THEORY, HEIGHT IS SIZE -- FIXED SIZE ERROR
      unsigned size;

      T data;

      Node(Node *r, Node *l, Node *p, T d, int h, int s) {
        right = r;
        left = l;
        parent = p;
        data = d;
        height = h;
        size = s;
      }
    };

    Node *root;

public:
    typedef T value_type;

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
        T &operator*() {
          return loc -> data;
        }
        Node* findSuccessor(Node* x) {
          if(x -> right != nullptr) {
            return OrderStat<T>::findMin(x -> right);
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
            return OrderStat<T>::findMax(x -> left);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> left) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        iterator &operator--() {
          //Node* temp = findPredecessor(loc);
          if(atEnd) {
            atEnd = false;
            return *this;
          }
          loc = findPredecessor(loc);
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
        Node* getNode() {
          return loc;
        }
        bool getBool() {
          return atEnd;
        }

    };

    class const_iterator {
      Node* loc;
      bool atEnd;
    public:
        friend class OrderStat<T>;
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
        const T &operator*() {
          return loc -> data;
        }
        Node* findSuccessor(Node* x) {
          if(x -> right != nullptr) {
            return OrderStat<T>::findMin(x -> right);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> right) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        const_iterator &operator++() {
          Node* temp = findSuccessor(loc); //mirror -- if gets freaky
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
            return OrderStat<T>::findMax(x -> left);
          }
          Node* y = x -> parent;
          while(y != nullptr && x == y -> left) {
            x = y;
            y = y -> parent;
          }
          return y;
        }
        const_iterator &operator--() {
          //Node* temp = findPredecessor(loc);
          if(atEnd) {
            atEnd = false;
            return *this;
          }
          loc = findPredecessor(loc);
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
        Node* getNode() {
          return loc;
        }
        bool getBool() {
          return atEnd;
        }
    };

    OrderStat() {
      root = nullptr;
    }

    Node* helpCopier(Node* x, Node* p) {
      Node* temp;
      if(x != nullptr) {
        temp = new Node(nullptr, nullptr, nullptr, x -> data, x -> height, x -> size);
        temp -> parent = p;
        temp -> left = helpCopier(x -> left, temp);
        temp -> right = helpCopier(x -> right, temp);
        return temp;
        //helpCopier(x -> left);
        //push_back(x -> data);
        //helpCopier(x -> right);
      } else return nullptr;
    }

    OrderStat(const OrderStat<T> &that) {
    /*  for(const T &d : that) {
        push_front(d);
      }
      root = that.root;*/
      root = nullptr;
      root = helpCopier(that.root, root);
    }

    ~OrderStat() {
      clear();
    }

    OrderStat &operator=(const OrderStat<T> &that) {
      clear();
      root = nullptr;
     root = helpCopier(that.root,root);
      return *this;
    }

    bool empty() const {
      return (root == nullptr);
    }

    unsigned size() const {
      return getHeight(root);
    }

    value_type &front() {
      return (findMin(root) -> data);
    }

    const value_type &front() const {
      return (findMin(root) -> data);
    }

    value_type &back() {
      return (findMax(root) -> data);
    }

    const value_type &back() const {
      return (findMax(root) -> data);
    }

    iterator insert(const_iterator position,const value_type& val) {
      iterator temp = iterator(position.loc, position.atEnd);
      if(position == cbegin()) {
        push_front(val);
        updateSize(cbegin().loc);
        balance(cbegin().loc);
      } else {
        position--;
        Node* found = position.loc -> right;
        position.loc -> right = new Node(found, nullptr, position.loc, val, 1, 1);
        if(found != nullptr) {
          found -> parent = position.loc -> right;
          updateHeight(found);
          balance(found);
        } else {
          updateHeight(position.loc -> right);  
          balance(position.loc -> right);
        }
      }
      temp--;
      return temp;
    }
      
/*
      Node* n = new Node(nullptr, nullptr, nullptr, val, 1, 0);
      if(position == begin()) {
        if(position.loc != nullptr) {
          Node* found = position.loc;
          found -> left = n;
          n -> parent = found;
      } else {
        root = n;
      }
    } else {
        Node* tmp = position.loc;
        Node* found = (--position).loc;
        if(! found->right){
          found->right = n;
          n->parent = found;
        }
      else{
        found = tmp;
        found->left = n;
        n->parent = found;
      }
    }
    updateHeight(n);
    updateSize(n);
    balance(n);
    return iterator(n, false);
    }
*/




    /*
      Node* z = new Node(nullptr, nullptr, nullptr, val, 0, 1);
      if(root == nullptr) {
        root = z;
      } else {
        if(position.loc -> left == nullptr && position != end()) {
          position.loc -> left = z;
          z -> parent = position.loc;
        } else {
          position--;
          position.loc -> right = z;
          z -> parent = position.loc;
        }
      }
      updateHeight(z);
      updateSize(z);
      balance(z);
      iterator temp = iterator(z, false);
      return temp;
    } */
      /*
      Node* x = root;
      iterator temp = iterator(position.loc, position.atEnd);
      if(position == cbegin()) {
        push_front(val);
        //getHeight(position.loc -> right);
        updateHeight(cbegin().loc);
        updateSize(cbegin().loc);
        balance(cbegin().loc);
        //return temp;
      } else {
        position--;
        Node* temp2 = position.loc -> right;
        position.loc -> right = new Node(temp2, nullptr, position.loc, val, 0, 1);
        if(temp2 != nullptr) {
          temp2 -> parent = position.loc -> right;
        }
        //getHeight(position.loc -> right);
        updateHeight(position.loc -> right);
        updateSize(position.loc -> right);
        balance(position.loc -> right);
      }
      --temp;
      return temp;
    }*/
    
    template <class InputIterator>
    void insert(const_iterator position,InputIterator first, InputIterator last) {
      for(auto iter = first; iter != last; ++iter) {
        position = insert(position, *iter);
        ++position;
      }
    }

    iterator find(const value_type& k) {
      Node* temp = root;
      while((temp != nullptr) && (k != (temp -> data))) {
        if(k < (temp -> data)) {
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

    const_iterator find(const value_type& k) const {
      Node* temp = root;
      while((temp != nullptr) && (k != (temp -> data))) {
        if(k < (temp -> data)) {
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

    iterator erase(const_iterator position) {
      Node* z = position.loc;
      if(z -> left == nullptr) {
        iterator temp = iterator(position.getNode(), position.getBool());
        ++temp;
        Node* ret = z -> right;
        transplant(z, z -> right);
        updateHeight(z);
        updateSize(z);
        delete z;
        balance(ret);
        //updateSize(findMax(ret)); //added
        //--elems;
        return temp;
      }
      else if(z -> right == nullptr) {
        iterator temp = iterator(position.getNode(), position.getBool());
        ++temp;
        Node* ret = z -> left;
        transplant(z, z -> left);
        delete z;
        updateHeight(findMin(ret));
        updateSize(findMin(ret));
        balance(ret);
        //updateSize(findMin(ret)); //added
        //--elems;
        return temp;
      } else {
        iterator temp = iterator(position.getNode(), position.getBool());
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
        updateSize(findMin(y -> right));
        balance(findMin(y -> right));
        //updateSize(findMin(y -> right)); //added
        //--elems;
        return temp;
      }
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

    void clearTree(Node* x) {
      if(x != nullptr) {
        if(x -> left != nullptr) {
          clearTree(x -> left);
        }
        if(x -> right != nullptr) {
          clearTree(x -> right);
        }
        delete x;
      }
    }

    void clear() {
      clearTree(root);
      //elems = 0;
      root = nullptr;
    }

    Node* selectNode(Node* t, int i) {
      if(t == nullptr) {
        return t;
      } else {
        int r = getSize(t -> left);
        if(i == r) {
          return t;
        } else if(i < r) {
          return selectNode(t -> left, i);
        } else {
          return selectNode(t -> right, i - (r+1));
        }
      }
      //std::cout << "error";
      //return t;
    }

    value_type &operator[](int index) {

     /* auto found = selectNode(root, index);
      if(found != nullptr) {
        return found -> data;
      }
      std::cout << "Error[]\n";
      //throw error;
    } */
      Node* rover = root;

      /*if(rover == nullptr) {
        std::cout << "error\n";
        return root -> data;
      } */

      while(rover != nullptr) {
        if(index < getHeight(rover -> left)) {
          rover = rover -> left;
        }
        else if(index > getHeight(rover -> left)) {
          index = index - getHeight(rover -> left) - 1;
          rover = rover -> right;
        }
        else return rover -> data;
      }

      std::cout << "error\n";
      return root -> data;
    }
    /*  auto temp = selectNode(root, index);
   //   if(temp != nullptr) {
        return temp -> data;
    //  } */
  //  }

    void push_front(const value_type& val) {
     // insert(begin(), val);
    //}
      if(root == nullptr) {
     root = new Node(nullptr, nullptr, nullptr, val, 1, 1);
        return;
      }
      Node* x = root;
      while(x -> left != nullptr) {
        x = x -> left;
      }
      x -> left = new Node(nullptr, nullptr, x, val, 1, 1); //orig 0 1
      updateHeight((x));
      updateSize((x));
      balance((x));
    }

    void pop_front() {
     // erase(begin());
   // } 
      erase(const_iterator(findMin(root),false));
      updateHeight(findMin(root));
      updateSize(findMin(root));
      balance(findMin(root));
      //updateSize(findMin(root));
    }

    void push_back(const value_type& val) {
    //  insert(end(), val);
   // } 
      if(root == nullptr) {
        root = new Node(nullptr, nullptr, nullptr, val, 1, 1);
        return;
      }
      Node* x = root;
      while(x -> right != nullptr) { //Added x != nullptr to prevent seqfault
        x = x -> right;
      }
      x -> right = new Node(nullptr, nullptr, x, val, 1, 1);
      updateHeight((x));
      updateSize((x));
      balance((x));
    }

    void pop_back() {
    //  erase(--end());
   // } /*
      erase(const_iterator(findMax(root), false));
      updateHeight(findMax(root));
      updateSize(findMax(root));
      balance(findMax(root));
      //updateSize(findMax(root));
    }

    bool operator==(const OrderStat<T>& rhs) const {
      if(size() != rhs.size()){
        return false;
      }      

      auto temp = cbegin();
      for(auto x = rhs.cbegin(); x != rhs.cend(); ++x) {
        if(x.loc->data != temp.loc->data) {
          return false;
        }
      temp++;
      }
      return true;
    }

    bool operator!=(const OrderStat<T>& rhs) const {
      return !(*this == rhs);
    }

    int getSize(Node* n) const {
      if(n == nullptr) {
        return 0; //-1;
      } else {
        return n -> size;
      }
    }

    void updateSize(Node* n) {
      while(n != nullptr) {
        n -> size = getSize(n -> left) + getSize(n -> right) + 1;
        n = n -> parent;
      }
    }

    void updateAll(Node* n) {
      Node* rover = n;
      while(rover != nullptr) {
        rover -> height = 1 + std::max(getHeight(rover -> left), getHeight(rover -> right));
        rover -> size = 1 + getSize(rover -> left) + getSize(rover -> right);

        rover = rover -> parent;
      }
    }

    int getHeight(Node* n) const {
      if(n == nullptr) {
        return 0; //-1
      } else {
        return n -> height;
      }
    }

    void updateHeight(Node* n) {
      while(n != nullptr) {
        n -> height = 1 + (getHeight(n -> left) + getHeight(n -> right)); //my sizes are too messed up
        n = n -> parent; // same logic as size, using one variable instead
      }
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
      if(x != nullptr) {
        while(x -> right != nullptr) {
          x = x -> right;
        }
      }
      return x;
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
            rover -> height = 1 + getHeight(rover -> left) + getHeight(rover -> right);   
            rover -> size = getSize(n -> left) + getSize(n -> right) + 1;
            updateHeight(rover -> parent -> left);
            //updateSize(rover -> parent -> left);
            //updateAll(rover -> parent -> left);
          } else {
            rightRotate(rover);
            //updateSize(findMin(rover));
            updateHeight(rover);
            //updateSize(rover);
            //updateAll(rover);
          }
        } else {
          if(getHeight(rover -> right -> right) < getHeight(rover -> right -> left)) {
            rightRotate(rover -> right);
            leftRotate(rover);
            rover -> height = 1 + getHeight(rover -> right) +  getHeight(rover -> left);
            rover -> size = getSize(n -> left) + getSize(n -> right) + 1;
            updateHeight(rover -> parent -> right);          
            //updateAll(rover -> parent -> right);
            //updateSize(rover -> parent -> right);
          } else {
            leftRotate(rover);
            updateHeight(rover);
            //updateSize(findMin(rover));
            //updateAll(rover);
            //updateSize(rover);
          }
        }
      }
    }

    Node* getroot() const {
      return root; // don't ask, don't tell
    }

    Node* returnRoot() const {
      return root;
    }

    T returnRootData() const {
      return root -> data;
    }

    /*Node* returnLeft(Node* x) const {
      return x -> left -> data;
    }

    Node* returnRight(Node* x) const {
      return x -> right -> data;
    } */

    void printPreOrder(Node* x) {
      if (x == nullptr) {
        std::cout << "NONE ";
        return;
      }
      std::cout << x -> data << " " << x -> height << " " << x -> size << "\n";
      std::cout << x -> data << "'s left : ";
      printPreOrder(x -> left);
      std::cout << x -> data << "'s right : ";
      printPreOrder(x -> right);
    }


    iterator begin() {// return iterator(findMin(root), false); }
      Node* ret = findMin(root);
      if(!ret) {
        return iterator(ret, true);
      } else {
        return iterator(ret, false);
      }
    }

    const_iterator begin() const { //return const_iterator(findMin(root), false); }
      Node* ret = findMin(root);
      if(!ret) {
        return const_iterator(ret, true);
      } else {
        return const_iterator(ret, false);
      }
    }

    iterator end() { //return iterator(findMax(root), true); }
      Node* ret = findMax(root);
      return iterator(ret, true);
    }

    const_iterator end() const { //return const_iterator(findMax(root), true); }
      Node* ret = findMax(root);
      return const_iterator(ret, true);
    }

    const_iterator cbegin() const { 
    /*  if(root == nullptr) {
        return const_iterator(root, true);
      } else {
        return const_iterator(findMin(root), false); 
      }
    } */
      Node* ret = findMin(root);
      if(!ret) {
        return const_iterator(ret, true);
      } else {
        return const_iterator(ret, false);
      }
    }

    const_iterator cend() const { //return const_iterator(findMax(root), true); }
      Node* ret = findMax(root);
      return const_iterator(ret, true);
    }

};

#endif
