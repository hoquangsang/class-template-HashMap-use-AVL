#include "TreeNode.h"

#pragma region private helper
int Node<int>::get_height(Node<int>* nodePtr) const {
	// the height of a null node is h_null (0)
	if (nodePtr == nullptr) return h_null;

	// get the height of node
	return nodePtr->get_height();
}
#pragma endregion

#pragma region constructor
Node<int>::Node() {
	// BEGIN: Implement the default constructor
	this->key = int();
	this->left = nullptr;
	this->right = nullptr;
	this->height = h_null;
	// END
}
Node<int>::Node(const int& inpKey) {
	// BEGIN: Implement the parameterized constructor
	this->key = inpKey;
	this->left = nullptr;
	this->right = nullptr;
	this->height = h_leaf;
	// END
}
Node<int>::Node(const int& inpKey, Node<int>* leftPtr, Node<int>* rightPtr) {
	// BEGIN: Implement the parameterized constructor
	this->key = inpKey;
	this->left = leftPtr;
	this->right = rightPtr;
	this->height = 1 + std::max(get_height(this->left), get_height(this->right));
	// END
}
Node<int>::Node(const Node<int>& inpNode) {
	// BEGIN: Implement the parameterized constructor
	this->key = inpNode.key;
	if (inpNode.left != nullptr) {
		this->left = new Node<int>(*inpNode.left);
	}
	if (inpNode.right != nullptr) {
		this->right = new Node<int>(*inpNode.right);
	}
	this->height = inpNode.height;
	// END
}
#pragma endregion

#pragma region public operations
// getter methods
int Node<int>::get_key() const {
	// BEGIN: Implement get this key value
	return this->key;
	// END
}
int Node<int>::get_height() const {
	// BEGIN: Implement get this height
	return this->height;
	// END
}
int Node<int>::get_balance() const {
	// BEGIN: Implement get balance factor
	int left_height = (this->left == nullptr) ? 0 : this->left->height;
	int right_height = (this->right == nullptr) ? 0 : this->right->height;
	return right_height - left_height;
	// END
}

Node<int>*& Node<int>::get_leftptr() {
	// BEGIN: Implement get left pointer
	return this->left;
	// END
}
Node<int>*& Node<int>::get_rightptr() {
	// BEGIN: Implement get right pointer
	return this->right;
	// END
}

// setter methods
void Node<int>::set_key(const int& inpKey) {
	// BEGIN: Implement set key
	this->key = inpKey;
	// END
}

void Node<int>::set_leftptr(Node<int>* nodePtr) {
	// BEGIN: Implement set left ptr
	this->left = nodePtr;
	// END
}

void Node<int>::set_rightptr(Node<int>* nodePtr) {
	// BEGIN: Implement set right ptr
	this->right = nodePtr;
	// END
}

void Node<int>::update_height() {
	// BEGIN: Implement update height
	this->height = 1 + std::max(get_height(left), get_height(right));
	// END
}

// friend ostream opearator
std::ostream& operator<<(std::ostream& os, const Node<int>& inpNode) {
	// BEGIN: Implement ostream 
	os << std::setw(3) << std::setfill('0') << inpNode.get_key() << " ";
	return os;
	// END
}
#pragma endregion