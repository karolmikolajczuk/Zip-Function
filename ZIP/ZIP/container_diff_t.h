#pragma once

#include <memory>
#include <iostream>
#include "JSON_Container.h"

class container_diff_t
{
public:

	container_diff_t() = default;
	container_diff_t(const container_diff_t& element) = default;
	container_diff_t(const container_diff_t&&) = delete;
	container_diff_t& operator=(const container_diff_t&) = default;
	container_diff_t& operator=(const container_diff_t&&) = delete;

	/*bool hasKids() {
		for (const auto& each : data) {
			if (each.findJValues())
				return true;
		}
	}*/

	//void addNewElement(std::pair<std::string, A>& element) {

	//}

	// because we have no idea what type is currently hiding in it
	// that's why the only way to "get" is by setting return-type as auto
	// returns first element which has that name and returns it's values
	decltype(auto) getValue(std::string& name) noexcept(true) {
		for(auto& var : this->data) {
			if (name == var.getName())
				return var.getValue();
		}
	}

	decltype(auto) getValue(std::string&& name) noexcept(true) {
		std::unique_ptr<std::string> parameter = 
			std::make_unique<std::string>(std::move(name));
		for (auto & var : this->data) {
			if (*parameter == var.getName())
				return var.getValue();
		}
	}

	// invoke printing json file
	void print() noexcept(true) {
		size_t nested_level = 0;
		for(auto& each_element : this->data) {
			this->printing(each_element, nested_level);
		}
	}

private:

	// printing whole json file
	void printing(JSON_Container& nested_data, size_t& nested_level) noexcept(true) {
		
		// TABS

		// make specific number of tabs
		this->printTabs(nested_level);
		
		// NAME TIME
		
		// in the same line print name and :
		std::cout << nested_data.getName() << ': ';
		
		// VALUE TIME

		// depending on value kept in memory...
		// if this is another object 
		if (typeid(nested_data.getValue()).name() == 
			typeid(JSON_Container).name()) {
			// then print open brace 
			std::cout << "{\n";
			// and invoke this method for value of current
			this->printing(std::any_cast<JSON_Container&>(nested_data.getValue()), ++nested_level);
			// end printing nested value minus 1 level
			--nested_level;
			// printing tabs
			this->printTabs(nested_level);
			// end brace
			std::cout << "}\n";
		}   // if this is whole array of objects
		else if (nested_data.getValue().type() == typeid(std::list<JSON_Container>)) {
			// assign the list of JSON_Containers to temp
			auto temp = std::any_cast<std::list<JSON_Container>>(nested_data.getValue());
			// check size of it (weird if its 0)
			if (!temp.size()) return;
			// print array open bracket
			std::cout << '[';

			// for each element of an array
			for(auto& element : temp) { // for element from std::list<elements>
				// if the type is JSON_Container then invoke the method for it
				if (element.getValue().type() == typeid(JSON_Container)) {
					// assign to temporary variable value
					auto temporary = std::any_cast<JSON_Container>(element.getValue());
					// invoke printing (nested again)
					this->printing(temporary, ++nested_level);
				}
				else { // when the values are primitive ones
					std::cout << element.getName() << ": ";
					//<< element.getValue();
					this->printPrimitives(element.getValue());
				}
			}
			std::cout << "]\n";
		} // when it's just primitive then print it
		else { 
			this->printPrimitives(nested_data.getValue());
		}
		std::cout << '\n';
	}

	// printing specific number of tabs 
	void printTabs(const size_t& nested_level) noexcept(true) {
		// make specific number of tabs
		for (unsigned int index = 0; index < nested_level; ++index) {
			std::cout << '\t';
		}
	}

	// checking type of parameter and making correct cast and printing
	void printPrimitives(std::any primitive_value) {
		if (primitive_value.type() == typeid(int))
			std::cout << std::any_cast<int>(primitive_value);
		else if (primitive_value.type() == typeid(double))
			std::cout << std::any_cast<double>(primitive_value);
		else if (primitive_value.type() == typeid(bool))
			std::cout << std::any_cast<bool>(primitive_value);
		else if (primitive_value.type() == typeid(std::string))
			std::cout << std::any_cast<std::string>(primitive_value);
		else // wtf? is it even possible?
			std::cout << "[UNKNOWN TYPE]";
	}

	std::list<JSON_Container> data;
};

