#include <iostream>
#include <queue>
#include "node.hpp"

namespace ft
{
	class RBTree
	{
		private:
		Node *root;

		// left rotates the given node
		void leftRotate(Node *x)
		{
			// new parent will be node's right child
			Node *nParent = x->right;

			// update root if current node is root
			if (x == root)
			root = nParent;

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

		void rightRotate(Node *x) {
			// new parent will be node's left child
			Node *nParent = x->left;

			// update root if current node is root
			if (x == root)
			root = nParent;

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

		void swapColors(Node *x1, Node *x2) {
			COLOR temp;
			temp = x1->color;
			x1->color = x2->color;
			x2->color = temp;
		}

		void swapValues(Node *u, Node *v) {
			int temp;
			temp = u->val;
			u->val = v->val;
			v->val = temp;
		}

		// fix red red at given node
		void fixRedRed(Node *x) {
			// if x is root color it black and return
			if (x == root) {
			x->color = BLACK;
			return;
			}

			// initialize parent, grandparent, uncle
			Node *parent = x->parent, *grandparent = parent->parent,
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
		Node *successor(Node *x) {
			Node *temp = x;

			while (temp && temp->left != NULL)
			temp = temp->left;

			return temp;
		}

		// find node that replaces a deleted node in BST
		Node *BSTreplace(Node *x) {
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
		void deleteNode(Node *v) {
			Node *u = BSTreplace(v);

			// True when u and v are both black
			bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
			Node *parent = v->parent;

			if (u == NULL) {
			// u is NULL therefore v is leaf
			if (v == root) {
				// v is root, making root null
				root = NULL;
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
			if (v == root) {
				// v is root, assign the value of u to v, and delete u
				v->val = u->val;
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
			deleteNode(u);
		}

		void fixDoubleBlack(Node *x) {
			if (x == root)
			// Reached root
			return;

			Node *sibling = x->sibling(), *parent = x->parent;
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
		void levelOrder(Node *x) {
			if (x == NULL)
			// return if node is null
			return;

			// queue for level order
			std::queue<Node *> q;
			Node *curr;

			// push x
			q.push(x);

			while (!q.empty()) {
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			std::cout << curr->val << " ";

			// push children to queue
			if (curr->left != NULL)
				q.push(curr->left);
			if (curr->right != NULL)
				q.push(curr->right);
			}
		}

		// prints inorder recursively
		void inorder(Node *x) {
			if (x == NULL)
			return;
			inorder(x->left);
			std::cout << x->val << " ";
			inorder(x->right);
		}

		public:
		// constructor
		// initialize root
		RBTree() { root = NULL; }

		Node *getRoot() { return root; }

		// searches for given value
		// if found returns the node (used for delete)
		// else returns the last node while traversing (used in insert)
		Node *search(int n) {
			Node *temp = root;
			while (temp != NULL) {
			if (n < temp->val) {
				if (temp->left == NULL)
				break;
				else
				temp = temp->left;
			} else if (n == temp->val) {
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
			Node *newNode = new Node(n);
			if (root == NULL)
			{
				// when root is null
				// simply insert value at root
				newNode->color = BLACK;
				root = newNode;
			}
			else
			{
				// TODO update new value of pair (val->second) here!! if elem already exists in map
				Node *temp = search(n);

				if (temp->val == n) {
					// return if value already exists
					return;
			}

			// if value is not found, search returns the node
			// where the value is to be inserted

			// connect new node to correct node
			newNode->parent = temp;

			if (n < temp->val)
				temp->left = newNode;
			else
				temp->right = newNode;

			// fix red red voilaton if exists
			fixRedRed(newNode);
			}
		}

		// utility function that deletes the node with given value
		void deleteByVal(int n)
		{
			// Tree is empty
			if (root == NULL)
				return;

			Node *v = search(n);

			if (v->val != n)
			{
				std::cout << "No node found to delete with value:" << n << std::endl;
				return;
			}

			deleteNode(v);
		}

		// prints inorder of the tree
		void printInOrder() {
			std::cout << "Inorder: " << std::endl;
			if (root == NULL)
			std::cout << "Tree is empty" << std::endl;
			else
			inorder(root);
			std::cout << std::endl;
		}

		// prints level order of the tree
		void printLevelOrder() {
			std::cout << "Level order: " << std::endl;
			if (root == NULL)
			std::cout << "Tree is empty" << std::endl;
			else
			levelOrder(root);
			std::cout << std::endl;
		}
	};
};

int main() {
ft::RBTree tree;

tree.insert(7);
tree.insert(3);
tree.insert(18);
tree.insert(10);
tree.insert(22);
tree.insert(8);
tree.insert(11);
tree.insert(26);
tree.insert(2);
tree.insert(6);
tree.insert(13);

tree.printInOrder();
tree.printLevelOrder();

std::cout<<std::endl<<"Deleting 18, 11, 3, 10, 22"<<std::endl;

tree.deleteByVal(18);
tree.deleteByVal(11);
tree.deleteByVal(3);
tree.deleteByVal(10);
tree.deleteByVal(22);

tree.printInOrder();
tree.printLevelOrder();
return 0;
}
