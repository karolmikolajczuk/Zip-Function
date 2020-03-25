#pragma once

#include <vector>
#include <variant>
#include <string>

// basing on vector library
// variant inside the container
template <typename T>
class template_container
{
	using types = std::variant<std::monostate, int, double, bool, std::string>;

	public:
		template_container() : _size { 0 }, _data { } { }
		template_container(size_t& size) : _size { size }, _data { } { }
		template_container(size_t&& size) : _size{ std::move(size)} { }
		template_container(std::vector<types>& data) : _size { data.size() }, _data { data } { }
		template_container(std::vector<types>&& data) : _data{ std::move(data) } { _size = _data.size();  }
		template_container& operator=(template_container&) = default;
		template_container& operator=(template_container&&) = default;

		const size_t size() const noexcept(true) { _size = _data.size();  return _data.size(); }

		void putData(const T& element) { this->_data.push_back({ element }); }

		decltype(auto) getDataByID(const int& element) const {	return this->_data.at(element); }

	private:
		size_t _size;
		std::vector<types> _data;
};

