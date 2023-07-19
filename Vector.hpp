#pragma once
#include <initializer_list>

struct out_of_range {};

template <typename T> class Vector {
private:
  T *_array;
  std::size_t _size;
  std::size_t _space;

public:
  // CONSTRUCTORS & DESTRUCTOR //
  Vector() noexcept;
  explicit Vector(std::size_t size) noexcept;
  Vector(std::size_t size, T value) noexcept;
  Vector(std::initializer_list<T>) noexcept;
  Vector(const Vector &obj) noexcept;
  Vector<T> &operator=(const Vector<T> &obj) noexcept;
  ~Vector() noexcept;
  // CONSTRUCTORS & DESTRUCTOR //

  // ITERATORS //
  class iterator;
  iterator begin() noexcept;
  iterator end() noexcept;
  const iterator begin() const noexcept;
  const iterator end() const noexcept;
  const iterator cbegin() const noexcept;
  const iterator cend() const noexcept;
  // ITERATORS //

  // SIZE //
  bool empty() const noexcept;
  std::size_t capacity() const noexcept;
  void reserve(const std::size_t newalloc) noexcept;
  void resize(const std::size_t newsize, const T value = T()) noexcept;
  std::size_t size() const noexcept;
  std::size_t max_size() const noexcept;
  void shrink_to_length() noexcept;
  // SIZE //

  // MODIFY //
  void clear() noexcept;
  void push_back(const T &value) noexcept;
  void pop_back() noexcept;
  void push_front(const T &value) noexcept;
  void pop_front() noexcept;
  void insert(std::size_t index, const T &value) noexcept;
  void remove(const std::size_t index) noexcept;
  // MODIFY //

  // ELEMENT ACCESS //
  T &at(std::size_t index);
  const T &at(std::size_t index) const;
  T &operator[](std::size_t index) noexcept;
  const T &operator[](std::size_t index) const noexcept;
  T &front() noexcept;
  const T &front() const noexcept;
  T &back() noexcept;
  const T &back() const noexcept;
  T *data() noexcept;
  const T *data() const noexcept;
  // ELEMENT ACCESS //
};

template <typename T> class Vector<T>::iterator {
private:
  T *_current;

public:
  iterator(T *ptr) noexcept : _current{ptr} {}

  T &operator*() noexcept { return *_current; }

  iterator &operator++() noexcept {
    _current++;
    return *this;
  }

  iterator &operator--() {
    _current--;
    return *this;
  }

  bool operator==(const iterator &obj) const noexcept {
    return _current == obj._current;
  }

  bool operator!=(const iterator &obj) const noexcept {
    return _current != obj._current;
  }
};

template <typename T>
inline Vector<T>::Vector() noexcept : _array{nullptr}, _size{0}, _space{0} {};

template <typename T>
inline Vector<T>::Vector(std::size_t size) noexcept
    : _array{new T[size]}, _size{size}, _space{size} {
  for (std::size_t i = 0; i < size; i++) {
    _array[i] = T();
  }
}

template <typename T>
inline Vector<T>::Vector(std::size_t size, T value) noexcept
    : _array{new T[size]}, _size{size}, _space{size} {
  for (std::size_t i = 0; i < size; i++) {
    _array[i] = value;
  }
}

// TODO
template <typename T>
inline Vector<T>::Vector(std::initializer_list<T> values) noexcept
    : _array{new T[values.size()]}, _size{static_cast<std::size_t>(
                                        values.size())},
      _space{static_cast<std::size_t>(values.size()) * 2} {
  std::size_t counter = 0;
  for (auto const &i : values) {
    _array[counter++] = i;
  }
}

template <typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &obj) noexcept {
  if (this == &obj)
    return *this;

  if (obj._size() <= _space) {
    for (std::size_t i = 0; i < obj._size(); i++) {
      _array[i] = obj._array[i];
    }
    _size = obj._size();
    return *this;
  }

  else {
    T *ptr = new T[obj._size];
    if (obj._size() <= _space) {
      for (std::size_t i = 0; i < obj._size(); i++) {
        ptr[i] = obj._array[i];
      }
      delete[] _array;
      _size = obj._size();
      _space = obj._space();
      _array = ptr;
      return *this;
    }
  }
}

template <typename T> Vector<T>::~Vector() noexcept { delete[] _array; }

