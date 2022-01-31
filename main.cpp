#include "vector.hpp"
#include <vector>
#include <stack>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
		typedef T												value_type;
		typedef Container										container_type;
		typedef size_t											size_type;

		protected:
		container_type											_c;

		//constructor

		public:
		explicit			stack(const container_type &ctnr = container_type()): _c(ctnr) {};

		// member funcs

		bool				empty(void) const {return (this->_c.empty());}
		size_type			size(void) const {return (this->_c.size());}
		value_type			&top(void) {return (this->_c.back());}
		const value_type	&top(void) const {return (this->_c.back());}
		void				push(const value_type &val) {this->_c.push_back(val);}
		void				pop(void) {this->_c.pop_back();}

		// non-member funcs overloads

		friend bool	operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs._c == rhs._c);
		}
		friend bool	operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs._c < rhs._c);
		}
	};

	template <class T, class Container>
	bool	operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Container>
	bool	operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Container>
	bool	operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool	operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (!(lhs < rhs));
	}
};

int	main()
{
	{
		// test with const!
		ft::stack<int, ft::vector<int> > stark;
		ft::stack<int, ft::vector<int> > stark1;

		stark.push(4);
		stark.push(4);
		stark.push(4);
		stark1.push(4);
		stark1.push(4);
		stark1.push(4);

		std::cout << "member funcs tests" << std::endl;

		stark.pop();
		std::cout << stark.empty() << std::endl;
		std::cout << stark.size() << std::endl;
		std::cout << stark.top() << std::endl;

		std::cout << "" << std::endl;

		stark1.pop();
		std::cout << stark1.empty() << std::endl;
		std::cout << stark1.size() << std::endl;
		std::cout << stark1.top() << std::endl;

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
