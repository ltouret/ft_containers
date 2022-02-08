#include "stack.hpp"
#include "vector.hpp"

//#include <stack>
//#include <vector>
#include <map>
#include "utils.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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

		// add other stuff
		private:
		allocator_type	_alloc;
		size_type		_size;

		public:
		// how do i do this? for typedef?
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

		allocator_type	get_allocator(void) const
		{
			allocator_type cpy_allocator(_alloc);
			return (cpy_allocator);
		}
		size_type		size(void) const {return (this->_size);}
		size_type		max_size(void) const {return (this->_alloc.max_size());}
		bool			empty(void) const
		{
			if (this->_size == 0)
				return (true);
			else
				return (false);
		}

		//key_compare		key_comp(void) const;
		//value_compare		value_comp(void) const;
	};
};

int	main()
{
	{
	  std::map<int,int> mymap;

  mymap[21] = 100;
  mymap[13] = 200;
  mymap[33] = 300;
  mymap[11] = 300;
  mymap[15] = 300;
  // doesnt break if a add another...
  mymap[20] = 300;
  mymap[20] = 300;
  mymap[20] = 330;

		// TODO mymap.end() can go backwards.
	std::map<int, int>::iterator eit = mymap.end();
	//--eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
  // show content:
  for (std::map<int,int>::reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); ++it)
    std::cout << it->first << " => " << it->second << " " << &*it << '\n';
	std::cout << &*mymap.begin() << " " << &*mymap.end() << std::endl;
	std::cout << &*mymap.begin() << " " << &*(++mymap.end()) << std::endl;
  mymap[36] = 300;
  mymap[38] = 300;
  //mymap.erase(36);
	std::cout << mymap.begin()->first << " " << (++mymap.end())->first << std::endl;
	std::cout << mymap.begin()->first << " " << (--mymap.end())->first << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	}
	return 0;
}
