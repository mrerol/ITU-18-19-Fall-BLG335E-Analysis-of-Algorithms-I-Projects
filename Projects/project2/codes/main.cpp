#define _CRT_SECURE_NO_WARNINGS

#include "heap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>

#define NUM_FILENAME "numbers.csv"


using namespace std;


int read_to_file_days(Heap *, string, int);
int read_to_file_numbers(Heap *, string);
void write_heap_to_screen(Heap *);
void call_center();
void number_analysis();
void execute_day(Heap*, int);

int main() {

	int choice = -1;
	bool flag = true;


	while (flag) {

		cout << "Welcome!" << endl;
		cout << "Press:" << endl << "1 - Call Center" << endl << "2 - Number Analysis" << endl << "3 - Exit" << endl;
		cout << "Choice: ";

		cin >> choice;

		system("CLS");

		if (choice == 1) {
			call_center();
		}
		else if (choice == 2) {
			number_analysis();
		}
		else if (choice == 3) {
			cout << "Bye!" << endl;
			getchar();
			getchar();
			return 0;
		}
		else
			cout << "Wrong choice! Try Again!" << endl;

		cin.clear();
		fflush(stdin);
	}

	getchar();
	return 0;
}

void call_center() {

	string temp_filename;

	ofstream writefile;
	writefile.open("day_analysis.txt");
	writefile.close();

	Heap *heap_arr = new Heap[4];

	//Heap *max_call_heap = new Heap(); -> heap_arr[0]
	//Heap *min_call_heap = new Heap();-> heap_arr[1]
	//Heap *best_preformance_heap = new Heap();-> heap_arr[2]
	//Heap *worst_preformance_heap = new Heap();-> heap_arr[3]


	for (int i = 1; i <= 10; i++) {
		temp_filename = "day" + to_string(i) + ".csv";
		read_to_file_days(heap_arr, temp_filename, i);
	}


}
void number_analysis() {

	clock_t t_start_step, t_end_step;


	ofstream writefile;
	writefile.open("numbers_sorted.csv");

	string num_filename = NUM_FILENAME;

	Heap *num_heap = new Heap();


	read_to_file_numbers(num_heap,num_filename);

	num_heap->build_max_heap();

	cout << "Sorting has been started!" << endl << endl;;
	for (int i = 0; i < 10; i++) {

		t_start_step = clock();

		cout << "Heigh of heap is :" << floor(log2(num_heap->get_heap_size())) << endl;

		for (int j = 0; j < 200000; j++) {
			writefile << num_heap->heap_extract_max('d') << endl;;
		}

		t_end_step = clock() ;
		cout << "Execution time of " << i + 1 << ". step : " << double(t_end_step - t_start_step) / (CLOCKS_PER_SEC) << " seconds" << endl;

		cout << endl;
	}
	cout << endl;

}
int read_to_file_days(Heap *heap_arr, string filename, int day) {

	ifstream readfile;
	readfile.open(filename);

	if (!readfile.is_open()) {
		cout << "Reading file cannot be opened!" << endl;
		return 0;
	}

	string line_string;
	string word = "";
	int counter_word = 0;
	int counter_line = 0;
	int counter_readed_line = 0;
	string line_array[4];
	while (!readfile.eof())
	{
		getline(readfile, line_string, '\n');
		line_string += "\n";

		if (line_string == "" || line_string == "\n")
			break;

		while (line_string[counter_line] != '\n') {

			if (line_string[counter_line] == ',') {
				line_array[counter_word] = word;
				counter_word++;
				word = "";
				counter_line++;
				continue;
			}
			word += line_string[counter_line];

			if (counter_word >= 4)
				break;

			counter_line++;
		}

		line_array[3] = word;

		int temp_id = stoi(line_array[0]);
		int temp_call = stoi(line_array[1]);
		int temp_positive = stoi(line_array[2]);
		int temp_negative = stoi(line_array[3]);
		int score = 2 * temp_call + temp_positive - temp_negative;

		counter_readed_line++;
		bool found = false;

		word = "";
		counter_word = 0;
		counter_line = 0;

		if (day == 1) {

			// ALL HEAP ARRAYS ARE SET
			for (int i = 0; i <= 1; i++) {
				heap_arr[i].arr[counter_readed_line - 1] = temp_call;
				heap_arr[i].id_arr[counter_readed_line - 1] = temp_id;
				heap_arr[i].length++;
				heap_arr[i].check_capacity();
			}
			for (int i = 2; i <= 3; i++) {
				heap_arr[i].arr[counter_readed_line - 1] = score;
				heap_arr[i].id_arr[counter_readed_line - 1] = temp_id;
				heap_arr[i].length++;
				heap_arr[i].check_capacity();
			}

			continue;

		}

		//MAXIMUM CALL
		// search all array for id in order to insert or update
		for (int i = 0; i < heap_arr[0].length; i++) { // search for id
			if (heap_arr[0].id_arr[i] == temp_id) {
				heap_arr[0].heap_increase_key(i, heap_arr[0].arr[i]+temp_call, heap_arr[0].id_arr[i]);
				found = true;
			}
		}

		if (!found) { // insert
			heap_arr[0].max_heap_insert(temp_call, temp_id);
			found = false;
		}

		// MINIMUM CALL
		// search all array for id in order to insert or update
		for (int i = 0; i < heap_arr[1].length; i++) { // search for id
			if (heap_arr[1].id_arr[i] == temp_id) {
				heap_arr[1].arr[i] += temp_call;
				found = true;
			}
		}
		if (!found) { // insert
			heap_arr[1].min_heap_insert(temp_call, temp_id);
			found = false;
		}

		//BEST PERFORMANCE
		// search all array for id in order to insert or update
		for (int i = 0; i < heap_arr[2].length; i++) { // search for id
			if (heap_arr[2].id_arr[i] == temp_id) {
				heap_arr[2].heap_increase_key(i, heap_arr[2].arr[i] + score, heap_arr[2].id_arr[i]);
				found = true;
			}
		}
		if (!found) { // insert
			heap_arr[2].max_heap_insert(score, temp_id);
			found = false;
		}

		//WORST PERFORMANCE
		// search all array for id in order to insert or update
		for (int i = 0; i < heap_arr[3].length; i++) { // search for id
			if (heap_arr[3].id_arr[i] == temp_id) {
				heap_arr[3].arr[i] += score;
				found = true;
			}
		}

		if(!found) { // insert
			heap_arr[3].min_heap_insert(score, temp_id);
			found = false;
		}

	} // end file reading

	execute_day(heap_arr, day);

	readfile.close();
	return counter_line -1;
}
int read_to_file_numbers(Heap *numbers_array, string filename) {

	clock_t t_start_reading, t_end_reading;

	ifstream readfile;
	readfile.open(filename);

	if (!readfile.is_open()) {
		cout << "Reading file cannot be opened!" << endl;
		return 0;
	}

	int counter_line = 0;
	t_start_reading = clock();
	cout << "Reading has been started!" << endl;
	while (readfile >> numbers_array->arr[counter_line++]) {
		//cout << numbers_array->arr[counter_line++] << endl;
		numbers_array->length++;
		numbers_array->check_capacity();
	}

	readfile.close();
	t_end_reading = clock();
	cout << "Reading has been completed in " << double(t_end_reading - t_start_reading) / (CLOCKS_PER_SEC) << " seconds" << endl;


	return counter_line -1;
}
void write_heap_to_screen(Heap *heap) {

	cout << "Heap array is shown below with given size: " << heap->length << endl;
	for (int i = 0; i < heap->length; i++) {
		cout << "ID: " << heap->id_arr[i];
		cout << " Value: " << heap->arr[i] << endl;

		if (i == 10)
			break;
	}
}
void execute_day(Heap *heap_arr, int day) {

	//write_heap_to_screen(&heap_arr[0]);

	int temp;
	
	ofstream writefile;
	writefile.open("day_analysis.txt", ofstream::out | ofstream::app);

	cout << "AFTER DAY - " << day << endl;
	writefile << "AFTER DAY - " << day << endl;

	cout << "BEST PERFORMANCE : ";
	writefile << "BEST PERFORMANCE : ";
	heap_arr[2].build_max_heap();
	int temp_arr[3];
	int temp_arr_id[3];
	for (int i = 0; i < 3; i++) {
		cout << "VALUE(" << heap_arr[2].heap_maximum('d') << ")-";
		temp_arr[i] = heap_arr[2].heap_maximum('d');
		temp_arr_id[i] = heap_arr[2].heap_extract_max('i');
		cout << "ID(" << temp_arr_id[i] << ")";
		writefile << temp_arr_id[i];
		if (i != 2) {
			cout << ", ";
			writefile << ", ";
		}
	}
	for (int i = 0; i < 3; i++)
		heap_arr[2].max_heap_insert(temp_arr[i], temp_arr_id[i]);

	cout << endl;
	writefile << endl;


	cout << "MAXIMUM CALLS    : ";
	writefile << "MAXIMUM CALLS    : ";
	heap_arr[0].build_max_heap();
	for (int i = 0; i < 3; i++) {
		cout << "VALUE("<<heap_arr[0].heap_maximum('d')<<")-";
		temp_arr[i] = heap_arr[0].heap_maximum('d');
		temp_arr_id[i] = heap_arr[0].heap_extract_max('i');
		cout << "ID(" << temp_arr_id[i] << ")";
		writefile << temp_arr_id[i];
		if (i != 2) {
			cout << ", ";
			writefile << ", ";
		}
	}
	for (int i = 0; i < 3; i++)
		heap_arr[0].max_heap_insert(temp_arr[i], temp_arr_id[i]);
	cout << endl;
	writefile << endl;


	if (day == 10) {

		cout << "WORST PERFORMANCE: ";
		writefile << "WORST PERFORMANCE: ";
		heap_arr[3].build_min_heap();
		for (int i = 0; i < 3; i++) {
			cout << "VALUE(" << heap_arr[3].heap_maximum('d') << ")-";
			temp = heap_arr[3].heap_extract_min('i');
			cout << "ID(" << temp << ")";
			writefile << temp;
			if (i != 2) {
				cout << ", ";
				writefile << ", ";
			}
		}
		cout << endl;
		writefile << endl;

		cout << "MINIMUM CALLS    : ";
		writefile << "MINIMUM CALLS    : ";
		heap_arr[1].build_min_heap();
		for (int i = 0; i < 3; i++) {
			cout << "VALUE(" << heap_arr[1].heap_maximum('d') << ")-";
			temp = heap_arr[1].heap_extract_min('i');
			cout << "ID(" << temp << ")";
			writefile << temp;
			if (i != 2) {
				cout << ", ";
				writefile << ", ";
			}
		}
		cout << endl;
		writefile << endl;
	}
	cout << endl;
	writefile << endl;

	writefile.close();
}
