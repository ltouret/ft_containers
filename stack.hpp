// TODO fix format, tabs

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"// TODO should stack include vector?
//#include <vector>
//#include <stack>

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

#endif
