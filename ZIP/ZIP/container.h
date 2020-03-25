#pragma once

#include <memory>
#include <iostream>

template<class T_T>
class container
{
	//using node_ptr = std::unique_ptr<Node>;
	struct Node {
		// value of 
		T_T value;

		// navigation
		Node* next;

		// constructor
		Node() : value{ NULL }, next{ nullptr } { }
		Node(T_T _val, Node* _next = nullptr) : value{ _val }, next{ _next } {	}
	};

	public:
	
		container() : first{ nullptr } { }
	
		container(container& _anothercontainer)
		{ first = _anothercontainer.front(); }

		container& operator=(container& _anothercontainer) 
		{ first = _anothercontainer.front(); }

		container(container&&) = delete;
		container& operator=(container&&) = delete; 

		void printContainer() {
			Node* current = first;
		
			size_t position = 1;
			while (current != nullptr) {
				std::cout << position++ << ": value=" 
						<< current->value << " address=" 
						<< current << '\n';
				current = current->next;			
			}
		}
	
		size_t size() {
			size_t size_v = 0;
			Node* current = first;
			while (current != nullptr) {
				//std::cout << current->value << std::endl;
				if (current) ++size_v;
				current = current->next;
			}

			return size_v;
		}

		T_T& getElement(int& position) {
			Node* current = first;
			for (int index = 0; ; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				if (index == position) return current;

				current = current->next;
			}
		}

		T_T& getElement(int&& position) {
			Node* current = first;
			for (int index = 0; ; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				if (index == position) return current;

				current = current->next;
			}
		}

		size_t getPosition(T_T& element) {
			Node* current = first;
			for (size_t index = 0; current != nullptr; ++index) {
				if (std::is_same<decltype(element), decltype(current->value)>) {
					if (current->value == element) return index;
				}
				else
					current = current->next;
			}
			return -1;
		}

		size_t getPosition(T_T&& element) {
			Node* current = first;
			for (size_t index = 0; current != nullptr; ++index) {
				if (std::is_same<decltype(element), decltype(current->value)>) {
					if (current->value == element) return index;
				}
				else
					current = current->next;
			}
			return -1;
		}

		void insertElement(int& position, T_T& element) {
			Node* current = first;
			Node* new_node;
			for (size_t index = 0; index <= position; ++index) {
				// no way 
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");

				if (current->next == nullptr && index + 1 == position) {
					current->next = new_node;
					new_node->next = nullptr;
					new_node->value = element;
					break;
				}
				else if (current && index + 1 == position) {
					new_node->next = current->next;
					current->next = new_node;
					new_node->value = element;
					break;
				}
				else
					current = current->next;
			}
		}
		void insertElement(int& position, T_T&& element) {
			Node* current = first;
			Node* new_node;
			for (size_t index = 0; index <= position; ++index) {
				// no way 
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");

				if (current->next == nullptr && index + 1 == position) {
					current->next = new_node;
					new_node->next = nullptr;
					new_node->value = element;
					break;
				}
				else if (current && index + 1 == position) {
					new_node->next = current->next;
					current->next = new_node;
					new_node->value = element;
					break;
				}
				else
					current = current->next;
			}
		}
		void insertElement(int&& position, T_T& element) {
			Node* current = first;
			Node* new_node;
			for (size_t index = 0; index <= position; ++index) {
				// no way 
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");

				if (current->next == nullptr && index + 1 == position) {
					current->next = new_node;
					new_node->next = nullptr;
					new_node->value = element;
					break;
				}
				else if (current && index + 1 == position) {
					new_node->next = current->next;
					current->next = new_node;
					new_node->value = element;
					break;
				}
				else
					current = current->next;
			}
		}

