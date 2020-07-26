#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <climits>
#include <cfloat>
#include <cstring>
#include "marketdata.h"

#define FILE_NAME_READ "log_inf.csv"
#define FILE_NAME_WRITE "sorted.csv"
#define ARGUMENT_SIZE 7

int READ_LINE_NUMBER = 0; // number of readed lines

using namespace std;

void *reading_file(char, int, string*);
void writing_file(void *, string *, int, char);
void InsertonSort(void *, char, int);
void mergeSort(void *, int, int, char);
void merge_price(MarketDataLastPrice *, int, int, int);
void merge_time(MarketDataTimeStamp *, int, int, int);

int main(int argc, char *argv[]) {

	if (argc != 7) {
		cout << "Missing Arguments!" << endl;
		return 1;
	}

	char algorithm_type;
	char feature;
	int N;

	for (int i = 1; i < ARGUMENT_SIZE; i+=2) {
		if (strcmp(argv[i], "-algo") == 0)
			algorithm_type = *(argv[i + 1]);
		if(strcmp(argv[i], "-feature") == 0)
			feature = *(argv[i + 1]);
		if (strcmp(argv[i], "-size") == 0)
			N = stoi((argv[i + 1]));
	}

	cout << "Sorting type: " << algorithm_type << " Feature type: " << feature << " Size: " << N << endl;

	clock_t t_start_total, t_end_total;
	clock_t t_start_reading, t_end_reading;
	clock_t t_start_sorting, t_end_sorting;
	clock_t t_start_writing, t_end_writing;

	t_start_total = clock();

	MarketDataTimeStamp *arr_time = NULL;
	MarketDataLastPrice *arr_price = NULL;
	string *read_data = new string[N];
	void *arr = NULL;

	// reading part
	t_start_reading = clock();
	cout << "Reading has been started!" << endl;

	if (feature == 't') {
		arr_time = (MarketDataTimeStamp *)reading_file('t', N, read_data);
		arr = arr_time;
	}
	else if (feature == 'p') {
		arr_price = (MarketDataLastPrice *)reading_file('p', N, read_data);
		arr = arr_price;
	}
	else 
		cout<<"Incorrect argument for reading!"<<endl;
	t_end_reading = clock();
	cout << "Reading has been completed in " << double(t_end_reading - t_start_reading) / (CLOCKS_PER_SEC) << " seconds" << endl;
	// end reading part


	// sorting part
	t_start_sorting = clock()*1000;
	cout << "Sorting has been started!" << endl;

	if (algorithm_type == 'i') {
		InsertonSort(arr, feature, READ_LINE_NUMBER);
	}else if (algorithm_type == 'm') {
		mergeSort(arr, 0, READ_LINE_NUMBER - 1, feature);
	}
	else
		cout<<"Incorrect argument for sorting!"<<endl;
	t_end_sorting = clock()*1000;
	cout << "Sorting has been completed in " << double(double(t_end_sorting) - double(t_start_sorting)) / (CLOCKS_PER_SEC) << " microseconds" << endl;
	// end sorting part


	// writing part
	t_start_writing = clock();
	cout << "Writing has been started!" << endl;

	if (feature == 't') {
		writing_file(arr, read_data, READ_LINE_NUMBER, 't');

	}
	else if (feature == 'p') {
		writing_file(arr, read_data, READ_LINE_NUMBER, 'p');

	}
	else
		cout<<"Incorrect argument for writing!"<<endl;
	t_end_writing = clock();
	cout << "Writing has been completed in " << double(t_end_writing - t_start_writing) / (CLOCKS_PER_SEC) << " seconds" << endl;

	// end writing part

	delete[] read_data;
	delete[] arr_time;
	delete[] arr_price;

	t_end_total = clock();
	cout << "Program has been completed in " << double(t_end_total - t_start_total) / (CLOCKS_PER_SEC) << " seconds" << endl;

	cout << "Press any key to quit!" << endl;
	getchar();
	return 0;
}

