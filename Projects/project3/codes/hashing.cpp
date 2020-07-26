# include "hashing.h"


void LinearHashing::do_hash() {

	if (!sized)
		hash_table = new std::string[hash_table_size];

	for (int i = 0; i < hash_table_size; i++) {
		hash_table[i] = "";
		//std::cout << line_arr[i] << std::endl;
	}


	for (int line = 0; line < size_input_array; line++) {
		for (int i = 0; i < hash_table_size ; i++) {
			if (add_hash(line, i)) {
				break;
			}
			else {
				//std::cout << "Collision is occured with (k,i,line):(" << line << "," << i << "," << line_arr->at(line) << ")" << std::endl;
				collision_hashing++;
			}

			if (number_inserted == hash_table_size) {
				std::cout << "Hash array is full!" << std::endl;
				return;
			}
		}
		
	}

}
bool LinearHashing::add_hash(int key, int index) {

	int location = get_hashing_index(key, index);

	if (hash_table[location] == "") {
		hash_table[location]= line_arr->at(key);
		key_line_pair[line_arr->at(key)] = key;
		number_inserted++;
		return true;
	}
	else return false;
	
}

int LinearHashing::get_hashing_index(int key, int index) {

	int location = (key + index) % hash_table_size;
	return location;
}
/*
void LinearHashing::search_element_by_line(int vocab_line, std::string search) {

	if (hash_table[vocab_line] == search)
		return true;
	else return false;

}*/

void LinearHashing::search_all(int read_line) {

	size_search_array = read_line;
	
	for (int i = 0; i < size_search_array; i++) {

		int vocab_line = key_line_pair[search_line_arr->at(i)];

		if (key_line_pair.find(search_line_arr->at(i)) == key_line_pair.end()) { // not found

			int rand_loc = rand() % hash_table_size;
			int counter = 0;
			int out_flag = 0;

			for (int j = 0; j < hash_table_size; j++) { // k
				for (int k = 0; k < hash_table_size; k++) { //i

					int temp_index = get_hashing_index((j+rand_loc)%hash_table_size,k);

					if (hash_table[temp_index ] != search_line_arr->at(i) && search_line_arr->at(i) != "") {
						collision_searching++;
					}
					else {
						number_found++;
						break;//found
					}

					counter++;
					if (counter == hash_table_size) {
						std::cout << "Whole hash table is searched ( m = " << hash_table_size << ") : but '"<< search_line_arr->at(i) <<"' is not found! Number of searched line is: " << counter << std::endl;
						out_flag = 1;
						break;
					}
				}
				if (out_flag)
					break;
			}
			
		}
		else {
			for (int j = 0; j < hash_table_size; j++) {
				int temp_index = get_hashing_index(vocab_line,j);
				if (hash_table[temp_index ] != search_line_arr->at(i) && search_line_arr->at(i)!="") {
					collision_searching++;
				}
				else{ 
					number_found++;
					break;//found
				}
			}
			
		}
		//std::cout << temp << " " << search_line_arr->at(i) << std::endl;
	}
	
}
void LinearHashing::write_to_file() {

	std::ofstream writefile;
	writefile.open("linear_hashing_table.txt", std::ios::out | std::ios::trunc);

	if (!writefile.is_open()) {
		std::cout << "Double Hashing writing file cannot be opened!" << std::endl;
		return;
	}

	int counter = 0;
	for (int i = 0; i < hash_table_size; i++) {
		if (hash_table[i] != "")
			counter++;
		writefile << i << " " << hash_table[i] << std::endl;

	}
	std::cout << "Number of inserted element with counter: " << counter << std::endl;

	writefile.close();
}
/*
for (int i = 0; i < size_input_array; i++) {
	if (add_hash(line, i)) {
		break;
	}
	else {
		//std::cout << "Collision is occured with double hashing (k,i,line):(" << line << "," << i << "," << line_arr->at(line) << ")" << std::endl;
		collision_hashing++;
		continue;
	}
}*/
void DoubleHashing::do_hash() {

	if (!sized)
		hash_table = new std::string[hash_table_size];


	for (int i = 0; i < hash_table_size; i++) {
		hash_table[i] = "";
		//std::cout << line_arr[i] << std::endl;
	}


	for (int line = 0; line < size_input_array; line++) {
		for (int i = 0; i < hash_table_size; i++) {
			if (add_hash(line, i)) {
				break;
			}
			else {
				//std::cout << "Collision is occured with double hashing (k,i,line):(" << line << "," << i << "," << line_arr->at(line) << ")" << std::endl;
				collision_hashing++;
			}

			if (number_inserted == hash_table_size) {
				std::cout << "Hash array is full!" << std::endl;
				return;
			}
		}

	}


	

}

