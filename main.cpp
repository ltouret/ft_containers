#include "vector.hpp"
#include <vector>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	};
};

int	main()
{
	{
		ft::vector<int> vec;
		for (int i = 0; i < 10; ++i) {vec.push_back(i);};
		ft::vector<int>::iterator rit = vec.begin();
		std::vector<int> svec;
		for (int i = 0; i < 10; ++i) {svec.push_back(i);};
		std::vector<int>::iterator srit = svec.begin();

		std::cout << *(rit + 2) <<std::endl;
		std::cout << *(2 + rit) <<std::endl;
		std::cout << *(rit) <<std::endl;
		std::cout << *(srit + 2) <<std::endl;
		std::cout << *(2 + srit) <<std::endl;
		std::cout << *(srit) <<std::endl;
	}
	return 0;
}
