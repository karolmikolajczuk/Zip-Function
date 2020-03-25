#include "zip.hpp"

int main() {

	auto res = tools::zip<std::list<int>, std::list<int>>(
		{ 1, 2, 3, 4 }, { 4, 5, 6, 7 });
	for (auto& list : res) {
		for (auto& element_in_list : list) {
			std::cout << element_in_list << " ";
		}
		std::cout << std::endl;
	}


	std::list<int> a1 = { 1, 2, 3, 4, 5, 6, 7 };
	std::list<int> a2 = { 83, 22, 31, 63, 88, 100 };
	std::list<int> a3 = { 0, 3, 5, 1, 4, 9 };

	for (const auto& list_from_zip : tools::zip_invoke(a1, a2, a3)) {
		for (const auto& elements : list_from_zip) {
			std::cout << elements << " ";
		}
		std::cout << std::endl;
	}



	return 1;
}