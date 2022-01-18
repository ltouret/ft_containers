# include "iterator_traits.hpp"

// TODO add const

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
		public:
		//typedef random_access_iterator<T>						iterator;
		typedef random_access_iterator<const T> 				if_const;
		typedef T				value_type;
		typedef T&				reference;
		typedef T*				pointer;
		typedef std::ptrdiff_t	difference_type;
		pointer					_ptr; // TODO send this to protected

		random_access_iterator(void): _ptr(NULL) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		//const_iterator(pointer ptr) : _ptr(ptr) {}
		random_access_iterator(const random_access_iterator &to_cpy) : _ptr(to_cpy._ptr) {}
		random_access_iterator	&operator=(const random_access_iterator &to_cpy)
		{
			this->_ptr = to_cpy._ptr;
			return (*this);
		}
		~random_access_iterator(void) {}

		//TODO ask Franco wtf this shit does
		operator if_const() const { std::cout << "YO\n"; return if_const(_ptr); }

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

		random_access_iterator	operator+(int n)
		{
			random_access_iterator	tmp(*this);
			tmp += n;
			return (tmp);
		}
		friend random_access_iterator	operator+(int n, random_access_iterator it)
		{
			random_access_iterator	tmp(it._ptr);
			tmp += n;
			return (it += n);
		}
		random_access_iterator	operator-(int n)
		{
			random_access_iterator	tmp(*this);
			tmp -= n;
			return (tmp);
		}
		difference_type			operator-(const random_access_iterator &src)
		{
			return (this->_ptr - src._ptr);
		}

		bool					operator<(const random_access_iterator &to_cmp)
		{
			return (this->_ptr < to_cmp._ptr);
		}
		bool					operator>(const random_access_iterator &to_cmp)
		{
			return (this->_ptr > to_cmp._ptr);
		}
		bool					operator<=(const random_access_iterator &to_cmp)
		{
			return (this->_ptr <= to_cmp._ptr);
		}
		bool					operator>=(const random_access_iterator &to_cmp)
		{
			return (this->_ptr >= to_cmp._ptr);
		}

		random_access_iterator	operator+=(int n)
		{
			this->_ptr += n;
			return (*this);
		}
		random_access_iterator	operator-=(int n)
		{
			this->_ptr -= n;
			return (*this);
		}

		reference				operator[](int n)
		{
			return (this->_ptr[n]);
		}
	};
};
