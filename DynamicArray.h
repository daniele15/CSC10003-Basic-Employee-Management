#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

using namespace std;

template <class MyClass>
class DynamicArray
{
private:
    MyClass* _a = NULL;
    int _maxSize;
    int _currentSize;
    const int _length = 10;
public:
    DynamicArray();
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();
    const DynamicArray& operator=(const DynamicArray& other);

    MyClass getAt(int index);

    MyClass operator[] (int index);

    int size();

    void push_back(MyClass value);

    void removeAt(int index);

    void clear();
};

template <class MyClass>
DynamicArray<MyClass>::DynamicArray() {
    _a = new MyClass[_length];
    _maxSize = _length;
    _currentSize = 0;
}
template <class MyClass>
DynamicArray<MyClass>::DynamicArray(const DynamicArray& other) {
    _maxSize = other._maxSize;
    _currentSize = other._currentSize;
    _a = new MyClass[_maxSize];

    for (int i = 0; i < _currentSize; i++) {
        _a[i] = other._a[i];
    }
}
template <class MyClass>
DynamicArray<MyClass>::~DynamicArray() {
    if (_a != NULL) {
        delete[] _a;
    }
}
template <class MyClass>
const DynamicArray<MyClass>& DynamicArray<MyClass>::operator=(const DynamicArray& other) {
    _maxSize = other._maxSize;
    _currentSize = other._currentSize;
    _a = new MyClass[_maxSize];

    for (int i = 0; i < _currentSize; i++) {
        _a[i] = other._a[i];
    }

    return *this;
}
template <class MyClass>
MyClass DynamicArray<MyClass>::getAt(int index) {
    if (index < _currentSize) {
        return _a[index];
    }
    else {
        throw "Index out of bound";
    }
}
template <class MyClass>
MyClass DynamicArray<MyClass>::operator[] (int index) {
    return getAt(index);
}
template <class MyClass>
int DynamicArray<MyClass>::size() { return _currentSize; }
template <class MyClass>
void DynamicArray<MyClass>::push_back(MyClass value) {
    if (_currentSize >= _maxSize) {

        _maxSize = _maxSize + _length;
        MyClass* temp = new MyClass[_maxSize];

        for (int i = 0; i < _currentSize; i++) {
            temp[i] = _a[i];
        }

        delete[] _a;

        _a = temp;
    }

    _a[_currentSize] = value;
    _currentSize++;
}
template <class MyClass>
void DynamicArray<MyClass>::removeAt(int index) {
    for (int i = index + 1; i < _currentSize; i++) {
        _a[i - 1] = _a[i];
    }

    _currentSize--;
}
template <class MyClass>
void DynamicArray<MyClass>::clear()
{
    if (_a != NULL)
        delete[] _a;
    _maxSize = 0;
    _currentSize = 0;
}

#endif