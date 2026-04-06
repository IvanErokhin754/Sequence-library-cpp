#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class DynamicArray{    
private:
    size_t size;
    T *data;

public:
    DynamicArray() : size(0), data(nullptr) {}
    DynamicArray(size_t size) : size(size) {
        data = new T[size];
    }
     DynamicArray(const DynamicArray &other) {
        size = other.size;
        data = new T[size];

        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }
    ~DynamicArray() {
        delete[] data;
    }
    
    T &operator[](size_t i) {
        if (i >= size)
            throw std::out_of_range("Index larger than size!");
        
        return data[i];
    }
    
    const T &operator[](size_t i) const { // const_cast<DynamicArray<T>*> (this)->operator[](i) || (*this)[...]
        if (i >= size)
            throw std::out_of_range("Index larger than size!");

        return data[i];
    }

    DynamicArray &operator=(const DynamicArray &other) { // перенос C11+
        if (this == &other)
            return *this;

        T *new_data = new T[other.size];

        for (size_t i = 0; i < other.size; i++) 
            new_data[i] = other.data[i];
        
        delete[] data;
        data = new_data;
        size = other.size;

        return *this;
    }

    void Resize(size_t new_size) {
        if (new_size == size) return;
        if (new_size == 0) {
            delete[] data; 
            data = nullptr; 
            size = 0; 
            return;
        }
        if (!data) {
            size = new_size; 
            data = new T[size]; 
            return;
        }

        T *new_data = new T[new_size];
        size_t minimum = std::min(new_size, size);
        for (size_t i = 0; i < minimum; i++){
            new_data[i] = data[i];
        }
        
        delete[] data;
        data = new_data;
        size = new_size;
    }   

    size_t GetSize() const {
        return size;
    }

};

#endif /* DYNAMIC_ARRAY_HPP */
