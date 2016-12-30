#ifndef FILEHASHMAP
#define FILEHASHMAP

#include<iostream>
#include<cstdio>
#include<string>

const unsigned char UNUSED = 255;
const unsigned char USED = 254;

template<typename K,typename V,typename Hash>
class FileHashMap {
    Hash hashFunction;
    // File name
    std::string fileName;
    // File pointer
    FILE* file;
    // Number of records stored
    unsigned storedItems;
    // Capacity of the file
    unsigned capacity;

    // Placed here to prevent copies.
    FileHashMap(const FileHashMap<K,V,Hash> &that);
    FileHashMap<K,V,Hash> &operator=(const FileHashMap<K,V,Hash> &that);

    // Helper functions recommended

    void writeSize() {
      std::fseek(file, 0, SEEK_SET);
      std::fwrite(&storedItems, sizeof(int), 1, file);
    }

    void writeCapacity() {
      std::fseek(file, sizeof(int), SEEK_SET);
      std::fwrite(&capacity, sizeof(int), 1, file);
    }

    void writeKey(std::pair<K,V> value_type, int location) {
      // std::cout << "LOCATION: " << location;
      std::fseek(file,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*location), SEEK_SET);
      std::fwrite(&USED, sizeof(char), 1, file);
      std::fwrite(&value_type.first, sizeof(K), 1, file);
      std::fwrite(&value_type.second, sizeof(V), 1, file);
    }

    unsigned char readChar(int location) const {
      unsigned char temp;
      std::fseek(file,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*location), SEEK_SET);
      std::fread(&temp, sizeof(char), 1, file);
      return temp;
    }

    std::pair<K,V> readPair(int location) const {
      std::pair<K,V> temp;
      std::fseek(file,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*location+sizeof(char)), SEEK_SET);
      std::fread(&temp.first, sizeof(K), 1, file);
      std::fread(&temp.second, sizeof(V), 1, file);
      return temp;
    }

    void writeUnusedSpace(int location) {
      std::fseek(file,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*location), SEEK_SET);
      std::fwrite(&UNUSED, sizeof(char), 1, file);
    }

    void writeStart() { // Make sure to reset capacity & storedItems when appropriate
      writeSize();
      writeCapacity();
      for(auto i = 0; i < capacity; ++i) {
        writeUnusedSpace(i);
      }
    }

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator {
        FILE *file;
        unsigned cap;
        unsigned loc;
      
        unsigned char readChar(int loc) const {
          unsigned char temp;
          std::fseek(file, (sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*loc), SEEK_SET);
          std::fread(&temp, sizeof(char), 1, file);
          return temp;
        }

        void advance() {
            // Code to move forward to the next used element after loc.
          while((readChar(loc) == UNUSED) && (loc < cap)) {
            loc += 1;
          }
        }

    public:
        const_iterator(FILE *f,unsigned c):file(f),cap(c),loc(0) {
            advance();
        }
        const_iterator(FILE *f,unsigned c,unsigned i):file(f),cap(c),loc(i) {}

        bool operator==(const const_iterator &i) const { return file==i.file && loc==i.loc; }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> operator*() const {
            K ktemp;
            V vtemp;

            std::fseek(file, (sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*loc+sizeof(char)), SEEK_SET);
            std::fread(&ktemp, sizeof(K), 1, file);
            //std::fseek(file, (sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*loc+sizeof(char)+sizeof(K)), SEEK_SET);
            std::fread(&vtemp, sizeof(V), 1, file);

            std::pair<K,V> p;
            p = std::make_pair(ktemp,vtemp);
            return p;
        }
        const_iterator &operator++() {
            ++loc;
            advance();
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        int iteratorLocation() {
          return loc;
        }
    };

    FileHashMap(const std::string &fname,const Hash &hf):hashFunction(hf),fileName(fname),file(fopen(fname.c_str(),"r+b")) {
        file = std::fopen(fname.c_str(), "rb+");
        if(file==nullptr) {
            // open with w+b and set up the file
          file = std::fopen(fname.c_str(), "wb+");
          storedItems = 0;
          capacity = 10;
          writeStart();
        } else {
            // read header information
          std::fread(&storedItems, sizeof(int), 1, file); //sizeof(int)?
          std::fread(&capacity, sizeof(int), 1, file);
        }
    }

    ~FileHashMap() {
        // close the file
      std::fclose(file);
    }

    bool empty() const {
      return (storedItems == 0);
    }

    unsigned size() const {
      return storedItems;
    }

    const_iterator find(const key_type& k) const {
      auto hFK = hashFunction(k) % capacity; // Same as bin, remove hFK from auto c = cbegin() + hFK if not working
      //for(int i = 0; i < capacity; i++) { //for(auto c = cbegin(); c != cend(); ++c)
        for(int i = 0; i < capacity; ++i) { 
          if(readChar(hFK) == UNUSED) {
          //std::cout << "CEND FROM FIRST READCHAR TEST" << "\n";
            return cend();
        }
        if(readPair(hFK).first == k) {
          return const_iterator(file, capacity, hFK);
        }
        hFK = (hFK + 1) % capacity;
        }
        return cend();
      }
/*
        K key = readPair(hFK).first;

        while(key != k) {
          hFK = (hFK + 1) % capacity;
          key = readPair(hFK).first;
          if(readChar(hFK) == UNUSED) {
            return cend();
          }
        }
        //std::cout << "FOUND AND RETURNED" << "\n";
        return const_iterator(file,capacity,hFK);
      } */
/*
        //hFK = (hFK + 1) % capacity;
        if(readPair(hFK).first == k) {
          //std::cout << "FOUND IN FIND" << "\n";
          return const_iterator(file, capacity, hFK);
        }

        hFK = (hFK + 1) % capacity;
      }
      //std::cout << "NEVER FOUND IN FIND AND RETURN CEND" << "\n";
      return cend();
    } */

    int count(const key_type& k) const {
      //auto hFK = hashFunction(k) % capacity;
      /*for(auto c = cbegin(); c != cend(); ++c) {
        if((*c).first == k) {
          return 1; //c
        }
      }
      return 0; //cend */

      auto found = find(k);
      if(found == cend()) {
        return 0;
      } else {
        return 1;
      }
    }

    std::pair<const_iterator,bool> insert(const value_type& val) {
   /*   auto temp = find(val.first);
      if(temp != end()) {
        return std::make_pair(temp, false);
      }

      int i = 0;
      int bin = (hashFunction(val.first)+i) % capacity;
      while(readChar(bin) == USED) {
        ++i;
        bin = (hashFunction(val.first) + i) % capacity;
      }

      writeKey(val, bin);
      ++storedItems;
      writeSize();
  
      return std::make_pair(const_iterator(file, capacity, bin), true);
    } */

      
      // write size and shit also
      if(storedItems > capacity / 2) {
        growTableAndRehash();
      }
      auto bin = hashFunction(val.first) % capacity;

      //std::cout << "BIN: " << bin;
      //std::cout << "\n";
      
      for(auto i = 0; i < capacity; ++i) {
        bin = bin % capacity;
        if(readChar(bin) == UNUSED) {
          writeKey(val,bin);
          ++storedItems;
          writeSize();
          return std::make_pair(const_iterator(file, capacity, bin), true);
        }
        else if(readPair(bin).first == val.first) {
          return std::make_pair(const_iterator(file, capacity, bin), false);
        }
        bin += 1;
        }
      }
        //std::cout << "HELLO ";
        //bin = bin % capacity;
        /*
        if((i == 0) || (i % 771 == 0)) {
          std::fseek(file,(sizeof(int)*2+(sizeof(char))*i), SEEK_SET);
          std::fwrite(&val.first, sizeof(K), 1, file);
          std::fwrite(&val.second, sizeof(V), 1, file);
        } */
       /*if(readChar(bin) == UNUSED) {
          //std::cout << "VENUS" << "\n";
          writeKey(val, bin);
          ++storedItems;
          writeSize();
          return std::make_pair(const_iterator(file, capacity, bin), true);
        }
        else if(readPair(bin).first == val.first) {
          //std::cout << "WHATS GOOD MILEY WHATS GOOD";
          //if(readPair(bin).first == val.first) {
            //std::cout << "I WILL ALWAYS LOVE YOU";
            return std::make_pair(const_iterator(file, capacity, bin), false);
          }
        bin = (bin + 1); // % capacity; // % capacity
      }
      //return std::make_pair(cend(), false); */
   // }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    void clear() {
      storedItems = 0;
      std::fclose(file);
      file = std::fopen(fileName.c_str(),"wb+");
      capacity = 10;
      writeStart(); /*
      storedItems = 0;
      //capacity = 10;
      writeStart(); */
    }

    const mapped_type operator[](const K &key) const {
      auto temp = find(key);
      return (*temp).second; 
    }

    const_iterator set(const value_type &val) {
      auto found = insert(val);
      if(!found.second){
        auto locForSet = (found.first).iteratorLocation();
        writeKey(val, locForSet);
        //++storedItems;
        //writeSize();
      }
      return found.first;
    }

    bool operator==(const FileHashMap<K,V,Hash>& rhs) const {
      if(size() != rhs.size()) {
        return false;
      }

      for(auto x = rhs.begin(); x != rhs.end(); ++x) {
        if((find((*x).first)) == end()) {
          //std::cout << "EQUALITY TEST WITHIN FUNCTION FAILED";
          //std::cout << "\n";
          return false;
        }
      }
      
      return true;

    /*  if(capacity != rhs.capacity) {
        return false;
      } */

      /*auto y = rhs.begin();

      for(auto x = begin(); x != end(); ++x) {
        if(((*x).first != (*y).first) || ((*x).second != (*y).second)) {
          return false;
        }
      ++y;
      }
      return true; */
    }

    bool operator!=(const FileHashMap<K,V,Hash>& rhs) const {
      return !(*this == rhs);
    }

    const_iterator begin() const { return const_iterator(file,capacity); }

    const_iterator end() const { return const_iterator(file,capacity,capacity); }

    const_iterator cbegin() const { return const_iterator(file,capacity); }

    const_iterator cend() const { return const_iterator(file,capacity,capacity); }

