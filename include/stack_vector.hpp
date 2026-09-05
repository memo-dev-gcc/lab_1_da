#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
class StackVector {
private:
  std::vector<T> data_;

public:
  StackVector() = default;

  void push(const T &x) { data_.push_back(x); }
  void push(T &&x) { data_.push_back(std::move(x)); }

  void pop() {
    if(data_.empty())
      throw std::out_of_range("pop on empty stack");
    data_.pop_back();
  }

  T &top() {
    if(data_.empty())
      throw std::out_of_range("top on empty stack");
    return data_.back();
  }

  const T &top() const {
    if(data_.empty())
      throw std::out_of_range("top on empty stack");
    return data_.back();
  }

  bool empty() const noexcept { return data_.empty(); }
  std::size_t size() const noexcept { return data_.size(); }
  std::size_t capacity() const noexcept { return data_.capacity(); }
};
