//#include "TreeNode.h"
//#include "AVLTree.h"
//#include "HashMap.h"
//#include "HashNode.h"

#include "Header.h"

int main(int argc, char** argv) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        std::cerr << "[Error]: Invalid command line argument\n";
        std::cout << "[Usage]: program.exe path\n";
        std::cout << "[Usage]: program.exe filename\n";
        return 1;
    }

    std::string output_filename;
    int m;
    int insertSize = 0;
    int* insertList = nullptr;
    int searchSize = 0;
    int* searchList = nullptr;

    // Load data from the file
    std::fstream stream;
    stream.open(argv[ 1 ], std::ios_base::in);
    if (!stream.is_open()) {
        std::cerr << "[!] Can't open (path of) file \"" << argv[ 1 ] << "\"\n";
        return 1;
    }

    // Read output filename
    stream >> output_filename;

    // Read size T (m)
    stream >> m;

    // Read size of the insert list
    stream >> insertSize;

    // Allocate memory for the insert list and read its content
    insertList = new int[ insertSize ];
    for (int idx = 0; idx < insertSize; idx++) {
        stream >> insertList[ idx ];
    }

    // Read size of the search list
    stream >> searchSize;

    // Allocate memory for the search list and read its content
    searchList = new int[ searchSize ];
    for (int idx = 0; idx < searchSize; idx++) {
        stream >> searchList[ idx ];
    }

    // close
    stream.close();

	

	// HASH MAP
	output_filename = get_path_file(output_filename);

	try {
        // Create a HashMap object
		HashMap<int> hashMap(m, output_filename);

        // Save the result of inserting elements from the insert list
		hashMap.save_result_insert_list(insertList, insertSize);

        // Save the result of searching elements from the search list
		hashMap.save_result_search_list(searchList, searchSize);

        // Print the hash table to the display file
        hashMap.display(_DISPLAY_PATH_);
	}
	catch (const std::runtime_error& ex) {
        // If an exception occurs, log the error message to the default output file
		stream.open(_DEFAULT_OUTPUT_PATH_, std::ios_base::out);
		if (stream.is_open() == false) exit(-1);
		stream << "[constructor] - khoi tao khong thanh cong\n";
		stream << ex.what();
		stream << "+ m = " << m << "\n";
		stream << "+ output file = " << output_filename;
		stream.flush();
		stream.close();
	}


	std::cout << "[^^] Complete!\n";

	return 0;
	
    // End main
}

//"C:\22120309\src\test.txt"