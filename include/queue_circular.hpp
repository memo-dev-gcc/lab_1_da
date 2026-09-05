#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueCircular {
private:
  T *data_ = nullptr;
  std::size_t head_ = 0;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

  void grow();
  std::size_t physical_index(std::size_t logical) const noexcept;

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
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }

  std::size_t moves() const noexcept { return moves_; }
  void reset_counters() noexcept { moves_ = 0; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// pop() NO debe desplazar los elementos restantes.

template<typename T>
std::size_t QueueCircular<T>::physical_index(std::size_t logical) const noexcept {
  return capacity_ == 0 ? 0 : (head_ + logical) % capacity_;
}

template<typename T>
void QueueCircular<T>::grow() {
  throw std::logic_error("TODO QueueCircular::grow");
}

template<typename T>
QueueCircular<T>::QueueCircular(const QueueCircular &) {
  throw std::logic_error("TODO QueueCircular copy constructor");
}

template<typename T>
QueueCircular<T>::QueueCircular(QueueCircular &&) noexcept {
  // TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(const QueueCircular &) {
  throw std::logic_error("TODO QueueCircular copy assignment");
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(QueueCircular &&) noexcept {
  // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  return *this;
}

template<typename T>
QueueCircular<T>::~QueueCircular() {
  delete[] data_;
}

template<typename T>
void QueueCircular<T>::push(const T &) {
  throw std::logic_error("TODO QueueCircular::push(const T&)");
}

template<typename T>
void QueueCircular<T>::push(T &&) {
  throw std::logic_error("TODO QueueCircular::push(T&&)");
}

template<typename T>
void QueueCircular<T>::pop() {
  throw std::logic_error("TODO QueueCircular::pop");
}

template<typename T>
T &QueueCircular<T>::front() {
  throw std::logic_error("TODO QueueCircular::front");
}

template<typename T>
const T &QueueCircular<T>::front() const {
  throw std::logic_error("TODO QueueCircular::front const");
}
