#include "AVLTree.h"

#pragma region maintain AVL
void AVLTree<int>::update_height(Node<int>*& inpRoot) {
	// BEGIN: Implement update height

	// Check if the node is null, nothing to update
	if (inpRoot == nullptr) return;

	// Update the height of the current node using its children's heights
	inpRoot->update_height();

	// END
}

void AVLTree<int>::rotate_left(Node<int>*& inpRoot) {
	// BEGIN: Implement rotate left
	if (inpRoot == nullptr) return;

	// 1. Set a temporary pointer to the right child of this node.
	Node<int>* tempPtr = inpRoot->get_rightptr();

	// 2. Set the right child of this node to the left child of the temporary pointer.
	inpRoot->set_rightptr(tempPtr->get_leftptr());

	// 3. Set the left child of the temporary pointer to this node.
	tempPtr->set_leftptr(inpRoot);

	// 4. Update the heights of this node and the temporary pointer.
	update_height(inpRoot);
	update_height(tempPtr);

	// 5. Set this node to the temporary pointer, making it the new root after rotation.
	inpRoot = tempPtr;
	// END
}
void AVLTree<int>::rotate_right(Node<int>*& inpRoot) {
	// BEGIN: Implement rotate right
	if (inpRoot == nullptr) return;

	// 1. Set a temporary pointer to the left child of this node.
	Node<int>* tempPtr = inpRoot->get_leftptr();

	// 2. Set the left child of this node to the right child of the temporary pointer.
	inpRoot->set_leftptr(tempPtr->get_rightptr());

	// 3. Set the right child of the temporary pointer to this node.
	tempPtr->set_rightptr(inpRoot);

	// 4. Update the heights of this node and the temporary pointer.
	update_height(inpRoot);
	update_height(tempPtr);

	// 5. Set this node to the temporary pointer, making it the new root after rotation.
	inpRoot = tempPtr;
	// END

}
void AVLTree<int>::update_balance(Node<int>*& inpRoot) {
	// BEGIN: Rebalance the tree
	if (inpRoot == nullptr) return;

	// Check the balance factor of the current node
	switch (inpRoot->get_balance())
	{
	case LEFT_SKEWED:
	{
		// Left-skewed case
		Node<int>*& leftSubTree = inpRoot->get_leftptr();

		// Check the balance factor of the left subtree
		// left - right
		if (leftSubTree->get_balance() == RIGHT_HEAVY) {
			rotate_left(leftSubTree);
		}
		// left - left
		rotate_right(inpRoot);
		break;
	}
	case RIGHT_SKEWED:
	{
		// Right-skewed case
		Node<int>*& rightSubTree = inpRoot->get_rightptr();

		// Check the balance factor of the right subtree
		// right - left
		if (rightSubTree->get_balance() == LEFT_HEAVY) {
			rotate_right(rightSubTree);
		}
		// right - right
		rotate_left(inpRoot);
		break;
	}
	}

	// Update the height of the current node after rebalancing
	inpRoot->update_height();
	// END
}
#pragma endregion

#pragma region constructor & destructor
AVLTree<int>::AVLTree() {
	// BEGIN: Default constructor
	this->root = nullptr;
	// END
}

AVLTree<int>::AVLTree(const Node<int>& inpNode) {
	// BEGIN: Constructor with a node
	this->root = new Node<int>(inpNode);
	// END
}

AVLTree<int>::AVLTree(const AVLTree<int>& inpTree) {
	// BEGIN: Copy constructor
	this->root = new Node<int>(*inpTree.root);
	// END
}

AVLTree<int>::~AVLTree() {
	// BEGIN: Destructor
	this->clear_tree();
	// END
}
#pragma endregion

#pragma region public opearations
// traversal
void AVLTree<int>::in_order_traversal(std::ostream& os) const {
	// BEGIN: In-order traversal
	in_order_traversal(this->root, os);
	// END
}

void AVLTree<int>::pre_order_traversal(std::ostream& os) const {
	// BEGIN: Pre-order traversal
	pre_order_traversal(this->root, os);
	// END
}

