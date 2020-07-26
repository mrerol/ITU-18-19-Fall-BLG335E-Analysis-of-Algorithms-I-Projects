#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "hashing.h"

#define INPUT_FILE "vocab.txt"
#define SEARCH_FILE "search.txt"
#define HASH_TABLE_SIZE_1 17863
#define HASH_TABLE_SIZE_2 21929

std::vector<std::string> read_input_file(std::string, int*);
std::vector<std::string> read_search_file(std::string, int*);

int main(int argc, char* argv[]) 
{

	if (argc != 3) {
		std::cout << "Program requires two filename! Try again" << std::endl;
		return 1;
	}

	std::string input_filename = std::string(argv[1]);
	std::string search_filename = std::string(argv[2]);

	//std::cout << input_file << std::endl << search_file << std::endl;
	
	std::cout << "Input file reading and creating hash tables for all type of hashing has been started!" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	std::vector<std::string> input_file_line_arr;

	int *read_line_number = new int;
	input_file_line_arr = read_input_file(input_filename, read_line_number);
	
	std::cout << "--------------------------------------------------------------" << std::endl;

	std::vector<std::string> search_file_line_arr;
	int *search_read_line_number = new int;
	*search_read_line_number = 0;
	search_file_line_arr = read_search_file(search_filename, search_read_line_number);

	LinearHashing *linear_hashing = new LinearHashing;
	linear_hashing->line_arr = &input_file_line_arr;
	linear_hashing->search_line_arr = &search_file_line_arr;

	DoubleHashing *double_hashing = new DoubleHashing;
	double_hashing->line_arr = &input_file_line_arr;
	double_hashing->search_line_arr = &search_file_line_arr;

	UniversalHashing *universal_hashing = new UniversalHashing;
	universal_hashing->search_line_arr = &search_file_line_arr;
	universal_hashing->line_arr = &input_file_line_arr;

	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "LINEAR HASHING:" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	// Linear Hashing with HASH_TABLE_SIZE_1
	std::cout << std::endl << "Creating Linear Hashing Table: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	linear_hashing->set_input_size(HASH_TABLE_SIZE_1, *read_line_number);
	linear_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_1 << ") : " << linear_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << linear_hashing->get_collision_hashing() << std::endl;
	//linear_hashing->write_to_file();

	// Linear Hashhing Search with HASH_TABLE_SIZE_1
	std::cout << std::endl << "Searching on Linear Hashing Table:: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	linear_hashing->set_input_size(HASH_TABLE_SIZE_1, *search_read_line_number);
	linear_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_1 << ") : " << linear_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with linear hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << linear_hashing->get_collision_searching() << std::endl;

	std::cout << "--------------------------------------------------------------" << std::endl;

	// Linear Hashing with HASH_TABLE_SIZE_2
	std::cout << std::endl << "Creating Linear Hashing Table: ( m = " << HASH_TABLE_SIZE_2 << ") : " << std::endl;
	linear_hashing->set_input_size(HASH_TABLE_SIZE_2, *read_line_number);
	linear_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_2 << ") : " << linear_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << linear_hashing->get_collision_hashing() << std::endl;
	//linear_hashing->write_to_file();

	// Linear Hashhing Search with HASH_TABLE_SIZE_2
	std::cout << std::endl << "Searching on Linear Hashing Table:: ( m = " << HASH_TABLE_SIZE_2 << ") : " << std::endl;
	linear_hashing->set_input_size(HASH_TABLE_SIZE_2, *search_read_line_number);
	linear_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_2 << ") : " << linear_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with linear hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << linear_hashing->get_collision_searching() << std::endl;
	
	// END - Linear Hashhing

	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "DOUBLE HASHING:" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	// Double Hashing with HASH_TABLE_SIZE_1
	std::cout << "Creating Double Hashing Table: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	double_hashing->set_input_size_and_prime(HASH_TABLE_SIZE_1, *read_line_number);
	double_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_1 << ") : " << double_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << double_hashing->get_collision_hashing() << std::endl;
	//double_hashing->write_to_file();

	// Double Hashhing Search with HASH_TABLE_SIZE_1
	std::cout << std::endl << "Searching on Double Hashing Table: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	double_hashing->set_input_size_and_prime(HASH_TABLE_SIZE_1, *search_read_line_number);
	double_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_1 << ") : " << double_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with double hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << double_hashing->get_collision_searching() << std::endl;
	
	std::cout << "--------------------------------------------------------------" << std::endl;
	
	// Double Hashing with HASH_TABLE_SIZE_2
	std::cout << "Creating Double Hashing Table: ( m = " << HASH_TABLE_SIZE_2 << ") : " << std::endl;
	double_hashing->set_input_size_and_prime(HASH_TABLE_SIZE_2, *read_line_number);
	double_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_2 << ") : " << double_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << double_hashing->get_collision_hashing() << std::endl;
	
	// Double Hashhing Search with HASH_TABLE_SIZE_2
	std::cout << std::endl << "Searching on Double Hashing Table: ( m = " << HASH_TABLE_SIZE_2 << ") : " << std::endl;
	double_hashing->set_input_size_and_prime(HASH_TABLE_SIZE_2, *search_read_line_number);
	double_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_2 << ") : " << double_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with double hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << double_hashing->get_collision_searching() << std::endl;
	
	// END - Double Hashhing 

	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "UNIVERSAL HASHING:" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	// Universal Hashing with HASH_TABLE_SIZE_1
	std::cout << "Creating Universal Hashing Table: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	universal_hashing->set_input_size(HASH_TABLE_SIZE_1, *read_line_number);
	universal_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_1 << ") : " << universal_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << universal_hashing->get_collision_hashing() << std::endl;
	//universal_hashing->write_to_file();

	// Universal Hashhing Search with HASH_TABLE_SIZE_1
	std::cout << std::endl << "Searching on Universal Hashing Table: ( m = " << HASH_TABLE_SIZE_1 << ") : " << std::endl;
	universal_hashing->set_input_size(HASH_TABLE_SIZE_1, *search_read_line_number);
	universal_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_1 << ") : " << universal_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with universal hashing ( m = " << HASH_TABLE_SIZE_1 << ") : " << universal_hashing->get_collision_searching() << std::endl;
	
	std::cout << "--------------------------------------------------------------" << std::endl;

	// Universal Hashing with HASH_TABLE_SIZE_2
	universal_hashing->set_input_size(HASH_TABLE_SIZE_2, *read_line_number);
	universal_hashing->do_hash();
	std::cout << "Number of inserted element:( m = " << HASH_TABLE_SIZE_2 << ") : " << universal_hashing->get_number_inserted() << std::endl;
	std::cout << "Collision number when insertion with linear hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << universal_hashing->get_collision_hashing() << std::endl;
	//universal_hashing->write_to_file();

	// Universal Hashing with HASH_TABLE_SIZE_2
	std::cout << std::endl << "Searching on Universal Hashing Table: ( m = " << HASH_TABLE_SIZE_2 << ") : " << std::endl;
	universal_hashing->set_input_size(HASH_TABLE_SIZE_2, *search_read_line_number);
	universal_hashing->search_all(*search_read_line_number);
	std::cout << "Number of found element:( m = " << HASH_TABLE_SIZE_2 << ") : " << universal_hashing->get_found_number() << std::endl;
	std::cout << "Collision number when searching with universal hashing ( m = " << HASH_TABLE_SIZE_2 << ") : " << universal_hashing->get_collision_searching() << std::endl;
	// END - Universal Hashhing 

	
	std::cout << "--------------------------------------------------------------" << std::endl;


	delete double_hashing;
	delete linear_hashing;
	delete universal_hashing;
	delete read_line_number;
	delete search_read_line_number;
	input_file_line_arr.clear();
	search_file_line_arr.clear();

	std::cout << std::endl <<"Press any key to exit!" << std::endl;
	getchar();
	return 0;
}

