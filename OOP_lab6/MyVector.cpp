#include "MyVector.h"

using namespace std;

template<class T>
myVector<T>::myVector()
{
    data = al.allocate(capacity);
}

template<class T>
myVector<T>::myVector(size_t _size) :
    size(_size), capacity(size*3/2)
{
    data = al.allocate(capacity);
    uninitialized_fill_n(data, size, T{});
}

template<class T>
myVector<T>::myVector(const myVector &Vector) :
    size(Vector.size), capacity(Vector.capacity)
{
        data = al.allocate(capacity);
        uninitialized_fill_n(data, size, T{});
        for (size_t i = 0; i < size; ++i){
            data[i] = Vector.data[i];
        }
}

template<class T>
myVector<T>::~myVector() {
    for (auto i = data; i < data + size; ++i)
        al.destroy(i);
    al.deallocate(data, capacity);
}

template<class T>
void myVector<T>::reserve (size_t _size){
    if (size != 0){
        resize(_size);
        return;
    }
    size = _size;
    capacity = size*3/2;
    data = al.allocate(capacity);
    uninitialized_fill_n(data, size, T{});
}

template<class T>
void myVector<T>::resize(size_t _size) {
    size_t _capacity = _size*3/2;
    T* new_data = al.allocate(_size);
    uninitialized_fill_n(new_data, _size, T{});
    size_t m = min(size, _size);
    for (size_t i = 0; i < m; ++i)
        new_data[i] = data[i];
    for (auto i = data; i < data + size; ++i)
        al.destroy(i);
    al.deallocate(data, capacity);
    size = _size;
    capacity = _capacity;
    data=new_data;
}


template<class T>
void myVector<T>::operator= (const myVector& Vector ) {
    resize(Vector.size);
    for (size_t i = 0; i < size; ++i){
        data[i] = Vector.data[i];
    }
}

template<class T>
T& myVector<T>::operator[](const size_t pos) const {
    return data[pos];
}
