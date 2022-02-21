#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator
	{
		public:
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef bidirectional_iterator<T>					iterator;
		// l15 should be const T??? try with and without when calling if_const
		//typedef bidirectional_iterator<T> 			const_iterator;
		typedef T										value_type;
		typedef T&										reference;
		typedef T*										pointer;
		typedef std::ptrdiff_t									difference_type;
		typedef Node<T>*								iterator_type;

		protected:
		iterator_type											_ptr;
		iterator_type											_end;

		// constructor

		public:
		bidirectional_iterator(void): _ptr(NULL), _end(NULL) {}
		bidirectional_iterator(iterator_type ptr, iterator_type end) : _ptr(ptr), _end(end) {}
		bidirectional_iterator(const bidirectional_iterator &to_cpy) : _ptr(to_cpy._ptr), _end(to_cpy._end) {}
		bidirectional_iterator	&operator=(const bidirectional_iterator &to_cpy)
		{
			this->_ptr = to_cpy._ptr;
			this->_end = to_cpy._end;
			return (*this);
		}
		~bidirectional_iterator(void) {}

		// TODO test this bs
		//operator const_iterator(void) const {return const_iterator(_ptr, _end);}

		// member functions

		bool					operator==(const bidirectional_iterator &to_cmp) const {return (this->_ptr == to_cmp._ptr);}
		bool					operator!=(const bidirectional_iterator &to_cmp) const {return (this->_ptr != to_cmp._ptr);}

		reference				operator*(void) const {return (this->_ptr->value);}
		pointer					operator->(void) const {return &(this->_ptr->value);}

		// TODO test ++ -- bidirectional_iterator
		bidirectional_iterator	&operator++(void)
		{
			if (this->_ptr == this->_end->predecessor())
				this->_ptr = this->_end;
			else
				this->_ptr = this->_ptr->successor();
			return (*this);
		}
		bidirectional_iterator	operator++(int)
		{
			bidirectional_iterator	tmp(*this);
			++*this;
			return (tmp);
		}
		bidirectional_iterator	&operator--(void)
		{
			iterator_type	tmp = this->_ptr;
			while (tmp)
			{
				if (tmp->predecessor() == NULL)
					break;
				tmp = tmp->predecessor();
			}
			//std::cout << tmp->value.first << _ptr->value.first << std::endl;
			if (this->_ptr == tmp)
				this->_ptr = this->_end;
			else
				this->_ptr = this->_ptr->predecessor();
			return (*this);
		}
		bidirectional_iterator	operator--(int)
		{
			//std::cout << _ptr->value.first << std::endl;
			bidirectional_iterator	tmp(*this);
			--*this;
			return (tmp);
		}

		iterator_type					getPtr(void) const {return (this->_ptr);}
		iterator_type					getEnd(void) const {return (this->_end);}
	};

	template <class T>
	class const_bidirectional_iterator
	{
		public:
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef bidirectional_iterator<T>					iterator;
		// l15 should be const T??? try with and without when calling if_const
		typedef const_bidirectional_iterator<T> 			const_iterator;
		typedef T										value_type;
		typedef const T&										reference;
		typedef const T*										pointer;
		typedef std::ptrdiff_t									difference_type;
		typedef Node<T>*								iterator_type;

		protected:
		iterator_type											_ptr;
		iterator_type											_end;

		// constructor

		public:
		const_bidirectional_iterator(void): _ptr(NULL), _end(NULL) {}
		const_bidirectional_iterator(iterator_type ptr, iterator_type end) : _ptr(ptr), _end(end) {}
		const_bidirectional_iterator(const iterator &to_cpy) : _ptr(to_cpy.getPtr()), _end(to_cpy.getEnd()) {}
		const_bidirectional_iterator(const const_bidirectional_iterator &to_cpy) : _ptr(to_cpy._ptr), _end(to_cpy._end) {}
		const_bidirectional_iterator	&operator=(const const_bidirectional_iterator &to_cpy)
		{
			this->_ptr = to_cpy._ptr;
			this->_end = to_cpy._end;
			return (*this);
		}
		~const_bidirectional_iterator(void) {}

		// TODO test this bs
		operator const_iterator(void) const {return const_iterator(_ptr, _end);}

		// member functions

		bool					operator==(const const_bidirectional_iterator &to_cmp) const {return (this->_ptr == to_cmp._ptr);}
		bool					operator!=(const const_bidirectional_iterator &to_cmp) const {return (this->_ptr != to_cmp._ptr);}

		reference				operator*(void) const {return (this->_ptr->value);}
		pointer					operator->(void) const {return &(this->_ptr->value);}

		// TODO test ++ -- const_bidirectional_iterator
		const_bidirectional_iterator	&operator++(void)
		{
			if (this->_ptr == this->_end->predecessor())
				this->_ptr = this->_end;
			else
				this->_ptr = this->_ptr->successor();
			return (*this);
		}
		const_bidirectional_iterator	operator++(int)
		{
			const_bidirectional_iterator	tmp(*this);
			++*this;
			return (tmp);
		}
		const_bidirectional_iterator	&operator--(void)
		{
			iterator_type	tmp = this->_ptr;
			while (tmp)
			{
				if (tmp->predecessor() == NULL)
					break;
				tmp = tmp->predecessor();
			}
			//std::cout << tmp->value.first << _ptr->value.first << std::endl;
			if (this->_ptr == tmp)
				this->_ptr = this->_end;
			else
				this->_ptr = this->_ptr->predecessor();
			return (*this);
		}
		const_bidirectional_iterator	operator--(int)
		{
			//std::cout << _ptr->value.first << std::endl;
			const_bidirectional_iterator	tmp(*this);
			--*this;
			return (tmp);
		}
	};
};

#endif