template <typename T>
inline typename Vector<T>::iterator Vector<T>::begin() noexcept {
  return Vector<T>::iterator(&_array[0]);
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::begin() const noexcept {
  return Vector<T>::iterator(&_array[0]);
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::end() noexcept {
  return Vector<T>::iterator(&_array[_size]);
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::end() const noexcept {
  return Vector<T>::iterator(&_array[_size]);
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::cbegin() const noexcept {
  return Vector<T>::iterator(&_array[0]);
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::cend() const noexcept {
  return Vector<T>::iterator(&_array[_size]);
}

template <typename T> inline bool Vector<T>::empty() const noexcept {
  return _size == 0;
}

template <typename T> inline std::size_t Vector<T>::capacity() const noexcept {
  return _space;
}

template <typename T>
inline void Vector<T>::reserve(const std::size_t newalloc) noexcept {
  if (newalloc <= _space)
    return;

  _space = newalloc;
  T *ptr = new T[_space];

  for (std::size_t i = 0; i < _size; i++) {
    ptr[i] = _array[i];
  }

  delete[] _array;

  _array = ptr;
}

template <typename T>
inline void Vector<T>::resize(const std::size_t newsize,
                              const T value) noexcept {

  reserve(newsize);

  for (std::size_t i = _size; i < _space; i++) {
    _array[i] = T();
  }

  _size = newsize;
}

template <typename T> inline std::size_t Vector<T>::size() const noexcept {
  return _size;
}

template <typename T> inline std::size_t Vector<T>::max_size() const noexcept {
  return _space;
}

template <typename T> inline void Vector<T>::shrink_to_length() noexcept {
  for (std::size_t i = _size; i < _space; i++) {
    delete _array[i];
  }
  _space = _size;
}

template <typename T> inline void Vector<T>::clear() noexcept {
  for (std::size_t i = 0; i < _size; i++) {
    _array[i] = T();
  }
}

template <typename T>
inline void Vector<T>::push_back(const T &value) noexcept {
  if (_space == 0)
    reserve(8);
  else if (_size == _space)
    reserve(2 * _space);

  _array[_size] = value;
  _size++;
}

template <typename T> inline void Vector<T>::pop_back() noexcept {
  if (_size > 0) {
    _array[_size - 1] = T();
    _size--;
  }
}

template <typename T>
inline void Vector<T>::push_front(const T &value) noexcept {
  if (_space == 0)
    reserve(8);
  else if (_size == _space)
    reserve(2 * _space);
  _size++;

  T temp[_space];
  for (std::size_t i = 0; i < _space; i++) {
    temp[i] = _array[i];
  }
  _array[0] = value;
  for (std::size_t i = 1; i < _size; i++) {
    _array[i] = temp[i - 1];
  }
};

template <typename T> inline void Vector<T>::pop_front() noexcept {
  if (_size > 0) {
    T temp[_space];
    for (std::size_t i = 0; i < _space; i++) {
      temp[i] = _array[i];
    }
    for (std::size_t i = 1; i < _size; i++) {
      _array[i - 1] = temp[i];
    }

    _array[_size - 1] = T();
    _size--;
  }
}

// TODO
template <typename T>
inline void Vector<T>::insert(std::size_t index, const T &value) noexcept {}

// TODO
template <typename T>
inline void Vector<T>::remove(std::size_t index) noexcept {}

template <class T> inline T &Vector<T>::at(std::size_t index) {
  if (index < 0 || _size <= index)
    throw out_of_range();
  return _array[index];
}

template <class T> inline const T &Vector<T>::at(std::size_t index) const {
  if (index < 0 || _size <= index)
    throw out_of_range();
  return _array[index];
}

template <class T> inline T &Vector<T>::operator[](std::size_t index) noexcept {
  return _array[index];
}

template <class T>
inline const T &Vector<T>::operator[](std::size_t index) const noexcept {
  return _array[index];
}

template <class T> inline T &Vector<T>::front() noexcept { return _array[0]; }

template <class T> inline const T &Vector<T>::front() const noexcept {
  return _array[0];
}

template <class T> inline T &Vector<T>::back() noexcept {
  return _array[_size - 1];
}

template <class T> inline const T &Vector<T>::back() const noexcept {
  return _array[_size - 1];
}

template <class T> inline T *Vector<T>::data() noexcept { return _array; }

template <class T> inline const T *Vector<T>::data() const noexcept {
  return _array;
}
