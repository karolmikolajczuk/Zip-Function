#pragma once

#include <any>
#include <list>
#include <string>

class JSON_Container
{
	public:		

		struct JValues
		{
			std::any value; // for single value
			std::list<std::any> values; // when it's array of values

			JValues& operator=(JValues& el) { return *this; }
		};


		JSON_Container(std::string& name, std::any& value) :
			_name{name} {
			if (value.type() == typeid(int))
				this->_value.value = std::any_cast<int>(value);
			else if (value.type() == typeid(double))
				this->_value.value = std::any_cast<double>(value);
			else if (value.type() == typeid(bool))
				this->_value.value = std::any_cast<bool>(value);
			else if (value.type() == typeid(std::string))
				this->_value.value = std::any_cast<std::string>(value);
			else if (value.type() == typeid(JSON_Container))
				this->_value.value = std::any_cast<JSON_Container>(value);

		}
		
		JSON_Container(std::string&& name, std::any&& value) :
			_name{std::move(name)} { 
			std::any v_temp = std::move(v_temp);
			if (v_temp.type() == typeid(int))
				this->_value.value = std::any_cast<int>(v_temp);
			else if (v_temp.type() == typeid(double))
				this->_value.value = std::any_cast<double>(v_temp);
			else if (v_temp.type() == typeid(bool))
				this->_value.value = std::any_cast<bool>(v_temp);
			else if (v_temp.type() == typeid(std::string))
				this->_value.value = std::any_cast<std::string>(v_temp);
			else if (v_temp.type() == typeid(JSON_Container))
				this->_value.value = std::any_cast<JSON_Container>(v_temp);
		}

		JSON_Container& operator=(JSON_Container& parameter) {
			_name = parameter.getName();
			_value = parameter._value;
		}

		std::any getValue() {
			if (!this->_value.values.size()) {
				if (this->_value.value.type() == typeid(int))
					return std::any_cast<int>(this->_value.value);
				else if (this->_value.value.type() == typeid(double))
					return std::any_cast<double>(this->_value.value);
				else if (this->_value.value.type() == typeid(bool))
					return std::any_cast<bool>(this->_value.value);
				else if (this->_value.value.type() == typeid(std::string))
					return std::any_cast<std::string>(this->_value.value);
				else if (this->_value.value.type() == typeid(JSON_Container))
					return std::any_cast<JSON_Container>(this->_value.value);
				else
					return NULL; // unknown type
			}

			return this->_value.values;
		}

		std::string getName() {
			return this->_name;
		}

		bool findJValues() {
			if (typeid(this->_value.value).name() == 
				typeid(JValues).name())
				return true;
			for (const auto& each : this->_value.values) {
				if (typeid(each).name() == 
					typeid(JValues).name())
					return true;
			}
		}

	private:

		std::string _name;
		JValues _value;
};

