#include "heap.h"
#include <climits>
#include <iostream>
#include <cmath>

using namespace std;


void Heap::max_heapify(int index) {

	int left = Left(index);
	int right = Right(index);
	int largest = index;

	if (left < heap_size && arr[left] > arr[index]) 
		largest = left;
	else
		largest = index;

	if (right < heap_size && arr[right] > arr[largest])
		largest = right;
	
	if (largest != index) {
		//swap
		swap(&arr[index], &arr[largest]);
		swap(&id_arr[index], &id_arr[largest]);

		max_heapify(largest);
	}
}
void Heap::min_heapify(int index) {

	int left = Left(index);
	int right = Right(index);
	int smallest = index;

	if (left < heap_size && arr[left] < arr[index])
		smallest = left;
	else
		smallest = index;

	if (right < heap_size && arr[right] < arr[smallest])
		smallest = right;

	if (smallest != index) {
		//swap
		swap(&arr[index], &arr[smallest]);
		swap(&id_arr[index], &id_arr[smallest]);

		min_heapify(smallest);
	}
}
void Heap::build_max_heap() {

	heap_size = length;
	for (int i = (length / 2) - 1; i >= 0; i--) {
		max_heapify(i);
	}
}
void Heap::build_min_heap() {

	heap_size = length;
	for (int i = (length / 2)- 1; i >= 0; i--) {
		min_heapify(i);
	}
}
void Heap::ascending_heapsort() {

	build_max_heap();
	
	for (int i = length - 1; i >= 1; i--) {
		//swap
		swap(&arr[i], &arr[0]);
		swap(&id_arr[i], &id_arr[0]);

		heap_size--;
		max_heapify(0);
	}
}
void Heap::descending_heapsort() {

	build_min_heap();

	for (int i = length - 1; i >= 1; i--) {
		//swap
		swap(&arr[i], &arr[0]);
		swap(&id_arr[i], &id_arr[0]);

		heap_size--;
		min_heapify(0);
	}
}
int Heap::heap_maximum(char which_arr) {
	if(which_arr=='i')
		return id_arr[0];
	return arr[0];
}
int Heap::heap_minimum(char which_arr) {
	if (which_arr == 'i')
		return id_arr[0];
	return arr[0];
}
int Heap::heap_extract_max(char which_arr) {

	if (heap_size < 1) {
		cout << "Heap underflow!" << endl;
		return '0';
	}
	if (heap_size == 1) {

		heap_size--;
		max_value = arr[0];
		max_value_id = id_arr[0];

		if (which_arr == 'i')
			return max_value_id;

		return max_value;
	}

	max_value = arr[0];
	max_value_id = id_arr[0];

	arr[0] = arr[heap_size - 1];
	id_arr[0] = id_arr[heap_size - 1];

	heap_size--;
	length--;
	max_heapify(0);

	if (which_arr == 'i')
		return max_value_id;

	return max_value;
}
int Heap::heap_extract_min(char which_arr) {

	if (heap_size < 1) {
		cout << "Heap underflow!" << endl;
		return 0;
	}
	if (heap_size == 1) {
		heap_size--;
		min_value = arr[0];
		min_value_id = id_arr[0];

		if (which_arr == 'i')
			return min_value_id;

		return min_value;
	}

	min_value = arr[0];
	min_value_id = id_arr[0];

	arr[0] = arr[heap_size - 1];
	id_arr[0] = id_arr[heap_size - 1];
	heap_size--;
	length--;
	min_heapify(0);


	if (which_arr == 'i')
		return min_value_id;

	return min_value;
}
void Heap::heap_increase_key(int index, int key, int id) {

	if (key < arr[index]) {
		cout << "New key is smaller than current key" << endl;
		return;
	}

	arr[index] = key;
	id_arr[index] = id;

	while (index > 1 && arr[Parent(index)] < arr[index]) {
		//swap
		swap(&arr[index], &arr[Parent(index)]);
		swap(&id_arr[index], &id_arr[Parent(index)]);

		index = Parent(index);
	}


}
void Heap::heap_decrease_key(int index, int key, int id) {

	if (key > arr[index]) {
		cout << "New key is smaller than current key" << endl;
		return;
	}
	arr[index] = key;
	id_arr[index] = id;
	while (index > 1 && arr[Parent(index)] > arr[index]) {
		//swap
		swap(&arr[index], &arr[Parent(index)]);
		swap(&id_arr[index], &id_arr[Parent(index)]);

		index = Parent(index);
	}


}
void Heap::max_heap_insert( int key, int id) {

	if (heap_size < length)
		heap_size = length;

	heap_size++;
	length++;

	if (capacity <= heap_size ) {
		capacity *= 2;
		int *temp_arr = new int[capacity];
		int *temp_id_arr = new int[capacity];

		for (int i = 0; i < length; i++) {
			temp_arr[i] = arr[i];
			temp_id_arr[i] = id_arr[i];
		}
		delete[] arr;
		delete[] id_arr;
		id_arr = temp_id_arr;
		arr = temp_arr;
	}

	arr[heap_size-1] = INT_MIN;
	heap_increase_key(heap_size-1, key, id);
	
}
void Heap::min_heap_insert(int key, int id) {

	if (heap_size < length)
		heap_size = length;

	heap_size++;
	length++;

	if (capacity <= heap_size) {
		capacity *= 2;
		int *temp_arr = new int[capacity];
		int *temp_id_arr = new int[capacity];

		for (int i = 0; i < length; i++) {
			temp_arr[i] = arr[i];
			temp_id_arr[i] = id_arr[i];

		}
		delete[] arr;
		delete[] id_arr;
		arr = temp_arr;
		id_arr = temp_id_arr;
	}

	arr[heap_size-1] = INT_MAX;
	heap_decrease_key(heap_size-1, key, id);

}
int Heap::Parent(int index) {

	if (index == 0) {
		cout << "Parents of root are not defined!" << endl;
		return 0;
	}

	return (index - 1) / 2;
}
int Heap::Left(int index) {
	
	return 2 * index + 1;

}
int Heap::Right(int index) {

	return 2 * (index + 1);
}
void Heap::check_capacity() {

	if (capacity <= length) {
		capacity *= 2;

		int *temp_arr = new int[capacity];
		int *temp_id_arr = new int[capacity];

		for (int i = 0; i < length; i++) {
			temp_arr[i] = arr[i];
			temp_id_arr[i] = id_arr[i];
		}
		delete[] arr;
		delete[] id_arr;

		arr = temp_arr;
		id_arr = temp_id_arr;
	}
}
void Heap::swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}