void* reading_file(char data_type, int N, string *read_data) {

	const char* file_name = FILE_NAME_READ;

	ifstream readfile;
	readfile.open(file_name);

	if (!readfile.is_open()) {
		cout << "Reading file cannot be opened!" << endl;
		return NULL;
	}

	MarketDataTimeStamp *arr_time = NULL;
	MarketDataLastPrice *arr_price = NULL;

	if (data_type == 't') {
		arr_time = new MarketDataTimeStamp[N];
	}
	if (data_type == 'p') {
		arr_price = new MarketDataLastPrice[N];
	}

	int counter_read_line = 0;
	string line_string;
	while (!readfile.eof())
	{
		getline(readfile, line_string, '\n');

		if (line_string == "")
			break;

		counter_read_line++;

		if (counter_read_line == 1)
			continue;

		if (counter_read_line == N+2)
			break;

		READ_LINE_NUMBER++;
		read_data[counter_read_line-2] = line_string;

		if (data_type == 't') {
			string year_str = line_string.substr(0, 4);
			string month_day_str = line_string.substr(5, 2) + line_string.substr(8, 2);
			string hour_minute_second_str = line_string.substr(11, 2) + line_string.substr(14, 2) + line_string.substr(17, 2);;
			string milisecond_str = line_string.substr(20, 6);

			arr_time[counter_read_line-2].year = stoi(year_str);
			arr_time[counter_read_line-2].month_day = stoi(month_day_str);
			arr_time[counter_read_line-2].hour_minute_second = stoi(hour_minute_second_str);
			arr_time[counter_read_line-2].milisecond = stoi(milisecond_str);
			arr_time[counter_read_line-2].index_file_line = counter_read_line-2;

		}
		if (data_type == 'p') {
			string sub_string;
			int counter_word = 0;
			for (int i = 0; line_string[i] != '\n'; i++) {

				if (line_string[i] == ',') {
					counter_word++;

					if (counter_word == 3) {
						arr_price[counter_read_line-2].index_file_line = counter_read_line-2;
						arr_price[counter_read_line-2].last_price = stof(sub_string);
						break;
					}

					sub_string = "";
					continue;
				}
				sub_string += line_string[i];
			}

		}
	}
	readfile.close();

	cout << "Number of read line is " << READ_LINE_NUMBER << endl;

	if (data_type == 't')
		return arr_time;
	else if (data_type == 'p')
		return arr_price;
	else return NULL;
}
void writing_file(void *arr, string* read_data, int N, char feature) {

	const char* file_name = FILE_NAME_WRITE;

	ofstream writefile;
	writefile.open(file_name,ios::out | ios::trunc);

	if (!writefile.is_open()) {
		cout << "Writing file cannot be opened!" << endl;
		return;
	}

	writefile << "timestamp,instrument_token,last_price,volume,sell_quantity,last_quantity,change,average_price , open,high,low,close ,depth_buy_price_0 ,depth_buy_orders_0 ,depth_buy_quantity_0 ,depth_sell_price_0 ,depth_sell_orders_0 ,depth_sell_quantity_0 ,depth_buy_price_1 ,depth_buy_orders_1 ,depth_buy_quantity_1 ,depth_sell_price_1 ,depth_sell_orders_1 ,depth_sell_quantity_1 ,depth_buy_price_2 ,depth_buy_orders_2 ,depth_buy_quantity_2 ,depth_sell_price_2 ,depth_sell_orders_2 ,depth_sell_quantity_2 ,depth_buy_price_3 ,depth_buy_orders_3 ,depth_buy_quantity_3 ,depth_sell_price_3 ,depth_sell_orders_3 ,depth_sell_quantity_3 ,depth_buy_price_4 ,depth_buy_orders_4 ,depth_buy_quantity_4 ,depth_sell_price_4 ,depth_sell_orders_4 ,depth_sell_quantity_4" << endl;
		

	MarketDataTimeStamp *arr_time = NULL;
	MarketDataLastPrice *arr_price = NULL;
	
	if (feature == 't'){
		arr_time = (MarketDataTimeStamp *)arr;

		for (int i = 0; i < N; i++) {
			//cout << read_data[arr_time[i].index_file_line].substr(0,26) << endl;
			writefile << read_data[arr_time[i].index_file_line] << endl;
		}

	}
	else if (feature == 'p') {
		arr_price = (MarketDataLastPrice *)arr;

		for (int i = 0; i < N; i++) {
			//cout << arr_price[i].last_price << endl;
			writefile << read_data[arr_price[i].index_file_line] << endl;
		}
	}

	writefile.close();

}
void mergeSort(void *arr, int left, int right, char feature) {

	MarketDataTimeStamp *arr_time = NULL;
	MarketDataLastPrice *arr_price = NULL;


	if (feature == 't') {
		arr_time = (MarketDataTimeStamp *)arr;

		
		if (left < right) {
			int middle = (left + right) / 2;
			mergeSort(arr_time, left, middle, feature);
			mergeSort(arr_time, middle + 1, right, feature);
			merge_time(arr_time, left, middle, right);
		}
	}
	else if (feature == 'p') {
		arr_price = (MarketDataLastPrice *)arr;
	
		if (left < right) {
			int middle = (left + right) / 2;
			mergeSort(arr_price, left, middle,feature);
			mergeSort(arr_price, middle + 1, right,feature);
			merge_price(arr_price, left, middle, right);
			
		}
	}

}
void merge_price(MarketDataLastPrice *arr_price, int left, int middle, int right) {

	int len_left = (middle - left) + 1;
	int len_right = (right - middle);

	MarketDataLastPrice *left_arr_price = new MarketDataLastPrice[len_left + 1];
	MarketDataLastPrice *right_arr_price = new MarketDataLastPrice[len_right + 1];

	for (int i = 0; i < len_left; i++) {
		left_arr_price[i] = arr_price[left + i];
	}
	for (int j = 0; j < len_right; j++) {
		right_arr_price[j] = arr_price[middle + j + 1];
	}
	left_arr_price[len_left].last_price = FLT_MAX;
	right_arr_price[len_right].last_price = FLT_MAX;

	//sorting
	int i = 0;
	int j = 0;
	for (int k = left; k <= right; k++) {
		if (left_arr_price[i] <= right_arr_price[j]) {
			arr_price[k] = left_arr_price[i];
			i++;
		}
		else {
			arr_price[k] = right_arr_price[j];
			j++;
		}
	}
	delete [] left_arr_price;
	delete [] right_arr_price;
}
void merge_time(MarketDataTimeStamp *arr_time, int left, int middle, int right) {

	int len_left = (middle - left) + 1;
	int len_right = (right - middle);

	MarketDataTimeStamp *left_arr_time = new MarketDataTimeStamp[len_left + 1];
	MarketDataTimeStamp *right_arr_time = new MarketDataTimeStamp[len_right + 1];

	for (int i = 0; i < len_left; i++) {
		left_arr_time[i] = arr_time[left + i];
	}
	for (int j = 0; j < len_right; j++) {
		right_arr_time[j] = arr_time[middle + j + 1];
	}
	left_arr_time[len_left].year = INT_MAX;
	right_arr_time[len_right].year = INT_MAX;
	left_arr_time[len_left].hour_minute_second = INT_MAX;
	right_arr_time[len_right].hour_minute_second = INT_MAX;
	left_arr_time[len_left].month_day = INT_MAX;
	right_arr_time[len_right].month_day = INT_MAX;
	left_arr_time[len_left].milisecond = INT_MAX;
	right_arr_time[len_right].milisecond = INT_MAX;

	//sorting
	int i = 0;
	int j = 0;
	for (int k = left; k <= right; k++) {
		if (left_arr_time[i] <= right_arr_time[j]) {
			arr_time[k] = left_arr_time[i];
			i++;
		}
		else {
			arr_time[k] = right_arr_time[j];
			j++;
		}
	}
	delete[] left_arr_time;
	delete[] right_arr_time;
}
void InsertonSort(void *arr,char type, int N) {

	if (type == 't') {
		MarketDataTimeStamp *arr_time = (MarketDataTimeStamp *)arr;
		MarketDataTimeStamp *temp = new MarketDataTimeStamp;

		int j;
		for (int i = 1; i < N; i++) {
			*temp = arr_time[i];
			j = i - 1;
			while (j >= 0 && arr_time[j] > *temp) {
				arr_time[j + 1] = arr_time[j];
				j -= 1;
			}
			arr_time[j + 1] = *temp;
		}
	
	}
	if (type == 'p') {
		MarketDataLastPrice *arr_price = (MarketDataLastPrice *)arr;
		MarketDataLastPrice *temp = new MarketDataLastPrice;

		int j;
		for (int i = 1; i < N; i++) {
			*temp = arr_price[i];
			j = i - 1;

			while (j >= 0 && arr_price[j].last_price > temp->last_price) {
				arr_price[j + 1] = arr_price[j];
				j -= 1;
			}
			arr_price[j + 1] = *temp;
		}
	}
	

}