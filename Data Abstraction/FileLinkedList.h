#ifndef FILEARRAYLIST
#define FILEARRAYLIST

#include<iostream>

template<typename T>
class FileLinkedList {
//      private:
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.
        // TODO - Private helper functions. (Maybe file IO with an index.)
        
        int length;
        FILE* file;
        int first; // for writeff?

       void writeSize() {
          std::fseek(file, 0, SEEK_SET);
          std::fwrite(&length, sizeof(int), 1, file);
        }

        void writeFirst() { //do I need a writeff?
          std::fseek(file, sizeof(int), SEEK_SET);
          std::fwrite(&first, sizeof(int), 1, file);
        }

        int readFirst() const {
          int temp;
          std::fseek(file, sizeof(int), SEEK_SET);
          std::fwrite(&temp, sizeof(int), 1, file);
          return temp;
        }

        int readPrev(int loc) const {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T)),SEEK_SET);
          int temp;
          std::fread(&temp, sizeof(int), 1, file);
          return temp;
        }

        int readNext(int loc) const {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T))+sizeof(int),SEEK_SET);
          int temp;
          std::fread(&temp, sizeof(int), 1, file);
          return temp;
        }

        T readData(int loc) const {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T))+2*sizeof(int),SEEK_SET);
          T temp;
          std::fread(&temp, sizeof(T), 1, file);
          return temp;
        }

        void writePrev(int loc, int nPrev) {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T)),SEEK_SET);
          std::fwrite(&nPrev, sizeof(int), 1, file); 
        }

        void writeNext(int loc, int nNext) {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T))+sizeof(int),SEEK_SET);
          std::fwrite(&nNext, sizeof(int), 1, file);
        }

        void writeData(int loc, T nData) {
          std::fseek(file, 2*sizeof(int)+loc*(2*sizeof(int)+sizeof(T))+2*sizeof(int),SEEK_SET);
          std::fwrite(&nData, sizeof(T), 1, file);
        }

        void writeNode(int index, int prev, int next, T data) {
          writePrev(index, prev);
          writeNext(index, next);
          writeData(index, data);
          //std::fseek(file, 2*sizeof(int)+index*(2*sizeof(int)+sizeof(T))+2*sizeof(int),SEEK_SET);
          //std::fwrite(&data, sizeof(int), 1, file); // Is it &data? 
        }

        int newNode() {
          if(first == -1) {
            return length+1;
          } else {
            int temp = first;
            first = readNext(first);
            writeFirst();
            return temp;
          }
        }
  
        void freeNode(int loc) {
          writeNext(loc, first);
          first = loc;
          writeFirst();
        } 
        
    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
              int index;
              FILE *iFile;
            public:
                const_iterator(int i,FILE *f):index(i), iFile(f) {}
                const_iterator(const const_iterator &i) {
                  index = i.index;
                  iFile = i.iFile;
                }
                T operator*() {
                  std::fseek(iFile, sizeof(int)*2+(sizeof(T) + sizeof(int)*2)*index + (sizeof(int))*2, SEEK_SET);
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
                  std::fseek(iFile, sizeof(int)*2+(sizeof(T) + sizeof(int)*2)*index + (sizeof(int)), SEEK_SET);
                  std::fread(&index, sizeof(int), 1, iFile);
                  return *this;
                }
                const_iterator &operator--() {
                  std::fseek(iFile, sizeof(int)*2+(sizeof(T) + sizeof(int)*2)*index, SEEK_SET);
                  std::fread(&index, sizeof(int), 1, iFile);
                  return *this;
                }
                const_iterator operator++(int) {
                  int temp;
                  temp = index;
                  std::fseek(iFile, sizeof(int)*2+(sizeof(T) + sizeof(int)*2)*index + (sizeof(int)), SEEK_SET);
                  std::fread(&index, sizeof(int), 1, iFile);
                  return const_iterator(temp, iFile);
                }
                const_iterator operator--(int) {
                  int temp;
                  temp = index;
                  std::fseek(iFile, sizeof(int)*2+(sizeof(T) + sizeof(int)*2)*index + (sizeof(int)), SEEK_SET);
                  std::fread(&index, sizeof(int), 1, iFile);
                  return const_iterator(temp, iFile);
                }

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname) {
          file = std::fopen(fname.c_str(), "rb+");
          if(file == nullptr) {
            file = std::fopen(fname.c_str(), "wb+");
            first = -1;
            length = 0;
            writeSize();
            writeFirst(); //writeFirst(); // Supposed to be writeFirst(-1); missing function/need redef
            //T nodeData; // Not initialized to anything, gives warning
            //writeNode(0, 0, 0, nodeData);
            writePrev(0,0);
            writeNext(0,0);
            //std::fseek(file, 2*sizeof(int)+index*(2*sizeof(int)+sizeof(T))+2*sizeof(int),SEEK_SET);
            //std::fwrite(&data, sizeof(int), 1, file);
          }else{
            std::fread(&length, sizeof(int), 1, file);
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
          file = std::fopen(fname.c_str(), "wb+");
          int tempA = 1;
          length = 0;
          first = -1;
          writeNext(0,1);
  //        writeSize();
          for(auto a = begin; a != end; ++a) {
             // push_back(*a);
            int tempB = tempA + 1;
            writeData(tempA, *a);
            writeNext(tempA, tempB);
            writePrev(tempA, tempA - 1);
            tempA = tempB;
            ++length;
          }
          writeNext(tempA - 1, 0);
          writePrev(0, length);
          writeSize();
          writeFirst();
        }

        ~FileLinkedList() {
          std::fclose(file);
        }

        void push_back(const T &t) {
          int loc = newNode();
          writeNode(loc, readPrev(0), 0, t);
          writeNext(readPrev(0), loc);
          writePrev(0, loc);
          ++length;
          writeSize();
        }

        void pop_back() {
          int victim = readPrev(0);
          writeNext(readPrev(readPrev(0)), 0);
          writePrev(0, readPrev(readPrev(0)));
          freeNode(victim);
          --length;
          writeSize();
        }        

        int size() const {
          return length;
        }

        void clear() {
          length = 0;
          writeSize();
          writeFirst(); //writeff(-1); must redefine
          //T nodeData;
          //writeNode(0,0,0, nodeData);
          writePrev(0,0);
          writeNext(0,0);
        }
        
        const_iterator insert(const_iterator position, const T &t) {
          int loc;
          if(first > 0) {
            writeData(first, t);
            writePrev(first, readPrev(position.index));
            int newF = readNext(first);
            writeNext(first, position.index);
            writeNext(readPrev(position.index), first);
            writePrev(position.index, first);
            first = newF;
          } else {
            loc = length + 1;
            writeData(length + 1, t);
            writePrev(length + 1, readPrev(position.index));
            writeNext(length + 1, position.index);
            writeNext(readPrev(position.index), length + 1);
            writePrev(position.index, length + 1);
          }  
 //         writeNode(position.index, readPrev(position.index), readNext(position.index), t);
          ++length;
          writeSize();
          writeFirst();
          return const_iterator(loc, file);
        }  
        
        T operator[](int index) const { 
          const_iterator temp = begin();
          for(int x = 0; x != index; ++x) {
            ++temp;
          }
          return readData(temp.index); 
        }
        
        const_iterator erase(const_iterator position) {
          int newF = position.index;
          int returnNext = readNext(newF);
          writeNext(readPrev(newF), readNext(newF));
          writePrev(readNext(newF), readNext(newF));
          writeNext(newF, first);
          first = newF;
          --length;
          writeSize();
          writeFirst();
          return const_iterator(returnNext, file);
        }
        
        void set(const T &value,int index) {
          const_iterator temp = begin();
          for(int a = 0; a != index; ++a) {
            temp++;
          }
          writeData(temp.index, value);
        }
       
        void set(const T &value,const_iterator position) {
          writeData(position.index, value);
        }

        const_iterator begin() { return const_iterator(readNext(0), file); }
        const_iterator begin() const { return const_iterator(readNext(0), file); }
        const_iterator end() { return const_iterator(0, file); }
        const_iterator end() const { return const_iterator(0,file); }
        const_iterator cbegin() const { return const_iterator(readNext(0), file); }
        const_iterator cend() const { return const_iterator(0, file); }
};

#endif
