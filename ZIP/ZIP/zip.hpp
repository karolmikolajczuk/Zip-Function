#pragma once

#include "container.h"
#include <list>
#include <any>
#include <vector>

namespace tools {
	/*
		sample input:
			{1, 2, 3, 4, 5}
			{3, 4, 5, 6, 8}
			{5, 7, 9, 5, 1}

		sample output:
			{
				{ 1, 3, 5 }
				{ 2, 4, 7 }
				{ 3, 5, 9 }
				{ 4, 6, 5 }
				{ 5, 8, 1 }
			}
	*/

	/*
		tools::zip({ 1, 2, 3}, {1, 2, 3}, {1, 2, 3});
		.
		.
		.
		auto zip = {{1, 1, 1,} {2, 2, 2} {3, 3, 3}};

		zip[0] -> {1, 1, 1}
		zip[0][0] -> 1; --->

	*/

	template<typename T1, typename T2>// typename... T3>
	std::list<std::list<int>> zip(T1 arg1, T2 arg2) {//, T3... args) {
		std::list<std::list<int>> zipped;
		
		// arg1 -> std::list<int> 
		// arg2 -> std::list<int>

		if (typeid(arg1) != typeid(std::list<int>) ||
			typeid(arg2) != typeid(std::list<int>))
			throw std::exception("DifferentTypes");

		size_t min_ = (std::size(arg1) > std::size(arg2)) ? 
			std::size(arg2) : std::size(arg1);

		for (int i = 0; i < min_; ++i) {

			typename T1::const_iterator itr_1 = arg1.begin();
			std::advance(itr_1, i);

			typename T2::const_iterator itr_2 = arg2.begin();
			std::advance(itr_2, i);

			zipped.push_back({ *itr_1, *itr_2 }); 
		}


		return zipped;
	}

	template <typename T>
	class Zip {

		public:

			// understanable and way more readable name of 
			// type where we are storing data
			typedef std::vector<T> zipped_t;

			// constructor for the whole data we are 
			// going to service
			template <typename... Args>
			Zip(const T& first, const Args& ... rest) :
				minimal_size{ first.size() },
				container_of_zipps{ first.size() } {
				// invoke zip method
				this->zip(first, rest...);
			}

			// google it
			inline operator zipped_t() const { // 
				return this->container_of_zipps;
			}

			inline zipped_t operator()() const { // zipped_t()
				return this->container_of_zipps;
			}

		private:

			// unpack all of the arguments given at constructor
			// and set it into our common container
			template <typename... Args>
			void zip(const T& first, const Args& ... rest) {

				// update the minimal size of container
				if (first.size() < this->minimal_size) this->minimal_size = first.size();

				for (size_t index = 0; index < this->minimal_size; ++index) {
					
					// create iterator for unknown yet type
					typename T::const_iterator iterator = first.begin();

					// set this iterator at the next position
					std::advance(iterator, index);

					// set value of iterator in the container
					container_of_zipps[index].push_back(*iterator);
				}

				// recursive zip until 
				// unpack all elements
				return zip(rest...);

			}
			
			// when unpacked everything
			// then resize container on the minimal size
			// cause size was set at the minimal point
			// while unpacking ALL of the arguments
			inline void zip() {
				this->container_of_zipps.resize(this->minimal_size);
			}

			// the minimal size of zipped elements
			// cause we don't know at the moment how
			// many zipps are possible to be done
			size_t minimal_size;

			// the container that is going to be returned
			zipped_t container_of_zipps;
	};

	// method that returns a container from Zip class
	template<typename T, typename... Args>
	typename Zip<T>::zipped_t zip_invoke(const T& first, const Args& ... rest) {
		return tools::Zip(first, rest...);
	}
}