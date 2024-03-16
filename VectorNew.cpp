#include "VectorNew.h"
using ValueType = int;

Vector::Vector(const ValueType* rawArray, const size_t size, float coef = 2.0f){
    _data = new ValueType[size];
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    for (size_t i = 0; i < size; i++)
    {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other){
    _data = new ValueType[other.size()];
    _size = other._size;
    _capacity = other._size;
    for (size_t i = 0; i < other._size; i++)
    {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other){
    Vector vec = Vector(other);
    return vec;
}


Vector::Vector(Vector&& other) noexcept{
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 2.0f;
}

Vector& Vector::operator=(Vector&& other) noexcept{
    Vector vec = Vector(other);
    
}

void Vector::pushBack(const ValueType& value){

}

size_t Vector::size() const{
    return _size;
}

size_t Vector::capacity() const{
    return _capacity;
}