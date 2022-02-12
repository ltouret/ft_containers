#include <iostream>
#include <bits/stdc++.h>

// TODO add search and delete and delete fix

using namespace std;
 
//enum Color {RED, BLACK};
# define RED 0
# define BLACK 1
 
struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;
 
    // Constructor
    Node(int data)
    {
       this->data = data;
       left = right = parent = NULL;
       this->color = RED;
    }
};
 
// Class to represent Red-Black Tree
class RBTree
{
public:
    Node *root;
    Node *_begin;
    Node *_end;
protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
public:
    // Constructor
    RBTree() { root = NULL; }
    void insert(const int &n);
    void inorder();
    void levelOrder();
	void	setup();
	void	detach();
	Node	*right(Node *root);
	Node	*left(Node *root);
 

void	init()
{
	_begin = new Node(0);
	_end  = new Node(1);
}
};
 
// A recursive function to do inorder traversal
void inorderHelper(Node *root)
{
    if (root == NULL)
        return;
 
    inorderHelper(root->left);
    cout << root->data << "  ";
    inorderHelper(root->right);
}
 
/* A utility function to insert
    a new node with given key
   in BST */
Node* BSTInsert(Node* root, Node *pt)
{
    /* If the tree is empty, return a new node */
    if (root == NULL)
       return pt;
 
    /* Otherwise, recur down the tree */
    if (pt->data < root->data)
    {
        root->left  = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
 
    /* return the (unchanged) node pointer */
    return root;
}
 
// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{
    if (root == NULL)
        return;
 
    std::queue<Node *> q;
    q.push(root);
 
    while (!q.empty())
    {
        Node *temp = q.front();
        cout << temp->data << "  ";
        q.pop();
 
        if (temp->left != NULL)
            q.push(temp->left);
 
        if (temp->right != NULL)
            q.push(temp->right);
    }
}
 
void RBTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *pt_right = pt->right;
 
    pt->right = pt_right->left;
 
    if (pt->right != NULL)
        pt->right->parent = pt;
 
    pt_right->parent = pt->parent;
 
    if (pt->parent == NULL)
        root = pt_right;
 
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
 
    else
        pt->parent->right = pt_right;
 
    pt_right->left = pt;
    pt->parent = pt_right;
}
 
void RBTree::rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->left;
 
    pt->left = pt_left->right;
 
    if (pt->left != NULL)
        pt->left->parent = pt;
 
    pt_left->parent = pt->parent;
 
    if (pt->parent == NULL)
        root = pt_left;
 
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
 
    else
        pt->parent->right = pt_left;
 
    pt_left->right = pt;
    pt->parent = pt_left;
}
 
// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;
 
    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED))
    {
 
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
 
        /*  Case : A
            Parent of pt is left child
            of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {
 
            Node *uncle_pt = grand_parent_pt->right;
 
            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color ==
                                                   RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
 
            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color,
                           grand_parent_pt->color);
                pt = parent_pt;
            }
        }
 
        /* Case : B
           Parent of pt is right child
           of Grand-parent of pt */
        else
        {
            Node *uncle_pt = grand_parent_pt->left;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color ==
                                                    RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color,
                         grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
 
    root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const int &data)
{
    Node *pt = new Node(data);
 
    // Do a normal BST insert
    root = BSTInsert(root, pt);
 
    // fix Red Black Tree violations
    fixViolation(root, pt);
	setup();
}
 
// Function to do inorder and level order traversals
void RBTree::inorder()     {  inorderHelper(root);}
void RBTree::levelOrder()  {  levelOrderHelper(root); }


Node *minimum(Node *node) {
	  if (!node)
		  return NULL;
    while (node->left != NULL) {
      node = node->left;
    }
	//cout << node->data << " " << node->right << endl;
    return node;
  }
  Node *maximum(Node *node) {
	  if (!node)
		  return NULL;
    while (node->right != NULL) {
      node = node->right;
    }
	//cout << node->left << endl;
    return node;
  }

Node	*RBTree::left(Node *root)
{
	Node *curr = root;
	while (curr && curr->left && curr->left != _begin)
		curr = curr->left;
	return curr;
}

Node	*RBTree::right(Node *root)
{
	Node *curr = root;
	while (curr && curr->right && curr->right != _end)
		curr = curr->right;
	return curr;
}

void	RBTree::setup()
{
	_begin->parent = left(root);
	_end->parent = right(root);
}
  Node *successor(Node *x) {
	  Node *tmp = x;
    if (tmp->right != NULL) {
      return minimum(tmp->right);
    }

    Node *y = tmp->parent;
    while (y != NULL && tmp == y->right) {
		//cout << tmp->data << " " << y->data << endl;
      tmp = y;
     y = y->parent;
			//cout << "yo" << endl;
    }
	//cout << "name" << endl;
    return y;
  }

  Node *predecessor(Node *x) {
	 Node *tmp = x;
    if (tmp->left != NULL) {
      return maximum(tmp->left);
    }

    Node *y = tmp->parent;
    while (y != NULL && tmp == y->left) {
      tmp = y;
      y = y->parent;
    }

    return y;
  }

// TODO if i add twice same key seg faults.

// Driver Code
int main()
{
    RBTree tree;

	tree.init();
  tree.insert(55);
  tree.insert(40);
  tree.insert(65);
  tree.insert(60);
  tree.insert(75);
  tree.insert(57);
  //tree.insert(57);

	//Node *begin = tree._begin->parent;
	//Node *end = tree._end;

	Node *begin = minimum(tree.root);
	Node *end = tree._end;
	end->parent = maximum(tree.root);

	// each time insert erase is called update _end->parent = maximun(tree.root);
	//the while loop l406 407 explains what to do when iterator ++ is called

	std::cout << begin->data << " " << end->data << std::endl;

	//tree.setup();

	std::cout << (end)->parent << std::endl;
	std::cout << (successor(end)) << std::endl;
	std::cout << (successor(end))->data << std::endl;
	std::cout << (predecessor(end))->data << std::endl;
	std::cout << (predecessor(predecessor(end)))->data << std::endl;

	while (begin != end)
	{
		cout << begin->data << " " << begin << endl;
		if (begin == maximum(tree.root))
		{
			begin = end;
			break;
		}
		begin = successor(begin);
	}

	{
		// demo mymap.begin()-- x 2
		std::cout << std::endl << "demo mymap.begin()-- x 2" << std::endl;
		Node *current = minimum(tree.root);
		Node *end = tree._end;
		end->parent = maximum(tree.root);

		std::cout << begin->data << " " << current->data << std::endl;

		/*
		std::cout << (end)->parent << std::endl;
		std::cout << (successor(end)) << std::endl;
		std::cout << (successor(end))->data << std::endl;
		std::cout << (predecessor(end))->data << std::endl;
		std::cout << (predecessor(predecessor(end)))->data << std::endl;
		*/

		cout << current->data << " " << current << endl;
		if (current == minimum(tree.root))
		{
			current = end;
		}
		std::cout << (current) << " " << current->data << std::endl;
		std::cout << (current)->parent << " " << current->parent->data << std::endl;
		current = predecessor(current);
		std::cout << (current) << " " << current->data << std::endl;
		std::cout << (current)->parent << " " << current->parent->data << std::endl;
	}
 
    cout << endl;
    cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    tree.levelOrder();
	cout << endl;
    return 0;
}
