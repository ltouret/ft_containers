#ifndef SET_HPP
# define SET_HPP

#include <iostream>
#include "utils.hpp"
#include "node.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
		public:
		typedef Key																	key_type;
		typedef Key									 								value_type;
		// try compare like this?
		typedef Compare																key_compare;
		typedef Compare																value_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef ft::const_bidirectional_iterator<value_type>						iterator;
		typedef ft::const_bidirectional_iterator<value_type>						const_iterator;
		typedef ft::reverse_iterator<iterator>										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef std::ptrdiff_t														difference_type;
		typedef size_t																size_type;
		typedef Node<value_type>													map_node;
		typedef typename Alloc::template rebind<map_node>::other					alloc_node;

		private:

		map_node		*_root;
		map_node		*_end;
		size_type		_size;
		key_compare		_compare;
		alloc_node		_alloc;

		public:

		// constructor

		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
		_root(),  _size(0), _compare(comp), _alloc(alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
		}

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
		_root(), _size(0), _compare(comp), _alloc(alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			insert(first, last);
		}

		set(const set &x):
		_root(), _size(0), _compare(x._compare), _alloc(x._alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			insert(x.begin(), x.end());
		}

		~set(void)
		{
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
			if (this->_size)
				clearTree(_root);
		}

		set	&operator=(const set &x)
		{
			set	tmp(x);

			this->swap(tmp);
			return (*this);
		}

		// iterators

		iterator				begin(void)
		{
			if (!this->size())
				return (this->end());
			else
				return (iterator(_root->minimum(_root), _end));
		}

		const_iterator			begin(void) const
		{
			if (!this->size())
				return (this->end());
			else
				return (const_iterator(_root->minimum(_root), _end));
		}

		iterator				end(void) {return iterator(_end, _end);}
		const_iterator			end(void) const {return const_iterator(_end, _end);}

		reverse_iterator		rbegin(void) {return reverse_iterator(end());}
		const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(end());}

		reverse_iterator		rend(void) {return reverse_iterator(begin());}
		const_reverse_iterator	rend(void) const {return const_reverse_iterator(begin());}

		// member funcs

		bool				empty(void) const
		{
			if (this->_size == 0)
				return (true);
			else
				return (false);
		}

		size_type			size(void) const {return (this->_size);}

		size_type			max_size(void) const {return (this->_alloc.max_size());}

		pair<iterator, bool>	insert(const value_type &val)
		{
			map_node	*newmap_node = NULL;

			if (_root == NULL)
			{
				newmap_node = new_node(val, NULL);
				newmap_node->color = BLACK;
				_root = newmap_node;
				_end->parent = _end->maximum(_root);
			}
			else
			{
				map_node	*temp = search(val);

				if (!_compare(val, temp->value) && !_compare(temp->value, val))
					return (ft::make_pair(iterator(temp, _end), false));

				newmap_node = new_node(val, temp);

				if (_compare(val, temp->value))
					temp->left = newmap_node;
				else
					temp->right = newmap_node;

				fixRedRed(newmap_node);
				_end->parent = _end->maximum(_root);
			}
			return (ft::make_pair(iterator(newmap_node, _end), true));
		}

		iterator				insert(iterator position, const value_type &val)
		{
			(void) position;
			return (insert(val).first);
		}

		template<class InputIterator>
		void					insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void		erase(iterator position)
		{
			erase(*position);
		}

		size_type	erase(const key_type &key)
		{
			if (_root == NULL)
				return (0);

			map_node	*v = search(key);

			if (!_compare(key, v->value) && !_compare(v->value, key))
			{
				deletemap_node(v);
				_end->parent = _end->maximum(_root);
				return (1);
			}
			return (0);
		}

		void		erase(iterator first, iterator last)
		{
			size_type	len = 0;
			iterator	tmp(first);
			key_type	key;

			while (tmp != last)
			{
				len++;
				tmp++;
			}

			while (len--)
			{
				tmp = (first);
				++first;
				key = *first;
				erase(tmp);
				first = find(key);
			}
		}

		void		swap(set &x)
		{
			size_type	tmp_size;
			map_node	*tmp_root;
			map_node	*tmp_end;

			tmp_size = this->_size;
			tmp_root = this->_root;
			tmp_end = this->_end;

			this->_size = x._size;
			this->_root = x._root;
			this->_end = x._end;

			x._size = tmp_size;
			x._root = tmp_root;
			x._end = tmp_end;
		}

		void			clear(void) {erase(begin(), end());};

		key_compare		key_comp(void) const {return (_compare);}

		value_compare	value_comp(void) const {return (value_compare(_compare));}

		iterator		find(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(k, *it) && !_compare(*it, k))
					return (it);
			}
			return (this->end());
		}

		const_iterator	find(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(k, *it) && !_compare(*it, k))
					return (it);
			}
			return (this->end());
		}

		size_type		count(const key_type &k) const
		{
			if (this->find(k) != this->end())
				return (1);
			return (0);
		}

		iterator		lower_bound(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(*it, k))
					return (it);
			}
			return (this->end());
		}

		const_iterator	lower_bound(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(*it, k))
					return (it);
			}
			return (this->end());
		}

		iterator		upper_bound(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_compare(k, *it))
					return (it);
			}
			return (this->end());
		}

		const_iterator	upper_bound(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_compare(k, *it))
					return (it);
			}
			return (this->end());
		}

		pair<iterator, iterator>				equal_range(const key_type &k)
		{
			iterator	lower = lower_bound(k);
			iterator	upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		}

		pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
		{
			const_iterator	lower = lower_bound(k);
			const_iterator	upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		}

		allocator_type	get_allocator(void) const
		{
			allocator_type cpy_allocator(_alloc);
			return (cpy_allocator);
		}

		private:

		// private funcs for tree

		void	clearTree(map_node *node)
		{
			if (node)
			{
				clearTree(node->left);
				clearTree(node->right);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
		}

		void	leftRotate(map_node *x)
		{
			map_node	*nParent = x->right;

			if (x == _root)
				_root = nParent;

			x->moveDown(nParent);
			x->right = nParent->left;

			if (nParent->left != NULL)
				nParent->left->parent = x;

			nParent->left = x;
		}

		void	rightRotate(map_node *x)
		{
			map_node	*nParent = x->left;

			if (x == _root)
				_root = nParent;

			x->moveDown(nParent);
			x->left = nParent->right;

			if (nParent->right != NULL)
				nParent->right->parent = x;

			nParent->right = x;
		}

		void	swapColors(map_node *x1, map_node *x2)
		{
			COLOR temp;
			temp = x1->color;
			x1->color = x2->color;
			x2->color = temp;
		}

		void	swapValues(map_node *u, map_node *v)
		{
			map_node	temp(u->value);
			temp.parent = u->parent;
			temp.left = u->left;
			temp.right = u->right;
			temp.color = u->color;

			_alloc.destroy(u);
			_alloc.construct(u, v->value);

			u->parent = temp.parent;
			u->left = temp.left;
			u->right = temp.right;
			u->color = temp.color;

			map_node	temp2(v->value);
			temp2.parent = v->parent;
			temp2.left = v->left;
			temp2.right = v->right;
			temp2.color = v->color;

			_alloc.destroy(v);
			_alloc.construct(v, temp.value);

			v->parent = temp2.parent;
			v->left = temp2.left;
			v->right = temp2.right;
			v->color = temp2.color;
		}

		void	fixRedRed(map_node *x)
		{
			if (x == _root)
			{
				x->color = BLACK;
				return;
			}

			map_node	*parent = x->parent;
			map_node	*grandparent = parent->parent;
			map_node	*uncle = x->uncle();

			if (parent->color != BLACK)
			{
				if (uncle != NULL && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grandparent->color = RED;
					fixRedRed(grandparent);
				}
				else
				{
					if (parent->isOnLeft())
					{
						if (x->isOnLeft())
							swapColors(parent, grandparent);
						else
						{
							leftRotate(parent);
							swapColors(x, grandparent);
						}
						rightRotate(grandparent);
					}
					else
					{
						if (x->isOnLeft())
						{
							rightRotate(parent);
							swapColors(x, grandparent);
						}
						else
							swapColors(parent, grandparent);
						leftRotate(grandparent);
					}
				}
			}
		}

		map_node	*successor(map_node *x)
		{
			map_node	*temp = x;

			while (temp && temp->left != NULL)
				temp = temp->left;
			return temp;
		}

		map_node	*BSTreplace(map_node *x)
		{
			if (x->left != NULL and x->right != NULL)
				return successor(x->right);

			if (x->left == NULL and x->right == NULL)
				return NULL;

			if (x->left != NULL)
				return x->left;
			else
				return x->right;
		}

		void	deletemap_node(map_node *v)
		{
			map_node	*u = BSTreplace(v);
			map_node	*parent = v->parent;
			bool		uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));

			if (u == NULL)
			{
				if (v == _root)
					_root = NULL;
				else
				{
					if (uvBlack)
						fixDoubleBlack(v);
					else
					{
						if (v->sibling() != NULL)
							v->sibling()->color = RED;
					}
					if (v->isOnLeft())
						parent->left = NULL;
					else
						parent->right = NULL;
				}
				_alloc.destroy(v);
				_alloc.deallocate(v, 1);
				this->_size--;
				return;
			}
			if (v->left == NULL or v->right == NULL)
			{
				if (v == _root)
				{
					_alloc.destroy(v);
					_alloc.deallocate(v, 1);
					u->parent = NULL;
					u->right = NULL;
					u->left = NULL;
					u->color = BLACK;
					_root = u;
					this->_size--;
				}
				else
				{
					if (v->isOnLeft())
						parent->left = u;
					else
						parent->right = u;

					_alloc.destroy(v);
					_alloc.deallocate(v, 1);
					this->_size--;
					u->parent = parent;

					if (uvBlack)
						fixDoubleBlack(u);
					else
						u->color = BLACK;
				}
				return;
			}
			swapValues(u, v);
			deletemap_node(u);
		}

		void	fixDoubleBlack(map_node *x)
		{
			if (x == _root)
				return;

			map_node	*sibling = x->sibling();
			map_node	*parent = x->parent;

			if (sibling == NULL)
				fixDoubleBlack(parent);
			else
			{
				if (sibling->color == RED)
				{
					parent->color = RED;
					sibling->color = BLACK;
					if (sibling->isOnLeft())
						rightRotate(parent);
					else
						leftRotate(parent);
					fixDoubleBlack(x);
				}
				else
				{
					if (sibling->hasRedChild())
					{
						if (sibling->left != NULL and sibling->left->color == RED)
						{
							if (sibling->isOnLeft())
							{
								sibling->left->color = sibling->color;
								sibling->color = parent->color;
								rightRotate(parent);
							}
							else
							{
								sibling->left->color = parent->color;
								rightRotate(sibling);
								leftRotate(parent);
							}
						}
						else
						{
							if (sibling->isOnLeft())
							{
								sibling->right->color = parent->color;
								leftRotate(sibling);
								rightRotate(parent);
							}
							else
							{
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								leftRotate(parent);
							}
						}
						parent->color = BLACK;
					}
					else
					{
						sibling->color = RED;
						if (parent->color == BLACK)
							fixDoubleBlack(parent);
						else
							parent->color = BLACK;
					}
				}
			}
		}

		map_node	*search(const key_type &key)
		{
			map_node *temp = _root;

			while (temp != NULL)
			{
				if (_compare(key, temp->value))
				{
					if (temp->left == NULL)
						break;
					else
						temp = temp->left;
				}
				else if (!_compare(key, temp->value) && !_compare(temp->value, key))
					break;
				else
				{
					if (temp->right == NULL)
						break;
					else
						temp = temp->right;
				}
			}
			return temp;
		}

		map_node				*new_node(const value_type &val, map_node *parent)
		{
			map_node	*newNode = _alloc.allocate(1);
			_alloc.construct(newNode, val);
			newNode->parent = parent;
			this->_size++;
			return (newNode);
		}

	};

	// non-member funcs overloads

	template <class Key, class Compare, class Alloc>
	bool	operator==(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class Compare, class Alloc>
	bool	operator!=(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool	operator<(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class Compare, class Alloc>
	bool	operator<=(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class Key, class Compare, class Alloc>
	bool	operator>(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool	operator>=(const set<Key,Compare,Alloc> &lhs, const set<Key,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class Compare, class Alloc>
	void	swap(ft::set<Key,Compare,Alloc> &lhs, ft::set<Key,Compare,Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
};

#endif
