#pragma once

#include <iterator>

// forward iterator, cause LinkedList doesn't need bidirection
// you can't move backward when you don't have pointer for 
// element before (position - 1)
// that's why our Iterator will be "just" forward

template <class Ty>
class Iterator
{
		// Iterator class with forward iterator behaviour
		// using it for linked list

	public:
	
		// constructor's
		Iterator() : instance{ Ty{ nullptr } } { }
		explicit Iterator(Ty* _instance) : instance{ _instance } { }
		Iterator(const Iterator<Ty>&) = default;
		
		// destructor
		~Iterator() { delete instance; }
		
		// iterator traits, 5 of them (plus 1)		
		using iterator_type = typename Ty*;
		using iterator_category = std::forward_iterator_tag;
		using value_type = typename Ty;
		using difference_type = std::ptrdiff_t;
		using reference = typename Ty&;
		using pointer = typename Ty*;
		
		// preparing iterator to be usefull
		// overloading operators
		Iterator<Ty>& operator=(const Iterator<Ty>&) = default;
		Iterator<Ty>& operator=(Iterator* p_iter) { instance = p_iter; return (*this); }

		reference operator*() const { return *instance; }
		//const reference operator*() const { return *instance; }

		pointer operator->() const { return instance; }

		Iterator& operator++() { ++instance; return *this; }
		Iterator operator++(int) { return Iterator(instance++); }

		operator bool() const {
			if (instance) return true;
			return false;
		}
		
		// get methods
		Ty* get() const { return instance; }
		const Ty* cget() const { return instance; }

	private:
		// pointer to a linked list on which we will work
		Ty* instance;
};
