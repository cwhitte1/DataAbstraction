#ifndef ARRAYLIST
#define ARRAYLIST

template<typename T>
class ArrayList {
  private:
    T* data;
    int length;
    int endList;
  public:
     
   // Types
    // value_type
    // iterator
    // const_iterator
    //  // General Methods
    class iterator {
    T* index;
    public:
    iterator(T *l):index(l) {}
    iterator():index(0) {}
    iterator(const iterator &i){
     index = i.index;
    } 
    T &operator*() {
      return *index;
    }
    bool operator==(const iterator &i) const {
      return (index == i.index);
    }
    bool operator!=(const iterator &i) const {
      return (index != i.index);
    }
    iterator &operator=(const iterator &i) {
       index = i.index;
       return *this;
    }    
    iterator &operator++() {
      index++;
      return *this;
    }
    iterator &operator--() {
      index--;
      return *this;
    }
    iterator operator++(int) {
      T* temp = index;
      index++;
      return temp;
    }
    iterator operator--(int) {
      T* temp = index;
      index++;
      return temp;
    }
    };   

    class const_iterator {
    T* index;
    public:
    const_iterator(T *l):index(l) {}
    const_iterator():index(0) {}
    const_iterator(const iterator &i){
      index = i.index;
    }
    const T &operator*() {
      return *index;
    }
    bool operator==(const const_iterator &i) const {
      return (index == i.index);
    }
    bool operator!=(const const_iterator &i) const {
      return (index != i.index);
    } 
    const_iterator &operator=(const iterator &i) {
      index = i.index;
      return *this;
    }
    const_iterator &operator++() {
      index++;
      return *this;
    }
    const_iterator &operator--() {
      index--;
      return *this;
    }
    const_iterator operator++(int) {
      T* temp = index;
      index++;
      return temp;
    }
    const_iterator operator--(int) {
       T* temp = index;
       index--;
       return temp;
    }
};

    ArrayList():data(new T[10]), length(10), endList(0) {}
    ArrayList(const ArrayList &that); // Not working
                                      
    ~ArrayList() {
      delete[] data;
    }
    void push_back(const T &t) {
      if(endList >= length) {
        T* temp = new T[length*2];
        for(int a = 0; a < endList; a++)
           temp[a] = data[a];

      delete[] data;
      data = temp;
      length = length * 2;
      }
      data[endList] = t;
      endList++;
    } // add to the end.

    void pop_back() {
      endList--;
    }                      // remove last element.
    int size() const { return endList; }
    void clear() { endList = 0; }
    

    void insert(const T &t,int index){
        if(endList >= length) {
        T* temp = new T[length*2];
        for(int a = 0; a < endList; ++a)
          temp[a] = data[a];

        delete[] data;
        data = temp;
        length = length * 2;
        }
        endList++;

    for(int g = endList - 1; g > index; g--) {
      data[g] = data[g - 1];
    }

    data[index] = t;

/*        T tempT = data[index];
        data[index] = t;
        for(int g = index + 1; g < endList; g++){
            T tempA = data[g];
            data[g] = tempT;
            tempT = tempA;
         } */
    }    // insert this element before the given index.
    const T &operator[](int index) const { return data[index]; } // get the element at index.
    T &operator[](int index){ return data[index]; }             // get the element at index.
    
    void remove(int index) {
       for(int i = index; i < endList i++) {
          data[i] = data[i + 1];
        }
        endList--;
    }               // remove the item at the given index.
    const ArrayList &operator=(const ArrayList<T> & otherArrayList);/*{
      delete[] data;
      data = new T[length];

      length = otherArrayList.length;
      endList = otherArrayList.endList;

      for(int a = 0; a < otherArrayList.endList; ++a) {
        data[a] = otherArrayList.data[a];
      }
      return *this;
    } */

    iterator begin() { return iterator(data); }
    const_iterator begin() const { return const_iterator(data); }
    iterator end() { return iterator(data + endList); }
    const_iterator end() const { return const_iterator(data + endList); }
    const_iterator cbegin() const { return const_iterator(data); }
    const_iterator cend() const { return const_iterator(data + endList); }

};

    template<typename T>
    ArrayList<T>::ArrayList(const ArrayList &that):data(new T[that.length]),length(that.length), endList(that.endList)
    {
    for(int a = 0; a < that.endList; ++a) {
      data[a] = that.data[a];
     }
    }

    template<typename T>
    const ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> & otherArrayList){
      delete[] data;
      data = new T[otherArrayList.length];

      length = otherArrayList.length;
      endList = otherArrayList.endList;
  
      for(int a = 0; a < otherArrayList.endList; ++a) {
        data[a] = otherArrayList.data[a];
      }
      return *this;
    }


#endif