int DoubleHashing::get_hashing_index(int key, int index) {

	int location_one = key % hash_table_size;
	int location_two = prime - (key % prime);

	int location = (location_one + location_two * index) % hash_table_size;

	return location;
}
bool DoubleHashing::add_hash(int key, int index) {


	int location = get_hashing_index(key, index);

	if (hash_table[location] == "") {
		hash_table[location] = line_arr->at(key);
		key_line_pair[line_arr->at(key)] = key;
		number_inserted++;
		return true;
	}
	else return false;

}

void DoubleHashing::search_all(int read_line) {

	size_search_array = read_line;


	for (int i = 0; i < size_search_array; i++) {

		int vocab_line = key_line_pair[search_line_arr->at(i)];
		

		if (key_line_pair.find(search_line_arr->at(i)) == key_line_pair.end()) { // not found

			int rand_loc = rand() % hash_table_size;
			int counter = 0;
			int out_flag = 0;

			for (int j = 0; j < hash_table_size; j++) { // k
				for (int k = 0; k < hash_table_size; k++) { //i
					int temp_index = get_hashing_index((j + rand_loc) % hash_table_size, k);

					if (hash_table[temp_index] != search_line_arr->at(i) && search_line_arr->at(i) != "") {
						collision_searching++;
					}
					else {
						number_found++;
						break;//found
					}
					counter++;
					if (counter == hash_table_size) {
						std::cout << "Whole hash table is searched ( m = " << hash_table_size << ") : but '" << search_line_arr->at(i) << "' is not found! Number of searched line is: " << counter << std::endl;
						out_flag = 1;
						break;
					}
				}
				if (out_flag)
					break;
			}

		}
		else {
			for (int j = 0; j < hash_table_size; j++) {
				int temp_index = get_hashing_index(vocab_line, j);
				if (hash_table[temp_index] != search_line_arr->at(i) && search_line_arr->at(i) != "") {
					collision_searching++;
				}
				else {
					number_found++;
					break;//found
				}
			}

		}
		//std::cout << temp << " " << search_line_arr->at(i) << std::endl;
	}
}
bool DoubleHashing::is_prime(int number) {

	int counter_divider = 0;
	for (int i = 2; i < number; i++) {
		if (number%i == 0)
			counter_divider++;
	}

	if (counter_divider == 0)
		return true;
	else return false;
}

void DoubleHashing::set_input_size_and_prime(int hash_table_size_in, int input_size_in) {

	size_input_array = input_size_in;
	hash_table_size = hash_table_size_in;
	collision_searching = 0;
	collision_hashing = 0;
	number_inserted = 0;
	number_found = 0;

	int i = hash_table_size - 1;
	for (; i >= 2; i--) {
		if (is_prime(i))
			break;
	}
	prime = i;
	std::cout << "Determined prime number is : " << prime << std::endl;
	
}
void DoubleHashing::write_to_file() {

	std::ofstream writefile;
	writefile.open("double_hashing_table.txt", std::ios::out | std::ios::trunc);

	if (!writefile.is_open()) {
		std::cout << "Double Hashing writing file cannot be opened!" << std::endl;
		return;
	}

	int counter = 0;
	for (int i = 0; i < hash_table_size; i++) {
		if (hash_table[i] != "")
			counter++;
		writefile << i << " " << hash_table[i] << std::endl;

	}
	std::cout << "Number of inserted element with counter: " << counter << std::endl;
	writefile.close();
}


