#ifndef pr_7
#define pr_7
#include <sstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
using namespace std;
template <class T>
class Iterator
	: public iterator<random_access_iterator_tag, T>
{
	T* current_;
public:
	explicit Iterator(T* ptr)
		: current_(ptr){
	}
	bool operator==(const Iterator<T>& other) const
	{
		return current_ == other.current_;
	}

	bool operator!=(const Iterator<T>& other) const
	{
		return !(*this == other);
	}

	Iterator& operator++()
	{
		++current_;
		return *this;
	}
	Iterator& operator--()
	{
		--current_;
		return *this;
	}

	T& operator*() const
	{
		return *current_;
	}
};


template<class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	template <typename... Args>
	void construct(pointer ptr, Args&&... args) {
		new(ptr) T(std::forward <Args> (args)...);
	}
	pointer allocate(size_type size){
		return static_cast<pointer> (::operator new[](sizeof(value_type) * size));
	}
	void deallocate(pointer ptr, size_type size=0){
		delete[] ptr;
	}
	void destroy(pointer ptr){
		ptr->~T();

	}
};
template<class T, class Alloc = Allocator<T>>
class Vector
{

public:
	using reverse_iterator = class std::reverse_iterator<Iterator<T>>;
	using iterator = Iterator<T>;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using size_type = size_t;
private:
	size_type allocated;
	T* data;
	size_type used;
	Alloc alloc;
public:
	explicit Vector(size_type size, const T& value) {
		used = size;
		data = alloc.allocate(size);
		allocated = size;
		for (pointer i = data; i != data + size; i++){
			alloc.construct(i, value);
		}
	}
	explicit Vector(size_type size = 0) {
		used = size;
		data = alloc.allocate(size);
		allocated = size;
		for (pointer i = data; i != data + size; i++){
			alloc.construct(i);
		}
	}
	void reserve(size_type size) {
		pointer new_data = alloc.allocate(size);
		for (size_type i = 0; i < used; i++) {
			alloc.construct(new_data + i, data[i]);
			alloc.destroy(data + i);
		}
		alloc.deallocate(data);
		data = new_data;
		allocated = size;
	}
	reference operator[](size_type i) {
		if (i < used) {
			return data[i];
		} else {
			throw std::out_of_range("out of range");
		}
	}
	void push_back(const value_type& value) {
		if (used + 1 > allocated){
			reserve((allocated+sizeof(value))*2);
		}
		alloc.construct(data + (used)++, value);
	}
	void pop_back() {
		if (used > 0) {
			alloc.destroy(data + used);
			--used;
		}
	}
	bool empty() {
		return !used;
	}
	size_t size() {
		return used;
	}
	void resize(size_type new_size){
		if (new_size > used){
			if(new_size >= allocated){
				alloc.reserve(new_size);
			}
			for (pointer p = used+1; p<new_size; p++){
				alloc.construct(p);
			}
		}
		if (new_size < used){
			for (pointer p = data + used; p > data + new_size; p--){
				alloc.destroy(p);
			}
		}
		used = new_size;
	}
	iterator begin() noexcept{
		return iterator(data);
	}
	reverse_iterator rbegin() noexcept{
		return reverse_iterator(end());
	}

	iterator end() noexcept{
		return iterator(data+used);

	}
	reverse_iterator rend() noexcept{
		return reverse_iterator(begin());
	}
	void clear() {
		for(size_t i = 0; i < allocated; ++i) {
			alloc.destroy(data + i);
		}
		allocated = 0;
		used = 0;
	}
	~Vector() {
		clear();
		alloc.deallocate(data, allocated);
	}
};
#endif 