#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

using std::size_t;
using std::move;
using std::out_of_range;

template<typename T>
class StackRaw {
private:
  T *data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  void grow();

public:
  StackRaw() = default;
  StackRaw(const StackRaw &other);
  StackRaw(StackRaw &&other) noexcept;
  StackRaw &operator=(const StackRaw &other);
  StackRaw &operator=(StackRaw &&other) noexcept;
  ~StackRaw();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &top();
  const T &top() const;

  bool empty() const noexcept { return size_ == 0; }
  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.

template<typename T>
void StackRaw<T>::grow() {
  size_t new_capacity = capacity_ == 0 ? 2 : capacity_ * 2;
  T * new_data = new T [new_capacity];
  try {
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = move(data_[i]);
    }
  } catch (...) {
    delete [] new_data;
    throw;
  }
  delete [] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

template<typename T>
StackRaw<T>::StackRaw(const StackRaw & another_stack) {
  T * tmp = new T [another_stack.capacity_];
  try {
    for (size_t i = 0; i < another_stack.size_; i++) {
      tmp[i] = another_stack.data_[i];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  data_ = tmp;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(const StackRaw & another_stack) {
  if (this == &another_stack) return *this;
  T * tmp = new T [another_stack.capacity_];
  try {
    for (size_t i = 0; i < another_stack.size_; i++) {
      tmp[i] = another_stack.data_[i];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  delete [] data_;
  data_ = tmp;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;
  return *this;
}

template<typename T>
StackRaw<T>::StackRaw(StackRaw && another_stack) noexcept {
  data_ = another_stack.data_;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;

  another_stack.data_ = nullptr;
  another_stack.size_ = another_stack.capacity_ = 0;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(StackRaw && another_stack) noexcept {
  if (this == &another_stack) return *this;
  delete [] data_;
  data_ = another_stack.data_;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;

  another_stack.data_ = nullptr;
  another_stack.size_ = another_stack.capacity_ = 0;
  return *this;
}

template<typename T>
StackRaw<T>::~StackRaw() {
  delete [] data_;
}

template<typename T>
void StackRaw<T>::push(const T & value) {
  if (size_ == capacity_) {
    // Guarda el valor antes de que grow() libere el arreglo anterior.
    T saved{};
    saved = value;
    grow();
    data_[size_] = move(saved);
  } else {
    data_[size_] = value;
  }
  size_++;
}

template<typename T>
void StackRaw<T>::push(T && value) {
  if (size_ == capacity_) {
    // Guarda el valor antes de que grow() libere el arreglo anterior.
    T saved{};
    saved = move(value);
    grow();
    data_[size_] = move(saved);
  } else {
    data_[size_] = move(value);
  }
  size_++;
}

template<typename T>
void StackRaw<T>::pop() {
  if (empty()) throw out_of_range("pop on empty stack");
  size_--;
}

template<typename T>
T & StackRaw<T>::top() {
  if (empty()) throw out_of_range("top on empty stack");
  return data_[size_ - 1];
}

template<typename T>
const T & StackRaw<T>::top() const {
  if (empty()) throw out_of_range("top on empty stack");
  return data_[size_ - 1];
}