void UniversalHashing::do_hash() {

	if (!sized)
		hash_table = new std::string[hash_table_size];

	for (int i = 0; i < hash_table_size; i++) {
		hash_table[i] = "";
		//std::cout << line_arr[i] << std::endl;
	}


	int decom_arr[3] = { 0 };
	int location_for_collasion;

	get_random_a();

	for (int line = 0; line < size_input_array; line++) {

		decomposition(line, decom_arr);
		//std::cout << "Decom..: " << line << " -- " << decom_arr[0] << " " << decom_arr[1] << " " << decom_arr[2] << std::endl;
		//std::cout << "rando..: " << line << " -- " << a[0] << " " << a[1] << " " << a[2] << std::endl;

		if (add_hash(line, decom_arr, &location_for_collasion))
			continue;
		
		//std::cout << "Collision is occured with universal hashing (key,location_for_collasion,line_string):(" << line << "," << *location_for_collasion << "," << line_arr->at(line) << ")" << std::endl;
		for (int i = 0; i < hash_table_size ; i++) {

			if (add_hash_with_linear_hashing(line,location_for_collasion, i)) {
				break;
			}
			else {
				//std::cout << "Collision is occured with lienar hashing (k,i,line):(" << line << "," << i << "," << line_arr->at(line) << ")" << std::endl;
				collision_hashing++;
			}

			if (number_inserted == hash_table_size) {
				std::cout << "Hash array is full!" << std::endl;
				return;
			}
		}


	}

}
bool UniversalHashing::add_hash(int key, int *decom_arr, int *location_for_collasion) {

	int location = get_hashing_index(key, decom_arr, location_for_collasion);

	if (hash_table[location] == "") {
		hash_table[location] = line_arr->at(key);
		key_line_pair[line_arr->at(key)] = key;
		number_inserted++;
		return true;
	}
	else return false;
}
bool UniversalHashing::add_hash_with_linear_hashing(int line,int key, int index) {

	int location = (key + index) % hash_table_size;

	if (hash_table[location] == "") {
		hash_table[location] = line_arr->at(line);
		key_line_pair[line_arr->at(line)] = line;
		number_inserted++;
		return true;
	}
	else return false;
}

int UniversalHashing::get_hashing_index(int key, int  *decom_arr, int *location_for_collasion) {

	int sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += decom_arr[i] * random_a[i];
	}

	int location = sum % hash_table_size;
	*location_for_collasion = location;

	return location;
}
int UniversalHashing::get_hashing_index_linear(int  key, int index) {

	int location = (key + index) % hash_table_size;
	return location;
}


