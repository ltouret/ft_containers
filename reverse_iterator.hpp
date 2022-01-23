#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

// TODO fix tabs :d

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
		typedef Iterator													iterator_type;
		typedef reverse_iterator<const Iterator> 							const_iterator;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;
		// TODO get this in protected

		// constructor
		reverse_iterator() : _current () {};
		reverse_iterator(iterator_type it) : _current(it) {};
		template<class Iter>
		reverse_iterator(const reverse_iterator<Iter> &to_cpy) : _current(to_cpy.base()) {};
		~reverse_iterator() {};

		operator const_iterator(void) const {return const_iterator(_current);}

		// member functions
		template <class Iter>
		reverse_iterator	&operator=(const reverse_iterator<Iter> &to_cpy)
		{
			this->_current = to_cpy.base();
			return (*this);
		}
		iterator_type		base(void) const {return (this->_current);};
		reference			operator*(void) const {iterator_type tmp = this->base(); return (*--tmp);};
		pointer				operator->(void) const {iterator_type tmp = this->base(); return (--tmp);}; // check if this works
		reference			operator[](difference_type n) const {std::cout <<"i am "<< -n-1 << std::endl; return (this->base()[-n-1]);}
		// check if this works //TODO fix this doesnt work and change base to _current cos faster
		reverse_iterator	&operator++(void) {--this->_current; return (*this);};
		reverse_iterator	operator++(int) {reverse_iterator tmp = *this; --this->_current; return (tmp);};
		reverse_iterator	&operator--(void) {++this->_current; return (*this);};
		reverse_iterator	operator--(int) {reverse_iterator tmp = *this; ++this->_current; return (tmp);};
		reverse_iterator	operator+(difference_type n) const {return (reverse_iterator(this->base() - n));};
		reverse_iterator	operator-(difference_type n) const {return (reverse_iterator(this->base() + n));};
		reverse_iterator	&operator+=(difference_type n) {this->_current -= n; return (*this);};
		reverse_iterator	&operator-=(difference_type n) {this->_current += n; return (*this);};

		protected: // test agin with this??
		iterator_type	_current;
	};
	// not member functions
	// TODO check if this works
	template< class Iterator1, class Iterator2 >
	bool	operator==(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool	operator!=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool	operator>(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool	operator>=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool	operator<(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool	operator<=(const ft::reverse_iterator<Iterator1> &lhs,
				const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template<class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
	{
		return (reverse_iterator<Iterator>(it.base() - n));
	}
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
};

#endif
