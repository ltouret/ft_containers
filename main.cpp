#include "stack.hpp"
#include "vector.hpp"

//#include <stack>
//#include <vector>
#include <map>
#include "utils.hpp"
#include "node.hpp"

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
		//typedef bidirectional_iterator<value_type, pointer, reference> 			iterator;
		//typedef bidirectional_iterator<value_type, const_pointer, const_reference>	const_iterator;
		//typedef reverse_iterator<const_iterator>									const_reverse_iterator;
		//typedef reverse_iterator<iterator>											reverse_iterator;
		typedef Node<value_type>													map_node;
		typedef std::ptrdiff_t														difference_type;
		typedef size_t																size_type;

		// add other stuff
		private:
		map_node		*_root;
		map_node		*_end;
		key_compare		_compare;
		allocator_type	_alloc;
		size_type		_size;

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
		void swapValues(map_node *u, map_node *v) {
			int temp;
			temp = u->value;
			u->value = v->value;
			v->value = temp;
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
		map_node *successor(map_node *x) {
			map_node *temp = x;

			while (temp && temp->left != NULL)
			temp = temp->left;

			return temp;
		}

		// find node that replaces a deleted node in BST
		map_node *BSTreplace(map_node *x) {
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
		void deletemap_node(map_node *v) {
			map_node *u = BSTreplace(v);

			// True when u and v are both black
			bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
			map_node *parent = v->parent;

			if (u == NULL) {
			// u is NULL therefore v is leaf
			if (v == _root) {
				// v is _root, making _root null
				_root = NULL;
			} else {
				if (uvBlack) {
				// u and v both black
				// v is leaf, fix double black at v
				fixDoubleBlack(v);
				} else {
				// u or v is red
				if (v->sibling() != NULL)
					// sibling is not null, make it red"
					v->sibling()->color = RED;
				}

				// delete v from the tree
				if (v->isOnLeft()) {
				parent->left = NULL;
				} else {
				parent->right = NULL;
				}
			}
			delete v;
			return;
			}

			if (v->left == NULL or v->right == NULL) {
			// v has 1 child
			if (v == _root) {
				// v is _root, assign the value of u to v, and delete u
				v->value = u->value;
				v->left = v->right = NULL;
				delete u;
			} else {
				// Detach v from tree and move u up
				if (v->isOnLeft()) {
				parent->left = u;
				} else {
				parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack) {
				// u and v both black, fix double black at u
				fixDoubleBlack(u);
				} else {
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
		/*
		void levelOrder(map_node *x) {
			if (x == NULL)
			// return if node is null
			return;

			// queue for level order
			std::queue<map_node *> q;
			map_node *curr;

			// push x
			q.push(x);

			while (!q.empty()) {
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			std::cout << curr->value << " ";

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
			std::cout << x->value << " ";
			inorder(x->right);
		}
		*/

		map_node *getRoot() { return _root; }

		// searches for given value
		// if found returns the node (used for delete)
		// else returns the last node while traversing (used in insert)
		map_node *search(int n) {
			map_node *temp = _root;
			while (temp != NULL) {
			if (n < temp->value) {
				if (temp->left == NULL)
				break;
				else
				temp = temp->left;
			} else if (n == temp->value) {
				break;
			} else {
				if (temp->right == NULL)
				break;
				else
				temp = temp->right;
			}
			}

			return temp;
		}

		// inserts the given value to tree
		void insert(int n) {
			map_node *newmap_node = new map_node(n);
			if (_root == NULL)
			{
				// when _root is null
				// simply insert value at _root
				newmap_node->color = BLACK;
				_root = newmap_node;
			}
			else
			{
				// TODO update new value of pair (val->second) here!! if elem already exists in map
				map_node *temp = search(n);

				if (temp->value == n) {
					// return if value already exists
					return;
			}

			// if value is not found, search returns the node
			// where the value is to be inserted

			// connect new node to correct node
			newmap_node->parent = temp;

			if (n < temp->value)
				temp->left = newmap_node;
			else
				temp->right = newmap_node;

			// fix red red voilaton if exists
			fixRedRed(newmap_node);
			}
		}

		// utility function that deletes the node with given value
		void deleteByVal(int n)
		{
			// Tree is empty
			if (_root == NULL)
				return;

			map_node *v = search(n);

			if (v->value != n)
			{
				std::cout << "No node found to delete with value:" << n << std::endl;
				return;
			}

			deletemap_node(v);
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

		//key_compare		key_comp(void) const;
		//value_compare		value_comp(void) const;
	};
};

int	main()
{
	{
	  std::map<int,int> mymap;

  mymap[21] = 100;
  mymap[13] = 200;
  mymap[33] = 300;
  mymap[11] = 300;
  mymap[15] = 300;
  // doesnt break if a add another...
  mymap[20] = 300;
  mymap[20] = 300;
  mymap[20] = 330;

		// TODO mymap.end() can go backwards.
		// TODO mymap.begin() -- goes to mymap.end(), then end - 1, etc
	std::map<int, int>::iterator eit = mymap.end();
	std::map<int, int>::iterator it = mymap.begin();
	std::cout << &*it << " " << it->first << " => " << it->second << std::endl;
	it--;
	std::cout << &*it << " " << it->first << " => " << it->second << std::endl;
	it--;
	std::cout << &*it << " " << it->first << " => " << it->second << std::endl;
	it--;
	std::cout << &*it << " " << it->first << " => " << it->second << std::endl;
	//--eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
  // show content:
  for (std::map<int,int>::reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); ++it)
    std::cout << it->first << " => " << it->second << " " << &*it << '\n';
	std::cout << &*mymap.begin() << " " << &*mymap.end() << std::endl;
	std::cout << &*mymap.begin() << " " << &*(++mymap.end()) << std::endl;
  mymap[36] = 300;
  mymap[38] = 300;
  //mymap.erase(36);
	std::cout << mymap.begin()->first << " " << (++mymap.end())->first << std::endl;
	std::cout << mymap.begin()->first << " " << (--mymap.end())->first << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
	++eit;
	//std::cout << std::endl;
	//int i = 0;
	//while (i < 100)
	{
		std::cout << &*eit << " " << eit->first << " => " << eit->second << std::endl;
		++eit;
		//i++;
	}
	}
	return 0;
}
