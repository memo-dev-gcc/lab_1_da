#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueShift {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

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
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }

  std::size_t moves() const noexcept { return moves_; }
  void reset_counters() noexcept { moves_ = 0; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// moves_ cuenta transferencias debidas a redimensionamiento o desplazamiento,
// no la asignación normal del elemento que se inserta.

template<typename T>
void QueueShift<T>::grow() {
  throw std::logic_error("TODO QueueShift::grow");
}

template<typename T>
QueueShift<T>::QueueShift(const QueueShift &) {
  throw std::logic_error("TODO QueueShift copy constructor");
}

template<typename T>
QueueShift<T>::QueueShift(QueueShift &&) noexcept {
  // TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(const QueueShift &) {
  throw std::logic_error("TODO QueueShift copy assignment");
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(QueueShift &&) noexcept {
  // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  return *this;
}

template<typename T>
QueueShift<T>::~QueueShift() {
  delete[] data_;
}

template<typename T>
void QueueShift<T>::push(const T &) {
  throw std::logic_error("TODO QueueShift::push(const T&)");
}

template<typename T>
void QueueShift<T>::push(T &&) {
  throw std::logic_error("TODO QueueShift::push(T&&)");
}

template<typename T>
void QueueShift<T>::pop() {
  throw std::logic_error("TODO QueueShift::pop");
}

template<typename T>
T &QueueShift<T>::front() {
  throw std::logic_error("TODO QueueShift::front");
}

template<typename T>
const T &QueueShift<T>::front() const {
  throw std::logic_error("TODO QueueShift::front const");
}
