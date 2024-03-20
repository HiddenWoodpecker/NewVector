#include "VectorNew.h"
using ValueType = int;

Vector::Iterator::Iterator(ValueType* ptr){
    _ptr = ptr;
}
ValueType* Vector::Iterator::operator->(){
    return _ptr;
}
const ValueType* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++(){
    _ptr++;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int a){
    _ptr += a;
    return *this;
}


ValueType& Vector::Iterator::operator*(){
    return *_ptr;
}
const ValueType& Vector::Iterator::operator*() const{
    return *_ptr;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return (*this == other);
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
    return (*this != other);
}
Vector::Iterator Vector::begin(){
    return Iterator(_data);
}

Vector::Iterator Vector::end(){
    return Iterator(_data + _capacity);
}

Vector::Vector(const ValueType* rawArray, const size_t size, float coef){
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
    _data = new ValueType[other._size];
    _size = other._size;
    _capacity = other._size;
    for (size_t i = 0; i < other._size; i++)
    {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other){
    _data = new ValueType[other.size()];
    _size = other._size;
    _capacity = other._size;
    for (size_t i = 0; i < other._size; i++)
    {
        _data[i] = other._data[i];
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept{

    if (this != &other){
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        delete other._data;
    }
}

Vector& Vector::operator=(Vector&& other) noexcept{

    if (this != &other){
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        delete other._data;
    }
    return *this;
}

ValueType& Vector::operator[](size_t idx){
    if (idx < _size){
        return _data[idx];
    }
    throw std::out_of_range("Out of range");
}

const ValueType& Vector::operator[](size_t idx) const{
    if (idx < _size){
        return _data[idx];
    }
    throw std::out_of_range("Out of range");
}

Vector::~Vector(){
    delete _data;
}

long long Vector::find(const ValueType& value) const{
    for (size_t i = 0; i < _size; i++)
    {
        if (*(_data + i) == value){
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity){
    if (_capacity < capacity){
        _capacity = capacity;
        ValueType* tmp = new ValueType[capacity];
        for (size_t i = 0; i < _size; i++){
            tmp[i] = _data[i];
        }
        delete _data;
        _data = tmp;
    }
}

void Vector::pushBack(const ValueType& value){
    if (_size >= _capacity){
        reserve(_capacity * _multiplicativeCoef);
    }
    _data[_size++] = value;
}

void Vector::insert(const ValueType& value, size_t pos){
    if (pos <= _size){
        if (_size >= _capacity){
            reserve(_capacity * _multiplicativeCoef);
        }
        memmove(_data + pos + 1, _data+pos, sizeof(ValueType)*(_size - pos));
        _data[pos] = value;
        ++_size;
    }
}

void Vector::insert(const ValueType* values, size_t size, size_t pos){
    if (pos <= _size){
        if (_size + size - 1 >= _capacity){
            reserve((_capacity+size) * _multiplicativeCoef);
        }
        memmove(_data + pos + size, _data+pos, sizeof(ValueType)*(_size - pos));
        for (size_t i = 0; i < size; i++){
            _data[i+pos] = values[i];
        }
        _size += size;
    }
}

void Vector::insert(const Vector& vector, size_t pos){
    
    if (pos <= _size){
        size_t size = vector.size();
        if (_size + size - 1 >= _capacity){
            reserve((_capacity+size) * _multiplicativeCoef);
        }
        memmove(_data + pos + size, _data+pos, sizeof(ValueType)*(_size - pos));
        for (size_t i = 0; i < size; i++){
            _data[i+pos] = vector[i];
        }
        _size += vector.size();
    }
}

void Vector::pushFront(const ValueType& value){
    insert(value, 0);
}

void Vector::popBack(){
    if (_size != 0){
        --_size;
    }
}

void Vector::popFront(){
    if (_size != 0){
        memmove(_data, _data + 1, _size);
        --_size;
    }
}

void Vector::erase(size_t pos, size_t count){
    if(pos + count > _size){
        _size = pos >= _size ? _size : pos;
    }
    else{
        size_t difference = _size - pos - count;
        for (size_t i = 0; i < difference; ++i){
            (*this)[i + pos] = (*this)[i + pos + count];
        }
        _size = _size - count;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    if (beginPos < endPos){
        erase(beginPos, endPos - beginPos);
    }
}


size_t Vector::size() const{
    return _size;
}

size_t Vector::capacity() const{
    return _capacity;
}

void Vector::shrinkToFit(){
    _capacity = _size;
}
double Vector::loadFactor() const{
    return (double)_size/_capacity;
}