		void insertElement(int&& position, T_T&& element) {
			Node* current = first;
			Node* new_node;
			for (size_t index = 0; index <= position; ++index) {
				// no way 
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");

				if (current->next == nullptr && index + 1 == position) {
					current->next = new_node;
					new_node->next = nullptr;
					new_node->value = element;
					break;
				}
				else if (current && index + 1 == position) {
					new_node->next = current->next;
					current->next = new_node;
					new_node->value = element;
					break;
				}
				else
					current = current->next;
			}
		}

		void pushElement(T_T& element) {
			if (first == nullptr) {
				this->first = new Node;
				this->first->value = element;
				this->first->next = nullptr;
			}
			else {
				Node* current = first;
				while (current != nullptr) {
					if (current->next == nullptr) {
						current->next = new Node(element);
						break;
					}
					current = current->next;
				}
			}
		}

		void pushElement(T_T&& element) {
			// there is no first value
			if (first == nullptr) {
				// then prepare 
				this->first = new Node;
				this->first->value = element;
				this->first->next = nullptr;
			}
			else {
				Node* current = first;
				while (current != nullptr) {
					if (current->next == nullptr) {
						Node* test = new Node(element, nullptr);
						Node* new_model = new Node();
						new_model->next = nullptr;
						new_model->value = element;
						current->next = new_model;
						break;
					}
					current = current->next;
				}
			}
		}

		T_T& popElement() {
			// take value
			auto val = first->value;
			auto mem = first->next;
		
			// make memory free
			first->value = NULL;
			first->next = nullptr;

			// set first 
			first = mem;
		
			return val;
		}

		T_T& popElement(int& position) {
			Node* current = first;
			for (size_t index = 0; index <= position; ++index) {
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");
				if (current != nullptr && index+1 == position) {
					auto popped_node = current->next;
					current->next = current->next->next;
					popped_node->next = nullptr;
					return popped_node->value;
				}
				current = current->next;
			}
		}

		T_T& popElement(int&& position) {
			Node* current = first;
			for (size_t index = 0; index <= position; ++index) {
				if (current == nullptr && index != position)
					throw std::out_of_range("You are out of range");
				else if (current != nullptr && index + 1 == position) {
					auto popped_node = current->next;
					current->next = current->next->next;
					popped_node->next = nullptr;
					return popped_node->value;
				}
				current = current->next;
			}
		}

		void removeElement(T_T& element) {
			Node* current = first;
			for (size_t index = 0; ; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				else if (current->next->value == element) { current->next = current->next->next; }
				else current = current->next;
			}
		}

		void removeElement(T_T&& element) {
			Node* current = first;
			for (size_t index = 0; ; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				else if (current->next->value == element) { current->next = current->next->next; }
				else current = current->next;
			}
		}

		void removeAt(size_t& position) {
			Node* current = first;
			for (size_t index = 0; index <= position; ++index) {
				if (current == nullptr && index != position) throw std::out_of_range("You are out of range");
				else if (current && index + 1 == position) { current->next = current->next->next; }
				else current = current->next;
			}
		}

		void removeAt(size_t&& position) {
			Node* current = first;
			for (size_t index = 0; index <= position; ++index) {
				if (current == nullptr && index != position) throw std::out_of_range("You are out of range");
				else if (current && index + 1 == position) { current->next = current->next->next; }
				else current = current->next;
			}
		}

		Node* front() {
			return first;
		}

		Node* back() {
			Node* current = first;
			while (current != nullptr) {
				if (current->next == nullptr) return current;
				current = current->next;
			}
		}

		Node* operator[](int& _index) {
			Node* current = first;
			for (size_t index = 0; index <= _index; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				if (index == _index) return current;
				current = current->next;
			}
			return nullptr;
		}

		Node* operator[](int&& _index) {
			Node* current = first;
			for (size_t index = 0; index <= _index; ++index) {
				if (current == nullptr) throw std::out_of_range("You are out of range");
				if (index == _index) return current;
				current = current->next;
			}
			return nullptr;
		}


	private:
		Node* first;

};

