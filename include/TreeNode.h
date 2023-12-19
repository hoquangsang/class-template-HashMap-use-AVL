#ifndef TreeNode_h
#define TreeNode_h
#include <iostream>
#include <iomanip>

enum HeightStatus {
    h_leaf = 1,                                                             // The height of a leaf node is 1.
    h_null = 0,                                                             // The height of a null node is 0.
};

enum KeyValueStatus {
    MIN_KEY = INT_MIN,                                                      // The minimum key value is INT_MIN = -2^31.
    MAX_KEY = INT_MAX,                                                      // The maximum key value is INT_MAX = 2^31 - 1.
};

template <class T> class Node;                                              // TreeNode BASE template

template <> class Node<int>                                                 // TreeNode int template
{
private:                                                                    // Private class properties and methods

    int key;                                                                // Key value
    Node<int>* left;                                                        // Left pointer link
    Node<int>* right;                                                       // Right pointer link
    int height;                                                             // Height: balance value

    int get_height(Node<int>* nodePtr) const;                               // Private method: get height of a node

public:                                                                     // Public class properties and methods

    // Constructors
    Node();                                                                 // Default constructor
    Node(const int& inpKey);                                                // Parameterized constructor
    Node(const int& inpKey, Node<int>* leftPtr, Node<int>* rightPtr);       // Parameterized constructor
    Node(const Node<int>& inpNode);                                         // Copy constructor

    // Getter methods
    int get_key() const;                                                    // Get the key value
    int get_height() const;                                                 // Get the height of the node
    int get_balance() const;                                                // Get the balance factor of the node
    Node<int>*& get_leftptr();                                              // Get the left pointer of the node
    Node<int>*& get_rightptr();                                             // Get the right pointer of the node

    // Setter methods
    void set_key(const int& inpKey);                                        // Set the key value
    void set_leftptr(Node<int>* nodePtr);                                   // Set the left pointer of the node
    void set_rightptr(Node<int>* nodePtr);                                  // Set the right pointer of the node

    // Update
    void update_height();                                                   // Update the height of the node

    // ostream operator
    friend std::ostream& operator<<(std::ostream&, const Node<int>&);       // Output stream operator
};


#endif //!TreeNode_h