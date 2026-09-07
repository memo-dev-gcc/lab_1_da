#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

using std::size_t;
using std::move;
using std::out_of_range;

template<typename T>
class QueueShift {
private:
  T *data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  size_t moves_ = 0;

  void grow();

public:
  QueueShift() = default;
  QueueShift(const QueueShift &other);
  QueueShift(QueueShift &&other) noexcept;
  QueueShift &operator=(const QueueShift &other);
  QueueShift &operator=(QueueShift &&other) noexcept;
  ~QueueShift();

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
void QueueShift<T>::grow() {
  size_t new_capacity = capacity_ == 0 ? 2 : capacity_ * 2;
  T * new_data = new T [new_capacity];
  try {
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = move(data_[i]);
      moves_++;
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
QueueShift<T>::QueueShift(const QueueShift & another_queue) {
  T * tmp = new T [another_queue.capacity_];
  try {
    for (size_t i = 0; i < another_queue.size_; i++) {
      tmp[i] = another_queue.data_[i];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  data_ = tmp;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  moves_ = another_queue.moves_;
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(const QueueShift & another_queue) {
  if (this == &another_queue) return *this;
  T * tmp = new T [another_queue.capacity_];
  try {
    for (size_t i = 0; i < another_queue.size_; i++) {
      tmp[i] = another_queue.data_[i];
    }
  } catch (...) {
    delete [] tmp;
    throw;
  }
  delete [] data_;
  data_ = tmp;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  moves_ = another_queue.moves_;
  return *this;
}

template<typename T>
QueueShift<T>::QueueShift(QueueShift && another_queue) noexcept {
  data_ = another_queue.data_;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  moves_ = another_queue.moves_;

  another_queue.data_ = nullptr;
  another_queue.size_ = another_queue.capacity_ = another_queue.moves_ = 0;
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(QueueShift && another_queue) noexcept {
  if (this == &another_queue) return *this;
  delete [] data_;
  data_ = another_queue.data_;
  size_ = another_queue.size_;
  capacity_ = another_queue.capacity_;
  moves_ = another_queue.moves_;

  another_queue.data_ = nullptr;
  another_queue.size_ = another_queue.capacity_ = another_queue.moves_ = 0;
  return *this;
}

template<typename T>
QueueShift<T>::~QueueShift() {
  delete [] data_;
}

template<typename T>
void QueueShift<T>::push(const T & value) {
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
void QueueShift<T>::push(T && value) {
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
void QueueShift<T>::pop() {
  if (empty()) throw out_of_range("pop on empty queue");
  for (size_t i = 1; i < size_; i++) {
    data_[i - 1] = move(data_[i]);
    moves_++;
  }
  size_--;
}

template<typename T>
T & QueueShift<T>::front() {
  if (empty()) throw out_of_range("front on empty queue");
  return data_[0];
}

template<typename T>
const T & QueueShift<T>::front() const {
  if (empty()) throw out_of_range("front on empty queue");
  return data_[0];
}
