#include <string>
#include <iostream>
#include <vector> 
#include <map> 
#include <iterator>
#include <fstream>
#include <ctime>
#include <cstdlib>

class LinearHashing {

private:
	int size_input_array; // number of reading line from input file
	int size_search_array; // number of reading line from searching file

	int hash_table_size; // m -> hash table size

	int number_inserted;
	int number_found;

	int collision_hashing;
	int collision_searching;
	bool sized;

	std::string *hash_table;
	std::map<std::string, int> key_line_pair;

	//std::map<int, std::string> index_string_pair;
public:
	LinearHashing() {
		sized = false;
		size_search_array = 0;
		size_input_array = 0;
		collision_hashing = 0;
		number_inserted = 0;
		collision_searching = 0;
		number_found = 0;
		hash_table_size = 0;

	};
	LinearHashing(int size_input_in, int size_search_in, int hash_table_size_in) {
		sized = true;
		collision_hashing = 0;
		collision_searching = 0;
		number_inserted = 0;
		number_found = 0;
		hash_table_size = hash_table_size_in;
		size_input_array = size_input_in;
		size_search_array = size_search_in;
		hash_table = new std::string[size_input_array];
	};
	~LinearHashing() {
		//delete[] line_arr;
		delete[] hash_table;
		
	};

	std::vector<std::string> *line_arr;
	std::vector<std::string> *search_line_arr;

	void do_hash();
	bool add_hash(int, int);
	void search_all(int);
	//void search_element_by_line( int, int);
	int get_hashing_index(int, int );
	void write_to_file();
	void set_input_size(int hash_table_size_in, int input_size_in) {
		size_input_array = input_size_in;
		hash_table_size = hash_table_size_in;
		collision_searching = 0; 
		collision_hashing = 0; 
		number_inserted = 0;
		number_found = 0;
	};
	int get_found_number() { return number_found; };
	int get_number_inserted() { return number_inserted; };
	int get_collision_hashing() { return collision_hashing; };
	int get_collision_searching() { return collision_searching; };

};

class DoubleHashing {

private:
	int size_input_array;
	int size_search_array;

	int hash_table_size;

	int number_inserted;
	int number_found;

	int collision_hashing;
	int collision_searching;
	bool sized;
	int prime;

	std::string *hash_table;
	std::map<std::string, int> key_line_pair;

	//std::map<int, std::string> index_string_pair;
public:
	DoubleHashing() {
		sized = false;
		size_input_array = 0;
		collision_hashing = 0;
		collision_searching = 0;
		hash_table_size = 0;
		number_found = 0;
		number_inserted = 0;
		prime = 2;
	};
	DoubleHashing(int hash_table_size_in, int input_size_in, int prime_in) {
		sized = true;
		collision_hashing = 0;
		collision_searching = 0;
		number_found = 0;
		size_input_array = input_size_in;
		hash_table_size = hash_table_size_in;
		prime = prime_in;
		number_inserted = 0;
		hash_table = new std::string[size_input_array];
	};
	~DoubleHashing() {
		//delete[] line_arr;
		delete[] hash_table;

	};

	std::vector<std::string> *line_arr;
	std::vector<std::string> *search_line_arr;

	void do_hash();
	bool add_hash(int, int);
	int get_hashing_index(int, int);
	void search_all(int);
	bool is_prime(int);
	void write_to_file();
	int get_number_inserted() { return number_inserted; };
	int get_found_number() { return number_found; };
	void set_input_size_and_prime(int, int);
	int get_collision_hashing() { return collision_hashing; };
	int get_collision_searching() { return collision_searching; };
};

class UniversalHashing {

private:
	int size_input_array;
	int size_search_array;

	int hash_table_size;
	int *random_a;

	int number_inserted;
	int number_found;

	int collision_hashing;
	int collision_searching;
	bool sized;
	int prime;

	std::string *hash_table;
	std::map<std::string, int> key_line_pair;

public:
	UniversalHashing() {
		sized = false;
		size_input_array = 0;
		size_search_array = 0;
		collision_hashing = 0;
		number_inserted = 0;
		number_found = 0;
		hash_table_size = 0;
		collision_searching = 0;
		prime = 2;
		random_a = new int[3];
		std::srand((unsigned int)std::time(NULL));
	};
	UniversalHashing(int hash_table_size_in, int size_input_in, int size_search_in, int prime_in) {
		sized = true;
		collision_hashing = 0;
		collision_searching = 0;
		number_inserted = 0;
		number_found = 0;
		hash_table_size = hash_table_size_in;
		size_input_array = size_input_in;
		size_search_array = size_search_in;
		prime = prime_in;
		random_a = new int[3];
		hash_table = new std::string[size_input_array];
		std::srand((unsigned int)std::time(NULL));
	};
	~UniversalHashing() {
		delete[] hash_table;

	};

	std::vector<std::string> *line_arr;
	std::vector<std::string> *search_line_arr;

	void do_hash();
	bool add_hash(int, int*, int*);
	void search_all(int);
	int get_hashing_index(int, int*, int*);
	int get_hashing_index_linear(int,int);
	bool add_hash_with_linear_hashing(int, int, int);
	void decomposition(int, int *);
	void get_random_a();
	void set_input_size(int hash_table_size_in, int input_size_in) {
		size_input_array = input_size_in;
		hash_table_size = hash_table_size_in;
		collision_searching = 0;
		collision_hashing = 0;
		number_inserted = 0;
		number_found = 0;
	};
	int get_number_inserted() { return number_inserted; };
	int get_found_number() { return number_found; };
	void write_to_file();
	int get_collision_hashing() { return collision_hashing; };
	int get_collision_searching() { return collision_searching; };
};
