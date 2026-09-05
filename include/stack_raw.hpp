#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class StackRaw {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
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
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// No se permite usar std::vector dentro de esta clase.

template<typename T>
void StackRaw<T>::grow() {
  if (capacity_ <= 0) capacity_ = 2;
  T * new_data = new T (capacity_ * 2);
  for (int i =0 ; i < size_; i++){
    new_data[i] = data_[i];
  }
  capacity_ *= 2;
  delete [] data_;
}

template<typename T>
StackRaw<T>::StackRaw(const StackRaw & another_stack) {
  T * tmp = nullptr;
  if (another_stack.capacity_ > capacity_)
    tmp = new T [another_stack.capacity_];
  else tmp = data_;

  for (size_t i = 0; i < another_stack.size_; i++) {
    tmp[i] = another_stack[i];
  }
  data_ = tmp;
}

template<typename T>
StackRaw<T>::StackRaw(StackRaw && another_stack) noexcept {
  T * tmp = data_;
  data_ = another_stack;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;

  another_stack = nullptr;
  another_stack.size_ = another_stack.capacity_ = 0;
  delete [] tmp;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(const StackRaw & another_stack) {
  T * tmp = data_;
  if ( another_stack.capacity_ > capacity_) tmp = new T [another_stack.capacity_];
  for (size_t i = 0 ; i < another_stack.size_ ; i++) {
    tmp [i] = another_stack [i];
  }
  delete [] data_;
  data_ = tmp;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(StackRaw && another_stack) noexcept {
  T * tmp = data_;
  data_ = another_stack;
  size_ = another_stack.size_;
  capacity_ = another_stack.capacity_;

  another_stack = nullptr;
  another_stack.size_ = another_stack.capacity_ = 0;
  delete [] tmp;

  return *this;
}

template<typename T>
StackRaw<T>::~StackRaw() {
  delete[] data_;
}

template<typename T>
void StackRaw<T>::push(const T & value) {
  if (size_ == capacity_) grow ();
  data_[size_++] = value;
}

template<typename T>
void StackRaw<T>::push(T && value) {
  if (size_ == capacity_) grow ();
  data_[size_++] = value;
}

template<typename T>
void StackRaw<T>::pop() {
  if (empty()) throw std::out_of_range ("Error there are no elements to delete");
  T value = data_[--size_];
  throw std::logic_error("TODO StackRaw::pop");
}

template<typename T>
T & StackRaw<T>::top() {
  if (empty()) throw std::out_of_range ("Error there are no elements to delete");
  T value = data_[size_-1];
  return value;
}

template<typename T>
const T &StackRaw<T>::top() const {
  if (empty()) throw std::out_of_range ("Error there are no elements to delete");
  const T value = data_[size_-1];
  return value;
}
