#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>

namespace zasulsky
{
  template < typename T >
  class Iterator;

  template < typename T >
  class Vector
  {
    using Iter = Iterator <T>;
  public:
    Vector() :
      data(nullptr),
      capacity(0),
      size(0)
    {}

    Vector(const Vector& other)
    {
      data = new T[other.capacity];
      capacity = other.capacity;
      size = other.size;
      for (int i = 0; i < size; ++i)
      {
        data[i] = other.data[i];
      }
    }

    ~Vector()
    {
      delete[] data;
    }

    Vector& operator=(const Vector& other)
    {
      if (this != &other)
      {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
        {
          data[i] = other.data[i];
        }
      }
      return *this;
    }

    void push_front(const T& value)
    {
      if (size >= capacity)
      {
        size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i)
        {
          new_data[i + 1] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
      }
      else
      {
        for (size_t i = size; i > 0; --i)
        {
          data[i] = data[i - 1];
        }
      }

      data[0] = value;
      ++size;
    }

    bool isRight(int index, int num)
    {
      bool res = false;
      for (size_t i = ++index; i < getSize(); i++)
      {
        int d = 0;
        d = data[i];
        if (d > num)
        {
          res = true;
        }
      }
      return res;
    }

    bool isLeft(int index, int num)
    {
      bool res = false;
      for (int i = --index; i >= 0; i--)
      {

        if (data[i] > num)
        {
          res = true;
        }
      }
      return res;
    }

    void push_back(const T& value)
    {
      if (size >= capacity)
      {
        size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i)
        {
          new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
      }
      data[size++] = value;
    }

    void push(const T& value)
    {
      if (size >= capacity)
      {
        size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i)
        {
          new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
      }
      data[size++] = value;
    }

    T& operator[](int index) {
      if (index < 0 || index >= static_cast<int>(getSize()))
      {
        throw std::out_of_range("Index out of bounds");
      }
      return data[index];
    }

    size_t getSize() const
    {
      return size;
    }

    void erase(int index)
    {
      if (index >= size)
      {
        throw std::out_of_range("Index out of bounds");
      }
      for (int i = index; i < size - 1; ++i)
      {
        data[i] = data[i + 1];
      }
      --size;
    }

    void erase(const Iter& it)
    {
      if (it.ptr < data || it.ptr >= data + size)
      {
        throw std::out_of_range("Iter is out of bounds");
      }

      int index = it.ptr - data;
      for (int i = index; i < size - 1; ++i)
      {
        data[i] = data[i + 1];
      }
      --size;
    }

    void clear()
    {
      delete[] data;
      data = nullptr;
      size = 0;
      capacity = 0;
    }

    bool operator==(const Vector& other) const
    {
      if (size != other.size)
      {
        return false;
      }

      for (int i = 0; i < size; ++i)
      {
        if (data[i] != other.data[i])
        {
          return false;
        }
      }

      return true;
    }

    T& back()
    {
      if (size == 0)
      {
        throw std::out_of_range("Vector is empty");
      }
      return data[size - 1];
    }

    T& front()
    {
      if (size == 0)
      {
        throw std::out_of_range("Vector is empty");
      }
      return data[0];
    }

    Iter begin()
    {
      return Iter(data);
    }

    Iter end()
    {
      return Iter(data + size);
    }

    T* getData()
    {
      return data;
    }
  private:
    T* data;
    size_t capacity;
    size_t size;
  };

  template < typename T >
  class Iterator : public std::iterator < std::bidirectional_iterator_tag, T >
  {
  public:
    friend class Vector< T >;

    T* ptr;

    Iterator(T* ptr) : ptr(ptr) {}

    T& operator*() const
    {
      return *ptr;
    }

    Iterator& operator++()
    {
      ++ptr;
      return *this;
    }

    Iterator& operator--()
    {
      --ptr;
      return *this;
    }

    Iterator& operator++(int)
    {
      Iterator temp = *this;
      ++ptr;
      return temp;
    }

    Iterator& operator--(int)
    {
      Iterator temp = *this;
      --ptr;
      return temp;
    }

    bool operator==(const Iterator& other) const
    {
      return ptr == other.ptr;
    }

    bool operator!=(const Iterator& other) const
    {
      return ptr != other.ptr;
    }
  };
}

#endif
