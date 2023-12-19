#include "HashMap.h"

#pragma region private helper
// calculating hash value
int HashMap<int>::hash_function(const int& key) const {
	// BEGIN: Calculate: h(k) = floor (m * [(k * A) mod 1])

	// 1. Calculate the decimal part of hash value using fmod
	double decimal_part = std::fmod(key * A, 1.00);

	// 2. Calculate the final hash value by taking the floor
	int hash_value = static_cast< int >(std::floor(size * decimal_part));

	return hash_value;

	// END: Hash function
}

// Check for collision at the specified hash value in the HashMap.
bool HashMap<int>::is_collision(const int& hashValue) const {
	// BEGIN

	// 1. Ensure the hashValue is within the valid range.
	if (0 > hashValue || hashValue > this->size) {
		// Invalid hashValue, no collision
		return false; 
	}

	// 2. Check if the slot is empty (nullptr), indicating no collision.
	else if (this->table[ hashValue ] == nullptr) {
		// No collision
		return false;
	}

	// 3. Check if the linked list at the specified hashValue is not empty, indicating a collision.
	return (this->table[ hashValue ]->empty_list() == false);

	// END
}
#pragma endregion

#pragma region constructor & destructor
// Constructor for the HashMap class.
HashMap<int>::HashMap(const int& m, const std::string& filename) {
	// BEGIN: contructor

	 // 1. Initialize member variables
	this->table = nullptr;
	this->size = m;

	// 2. Open the output file and check for success.
	this->output.open(filename);
	if (this->output.is_open() == false) {
		// If the file opening fails, throw a runtime_error with an appropriate message.
		throw std::runtime_error("+ khong the mo duong dan toi tap tin chua du lieu output\n");
	}

	// 3. Allocate memory for the table array using nothrow, and check for success.
	this->table = new (std::nothrow) Entry[ this->size ];

	if (!table || m < 1) {
		// If memory allocation fails, log the failure message.
		this->output << "[constructor] - khoi tao khong thanh cong\n";

		this->output << "+ cap phat khong thanh cong bang T do " << (m < 1 ? "m khong hop le\n" : "khong du bo nho cap phat\n");

		this->output << "+ m = " << m << "\n";
		
		this->output << "+ output file = " << filename;

		this->output.close();

		// Switch back to sync with stdio, print completion message, and exit with error code.
		std::ios_base::sync_with_stdio(true);

		std::cout << "[^^] Complete!\n";
		exit(-1);
	}
	else {
		// If memory allocation is successful, initialize each element in the table array to nullptr.
		for (int idx = 0; idx < this->size; idx++) {
			this->table[ idx ] = nullptr;
		}

		// Log the success message.
		this->output << "[constructor] - khoi tao thanh cong\n";

		this->output << "+ m = " << m << "\n";

		this->output << "+ output file = " << filename << "\n";

		// Switch back to sync with stdio.
		std::ios_base::sync_with_stdio(false);
	}

	// END
}

HashMap<int>::~HashMap() {
	// BEGIN: Destructor

	int count = 0;
	// 1. Iterate through each element in the table array and count collision elements
	for (int idx = 0; idx < size; idx++) {

		// 2. If the element is not nullptr.
		if (table[ idx ] != nullptr) {

			// update the collision count.
			int entryCol = this->table[ idx ]->count_collisions();
			count += entryCol;

			// delete the entry
			delete table[ idx ];
			table[ idx ] = nullptr;
		}
	}
	// 3. Delete the table array
	delete[] table;

	// 4. Log the destruction message
	output << "[destructor] - huy bo thanh cong\n";
	output << "+ so phan tu xung dot da delete = " << count << "\n";
	output << "+ da delete bang T";
	output.flush();
	output.close();

	// 5. Switch back to sync with stdio
	std::ios_base::sync_with_stdio(true);
	
	// END
}

#pragma endregion

#pragma region public operations

Entry* HashMap<int>::get_table() const {
	// BEGIN: Get the hash table

	// Retrieve the pointer to the hash table
	return this->table;

	// END
}

int HashMap<int>::get_size() const {
	// BEGIN: Get the size of the hash table

	// Retrieve the size of the hash table
	return this->size;

	// END
}

void HashMap<int>::insert(const int& key) {
	// BEGIN: Insertion Process

	// 1. Calculate the hash value for the given key
	int hashValue = hash_function(key);

	// 2. Check if the slot is empty
	if (this->table[ hashValue ] == nullptr) {
		// If empty, create a new HashNode and insert the key
		this->table[ hashValue ] = new HashNode<int>(key);
	}
	else {
		// If not empty, insert the key into the existing HashNode (handle collision)
		this->table[ hashValue ]->insert(key);
	}

	// END
}

void HashMap<int>::save_result_insert_list(const int* list, const int& size) {
	// BEGIN: save result of insert list

	for (int idx = 0; idx < size; idx++) {
		// 1. Get the key from the list
		int key = list[ idx ];

		// 2. Insert the key into the HashMap.
		this->insert(key);

		// 3. Calculate the hash value for the key.
		int hash_value = hash_function(key);

		// 4. Check if there is a collision at the hash value.
		bool collison = this->is_collision(hash_value);

		// 5.  Log the result of the insertion.
		this->output << "[insert " << idx + 1 << "] - thanh cong\n";

		this->output << "+ key = " << key << "\n";

		this->output << "+ hash value = " << hash_value << "\n";

		this->output << "+ xung dot: [" << (collison == true ? "co" : "khong") << "]\n";
	}

	// END
}

bool HashMap<int>::search(const int& key) {
	// BEGIN: Search for key in the HashMap

	// 1. Calculate the hash value for the key.
	int hashValue = hash_function(key);

	// 2. Check if the element at the hash value is nullptr.
	if (this->table[ hashValue ] == nullptr) {
		return false;
	}

	// 3. Use the search method of the corresponding entry to check for the key.
	return (this->table[ hashValue ]->search(key));

	// END
}

void HashMap<int>::save_result_search_list(const int* list, const int& size) {
	// BEGIN: Save result of search list

	for (int idx = 0; idx < size; idx++) {
		// 1. Get the key from the list.
		int key = list[ idx ];

		// 2. Check if the key is found in the HashMap.
		bool found = this->search(key);

		// 3. Calculate the hash value for the key.
		int hashValue = hash_function(key);

		// 4 Check if there is a collision at the hash value.
		bool collision = this->is_collision(hashValue);

		// 5. Log the result of the search.
		this->output << "[search " << idx + 1 << "] - " << (found == true ? "" : "khong") << " tim thay\n";

		this->output << "+ key = " << key << "\n";

		this->output << "+ hash value = " << hashValue << "\n";

		this->output << "+ xung dot: [" << (collision == true ? "co" : "khong") << "]\n";
	}

	// END
}

// Display: print file
void HashMap<int>::display(const std::string& filename) {
	// BEGIN
	std::ofstream stream;
	stream.open(filename);
	stream << *this;
	stream.close();
	// END
}

// friend
std::ostream& operator<<(std::ostream& os, HashMap<int>& inpMap) {
	// BEGIN
	for (int idx = 0; idx < inpMap.get_size(); idx++) {
		// Print the index with padding
		os << "[" << std::setw(3) << std::setfill('0') << idx << "] ";

		// Check if the element at the index is not nullptr, then print its content.
		if (inpMap.get_table()[idx] != nullptr) {
			os << *inpMap.get_table()[idx];
		}

		// Check if it's not the last index, then print a newline.
		if (idx != inpMap.get_size() - 1) os << "\n";
	}
	return os;

	// END
}
#pragma endregion