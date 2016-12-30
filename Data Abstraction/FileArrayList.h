#ifndef FILEARRAYLIST
#define FILEARRAYLIST

#include<iostream>

template<typename T>
class FileArrayList {
        FileArrayList(const FileArrayList<T> &that) = delete;
        FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        // TODO - Your private data.
        
/*        T* data;
        int length;
        int endList; */

        FILE *file;
        int length;

        // TODO - Private helper functions. (Maybe file IO with an index.)
        
        void writeSize() {
          std::fseek(file, 0, SEEK_SET);
          std::fwrite(&length, sizeof(int), 1, file);
        }
        
        void writeTo(int i, const T t) {
          std::fseek(file, sizeof(T)*i + sizeof(int), SEEK_SET);
          std::fwrite(&t, sizeof(T), 1, file);
        }

        T findElem(int index) const {
          std::fseek(file, sizeof(T)*index + sizeof(int), SEEK_SET);
          T temp;
          std::fread(&temp, sizeof(T), 1, file);
          return temp;
        }
        
    public:
        typedef T value_type;

        class const_iterator {
                int index; // TODO - Your private data. not T*?
                FILE *iFile;
            public:
                const_iterator(int i,FILE *f):index(i), iFile(f) {}
                const_iterator(const const_iterator &i) {
                  index = i.index;
                  iFile = i.iFile;
                }
                T operator*() { // Should this not be const?
                  std::fseek(iFile, sizeof(T)*index + sizeof(int), SEEK_SET);
                   T temp;
                   std::fread(&temp, sizeof(T), 1, iFile);
                   return temp;         
                }
                bool operator==(const const_iterator &i) const {
                  return ((index == i.index) && (iFile == i.iFile));
                }
                bool operator!=(const const_iterator &i) const {
                  return ((index != i.index) || (iFile != i.iFile));
                }
                const_iterator &operator=(const const_iterator &i) {
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
                 int temp = index;
                 index++;
                 return const_iterator(temp, iFile);
               }
               const_iterator operator--(int) {
                 int temp = index;
                 index--;
                 return const_iterator(temp, iFile);
               }
/*
                T operator*();
                bool operator==(const const_iterator &i) const;
                bool operator!=(const const_iterator &i) const;
                const_iterator &operator=(const const_iterator &i);
                const_iterator &operator++();
                const_iterator &operator--();
                const_iterator operator++(int);
                const_iterator operator--(int);
*/
               friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname) {
          file = std::fopen(fname.c_str(), "rb+");
          if(file == nullptr) {
            file = std::fopen(fname.c_str(), "wb+");
            length = 0;
            writeSize();
          } else {
            std::fread(&length, sizeof(int), 1, file);
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
            file = std::fopen(fname.c_str(), "wb+");
           // if(file == nullptr) {
            length = 0;
            writeSize();
            for(auto a = begin; a != end; a++) {
              push_back(*a);
            }
        }
        
        ~FileArrayList() { std::fclose(file); }
        
        void push_back(const T &t) {
          writeTo(length,t);
          ++length;
          writeSize();
        }
  
        void pop_back() {
          --length;
          writeSize();
        }
        
        int size() const {
          return length;
        }
        
        void clear() {
          length = 0;
          writeSize();
        }        

        const_iterator insert(const_iterator position, const T &t) {
        for(int d = length; d > position.index; --d) { // d = 0?
          writeTo(d, findElem(d-1));
        }
        writeTo(position.index, t);
        ++length; //to I need to writeSize again?
        return const_iterator(position.index, file); //position
        }
        
        T operator[](int index) const {
          return findElem(index);
        }
        
        const_iterator erase(const_iterator position) { //haven't fixed insert yet, could be VERY wrong
        for(int b = position.index; b < length; ++b) {
        writeTo(b, findElem(b+1));
         }
        --length;
        return const_iterator(position.index, file);
        }
        
        void set(const T &value,int index) {
          writeTo(index, value);
        }

        const_iterator begin() { return const_iterator(0,file); }
        const_iterator begin() const { return const_iterator(0,file); }
        const_iterator end() { return const_iterator(length,file); }
        const_iterator end() const  { return const_iterator(length,file); }
        const_iterator cbegin() const { return const_iterator(0,file); }
        const_iterator cend() const { return const_iterator(length,file); }
};

#endif