void AVLTree<int>::post_order_traversal(std::ostream& os) const {
	// BEGIN: Post-order traversal
	post_order_traversal(this->root, os);
	// END
}

void AVLTree<int>::level_order_traversal(std::ostream& os) const {
	// BEGIN: Level-order traversal
	level_order_traversal(this->root, os);
	// END
}

// boolean
bool AVLTree<int>::is_empty() const {
	// BEGIN: Check if the tree is empty
	return (this->root == nullptr);
	// END
}

bool AVLTree<int>::is_AVL() const {
	// BEGIN: Check if the tree is AVL
	return is_AVL(this->root);
	// END
}

bool AVLTree<int>::search(const int& inpKey) const {
	// BEGIN: Search for a key in the tree
	return search(this->root, inpKey);
	// END
}

// getter methods
Node<int>* AVLTree<int>::get_root() const {
	// BEGIN: Get the root of the tree
	return this->root;
	// END
}

int AVLTree<int>::height_tree() const {
	// BEGIN: Get the height of the tree
	return this->root->get_height();
	// END
}

int AVLTree<int>::get_max() const {
	// BEGIN: Get the maximum key in the tree
	if (is_empty()) return int();
	return max_node(this->root)->get_key();
	// END
}

int AVLTree<int>::get_min() const {
	// BEGIN: Get the minimum key in the tree
	if (is_empty()) return int();
	return min_node(this->root)->get_key();
	// END
}

int AVLTree<int>::count() const {
	// BEGIN: Get the number of nodes in the tree
	return count(this->root);
	// END
}

// inserter & remove
void AVLTree<int>::insert(const int& inpKey) {
	// BEGIN: Insert a key into the tree
	insert(this->root, inpKey);
	// END
}

void AVLTree<int>::remove(const int& inpKey) {
	// BEGIN: Remove a key from the tree
	remove(this->root, inpKey);
	// END
}

// display
void AVLTree<int>::display() const {
	// BEGIN: Display the tree using pre-order traversal
	std::cout << *this;
	// END
}

// clear
void AVLTree<int>::clear_tree() {
	// BEGIN: Clear the entire tree
	clear_tree(this->root);
	// END
}

// assign operator:
AVLTree<int>& AVLTree<int>::operator=(const AVLTree<int>& inpTree) {
	// BEGIN: Assignment operator to copy the tree
	if (this != &inpTree) {
		this->clear_tree();
		this->root = copy_node(inpTree.get_root());
	}
	return *this;
	// END
}

// friend
std::ostream& operator<<(std::ostream& os, const AVLTree<int>& inpTree) {
	// BEGIN: Friend function to output the tree using pre-order traversal
	inpTree.pre_order_traversal(os);
	return os;
	// END
}

#pragma endregion

#pragma region private helper
// traversal
void AVLTree<int>::in_order_traversal(Node<int>* inpRoot, std::ostream& os) const {
	// BEGIN: In-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Recursively call for the left child node:
	in_order_traversal(inpRoot->get_leftptr(), os);

	// 3. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// 4. Recursively call for the right child node:
	in_order_traversal(inpRoot->get_rightptr(), os);

	// END
}
void AVLTree<int>::pre_order_traversal(Node<int>* inpRoot, std::ostream& os) const {
	// BEGIN: Pre-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// 3. Recursively call for the left child node:
	pre_order_traversal(inpRoot->get_leftptr(), os);

	// 4. Recursively call for the right child node:
	pre_order_traversal(inpRoot->get_rightptr(), os);

	// END
}
void AVLTree<int>::post_order_traversal(Node<int>* inpRoot, std::ostream& os) const {
	// BEGIN: Post-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Recursively call for the left child node:
	post_order_traversal(inpRoot->get_leftptr(), os);

	// 3. Recursively call for the right child node:
	post_order_traversal(inpRoot->get_rightptr(), os);

	// 4. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// END
}
void AVLTree<int>::level_order_traversal(Node<int>* inpRoot, std::ostream& os) const {
	// BEGIN: Level-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Create a queue to keep track of nodes at each level.
	std::queue<Node<int>*> queue;
	queue.push(inpRoot);

	// 3. Process nodes level by level using the queue.
	while (!queue.empty()) {
		// 4. Get the front node from the queue.
		Node<int>* cur_node = queue.front();
		// 5. Output the value of the current node to the stream.
		os << *cur_node << " ";
		// 6. Remove the front node from the queue.
		queue.pop();

		// 7. Enqueue the left child if it exists.
		if (cur_node->get_leftptr()) {
			queue.push(cur_node->get_leftptr());
		}

		// 8. Enqueue the right child if it exists.
		if (cur_node->get_rightptr()) {
			queue.push(cur_node->get_rightptr());
		}
	}

	// END
}


