#ifndef HEAPSORT
#define HEAPSORT

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
void maxHeapify(const T& a, int i, int n) {
  int b;
  auto temp = a[i];

  b = 2 * i;

  while(b <= n) {
    if(b < n && a[b+1] > a[b]) {
      b = b + 1;
    }
    if (temp > a[b]) {
      return;
    } else if (temp <= a[b]) {
      a[b/2] = a[b];
      b = 2 * b;
    }
  }

  a[b/2] = temp;
  return;
}


template<typename T>
void heapsort(T begin, T end) {
  using D = typename std::iterator_traits<T>::value_type;
  //friend void maxHeapify(const T& a, int i, int n);

  std::vector<D> data(begin, end);

  auto n = data.size();

  int v;
  int temp;

  for(v = n; v >= 2; v--) {
    temp = data[v];
    data[v] = data[1];
    data[1] = temp;
    maxHeapify(data, 1, v - 1);
  }

  T swapper = begin;
  int swapidx = 0;
  while(swapper != end) {
    *swapper = data[swapidx];
    ++swapper;
    ++swapidx;
  }
}

/*template<typename T>
constexpr void maxHeapify(const T& a, int i, int n) {
  int b;
  auto temp = a[i];

  b = 2 * i;

  while(b <= n) {
    if(b < n && a[b+1] > a[b]) {
      b = b + 1;
    }
    if (temp > a[b]) {
      return;
    } else if (temp <= a[b]) {
      a[b/2] = a[b];
      b = 2 * b;
    }
  }

  a[b/2] = temp;
  return;
} */

#endif
