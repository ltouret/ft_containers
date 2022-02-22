#ifndef NODE_HPP
# define NODE_HPP

//#include <iostream>

namespace ft
{
	enum COLOR {RED, BLACK};

	template<class Pair>
	struct Node
	{
		Pair	value;
		COLOR	color;
		Node	*left;
		Node	*right;
		Node	*parent;

		explicit Node() : value()
		{
			parent = left = right = NULL;
			color = RED;
		}

		Node(const Pair &data) : value(data)
		{
			parent = left = right = NULL;
			color = RED;
		}

		~Node(){};

		Node	*uncle(void)
		{
			if (parent == NULL or parent->parent == NULL)
				return NULL;

			if (parent->isOnLeft())
				return parent->parent->right;
			else
				return parent->parent->left;
		}

		bool	isOnLeft(void)
		{
			if (parent == NULL)
				return (0);
			return this == parent->left;
		}

		Node	*sibling(void)
		{
			if (parent == NULL)
				return NULL;

			if (isOnLeft())
				return parent->right;

			return parent->left;
		}

		void	moveDown(Node *nParent)
		{
			if (parent != NULL)
			{
				if (isOnLeft())
					parent->left = nParent;
				else
					parent->right = nParent;
			}
			nParent->parent = parent;
			parent = nParent;
		}

		bool	hasRedChild(void)
		{
			return (left != NULL and left->color == RED) ||
				(right != NULL and right->color == RED);
		}

		Node	*minimum(Node *node)
		{
			if (!node)
				return NULL;
			while (node->left != NULL)
				node = node->left;
			return node;
		}

		Node	*maximum(Node *node)
		{
			if (!node)
				return NULL;
			while (node->right != NULL)
				node = node->right;
			return node;
		}

		Node	*successor(void)
		{
			Node *tmp = this;
			if (tmp->right != NULL)
				return minimum(tmp->right);

			Node *y = tmp->parent;
			while (y != NULL && tmp == y->right)
			{
				tmp = y;
				y = y->parent;
			}
			return y;
		}

		Node	*predecessor(void)
		{
			Node *tmp = this;
			if (tmp->left != NULL)
				return maximum(tmp->left);

			Node *y = tmp->parent;
			while (y != NULL && tmp == y->left)
			{
				tmp = y;
				y = y->parent;
			}
			return y;
		}
	};
};

#endif
