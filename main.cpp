// TODO get this into its own file (vector)
// fix tabs!
// add ifndef protection to file

# include <iostream>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include <vector>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public:
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef T&												reference;
		typedef const T&										const_reference;
		typedef T*												pointer;
		typedef const T*										const_pointer;
		typedef ft::random_access_iterator<T>					iterator;
		typedef ft::random_access_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef size_t											size_type;

		private:
		size_type				_size;
		size_type				_capacity;
		allocator_type			_alloc;
		pointer					_array;

		public:
		// constructor - destructor
		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(NULL) {}
		//~vector(void) {std::cout << "bye\n";}

		// iterators
		iterator		begin(void) {return iterator(&this->_array[0]);}
		const_iterator	begin(void) const {return const_iterator(&this->_array[0]);}
		iterator		end(void) {return iterator(&this->_array[_size]);}
		const_iterator	end(void) const {return const_iterator(&this->_array[_size]);}
		reverse_iterator	rbegin(void) {return reverse_iterator(end());}
		const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(end());}
		reverse_iterator	rend(void) {return reverse_iterator(begin());}
		const_reverse_iterator	rend(void) const {return const_reverse_iterator(begin());}

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
		reference		operator[] (size_type n)
		{
			reference	r = this->_array[n];
			return (r);
		}
		const_reference	operator[] (size_type n) const
		{
			const_reference	r = this->_array[n];
			return (r);
		}
		reference		at(size_type n)
		{
			//if (n >= this->_size)
			//	throw std::out_of_range(out_of_range_msg(n));
			reference	r = *(this->_array + n);
			return (r);
		}
		const_reference	at(size_type n) const
		{
			//if (n >= this->_size)
			//	throw std::out_of_range(out_of_range_msg(n));
			const_reference	r = *(this->_array + n);
			return (r);
		}
		reference		front()
		{
			reference	r = *(this->_array);
			return (r);
		}
		const_reference	front() const
		{
			const_reference	r = *(this->_array);
			return (r);
		}
		reference		back()
		{
			reference	r = *(this->_array + this->_size - 1);
			return (r);
		}
		const_reference	back() const
		{
			const_reference	r = *(this->_array + this->_size - 1);
			return (r);
		}
		allocator_type	get_allocator() const
		{
			allocator_type cpy_allocator(_alloc);
			return (cpy_allocator);
		}
		void			reserve(size_type n)
		{
			if (n > this->max_size())
			{
				// TODO length excep
				//if (n > this->max_size())
				//throw std::length_error("vector::reserve");
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
		// if i try to resize till max_size what happens?
		void			resize(size_type n, value_type val = value_type())
		{
			if (n < this->_size)
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_array[i]);
				this->_size = n;
			}
			else
			{
				reserve(n);
				for (size_type i = 0; i < n; ++i)
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
			if (this->_size > 0)
			{
				this->_alloc.destroy(&this->_array[this->_size - 1]);
				this->_size--;
			}
			return ;
		}
		void			clear(void)
		{
			// check if this works?
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
		//TODO assign can work with only push_back...
		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last)
		{
			// protection is useless cos if last - first < 0 then undefined behavior
			// what if capacity is 0 and I alloc 0?
			int	n = last - first;
			if (n < 0)
				n = 0;
			clear();
			reserve(n);
			for (; first != last; ++first)
			{
				this->_alloc.construct(&this->_array[_size], *first);
				this->_size++;
			}
			return ;
		}
		void			assign(size_type n, const value_type& val)
		{
			// if n negative? undefined?
			clear();
			reserve(n);
			while (this->_size < n)
			{
				this->_alloc.construct(&this->_array[_size], val);
				this->_size++;
			}
			return ;
		}
		/*
		iterator	erase(iterator position)
		{
			return ;
		}
		iterator	erase(iterator first, iterator last)
		{
			return ;
		}
		*/
	};
};

int	main()
{
	ft::vector<float> hey;
	float dis[5];
	dis[0] = 1.1;
	dis[1] = 1.2;
	dis[2] = 1.3;
	dis[3] = 1.4;
	hey.push_back(5.1);
	hey.assign(100, 10.1);
	hey.pop_back();
	//std::cout << hey.size() << std::endl;
	//(*hey.begin())++;
	ft::random_access_iterator<float> hy(&dis[0]);
	//hy++;
	std::cout << *(hy + 1) << std::endl; 
	std::cout << *(1 + hy) << std::endl; 
	//std::cout << hy;
	std::cout << *hy << std::endl;
	std::cout << (dis[0] -= -2) << std::endl;
	ft::vector<float> dev;
	ft::vector<float>::iterator itr(&dev[0]);
	itr = dev.begin();
	std::cout << *hy << std::endl;
	const ft::vector<float> dav;
	const ft::vector<float>::const_iterator itra = dav.begin();//(&dev[0]);
	//const std::vector<float> lolo;
	//const std::vector<float>::const_iterator lol = lolo.begin();
	ft::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	ft::vector<int>::const_iterator itc = vec.begin();
	ft::vector<int>::const_reverse_iterator itz = vec.rbegin();
	{
	std::cout << "test reverse" << std::endl;
	std::cout << *itz << std::endl;
	itz += 1;
	std::cout << *itz << std::endl;
	itz -= 1;
	std::cout << *itz << std::endl;
	std::cout << "test reverse" << std::endl;
	}
	//itc++;
	std::cout << *itc << std::endl;
	std::cout << *itz << std::endl;
	std::cout << (vec.rend() <= vec.rbegin()) << std::endl;
	std::cout << *(1 + vec.rbegin()) << std::endl;
	std::cout << *(vec.rend() - 1) << std::endl;
	std::vector<float> lolo;
	lolo.push_back(1.3);
	lolo.push_back(1.2);
	std::vector<float>::iterator lol = lolo.begin();
	std::cout << &*lolo.begin() << " " << &*lolo.rend() << std::endl;
	std::cout << lolo.rend () - lolo.rbegin() << std::endl;
	(void) lol;
	//std::cout << *itr << std::endl;
	return (0);
}
