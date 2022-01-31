#include "stack.hpp"
#include "vector.hpp"

//#include <stack>
//#include <vector>

namespace ft
{
	//template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
	class map
	{
	};
};

int	main()
{
	{
		// test with const!
		ft::stack<ft::vector<int> > stark;
		ft::stack<ft::vector<int> > stark1;
		ft::vector<int> vec(4,4);
		ft::vector<int> vec1(4,4);

		stark.push(vec);
		stark1.push(vec1);

		std::cout << "member funcs tests" << std::endl;

		//stark.pop();
		std::cout << stark.empty() << std::endl;
		std::cout << stark.size() << std::endl;
		std::cout << (stark.top()[0]) << std::endl;

		std::cout << "" << std::endl;

		//stark1.pop();
		std::cout << stark1.empty() << std::endl;
		std::cout << stark1.size() << std::endl;
		std::cout << (stark1.top()[0]) << std::endl;

		std::cout << "" << std::endl;
		std::cout << "equals tests" << std::endl;

		std::cout << (stark == stark1) << std::endl;
		std::cout << (stark != stark1) << std::endl;
		std::cout << (stark < stark1) << std::endl;
		std::cout << (stark <= stark1) << std::endl;
		std::cout << (stark > stark1) << std::endl;
		std::cout << (stark >= stark1) << std::endl;
	}
	return 0;
}
