#pragma once

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename T>
size_t my_lower_bound(const vector<T> &a, const T &x) {
  size_t l = 0;
  size_t h = a.size();
  while (l < h) {
    size_t m = l + (h - l) / 2;
    if (a[m] >= x){
      h = m;
    }else{
      l = m + 1;
    }
  }
  return l;
}

template<typename T>
size_t my_upper_bound(const vector<T> &a, const T &x) {
  size_t l = 0;
  size_t h = a.size();
  while (l < h) {
    size_t m = l + (h - l) / 2;
    if (a[m] <= x){
      l = m + 1;
    }else{
      h = m;
    }
  }
  return l;
}
