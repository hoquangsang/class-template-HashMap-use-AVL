#ifndef AVLTree_h
#define AVLTree_h

#include <iostream>
#include <queue>
#include "TreeNode.h"

enum BalanceStatus {
	LEFT_HEAVY = -1,														// Node is left-heavy
	LEFT_SKEWED = -2,														// Node is left-skewed
	RIGHT_HEAVY = 1,														// Node is right-heavy
	RIGHT_SKEWED = 2,														// Node is severely right-skewed
	BALANCED = 0															// Node is balanced
};

template <class T> class AVLTree;											// AVL Tree BASE template

template <> class AVLTree<int>												// AVL Tree int
{
private:
	// Private class properties and methods
	Node<int>* root;														// Property: root node

	// AVL tree maintenance methods
	void update_height(Node<int>*& inpRoot);								// Update the height of a node
	void rotate_left(Node<int>*& inpRoot);									// Rotate the tree to the left
	void rotate_right(Node<int>*& inpRoot);									// Rotate the tree to the right
	void update_balance(Node<int>*& inpRoot);								// Update the balance factor of a node
public:
	// Public class properties and methods
	AVLTree();																// Default constructor
	AVLTree(const Node<int>&);												// Parameterized constructor
	AVLTree(const AVLTree<int>&);											// Copy constructor
	~AVLTree();																// Destructor

	void in_order_traversal(std::ostream&) const;							// Depth-First Traversal: in-order traversal
	void pre_order_traversal(std::ostream&) const;							// Depth-First Traversal: pre-order traversal
	void post_order_traversal(std::ostream&) const;							// Depth-First Traversal: post-order traversal
	void level_order_traversal(std::ostream&) const;						// Breadth-First Traversal: lever-order traversal

	bool is_empty() const;													// Check if the tree is empty
	bool is_AVL() const;													// Check if the tree is AVL-compliant
	bool search(const int&) const;											// Search for a key in the tree

	Node<int>* get_root() const;											// Get the root of the tree
	int height_tree() const;												// Get the height of the tree
	int get_max() const;													// Get the maximum key in the tree
	int get_min() const;													// Get the minimum key in the tree
	int count() const;														// Count the number of nodes in the tree
	
	void insert(const int&);												// Insert a key into the tree
	void remove(const int&);												// Remove a key from the tree
	
	void display() const;													// display tree
	void clear_tree();														// Clear the entire tree

	AVLTree<int>& operator=(const AVLTree<int>&);							// Assignment operator

	friend std::ostream& operator<<(std::ostream&, const AVLTree<int>&);	// Output stream operator

protected:
	// Protected class properties and methods (helper)
	void in_order_traversal(Node<int>*, std::ostream&) const;				// Traverse and print nodes in in-order sequence.
	void pre_order_traversal(Node<int>*, std::ostream&) const;				// Traverse and print nodes in pre-order sequence.
	void post_order_traversal(Node<int>*, std::ostream&) const;				// Traverse and print nodes in post-order sequence.
	void level_order_traversal(Node<int>*, std::ostream&) const;			// Traverse and print nodes in level-order sequence.
																			   															   
	bool is_AVL(Node<int>*, int min = MIN_KEY, int max = MAX_KEY) const;	// Check if the AVL tree rooted at inpRoot is balanced.
	bool search(Node<int>*, const int&) const;								// Search for a key in the AVL tree rooted at inpRoot.
																			   															   
	Node<int>* min_node(Node<int>* inpRoot) const;							// Find the node with the minimum key in the AVL tree rooted at inpRoot.
	Node<int>* max_node(Node<int>* inpRoot) const;							// Find the node with the maximum key in the AVL tree rooted at inpRoot.
	int count(Node<int>* inpRoot) const;									// Count the number of nodes in the AVL tree rooted at inpRoot.
	int get_height(Node<int>* inpRoot) const;								// Get the height of the AVL tree rooted at inpRoot.
																			   												   
	void insert(Node<int>*& inpRoot, const int& inpKey);					// Insert a key into the AVL tree rooted at inpRoot.
	void remove(Node<int>*& inpRoot, const int& inpKey);					// Remove a key from the AVL tree rooted at inpRoot.
																			   														   
	Node<int>* copy_node(Node<int>* inpNode);								// Create a deep copy of the subtree rooted at inpNode.
	void clear_tree(Node<int>*& inpRoot);									// Recursively clear the AVL tree rooted at inpRoot.
};

#endif // !AVLTree_h