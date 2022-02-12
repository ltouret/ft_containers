#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

namespace ft
{
	//TODO erase comments to start wtih Pair template
	enum COLOR {RED, BLACK};

	template<class Pair>
	struct Node
	{
		// TODO change int val for pair
		Pair	value;
		COLOR	color;
		Node	*left;
		Node	*right;
		Node	*parent;

		// TODO maybe add more constructors?
		Node()
		{
			parent = left = right = NULL;
			color = RED;
		}
		Node(int value) : value(value)
		{
			parent = left = right = NULL;

			// Node is created during insertion
			// Node is red at insertion
			color = RED;
		}

		// returns pointer to uncle
		Node *uncle()
		{
			// If no parent or grandparent, then no uncle
			if (parent == NULL or parent->parent == NULL)
			return NULL;

			if (parent->isOnLeft())
			// uncle on right
			return parent->parent->right;
			else
			// uncle on left
			return parent->parent->left;
		}

		// check if node is left child of parent
		bool isOnLeft() {return this == parent->left;};

		// returns pointer to sibling
		Node *sibling()
		{
			// sibling null if no parent
			if (parent == NULL)
			return NULL;

			if (isOnLeft())
			return parent->right;

			return parent->left;
		}

		// moves node down and moves given node in its place
		void moveDown(Node *nParent)
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

		bool hasRedChild()
		{
			return (left != NULL and left->color == RED) ||
				(right != NULL and right->color == RED);
		}

		Node *minimum(Node *node)
		{
			if (!node)
				return NULL;
			while (node->left != NULL)
				node = node->left;
			return node;
		}

		Node *maximum(Node *node)
		{
			if (!node)
				return NULL;
			while (node->right != NULL)
				node = node->right;
			return node;
		}

		Node	*successor(Node *x)
		{
			Node *tmp = x;
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

		Node	*predecessor(Node *x)
		{
			Node *tmp = x;
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
