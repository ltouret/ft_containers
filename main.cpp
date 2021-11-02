// TODO get this into its own file (vector)
// add ifndef protection to file

# include <iostream>
# include <vector>

template < class T, class Alloc = std::allocator<T> > 
class vector {
	public:
	typedef T												value_type;
	typedef Alloc											allocator_type;
	typedef T&												reference;
	typedef const T&										const_reference;
	typedef T*												pointer;
	typedef const T*										const_pointer;
	//typedef random_access_iterator<T>		 				iterator;
	//typedef random_access_iterator<const T> 				const_iterator;
	//typedef reverse_iterator<const_iterator>				const_reverse_iterator;
	//typedef reverse_iterator<iterator>					reverse_iterator;
	typedef std::ptrdiff_t									difference_type;
	typedef size_t											size_type;

	private:
	size_type				_size;
	size_type				_capacity;
	allocator_type			_alloc;
	pointer 				_array;

	size_type		size() const {return (this->_size);}
	size_type		max_size() const {return (this->alloc.max_size);}
	size_type		capacity() const {return (this->_capacity);}
	bool			empty() const
	{
		if (this->_size == 0)
			return (true);
		else
			return (false);
	}
	reference		operator[] (size_type n)
	{
		reference	r = *(this->_array + n);
		return (r);
	}
	const_reference	operator[] (size_type n) const
	{
		const_reference	r = *(this->_array + n);
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
		this->_alloc.construct(&this->_array[_size], val);
		this->_size++;
		}
		return ;
	}
	void			pop_back(void)
	{
		if (this->_size > 1)
		{
			this->_alloc.destroy(&this->_array[this->_size - 1]);
			this->_size--;
		}
		return ;
	}
};

int	main()
{
	/*
	std::vector<float> hey;
	hey.push_back(5.1);
	(*hey.begin())++;
	std::cout << hey[0] << std::endl;
	*/
	return (0);
}
