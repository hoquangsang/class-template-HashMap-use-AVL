#ifndef HashMap_h
#define HashMap_h

#include <iostream>
#include <fstream>
#include <string>
#include "HashNode.h"
#include "AVLTree.h"
#include "TreeNode.h"

// The golden ratio (used in the hash function)
#define A (std::sqrt(5.00) - 1.00) / 2.00 

// Entry type definition for the HashMap
typedef HashNode<int>* Entry;

// Class template HashMap
template <class T> class HashMap;

// Template specialization for the HashMap class with type int
template <> class HashMap<int>
{
protected:
private:
	// Private class properties and methods
	Entry* table;															// Array of entries (buckets) for the HashMap
	int size;																// Size of Array
	std::ofstream output;													// Output file stream for logging

	int hash_function(const int& key) const;								// Hash function to calculate the index based on the key
	bool is_collision(const int& hashValue) const;							// Check if there is a collision at the specified hash value

public:
	// Public class properties and methods

	HashMap(const int&, const std::string&);								// Constructor with specified size and output file name
	~HashMap();																// Destructor to free allocated memory

	Entry* get_table() const;												// Get the array of entries (buckets) in the HashMap
	int get_size() const;													// Get the size of the HashMap

	void insert(const int& key);											// Insert a key into the HashMap
	void save_result_insert_list(const int*, const int&);					// Insert multiple keys from an array into the HashMap ad
	
	bool search(const int& key);											// Search for a key in the HashMap
	void save_result_search_list(const int*, const int&);					// Search for multiple keys from an array in the HashMap

	void display(const std::string&);										// Display the contents of the HashMap

	friend std::ostream& operator<<(std::ostream&, HashMap<int>&);			// Friend function to overload the stream insertion operator for output


};

#endif // !HashMap_h