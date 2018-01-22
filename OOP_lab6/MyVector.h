#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <exception>

using namespace std;

template <class T>
class myVector {
public:
    myVector();

    myVector(size_t);

    myVector(const myVector &);

    myVector(myVector &&);

    ~myVector();

    myVector& operator= (const myVector &);

    myVector& operator= (myVector &&);

    void resize(size_t );

    void reserve(size_t );

    void push_back(const T&);

    T& at(size_t ) const;

    T& operator[] (size_t ) const;

    size_t Size() const;

    size_t Capacity() const;

private:
    allocator<T> al;
    T* data;
    size_t size = 0;
    size_t capacity = 5;
};




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
myVector<T>::myVector(myVector &&Vector) :
    size(Vector.size), capacity(Vector.capacity), data(Vector.data)
{
        Vector.data = nullptr;
        Vector.size = 0;
        Vector.capacity = 0;
}

template<class T>
myVector<T>::~myVector() {
    for (auto i = data; i < data + size; ++i)
        al.destroy(i);
    al.deallocate(data, capacity);
}

template<class T>
void myVector<T>::reserve (size_t _size){
    capacity = _size;
    data = al.allocate(capacity);
}

template<class T>
void myVector<T>::resize(size_t _size) {
    size_t _capacity = _size*3/2;
    T* new_data = al.allocate(_capacity);
    uninitialized_fill_n(new_data, _size, T{});
    size_t m = min(size, _size);
    for (size_t i = 0; i < m; ++i)
        new_data[i] = data[i];
    for (auto i = data; i < data + size; ++i)
        al.destroy(i);
    al.deallocate(data, capacity);
    size = _size;
    capacity = _capacity;
    data = new_data;
}


template<class T>
myVector<T>& myVector<T>::operator= (const myVector& Vector ) {
    resize(Vector.size);
    for (size_t i = 0; i < size; ++i){
        data[i] = Vector.data[i];
    }
    return *this;
}

template<class T>
myVector<T>& myVector<T>::operator= (myVector&& Vector ) {
    if (this != &Vector) {
        for (auto i = data; i < data + size; ++i)
            al.destroy(i);
        al.deallocate(data, capacity);
        data = Vector.data;
        size = Vector.size;
        capacity = Vector.capacity;
        Vector.size = 0;
        Vector.capacity = 0;
        Vector.data = nullptr;
    }
    return *this;
}

template<class T>
void myVector<T>::push_back (const T& el) {
    if (size < capacity){
        uninitialized_fill_n(data + size, 1, T{});
        data[size++] = el;
    }
    else {
        resize(size+1);
        uninitialized_fill_n(data + size, 1, T{});
        data[size] = el;
    }
}

template<class T>
T& myVector<T>::at (size_t pos) const {
    if (pos >= 0 && pos < size)
        return data[pos];
    else
        throw out_of_range("Out of range");
}

template<class T>
T& myVector<T>::operator[](size_t pos) const {
    return data[pos];
}

template<class T>
size_t myVector<T>::Size () const {
    return size;
}

template<class T>
size_t myVector<T>::Capacity () const {
    return capacity;
}



#endif // MYVECTOR_H_INCLUDED
