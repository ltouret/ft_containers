	template <class InputIterator>
	void    assign (InputIterator first, InputIterator last)
	{
		//clear();
		for (; first != last; ++first)
			push_back(*first);
		return ;
	}

    void    assign (size_type n, const value_type& val)
    {
        //clear()
        while (n--)
            push_back(val);
        return ;
    }

    iterator    erase (iterator position)
    {
        return ;
    }

    iterator    erase (iterator first, iterator last)
    {
        return ;
    }
 