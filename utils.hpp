#ifndef UTILS_HPP
# define UTILS_HPP

# include "iterator_traits.hpp"
# include "random_access_iterator.hpp"

namespace ft
{
	template <typename T>
	struct	is_integral
	{
		static const bool value = false;
	};

	template <>
	struct	is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<short unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long long unsigned>
	{
		static const bool value = true;
	};

	template <bool Cond, class T = void>
	struct	enable_if
	{
	};

	template <class T>
	struct	enable_if<true, T>
	{
		typedef T type;
	};

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	// Equal

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	// Lexicographical compare

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	// Pair

	template <class T1, class T2>
	struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

		// constructor

		pair(): first(), second() {};

		pair(const first_type &a, const second_type &b) : first(a), second(b) {};

		// TODO dis is useless
		template<class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {};

		pair	&operator=(const pair &pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	ft::pair<T1,T2>	make_pair(T1 x, T2 y) {return (ft::pair<T1,T2>(x,y));};

	template <class T1, class T2>
	bool	operator==(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return lhs.first == rhs.first && lhs.second == rhs.second;}

	template <class T1, class T2>
	bool	operator!=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return !(lhs == rhs);}

	template <class T1, class T2>
	bool	operator<(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);}

	template <class T1, class T2>
	bool	operator>(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return rhs < lhs;}

	template <class T1, class T2>
	bool	operator<=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return rhs > lhs;}

	template <class T1, class T2>
	bool	operator>=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
	{return rhs < lhs;}
};

#endif
