#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

using std::size_t;
using std::move;
using std::out_of_range;

template<typename T>
class QueueCircular {
private:
  T *data_ = nullptr;
  size_t head_ = 0;
  size_t size_ = 0;
  size_t capacity_ = 0;
  size_t moves_ = 0;

  void grow();
  size_t physical_index(size_t logical) const noexcept;

public:
  QueueCircular() = default;
  QueueCircular(const QueueCircular &other);
  QueueCircular(QueueCircular &&other) noexcept;
  QueueCircular &operator=(const QueueCircular &other);
  QueueCircular &operator=(QueueCircular &&other) noexcept;
  ~QueueCircular();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &front();
  const T &front() const;

  bool empty() const noexcept { return size_ == 0; }
  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }

  size_t moves() const noexcept { return moves_; }
  void reset_counters() noexcept { moves_ = 0; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// moves_ cuenta transferencias por crecimiento o desplazamiento.

template<typename T>
size_t QueueCircular<T>::physical_index(size_t logical) const noexcept {
  return capacity_ == 0 ? 0 : (head_ + logical) % capacity_;
}

template<typename T>
void QueueCircular<T>::grow() {
  size_t new_capacity = capacity_ == 0 ? 2 : capacity_ * 2;
  T * new_data = new T [new_capacity];
  try {
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = move(data_[physical_index(i)]);
      moves_++;
    }
  } catch (...) {
    delete [] new_data;
    throw;
  }
  delete [] data_;
  data_ = new_data;
  capacity_ = new_capacity;
  head_ = 0;
}

template<typename T>
QueueCircular<T>::QueueCircular(const QueueCircular & another_queue) {
  T * tmp = new T [another_queue.capacity_];
  try {
    for (size_t i = 0; i < another_queue.size_; i++) {
      tmp[i] = another_queue.data_[another_queue.physical_index(i)];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  data_ = tmp;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  head_ = 0;
  moves_ = another_queue.moves_;
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(const QueueCircular & another_queue) {
  if (this == &another_queue) return *this;
  T * tmp = new T [another_queue.capacity_];
  try {
    for (size_t i = 0; i < another_queue.size_; i++) {
      tmp[i] = another_queue.data_[another_queue.physical_index(i)];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  delete [] data_;
  data_ = tmp;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  head_ = 0;
  moves_ = another_queue.moves_;
  return *this;
}

template<typename T>
QueueCircular<T>::QueueCircular(QueueCircular && another_queue) noexcept {
  data_ = another_queue.data_;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  head_ = another_queue.head_;
  moves_ = another_queue.moves_;

  another_queue.data_ = nullptr;
  another_queue.size_ = another_queue.capacity_ = another_queue.head_ = another_queue.moves_ = 0;
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(QueueCircular && another_queue) noexcept {
  if (this == &another_queue) return *this;
  delete [] data_;
  data_ = another_queue.data_;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  head_ = another_queue.head_;
  moves_ = another_queue.moves_;

  another_queue.data_ = nullptr;
  another_queue.size_ = another_queue.capacity_ = another_queue.head_ = another_queue.moves_ = 0;
  return *this;
}

template<typename T>
QueueCircular<T>::~QueueCircular() {
  delete [] data_;
}

template<typename T>
void QueueCircular<T>::push(const T & value) {
  if (size_ == capacity_) {
    // Guarda el valor antes de que grow() libere el arreglo anterior.
    T saved{};
    saved = value;
    grow();
    data_[physical_index(size_)] = move(saved);
  } else {
    data_[physical_index(size_)] = value;
  }
  size_++;
}

template<typename T>
void QueueCircular<T>::push(T && value) {
  if (size_ == capacity_) {
    // Guarda el valor antes de que grow() libere el arreglo anterior.
    T saved{};
    saved = move(value);
    grow();
    data_[physical_index(size_)] = move(saved);
  } else {
    data_[physical_index(size_)] = move(value);
  }
  size_++;
}

template<typename T>
void QueueCircular<T>::pop() {
  if (empty()) throw out_of_range("pop on empty queue");
  head_ = (head_ + 1) % capacity_;
  size_--;
}

template<typename T>
T & QueueCircular<T>::front() {
  if (empty()) throw out_of_range("front on empty queue");
  return data_[head_];
}

template<typename T>
const T & QueueCircular<T>::front() const {
  if (empty()) throw out_of_range("front on empty queue");
  return data_[head_];
}
