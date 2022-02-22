#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public:

		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::random_access_iterator<T>					iterator;
		typedef ft::random_access_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef size_t											size_type;

		private:

		size_type												_size;
		size_type												_capacity;
		allocator_type											_alloc;
		pointer													_array;

		// constructor

		public:

		explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(NULL) {}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):
		_size(n), _capacity(n), _alloc(alloc), _array(NULL)
		{
			this->_array = this->_alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_array[i], val);
			return ;
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0):
		_size(0), _capacity(0), _alloc(alloc), _array(NULL)
		{
			this->assign(first, last);
			return ;
		}

		vector(const vector &x):
		_size(x._size), _capacity(x._size), _alloc(x._alloc), _array(NULL)
		{
			this->_array = this->_alloc.allocate(x._size);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_array[i], x._array[i]);
			return ;
		}

		~vector(void)
		{
			this->clear();
			this->_alloc.deallocate(this->_array, this->_capacity);
			return ;
		}

		vector	&operator=(const vector &x)
		{
			vector	tmp(x);
			this->swap(tmp);
			return (*this);
		}

		// iterators

		iterator				begin(void) {return iterator(&this->_array[0]);}
		const_iterator			begin(void) const {return const_iterator(&this->_array[0]);}

		iterator				end(void) {return iterator(&this->_array[_size]);}
		const_iterator			end(void) const {return const_iterator(&this->_array[_size]);}

		reverse_iterator		rbegin(void) {return reverse_iterator(end());}
		const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(end());}

		reverse_iterator		rend(void) {return reverse_iterator(begin());}
		const_reverse_iterator	rend(void) const {return const_reverse_iterator(begin());}

		// member funcs

		size_type		size(void) const {return (this->_size);}

		size_type		max_size(void) const {return (this->_alloc.max_size());}

		size_type		capacity(void) const {return (this->_capacity);}

		bool			empty(void) const
		{
			if (this->_size == 0)
				return (true);
			else
				return (false);
		}

		reference		operator[](size_type n)
		{
			reference	r = this->_array[n];
			return (r);
		}

		const_reference	operator[](size_type n) const
		{
			const_reference	r = this->_array[n];
			return (r);
		}

		reference		at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range("_M_range_check\n");
			reference	r = *(this->_array + n);
			return (r);
		}

		const_reference	at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range("_M_range_check\n");
			const_reference	r = *(this->_array + n);
			return (r);
		}

		reference		front(void)
		{
			reference	r = *(this->_array);
			return (r);
		}

		const_reference	front(void) const
		{
			const_reference	r = *(this->_array);
			return (r);
		}

		reference		back(void)
		{
			reference	r = *(this->_array + this->_size - 1);
			return (r);
		}

		const_reference	back(void) const
		{
			const_reference	r = *(this->_array + this->_size - 1);
			return (r);
		}

		allocator_type	get_allocator(void) const
		{
			allocator_type cpy_allocator(_alloc);
			return (cpy_allocator);
		}

		void			reserve(size_type n)
		{
			if (n > this->max_size())
			{
				if (n > this->max_size())
				throw std::length_error("vector::reserve");
			}
			if (n > this->_capacity)
			{
				value_type *new_array = _alloc.allocate(n);
				for (size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.construct(&new_array[i], this->_array[i]);
					this->_alloc.destroy(&this->_array[i]);
				}
				this->_alloc.deallocate(this->_array, this->_capacity);
				this->_capacity = n;
				this->_array = new_array;
			}
			return ;
		}

		void			resize(size_type n, value_type val = value_type())
		{
			if (n < this->_size)
			{
				for (size_type i = n; i < this->_size; ++i)
					this->_alloc.destroy(&this->_array[i]);
				this->_size = n;
			}
			else if (n > this->_size)
			{
				if (n > this->_capacity)
				{
					if (this->_capacity == 0)
						reserve(n);
					else
					{
						if (this->_size * 2 >= n)
							reserve(this->_size * 2);
						else
							reserve(n);
					}
				}
				for (size_type i = this->_size; i < n; ++i)
					this->_alloc.construct(&this->_array[i], val);
				this->_size = n;
			}
			return ;
		}

		void			push_back(const value_type &val)
		{
			if (this->_size + 1 > this->_capacity)
			{
				if (this->_capacity == 0)
					reserve(1);
				else
					reserve(this->_capacity * 2);
			}
			this->_alloc.construct(&this->_array[_size], val);
			this->_size++;
			return ;
		}

		void			pop_back(void)
		{
			this->_alloc.destroy(&this->_array[this->_size - 1]);
			this->_size--;
			return ;
		}

		void			clear(void)
		{
			while (this->_size > 0)
				pop_back();
			return ;
		}

		void			swap(vector &x)
		{
			value_type	*tmp_array = this->_array;
			size_type	tmp_capacity = this->_capacity;
			size_type	tmp_size = this->_size;
			this->_array = x._array;
			this->_capacity = x._capacity;
			this->_size = x._size;
			x._array = tmp_array;
			x._capacity = tmp_capacity;
			x._size = tmp_size;
			return ;
		}

		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		assign(InputIterator first, InputIterator last)
		{
			size_type		n = 0;
			InputIterator	tmp(first);
			while (tmp != last)
			{
				tmp++;
				n++;
			}
			this->clear();
			this->reserve(n);
			for (; first != last; ++first)
			{
				this->_alloc.construct(&this->_array[_size], *first);
				this->_size++;
			}
			return ;
		}

		void			assign(size_type n, const value_type& val)
		{
			this->clear();
			this->reserve(n);
			while (this->_size < n)
			{
				this->_alloc.construct(&this->_array[_size], val);
				this->_size++;
			}
			return ;
		}

		iterator	erase(iterator pos) {return (this->erase(pos, ++pos));}

		iterator	erase(iterator first, iterator last)
		{
			iterator	tmp;

			if (first == last)
				return (last);
			tmp = first;
			this->_size -= last- first;
			while (tmp != last)
			{
				this->_alloc.destroy(&*(tmp));
				tmp++;
			}
			tmp = first;
			while (tmp != this->end())
			{
				this->_alloc.construct(&*(tmp), *(last));
				this->_alloc.destroy(&*(last));
				tmp++;
				last++;
			}
			return (first);
		}

		iterator	insert(iterator position, const value_type &val)
		{
			size_type	index = position - this->begin();

			if (this->_size + 1 > this->_capacity)
			{
				if (this->_capacity == 0)
					reserve(1);
				else
					reserve(this->_capacity * 2);
			}
			this->_size++;
			for (size_type	i = this->_size - 1; i > index; i--)
			{
				this->_alloc.construct(&(this->_array[i]), (this->_array[i - 1]));
				this->_alloc.destroy(&(this->_array[i - 1]));
			}
			this->_alloc.construct(&(this->_array[index]), (val));
			return (iterator(&this->_array[index]));
		}

		void	insert(iterator position, size_type n, const value_type &val)
		{
			if (this->_size + n > this->_capacity)
			{
				size_type	backup = position - this->begin();
				if (this->_capacity == 0)
					reserve(n);
				else
				{
					if (this->_size * 2 >= this->_size + n)
						reserve(this->_size * 2);
					else
						reserve(this->_size + n);
				}
				position = this->begin() + backup;
			}
			for (size_type	i = 0; i < n; i++)
				position = insert(position, val);
			return ;
		}

		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
		insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type		n = 0;
			InputIterator	tmp(first);
			while (tmp != last)
			{
				tmp++;
				n++;
			}
			if (this->_size + n > this->_capacity)
			{
				size_type	backup = position - this->begin();
				if (this->_capacity == 0)
					reserve(n);
				else
				{
					if (this->_size * 2 >= this->_size + n)
						reserve(this->_size * 2);
					else
						reserve(this->_size + n);
				}
				position = this->begin() + backup;
			}
			for (; first != last; ++first, ++position)
				insert(position, *first);
			return ;
		}
	};

	// non-member funcs overloads

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y) {x.swap(y);}
};

#endif
