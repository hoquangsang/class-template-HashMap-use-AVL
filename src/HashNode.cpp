#include "HashNode.h"


#pragma region constructor & destructor
// Default constructor
HashNode<int>::HashNode() {
    // BEGIN: Default constructor for HashNode

    // 1. Set the key to the default value for int.
    this->key = int();

    // 2. Create a new AVL tree for handling collisions.
    this->collisionList = new AVLTree<int>();

    // END
}

// Parameterized constructor with a key
HashNode<int>::HashNode(const int& inpKey) {
    // BEGIN: Parameterized constructor with a key for HashNode

    // 1. Set the key to the specified input key.
    this->key = inpKey;

    // 2. Create a new AVL tree for handling collisions.
    this->collisionList = new AVLTree<int>();

    // END: Parameterized constructor with a key for HashNode
}

// Parameterized constructor with a key and existing AVL tree
HashNode<int>::HashNode(const int& inpKey, const AVLTree<int>& inpTree) {
    // BEGIN: Parameterized constructor with a key and existing AVL tree for HashNode

    // 1. Set the key to the specified input key.
    this->key = inpKey;

    // 2. Create a new AVL tree for handling collisions with the specified existing tree.
    this->collisionList = new AVLTree<int>(inpTree);

    // END
}

// Destructor
HashNode<int>::~HashNode() {
    // BEGIN: Destructor for HashNode

    // 1. Check if the collisionList is not nullptr.
    if (this->collisionList != nullptr) {

        // 2. Clear the AVL tree (collisionList) to release memory.
        this->collisionList->clear_tree();

        // 3. Delete the AVL tree (collisionList).
        delete this->collisionList;

        // 4. Set the collisionList pointer to nullptr.
        this->collisionList = nullptr;
    }

    // END
}

#pragma endregion

#pragma region public opearations
int HashNode<int>::get_key() const {
    // BEGIN: Get the key of the HashNode

    // Return the key value of the HashNode.
    return this->key;

    // END
}

AVLTree<int>* HashNode<int>::get_listptr() const {
    // BEGIN: Get the pointer to the collision list of the HashNode

    // Return the pointer to the collision list (AVL tree) of the HashNode.
    return this->collisionList;

    // END
}

int HashNode<int>::count_collisions() const {
    // BEGIN: Count the number of collisions in the collision list of the HashNode

    // Use the count method of the collision list (AVL tree) to get the number of collisions.
    return this->collisionList->count();

    // END
}

bool HashNode<int>::empty_list() const {
    // BEGIN: Check if the HashNode has collisions

    // Return true if the collision list is not empty, indicating collisions.
    return this->collisionList->is_empty();

    // END
}

void HashNode<int>::insert(const int& inpKey) {
    // BEGIN: Insert a key into the collision list of the HashNode

    // Use the insert method of the collision list (AVL tree) to handle collisions.
    this->collisionList->insert(inpKey);

    // END
}

bool HashNode<int>::search(const int& inpKey) const {
    // BEGIN: Search for a key in the HashNode and its collision list

    // 1. Check if the key of the HashNode matches the input key.
    if (this->key == inpKey) {
        return true;
    }
    else {
        // 2. If not, search for the key in the collision list (AVL tree).
        return this->collisionList->search(inpKey);
    }

    // END
}

void HashNode<int>::display() const {
    // BEGIN: Display the key and collision list of the HashNode

    // 1. Display the key with padding and formatting.
    std::cout << std::setw(3) << std::setfill('0') << key << " ";

    // 2. Display the collision list using the << operator.
    std::cout << *this->collisionList;

    // END
}

HashNode<int>& HashNode<int>::operator=(const HashNode<int>& inpOther) {
    // BEGIN: Assignment operator to copy the content of another HashNode

    // 1. Check for self-assignment.
    if (this != &inpOther) {
        // 2. Clear the existing collision list of the current HashNode.
        this->collisionList->clear_tree();
        delete this->collisionList;
        this->collisionList = nullptr;

        // 3. Copy the key from the other HashNode.
        this->key = inpOther.get_key();

        // 4. Copy the collision list (AVL tree) from the other HashNode.
        *this->collisionList = *inpOther.collisionList;
    }

    // 5. Return a reference to the modified HashNode.
    return *this;

    // END
}

std::ostream& operator<<(std::ostream& os, const HashNode<int>& inpNode) {
    // BEGIN: Friend function to display the HashNode content using the << operator

    // 1. Display the key with padding and formatting.
    os << std::setw(3) << std::setfill('0') << inpNode.get_key() << "  ";

    // 2. Display the collision list using the << operator.
    os << *inpNode.get_listptr();

    // 3. Return the modified output stream.
    return os;

    // END
}

#pragma endregion