void UniversalHashing::search_all(int read_line) {

	size_search_array = read_line;

	int decom_arr[3] = { 0 };
	int *location_for_collasion = new int;


	for (int i = 0; i < size_search_array; i++) { // searched line - i

		int counter = 0;
		int vocab_line = key_line_pair[search_line_arr->at(i)];

		if (key_line_pair.find(search_line_arr->at(i))== key_line_pair.end()) { // not found

			int rand_loc = rand() % hash_table_size;
			decomposition(vocab_line, decom_arr);
			int temp_index = get_hashing_index(rand_loc, decom_arr, location_for_collasion);  //check unseen word at random location

			if (hash_table[temp_index] == search_line_arr->at(i)) { // if  found then continue but surely this not work
				number_found++;
				continue;//found
			}
			// not found
			// linear searching
			for (int k = 0; k < hash_table_size; k++) { // i // continue search with linear hashing

				int temp_index = get_hashing_index_linear(*location_for_collasion,k);

				if (hash_table[temp_index] != search_line_arr->at(i) && search_line_arr->at(i) != "") {
					collision_searching++;
				}
				else {
					number_found++;
					break;//found
				}
				counter++;
				if (counter == hash_table_size) {
					std::cout << "Whole hash table is searched ( m = " << hash_table_size << ") : but '" << search_line_arr->at(i) << "' is not found! Number of searched line is: " << counter + 1 << std::endl;
					break;
				}
		

			}

		}
		else { // if there is a key in map
			int rand_loc = rand() % hash_table_size;
			decomposition(vocab_line, decom_arr);
			int temp_index = get_hashing_index(rand_loc, decom_arr, location_for_collasion);

			if (hash_table[temp_index] == search_line_arr->at(i)) { // not probable
				number_found++;
				continue;//found
			}

			//std::cout << *location_for_collasion << std::endl;

			// linear searching
			for (int k = 0; k < hash_table_size; k++) { // i // continue search with linear hashing

				int temp_index = get_hashing_index_linear(*location_for_collasion, k);

				if (hash_table[temp_index] != search_line_arr->at(i) && search_line_arr->at(i) != "") {
					collision_searching++;
				}
				else {
					number_found++;
					break;//found
				}
				counter++;
				if (counter == hash_table_size) {
					std::cout << "Whole hash table is searched ( m = " << hash_table_size << ") : but '" << search_line_arr->at(i) << "' is not found! Number of searched line is: " << counter + 1 << std::endl;
					break;
				}
			}
			//std::cout << k << std::endl;
		}
	}
}
void UniversalHashing::get_random_a() {

	random_a[0] = std::rand();
	random_a[0] %= hash_table_size;

	random_a[1] = std::rand();
	random_a[1] %= hash_table_size;

	random_a[2] = std::rand();
	random_a[2] %= hash_table_size;

	std::cout << "Random a: a[0]: " << random_a[0] << " a[1]: " << random_a[1] << " a[2]: " << random_a[2] << std::endl;

}
void UniversalHashing::decomposition(int key, int *decom_arr) {

	int step_counter = 0;
	bool step_k0 = true, step_k1 = true, step_k2 = true;
	decom_arr[0] = 0;
	decom_arr[1] = 0;
	decom_arr[2] = 0;

	while (key > 0 && step_counter <= 5) {
		if (step_counter==0 && step_k2) {
			decom_arr[2] = key % 10;
			step_k2 = false;

		}
		else if(step_counter == 1 && !step_k2){
			decom_arr[2] += (key % 10) * 10;

		}
		if (step_counter == 2 && step_k1) {
			decom_arr[1] = key % 10;
			step_k1 = false;

		}
		else if (step_counter == 3 && !step_k1) {
			decom_arr[1] += (key % 10) * 10;

		}
		if (step_counter == 4 && step_k0) {
			decom_arr[0] = key % 10;
			step_k0 = false;
		}
		else if (step_counter == 5 && !step_k0) {
			decom_arr[0] += (key % 10) * 10;

		}

		step_counter++;
		key /= 10;
	}

	//std::cout << "iceri..: " << " -- " << decom_arr[0] << " " << decom_arr[1] << " " << decom_arr[2] << std::endl;

}
void UniversalHashing::write_to_file() {

	std::ofstream writefile;
	writefile.open("universal_hashing_table.txt", std::ios::out | std::ios::trunc);

	if (!writefile.is_open()) {
		std::cout << "Universal Hashing writing file cannot be opened!" << std::endl;
		return;
	}

	int counter = 0;
	for (int i = 0; i < hash_table_size; i++) {
		if (hash_table[i] != "")
			counter++;
		writefile << i << " " << hash_table[i] << std::endl;
	
	}
	std::cout << "Number of inserted element with counter: " << counter << std::endl;
	writefile.close();
}
