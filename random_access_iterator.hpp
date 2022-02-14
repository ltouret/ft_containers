#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

// TODO clean file, fix format

namespace ft
{
	// TODO should this be Class?? 
	template <class T>
	class random_access_iterator
	{
		public:
		typedef std::random_access_iterator_tag					iterator_category;
		typedef random_access_iterator<T>						iterator;
		typedef random_access_iterator<const T> 				const_iterator;
		typedef T												value_type;
		typedef T&												reference;
		typedef T*												pointer;
		typedef std::ptrdiff_t									difference_type;

		protected:
		pointer													_ptr;

		// constructor

		public:
		random_access_iterator(void): _ptr(NULL) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator(const random_access_iterator &to_cpy) : _ptr(to_cpy._ptr) {}
		random_access_iterator	&operator=(const random_access_iterator &to_cpy)
		{
			this->_ptr = to_cpy._ptr;
			return (*this);
		}
		~random_access_iterator(void) {}

		operator const_iterator(void) const {return const_iterator(_ptr);}

		// member functions

		bool					operator==(const random_access_iterator &to_cmp) const {return (this->_ptr == to_cmp._ptr);}
		bool					operator!=(const random_access_iterator &to_cmp) const {return (this->_ptr != to_cmp._ptr);}

		reference				operator*(void) const {return (*this->_ptr);}
		pointer					operator->(void) const {return (this->_ptr);}

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

		random_access_iterator	operator+(difference_type n) const
		{
			random_access_iterator	tmp(*this);
			tmp += n;
			return (tmp);
		}
		friend random_access_iterator	operator+(difference_type n, random_access_iterator it)
		{
			random_access_iterator	tmp(it._ptr);
			tmp += n;
			return (tmp);
		}
		random_access_iterator	operator-(difference_type n) const
		{
			random_access_iterator	tmp(*this);
			tmp -= n;
			return (tmp);
		}
		difference_type			operator-(const random_access_iterator &src) const
		{
			return (this->_ptr - src._ptr);
		}

		bool					operator<(const random_access_iterator &to_cmp) const
		{
			return (this->_ptr < to_cmp._ptr);
		}
		bool					operator>(const random_access_iterator &to_cmp) const
		{
			return (this->_ptr > to_cmp._ptr);
		}
		bool					operator<=(const random_access_iterator &to_cmp) const
		{
			return (this->_ptr <= to_cmp._ptr);
		}
		bool					operator>=(const random_access_iterator &to_cmp) const
		{
			return (this->_ptr >= to_cmp._ptr);
		}

		random_access_iterator	operator+=(difference_type n)
		{
			this->_ptr += n;
			return (*this);
		}
		random_access_iterator	operator-=(difference_type n)
		{
			this->_ptr -= n;
			return (*this);
		}

		reference				operator[](difference_type n) const
		{
			return (this->_ptr[n]);
		}
	};
};

#endif