private:
    void growTableAndRehash() {
      FILE* tempFile; // = std::fopen((fileName + ".grow").c_str(), "wb+");
      std::string newname = fileName + ".grow";
      int tempCap = capacity * 2 + 1;

      tempFile = std::fopen(newname.c_str(),"wb+");

      std::fseek(tempFile, 0, SEEK_SET);

      std::fwrite(&storedItems, sizeof(int), 1, tempFile);
      std::fwrite(&tempCap, sizeof(int), 1, tempFile);      

      for(int i = 0; i < tempCap; ++i) {
        std::fseek(tempFile,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*i), SEEK_SET);
        std::fwrite(&UNUSED, sizeof(char), 1, tempFile);
      }

      unsigned char tempC = USED;

      for(auto c = begin(); c != end(); ++c) { //val : *this) {
        //std::cout << "GROWING" << "\n";
        auto cpr = *c;
        auto bin = hashFunction(cpr.first) % tempCap;//capacity
        //auto cpr = *c; 
        for(auto i = 0; i < capacity; ++i) { //capacity
          //std::cout << "DID WE MAKE IT HERE?" << "\n";
          //unsigned char temp;
          std::fseek(tempFile,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*bin), SEEK_SET);
          std::fread(&tempC, sizeof(char), 1, tempFile);
          if(tempC == UNUSED) {
            //std::cout<< "WE MADE IT" << "\n";
            //std::cout << "ACTUALLY WRITING VAL" << "\n";
            std::fseek(tempFile,(sizeof(int)*2+(sizeof(char)+sizeof(K)+sizeof(V))*bin), SEEK_SET);
            std::fwrite(&USED, sizeof(char), 1, tempFile);
            std::fwrite(&cpr.first, sizeof(K), 1, tempFile);
            std::fwrite(&cpr.second, sizeof(V), 1, tempFile);
            i = capacity;
          }
          bin = (bin + 1) % tempCap;
        }
      }
      std::fclose(file);
      std::fclose(tempFile);
      std::rename(newname.c_str(), fileName.c_str());
      file = std::fopen(fileName.c_str(), "rb+");
      capacity = tempCap;
    }
};

#endif
