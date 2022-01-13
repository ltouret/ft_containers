# include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
		public:
		typedef T	value_type;
		typedef T&	reference;
		typedef T*	pointer;
		pointer		_ptr; // TODO send this to protected

		random_access_iterator(void): _ptr(NULL) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator(const random_access_iterator &to_cpy) : _ptr(to_cpy._ptr) {}
		random_access_iterator	&operator=(const random_access_iterator &to_cpy)
		{
			this->_ptr = to_cpy._ptr;
			return (*this);
		}
		~random_access_iterator(void) {}

		bool					operator==(const random_access_iterator &to_cmp) {return (this->_ptr == to_cmp._ptr);}
		bool					operator!=(const random_access_iterator &to_cmp) {return (this->_ptr != to_cmp._ptr);}

		//TODO check the next two...
		reference				operator*(void) {return (*this->_ptr);}
		pointer					operator->(void) {return (this->_ptr);}

		random_access_iterator	&operator++(void)
		{
			++this->_ptr;
			return (*this);
		}
		random_access_iterator	operator++(int)
		{
			random_access_iterator	tmp(*this);
			++this->_ptr;
			return (tmp);
		}
		random_access_iterator	&operator--(void)
		{
			--this->_ptr;
			return (*this);
		}
		random_access_iterator	operator--(int)
		{
			random_access_iterator	tmp(*this);
			--this->_ptr;
			return (tmp);
		}
	};
};
