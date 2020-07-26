#define CAPACITY 100

class Heap {
private:
	int capacity;  // capacity of array

	int heap_size; // heap number of array
	int max_value;
	int min_value;
	int max_value_id;
	int min_value_id;

	void max_heapify(int);
	void min_heapify(int);
public:

	int length;    // elements numbers of array

	int *arr;
	int *id_arr;
	
	Heap() :capacity(CAPACITY), length(0), heap_size(0) {
		arr = new int[CAPACITY];
		id_arr = new int[CAPACITY];
	};
	Heap(int size):capacity(size), length(0), heap_size(0) {
		arr = new int[size];
		id_arr = new int[size];
	};
	~Heap() { 
		delete[] arr;
		delete[] id_arr;
	};

	int Parent(int);
	int Left(int);
	int Right(int);


	void build_max_heap();
	void build_min_heap();
	void ascending_heapsort();
	void descending_heapsort();
	int heap_maximum(char);
	int heap_minimum(char);
	int heap_extract_max(char);
	int heap_extract_min(char);
	void heap_increase_key(int , int, int);
	void heap_decrease_key(int, int, int);
	void max_heap_insert(int, int);
	void min_heap_insert(int, int);

	void check_capacity();
	void swap(int *, int *);

	int get_heap_size() { return heap_size; };
	void set_heap_size(int size) { heap_size = size; };
	int get_heap_size(int size) { return heap_size; };
};

