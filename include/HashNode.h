#ifndef HashNode_h
#define HashNode_h

#include <iostream>	
#include "AVLTree.h"

// class template HashNode
template <class T> class HashNode;

// Specialization of HashNode class for type int
template <> class HashNode<int>
{
private:
	// Private class properties and methods
	int key;																// Key of the hash node
	AVLTree<int>* collisionList;											// AVL tree to handle collisions

public:
	// Public class properties and methods
	HashNode();																// Default constructor
	HashNode(const int&);													// Constructor with a key
	HashNode(const int&, const AVLTree<int>&);								// Constructor with a key and existing AVL tree
	~HashNode();															// Destructor

	int get_key() const;													// Get the key of the hash node
	AVLTree<int>* get_listptr() const;										// Get a pointer to the collision list (AVL tree)
	int count_collisions() const;											// Count the number of collisions in the collision list

	bool empty_list() const;												// Check if the hash node has collisions (non-empty collision list)
	void insert(const int&);												// Insert a key into the collision list (AVL tree)
	bool search(const int&) const;											// Search for a key in the collision list
	void display() const;													// Display the collision list

	HashNode<int>& operator=(const HashNode<int>&);							// Assignment operator to copy the content of another HashNode

	friend std::ostream& operator<<(std::ostream&, const HashNode<int>&);	// Friend function for stream output
};

#endif // !HashNode_h