std::vector<std::string> read_input_file(std::string input_filename, int *read_line_number) 
{

	std::vector<std::string> line_arr;

	std::ifstream readfile;
	readfile.open(input_filename);

	if (!readfile.is_open()) {
		std::cout << "Reading file cannot be opened!" << std::endl;
		std::vector<std::string> temp{ "error" };
		return temp;
	}

	std::string line_string;
	int line_number_counter = 0;
	while (!readfile.eof())
	{
		
		std::getline(readfile, line_string, '\n');

		if (line_string == "")
			continue;

		line_number_counter++;
		
		line_arr.push_back(line_string);
		//std::cout << (*linear_hashing).line_arr[line_number_counter] << std::endl;
		

	}


	readfile.close();
	std::cout << line_number_counter << " line is read from: " << input_filename << std::endl;
	*read_line_number = line_number_counter;
	return line_arr;
}

std::vector<std::string> read_search_file(std::string search_filename, int *read_line_number) 
{

	std::vector<std::string> line_arr;

	std::ifstream readfile;
	readfile.open(search_filename);

	if (!readfile.is_open()) {
		std::cout << "Reading file cannot be opened!" << std::endl;
		std::vector<std::string> temp{ "error" };
		return temp;
	}

	std::string line_string;
	int line_number_counter = 0;
	while (!readfile.eof())
	{
		
		std::getline(readfile, line_string, '\n');

		if (line_string == "")
			continue;

		line_number_counter++;
		
		line_arr.push_back(line_string);
		//std::cout << line_arr[line_number_counter] << std::endl;

	}

	readfile.close();
	std::cout << line_number_counter << " line is read from: " << search_filename << std::endl;
	*read_line_number = line_number_counter;
	return line_arr;
}