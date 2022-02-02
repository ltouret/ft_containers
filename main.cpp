#include "stack.hpp"
#include "vector.hpp"

//#include <stack>
//#include <vector>
#include "utils.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > > // TODO add my ft::pair
	class map
	{
		public:
		typedef Key																	key_type;
		typedef T																	mapped_type;
		typedef ft::pair<const key_type, mapped_type> 								value_type;
		// add here value_compare
		typedef Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		//typedef bidirectional_iterator<value_type, pointer, reference> 			iterator;
		//typedef bidirectional_iterator<value_type, const_pointer, const_reference>	const_iterator;
		//typedef reverse_iterator<const_iterator>									const_reverse_iterator;
		//typedef reverse_iterator<iterator>											reverse_iterator;
		typedef std::ptrdiff_t														difference_type;
		typedef size_t																size_type;

		public:
		// how do i do this?
		class value_compare
		{
			friend class map;

			protected:
			Compare comp;
			value_compare	(Compare c) : comp(c) {};

			public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool	operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};
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
