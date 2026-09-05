#pragma once

#include <cstddef>
#include <vector>

template<typename T>
std::size_t my_lower_bound(const std::vector<T> &a, const T &x) {
  (void)x;
  // TODO: primera posición i tal que a[i] >= x.
  // Debe usar O(log n) comparaciones y puede asumir que a está ordenado.
  return a.size();
}

template<typename T>
std::size_t my_upper_bound(const std::vector<T> &a, const T &x) {
  (void)x;
  // TODO: primera posición i tal que a[i] > x.
  // Debe usar O(log n) comparaciones y puede asumir que a está ordenado.
  return a.size();
}