// boolean
bool AVLTree<int>::is_AVL(Node<int>* inpRoot, int min, int max) const {
	// BEGIN: Check if the tree rooted at inpRoot is an AVL tree

	// 1. Check the base case: If the current node is nullptr, it is an AVL tree.
	if (inpRoot == nullptr) return true;

	// 2. Get the key of the current node.
	int key = inpRoot->get_key();

	// 3. Check if the key is within the valid range for an AVL tree.
	if (min >= key || key >= max) {
		return false;
	}

	// 4. Check if the balance factor of the current node is within the acceptable range.
	if (std::abs(inpRoot->get_balance()) > 1) {
		return false;
	}

	// 5. Recursively check the left subtree, ensuring keys are within the appropriate range.
	// 6. Recursively check the right subtree, ensuring keys are within the appropriate range.
	return is_AVL(inpRoot->get_leftptr(), min, key)
		&& is_AVL(inpRoot->get_rightptr(), key, max);

	// END
}

bool AVLTree<int>::search(Node<int>* inpRoot, const int& inpKey) const {
	// BEGIN: Search for a key in the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, the key is not found.
	if (inpRoot == nullptr) return false;

	// 2. Compare the target key with the key of the current node.
	else if (inpKey < inpRoot->get_key()) {
		// 3. If the target key is less than the current node's key, recursively search in the left subtree.
		return search(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		// 4. If the target key is greater than the current node's key, recursively search in the right subtree.
		return search(inpRoot->get_rightptr(), inpKey);
	}

	// 5. If the target key is equal to the current node's key, the key is found.
	return true;

	// END
}


// getter
Node<int>* AVLTree<int>::min_node(Node<int>* inpRoot) const {
	// BEGIN: Find the node with the minimum key in the AVL tree rooted at inpRoot

	// 1. Initialize the minimum node as the root of the subtree.
	Node<int>* minNode = inpRoot;

	// 2. Traverse the left child pointers until the leftmost node is reached.
	while (minNode->get_leftptr()) {
		minNode = minNode->get_leftptr();
	}

	// 3. Return the node with the minimum key.
	return minNode;

	// END
}

Node<int>* AVLTree<int>::max_node(Node<int>* inpRoot) const {
	// BEGIN: Find the node with the maximum key in the AVL tree rooted at inpRoot

	// 1. Initialize the maximum node as the root of the subtree.
	Node<int>* maxNode = inpRoot;

	// 2. Traverse the right child pointers until the rightmost node is reached.
	while (maxNode->get_rightptr()) {
		maxNode = maxNode->get_rightptr();
	}

	// 3. Return the node with the maximum key.
	return maxNode;

	// END
}

int AVLTree<int>::count(Node<int>* inpRoot) const {
	// BEGIN: Count the number of nodes in the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, return 0.
	if (inpRoot == nullptr) return 0;

	// 2. Recursively count the nodes in the left and right subtrees, and add 1 for the current node.
	return 1 + count(inpRoot->get_leftptr()) + count(inpRoot->get_rightptr());

	// END
}

int AVLTree<int>::get_height(Node<int>* inpRoot) const {
	// BEGIN: Get the height of the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, return 0.
	if (inpRoot == nullptr) return 0;

	// 2. Return the height of the current node.
	return inpRoot->get_height();

	// END
}

// insert & remove
void AVLTree<int>::insert(Node<int>*& inpRoot, const int& inpKey) {
	// BEGIN: Insert a key into the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, create a new node with the key.
	if (inpRoot == nullptr) {
		inpRoot = new Node<int>(inpKey);
		return;
	}
	else if (inpKey < inpRoot->get_key()) {
		// 2. If the key is less than the current node's key, recursively insert into the left subtree.
		insert(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		// 3. If the key is greater than the current node's key, recursively insert into the right subtree.
		insert(inpRoot->get_rightptr(), inpKey);
	}
	else {
		// 4. If the key is equal to the current node's key, do nothing (no duplicates allowed).
		return;
	}

	// 5. Update the height of the current node.
	inpRoot->update_height();

	// 6. Update the balance factor and perform rotations if necessary.
	update_balance(inpRoot);

	// END
}

void AVLTree<int>::remove(Node<int>*& inpRoot, const int& inpKey) {
	// BEGIN: Remove a key from the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, the key does not exist.
	if (inpRoot == nullptr) {
		std::cerr << "[!] key " << inpKey << " not exist\n";
		return;
	}
	else if (inpKey < inpRoot->get_key()) {
		// 2. If the key is less than the current node's key, recursively remove from the left subtree.
		remove(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		// 3. If the key is greater than the current node's key, recursively remove from the right subtree.
		remove(inpRoot->get_rightptr(), inpKey);
	}
	else {
		// 4. Handle cases where the node to be removed has one or no child.
		if (inpRoot->get_leftptr() == nullptr) {
			Node<int>* reNode = inpRoot;
			inpRoot = inpRoot->get_rightptr();
			delete reNode;
		}
		else if (inpRoot->get_rightptr() == nullptr) {
			Node<int>* reNode = inpRoot;
			inpRoot = inpRoot->get_leftptr();
			delete reNode;
		}
		else {
			// 5. Handle case where the node to be removed has two children.
			Node<int>* reNode = min_node(inpRoot->get_rightptr());
			inpRoot->set_key(reNode->get_key());
			remove(inpRoot->get_rightptr(), reNode->get_key());
		}
	}

	// 6. Update the balance factor and perform rotations if necessary.
	update_balance(inpRoot);

	// END
}

Node<int>* AVLTree<int>::copy_node(Node<int>* inpNode) {
	// BEGIN: Create a deep copy of the subtree rooted at inpNode

	// 1. Check the base case: If the current node is nullptr, return nullptr.
	if (inpNode != nullptr) {
		// 2. Create a new node with the key of the current node.
		Node<int>* newRoot = new Node<int>(inpNode->get_key());

		// 3. Recursively copy the left and right subtrees.
		Node<int>* leftPtr = copy_node(inpNode->get_leftptr());
		Node<int>* rightPtr = copy_node(inpNode->get_rightptr());

		// 4. Set the left and right child pointers of the new node.
		newRoot->set_leftptr(leftPtr);
		newRoot->set_rightptr(rightPtr);

		// 5. Return the new node.
		return newRoot;
	}

	// 6. If the current node is nullptr, return nullptr.
	return nullptr;

	// END
}

void AVLTree<int>::clear_tree(Node<int>*& inpRoot) {
	// BEGIN: Recursively clear the AVL tree rooted at inpRoot

	// 1. Check if the current node is not nullptr.
	if (inpRoot) {
		// 2. Recursively clear the left and right subtrees.
		Node<int>* leftPtr = inpRoot->get_leftptr();
		Node<int>* rightPtr = inpRoot->get_rightptr();
		clear_tree(leftPtr);
		clear_tree(rightPtr);

		// 3. Delete the current node and set it to nullptr.
		delete inpRoot;
		inpRoot = nullptr;
	}

	// END
}

#pragma endregion