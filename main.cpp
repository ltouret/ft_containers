#include "stack.hpp"
#include "vector.hpp"

//#include <stack>
//#include <vector>
#include <map>
#include "utils.hpp"
#include "node.hpp"
#include "bidirectional_iterator.hpp"
//TODO erase me
#include <queue>
#include <vector>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
		typedef Key																	key_type;
		typedef T																	mapped_type;
		typedef ft::pair<const key_type, mapped_type> 								value_type;
		// add here value_compare
		typedef Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef bidirectional_iterator<key_type, mapped_type>						iterator;
		typedef bidirectional_iterator<key_type, mapped_type>						const_iterator;
		// why reverse_iterator<const> before the non const?????
		typedef reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef reverse_iterator<iterator>											reverse_iterator;
		typedef Node<value_type>													map_node;
		typedef std::ptrdiff_t														difference_type;
		typedef size_t																size_type;
		typedef typename Alloc::template rebind<map_node>::other					alloc_node;

		// add other stuff
		// TODO all is public to test!
		public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _root(),  _size(0), _compare(comp), _alloc(alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		: _root(), _size(0), _compare(comp), _alloc(alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			insert(first, last);
		}

		map(const map &x): _root(), _size(0), _compare(x._compare), _alloc(x._alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			insert(x.begin(), x.end());
		}

		void clearTree(map_node *node)
		{
			if (node)
			{
				clearTree(node->left);
				clearTree(node->right);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
		}

		~map()
		{
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
			if (this->_size)
				clearTree(_root);
			//std::cout << "bye" << std::endl;
		}

		// TOdo check if this works (operator=)
		map	&operator=(const map &x)
		{
			map	tmp(x);
			this->swap(tmp);
			return (*this);
		}

		map_node		*_root;
		map_node		*_end;
		size_type		_size;
		key_compare		_compare;
		alloc_node		_alloc;

		// left rotates the given node
		void leftRotate(map_node *x)
		{
			// new parent will be node's right child
			map_node *nParent = x->right;

			// update _root if current node is _root
			if (x == _root)
			_root = nParent;

			x->moveDown(nParent);

			// connect x with new parent's left element
			x->right = nParent->left;
			// connect new parent's left element with node
			// if it is not null
			if (nParent->left != NULL)
			nParent->left->parent = x;

			// connect new parent with x
			nParent->left = x;
		}

		void rightRotate(map_node *x) {
			// new parent will be node's left child
			map_node *nParent = x->left;

			// update _root if current node is _root
			if (x == _root)
			_root = nParent;

			x->moveDown(nParent);

			// connect x with new parent's right element
			x->left = nParent->right;
			// connect new parent's right element with node
			// if it is not null
			if (nParent->right != NULL)
			nParent->right->parent = x;

			// connect new parent with x
			nParent->right = x;
		}

		void swapColors(map_node *x1, map_node *x2) {
			COLOR temp;
			temp = x1->color;
			x1->color = x2->color;
			x2->color = temp;
		}

		// TODO check when this is needed and maybe erase
		// TODO check leaks here
		void swapValues(map_node *u, map_node *v)
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

			//std::cout << "v " << v->value.first << " u " << u->value.first << std::endl;
		}

		// fix red red at given node
		void fixRedRed(map_node *x) {
			// if x is _root color it black and return
			if (x == _root) {
			x->color = BLACK;
			return;
			}

			// initialize parent, grandparent, uncle
			map_node *parent = x->parent, *grandparent = parent->parent,
				*uncle = x->uncle();

			if (parent->color != BLACK) {
			if (uncle != NULL && uncle->color == RED) {
				// uncle red, perform recoloring and recurse
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			} else {
				// Else perform LR, LL, RL, RR
				if (parent->isOnLeft()) {
				if (x->isOnLeft()) {
					// for left right
					swapColors(parent, grandparent);
				} else {
					leftRotate(parent);
					swapColors(x, grandparent);
				}
				// for left left and left right
				rightRotate(grandparent);
				} else {
				if (x->isOnLeft()) {
					// for right left
					rightRotate(parent);
					swapColors(x, grandparent);
				} else {
					swapColors(parent, grandparent);
				}

				// for right right and right left
				leftRotate(grandparent);
				}
			}
			}
		}

		// find node that do not have a left child
		// in the subtree of the given node
		map_node *successor(map_node *x)
		{
			map_node *temp = x;
			while (temp && temp->left != NULL)
				temp = temp->left;
			return temp;
		}

		// find node that replaces a deleted node in BST
		map_node *BSTreplace(map_node *x)
		{
			// when node have 2 children
			if (x->left != NULL and x->right != NULL)
				return successor(x->right);

			// when leaf
			if (x->left == NULL and x->right == NULL)
				return NULL;

			// when single child
			if (x->left != NULL)
				return x->left;
			else
				return x->right;
		}

		// deletes the given node
		void deletemap_node(map_node *v)
		{
			map_node *u = BSTreplace(v);

			// True when u and v are both black
			bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
			map_node *parent = v->parent;

			if (u == NULL)
			{
				// u is NULL therefore v is leaf
				if (v == _root)
				{
					// v is _root, making _root null
					_root = NULL;
				}
				else
				{
					if (uvBlack)
					{
						fixDoubleBlack(v);
						// u and v both black
						// v is leaf, fix double black at v
					}
					else
					{
						// u or v is red
						if (v->sibling() != NULL)
							v->sibling()->color = RED;
							// sibling is not null, make it red"
					}
					// delete v from the tree
					if (v->isOnLeft())
						parent->left = NULL;
					else
						parent->right = NULL;
				}
				//std::cout << "v " << v->value.first<< " u " << u<<" "<< _size << " " << _root << std::endl;
				_alloc.destroy(v);
				_alloc.deallocate(v, 1);
				_size--;
				return;
			}
			if (v->left == NULL or v->right == NULL)
			{
				// TODO check leakis in line 286, not deallocations just construt maybe its broken 
				// v has 1 child
				if (v == _root)
				{
					// TODO need to find a way to change cosnt val of pair.first in v
					// v is _root, assign the value of u to v, and delete u

					//v->value = u->value;
					//std::cout << &v->value << std::endl;
					//std::cout << "v " << v->value.first << " u " << u->value.first <<" "<< _size << " " << _root->value.first << std::endl;
					//std::cout << "v " << v->color << " u " << u->color << std::endl;
					_alloc.destroy(v);
					_alloc.deallocate(v, 1);
					value_type	tmp = u->value;
					_alloc.destroy(u);
					_alloc.construct(u, tmp);
					//std::cout << "v " << v->value.first << " u " << u->value.first<<" "<< _size << " " << _root->value.first << std::endl;
					//_alloc.deallocate(v, 1);
					u->color = BLACK;
					//std::cout << &_root->value << std::endl;
					_root = u;
					//v->parent = v->left = v->right = NULL;
					//std::cout << &v->value << std::endl;
					//std::cout << &_root->value << std::endl;
					//v->color = BLACK;
					_size--;
					//std::cout << "v " << v->value.first << " u " << u->value.first<<" "<< _size << " " << _root->value.first << std::endl;
					//std::cout << "v " << v<< " u " << u<<" "<< _size << " " << _root << std::endl;
					//std::cout << "v " << v->color << " u " << u->color << std::endl;
				}
				else
				{
					// Detach v from tree and move u up
					if (v->isOnLeft())
						parent->left = u;
					else
						parent->right = u;
					_alloc.destroy(v);
					_alloc.deallocate(v, 1);
					_size--;
					u->parent = parent;
					if (uvBlack)
					{
						// u and v both black, fix double black at u
						fixDoubleBlack(u);
					}
					else
					{
						// u or v red, color u black
						u->color = BLACK;
					}
				}
				return;
			}
			// v has 2 children, swap values with successor and recurse
			swapValues(u, v);
			deletemap_node(u);
		}

		void fixDoubleBlack(map_node *x) {
			if (x == _root)
			// Reached _root
			return;

			map_node *sibling = x->sibling(), *parent = x->parent;
			if (sibling == NULL) {
			// No sibiling, double black pushed up
			fixDoubleBlack(parent);
			} else {
			if (sibling->color == RED) {
				// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) {
				// left case
				rightRotate(parent);
				} else {
				// right case
				leftRotate(parent);
				}
				fixDoubleBlack(x);
			} else {
				// Sibling black
				if (sibling->hasRedChild()) {
				// at least 1 red children
				if (sibling->left != NULL and sibling->left->color == RED) {
					if (sibling->isOnLeft()) {
					// left left
					sibling->left->color = sibling->color;
					sibling->color = parent->color;
					rightRotate(parent);
					} else {
					// right left
					sibling->left->color = parent->color;
					rightRotate(sibling);
					leftRotate(parent);
					}
				} else {
					if (sibling->isOnLeft()) {
					// left right
					sibling->right->color = parent->color;
					leftRotate(sibling);
					rightRotate(parent);
					} else {
					// right right
					sibling->right->color = sibling->color;
					sibling->color = parent->color;
					leftRotate(parent);
					}
				}
				parent->color = BLACK;
				} else {
				// 2 black children
				sibling->color = RED;
				if (parent->color == BLACK)
					fixDoubleBlack(parent);
				else
					parent->color = BLACK;
				}
			}
			}
		}

		// prints level order for given node
		void levelOrder(map_node *x) {
			if (x == NULL)
			// return if node is null
			return;

			// queue for level order
			std::queue<map_node *> q;
			map_node *curr;

			// push x
			q.push(x);

			while (!q.empty())
			{
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			std::cout << curr->value.first << " ";

			// push children to queue
			if (curr->left != NULL)
				q.push(curr->left);
			if (curr->right != NULL)
				q.push(curr->right);
			}
		}

		// prints inorder recursively
		void inorder(map_node *x) {
			if (x == NULL)
			return;
			inorder(x->left);
			std::cout << x->value.first << " ";
			inorder(x->right);
		}

		iterator	find(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(k, it->first) && !_compare(it->first, k))
					return (it);
			}
			return (this->end());
		}

		const_iterator	find(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(k, it->first) && !_compare(it->first, k))
					return (it);
			}
			return (this->end());
		}

		size_type	count(const key_type &k) const
		{
			if (this->find(k) != this->end())
				return (1);
			return (0);
		}

		iterator	lower_bound(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(it->first, k))
					return (it);
			}
			return (this->end());
		}

		const_iterator	lower_bound(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!_compare(it->first, k))
					return (it);
			}
			return (this->end());
		}

		iterator	upper_bound(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_compare(k, it->first))
					return (it);
			}
			return (this->end());
		}

		const_iterator	upper_bound(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_compare(k, it->first))
					return (it);
			}
			return (this->end());
		}

		pair<iterator,iterator>	equal_range(const key_type &k)
		{
			iterator	lower = lower_bound(k);
			iterator	upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
		{
			const_iterator	lower = lower_bound(k);
			const_iterator	upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		}

		map_node *search(const key_type &key)
		{
			map_node *temp = _root;
			while (temp != NULL)
			{
				//std::cout<< temp->value.first << std::endl;
				if (_compare(key, temp->value.first))
				{
					if (temp->left == NULL)
						break;
					else
						temp = temp->left;
				}
				else if (!_compare(key, temp->value.first) && !_compare(temp->value.first, key))
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

		map_node	*new_node(const value_type &val, map_node *parent)
		{
			map_node	*newNode = _alloc.allocate(1);
			_alloc.construct(newNode, val);
			newNode->parent = parent;
			this->_size++;
			return (newNode);
		}

		// inserts the given value to tree
		pair<iterator,bool>	insert(const value_type &val)
		{
			map_node	*newmap_node = NULL;
			if (_root == NULL)
			{
				// when _root is null
				// simply insert value at _root
				newmap_node = new_node(val, NULL);
				newmap_node->color = BLACK;
				_root = newmap_node;
				_end->parent = _end->maximum(_root);
				//std::cout << newmap_node->value.first << _root->value.first << std::endl;
				//std::cout << _end->parent->value.first << std::endl;
				//return (ft::make_pair(iterator(newmap_node, _end), true));
			}
			else
			{
				// TODO update new value of pair (val->second) here!! if elem already exists in map
				map_node *temp = search(val.first);

				if (!_compare(val.first, temp->value.first) && !_compare(temp->value.first, val.first))
					return (ft::make_pair(iterator(temp, _end), false));

				// if value is not found, search returns the node
				// where the value is to be inserted

				// connect new node to correct node
				newmap_node = new_node(val, temp);
				//newmap_node->parent = temp;

				if (_compare(val.first, temp->value.first))
					temp->left = newmap_node;
				else
					temp->right = newmap_node;

				// fix red red voilaton if exists
				fixRedRed(newmap_node);
				_end->parent = _end->maximum(_root);
				//std::cout << _end->parent->value.first << std::endl;
			}
			return (ft::make_pair(iterator(newmap_node, _end), true));
		}

		iterator	insert(iterator position, const value_type &val)
		{
			(void) position;
			return (insert(val).first);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		mapped_type	&operator[](const key_type &k)
		{
			return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
		}

		void	erase(iterator position)
		{
			erase(position->first);
		}

		size_type	erase(const key_type &key)
		{
			// Tree is empty
			if (_root == NULL)
				return (0);

			map_node *v = search(key);

			//if (v->value != n)
			//std::cout << key << " " << v->value.first << std::endl; 
			if (!_compare(key, v->value.first) && !_compare(v->value.first, key))
			{
				//std::cout << "node found to delete" << std::endl;
				//std::cout << v->value.first << std::endl; 
				deletemap_node(v);
				_end->parent = _end->maximum(_root);
				//std::cout << _end->parent->value.first << std::endl;
				return (1);
			}
			return (0);
		}

		void	erase(iterator first, iterator last)
		{
			//std::cout << (first)->first << " " << (last)->first << std::endl;
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
				//std::cout << &*tmp << " " << tmp->first << std::endl;
				//std::cout << &*first << " " << first->first << std::endl;
				//std::cout << search(tmp->first)->value.first << " " << tmp->first << std::endl; 
				++first;
				key = first->first;
				//std::cout << &*tmp << std::endl;
				//std::cout << &*first << " " << key << std::endl;
				erase(tmp);
				first = find(key);
				//std::cout << &*tmp << " " << tmp->first << std::endl;
				//std::cout << &*first << " " << first->first << std::endl;
				//printHelper(_root, "", true);
			}
		}

		void	swap(map &x)
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

		void	clear(void) {erase(begin(), end());};

		void	printHelper(map_node *root, std::string indent, bool last)
		{
			if (root != NULL)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}
				std::string sColor = root->color ? "BLACK" : "RED";
				std::cout << root->value.first << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}

		public:
		// how do i do this? for typedef?
		class value_compare
		{
			friend class map;

			protected:
			Compare comp;
			value_compare	(Compare c) : comp(c) {};

			public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool	operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		iterator		begin(void)
		{
			if (!this->size())
				return (this->end());
			else
				return (iterator(_root->minimum(_root), _end));
		}

		const_iterator	begin(void) const
		{
			if (!this->size())
				return (this->end());
			else
				return (const_iterator(_root->minimum(_root), _end));
		}

		iterator		end(void) {return iterator(_end, _end);}
		const_iterator	end(void) const {return const_iterator(_end, _end);}

		reverse_iterator		rbegin(void) {return reverse_iterator(end());}
		const_reverse_iterator	rbegin(void) const {return const_reverse_iterator(end());}

		reverse_iterator		rend(void) {return reverse_iterator(begin());}
		const_reverse_iterator	rend(void) const {return const_reverse_iterator(begin());}

		allocator_type	get_allocator(void) const
		{
			allocator_type cpy_allocator(_alloc);
			return (cpy_allocator);
		}
		size_type		size(void) const {return (this->_size);}
		size_type		max_size(void) const {return (this->_alloc.max_size());}
		bool			empty(void) const
		{
			if (this->_size == 0)
				return (true);
			else
				return (false);
		}

		key_compare key_comp(void) const {return (_compare);}
		value_compare value_comp(void) const {return (value_compare(_compare));}
	};

	// non-member funcs overloads

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key,T,Compare,Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
};

template< class T >
void	display( T map, std::string keyType, std::string valueType ) {
			
	std::cout << std::endl << "[+] map<" << keyType << "," << valueType << "> content: " << std::endl << std::endl << "{ ";

	typename T::iterator	it, ite = map.end();
	for (it = map.begin(); it != ite; it++)
		std::cout << it->first << ":" << it->second << " ";

	std::cout << "}" << std::endl << std::endl;
}

int	main()
{
	{
		{
			ft::map<int, std::string> map;
			std::string arrayS[] = {"zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix"};


			for (int i = 0; i < 11; i++)
				map[i] = arrayS[i];

			//map.erase(0);
			//map.erase(10);
			map.printHelper(map._root, "", true);
			//std::cout << (++map.begin())->first << " " << (--map.end())->first << std::endl;
			map.erase(++map.begin(), --map.end());
			display(map, "int", "std::string");
			//checkSize(map, keyType, valueType)
		}

		return 0;
		ft::map<int, int> m;
		ft::map<int, int> mm;
		/*
		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> kit;
		ft::pair<ft::map<int, int>::iterator, bool> kit = m.insert(ft::pair<int,int>(55,100));
		std::cout << kit.first->first << " " << kit.first->second << " " << kit.second << std::endl;
		kit = m.insert(ft::pair<int,int>(55,100));
		std::cout << kit.first->first << " " << kit.first->second << " " << kit.second << std::endl;
		*/

		//std::cout << (m.insert(dit, ft::pair<int,int>(55,100)))->second << std::endl;
		//std::cout << m.insert(ft::pair<int,int>(55,100)).second << std::endl;
		//std::cout << m.insert(ft::pair<int,int>(55,100)).first->first << std::endl;
		//std::cout << m.insert(ft::pair<int,int>(55,100)).first->first << std::endl;
		//std::cout << ins->first << std::endl;
		m.insert(ft::pair<int,int>(55,100));
		m.insert(ft::pair<int,int>(40,100));
		m.insert(ft::pair<int,int>(65,100));
		m.insert(ft::pair<int,int>(60,100));
		m.insert(ft::pair<int,int>(75,100));
		m.insert(ft::pair<int,int>(57,100));
		m[45] = 100;

		ft::map<int, int> m1(m);

		m1.printHelper(m1._root, "", true);
		std::cout << m1.size() << std::endl;
		m.printHelper(m._root, "", true);
		std::cout << m.size() << std::endl;
		std::cout << std::endl;

		std::cout << (m == m1) << std::endl;
		std::cout << (m != m1) << std::endl;
		std::cout << (m < m1) << std::endl;
		std::cout << (m <= m1) << std::endl;
		std::cout << (m > m1) << std::endl;
		std::cout << (m >= m1) << std::endl;

		//return 0;

		//m.printHelper(m._root, "", true);
		//m.erase(m.begin(), ++m.begin());
		//m.erase(m.begin());
		mm.insert(m.begin(), ++m.begin());
		//m.printHelper(mm._root, "", true);
		//mm.clear();
		ft::map<int, int>::iterator	dit = m.begin();
		while (dit != m.end())
		{
			//std::cout << dit->first << " " <<&*dit << std::endl;
			++dit;
		}
		std::cout << std::endl;

		m.swap(mm);
		m.printHelper(m._root, "", true);
		std::cout << m.size() << std::endl;
		std::cout << std::endl;
		m.printHelper(mm._root, "", true);
		std::cout << mm.size() << std::endl;
		m.clear();
		mm.clear();

		/*
		m.erase(65);
		m.erase(75);
		m.erase(60);
		m.erase(45);
		m.erase(55);
		m.erase(57);
		m.erase(40);
		*/

		m.printHelper(m._root, "", true);
		std::cout << m.size() << std::endl;
		//mm[60] = 100;
		//m.printHelper(mm._root, "", true);

		return 0;

		ft::map<int, int>::iterator	it = m.begin();
		std::cout << m._end << std::endl;
		while (it != m.end())
		{
			std::cout << it->first << std::endl;
			++it;
		}
		std::cout << &*it << std::endl;

		ft::map<int, int>::reverse_iterator	rit = m.rbegin();
		std::cout << &*rit << std::endl;
		while (rit != m.rend())
		{
			std::cout << rit->first << std::endl;
			++rit;
		}
		std::cout << &*rit << std::endl;

		m.printHelper(m._root, "", true);
		//return 0;

		ft::map<int, int>::map_node *current = m._root->minimum(m._root);
		ft::map<int, int>::map_node *end = m._end;

		//end->parent = NULL;
		//std::cout << end->successor(end) << std::endl;
		//std::cout << end->predecessor(end) << std::endl;
		//TODO if size == 0 end->parent == NULL

		while (current != end)
		{
			std::cout << current->value.first << " " << current << std::endl;
			if (current == current->maximum(m._root))
			{
				current = end;
				break;
			}
			current = current->successor();
		}

		m.printHelper(m._root, "", true);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(55);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(57);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(40);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(65);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(75);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.erase(60);
		std::cout << m.size() << std::endl;
		std::cout << m._root->maximum(m._root) << std::endl;
		/*
		std::cout << m._root->value.first << " " << m._root->value.second << std::endl;
		std::cout << m._root->left->value.first << std::endl;
		std::cout << m._root->right->value.first << std::endl;
		std::cout << m._size << std::endl;
		*/
		//std::cout << m.search(55)->value.first << std::endl;
		m.printHelper(m._root, "", true);
		m.levelOrder(m._root);
		std::cout << std::endl;
		m.inorder(m._root);
		std::cout << std::endl;
	}
	{
		return 0;
		// can only change mapped value with iterator or with [] operator and only if ! const
		std::map<int, int> m;
		std::map<int, int>::reverse_iterator rit = m.rbegin();
		std::cout << &*rit << std::endl;
		std::cout << &*m.end() << std::endl;
		m.insert(std::pair<int,int>(40,100));
		//const std::map<int, int> my(m);
		m.insert(std::pair<int,int>(40,120));
		//my.find(40)->second = 10;
		//std::cout << my.find(40)->second << std::endl;
		std::map<int, int>::iterator it = m.begin();
		std::cout << it->first << " " << it->second << std::endl;
		m[40] = 10;
		std::cout << it->first << " " << it->second << std::endl;
		it->second = 160;
		std::cout << it->first << " " << it->second << std::endl;
		std::cout << m[40] << std::endl; 
		m.erase(40);
		m.erase(40);
		m.erase(40);
		m.erase(40);
		m.erase(40);
		it = m.begin();
		std::map<int, int>::iterator eit = m.end();
		std::cout << &*it << " " << &* eit << std::endl;
		m.insert(std::pair<int,int>(40,120));
		it = m.begin();
		std::cout << &*it << " " << &* eit << std::endl;
		it++;
		std::cout << &*it << std::endl;
		std::cout << m.size() << std::endl;
		std::cout << m[40] << std::endl; 
	}
	return 0;
}
