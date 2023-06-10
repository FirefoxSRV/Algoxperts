
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class RadixHeap {
private:
    static const int NUM_BUCKETS = 64;
    static const int MAX_VALUES = 1000;

    int buckets[NUM_BUCKETS][MAX_VALUES];
    int bucket_sizes[NUM_BUCKETS];
    int min_value;

public:
    RadixHeap() : bucket_sizes{}, min_value(-1) {}

    bool is_empty() {
        return min_value == -1;
    }

    void insert(int value) {
        int mask = value & -value;
        int index = static_cast<int>(log2(mask));
        buckets[index][bucket_sizes[index]] = value;
        bucket_sizes[index]++;

        if (min_value == -1 || value < min_value) {
            min_value = value;
        }
    }

    int extract_min() {
        int min_bucket = find_min_bucket();
        int min_value = buckets[min_bucket][0];
        for (int i = 1; i < bucket_sizes[min_bucket]; i++) {
            buckets[min_bucket][i - 1] = buckets[min_bucket][i];
        }
        bucket_sizes[min_bucket]--;

        if (bucket_sizes[min_bucket] == 0) {
            update_min_value();
        }
        return min_value;
    }

    void delete_min() {
        int min_bucket = find_min_bucket();
        for (int i = 1; i < bucket_sizes[min_bucket]; i++) {
            buckets[min_bucket][i - 1] = buckets[min_bucket][i];
        }
        bucket_sizes[min_bucket]--;

        if (bucket_sizes[min_bucket] == 0) {
            update_min_value();
        }
    }

    void merge(RadixHeap& other_heap) {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            int other_size = other_heap.bucket_sizes[i];
            for (int j = 0; j < other_size; j++) {
                buckets[i][bucket_sizes[i] + j] = other_heap.buckets[i][j];
            }
            bucket_sizes[i] += other_size;
            other_heap.bucket_sizes[i] = 0;
        }
        update_min_value();
        other_heap.update_min_value();
    }

    int find_min_bucket() {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            if (bucket_sizes[i] > 0) {
                return i;
            }
        }
        return -1; // No non-empty bucket found
    }

    void update_min_value() {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            if (bucket_sizes[i] > 0) {
                min_value = *std::min_element(buckets[i], buckets[i] + bucket_sizes[i]);
                return;
            }
        }
        min_value = -1; // No non-empty bucket found
    }

    void print_heap() {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            int size = bucket_sizes[i];
            if (size > 0) {
                for (int j = 0; j < size; j++) {
                    cout << buckets[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
};

void printWelcome() {
    cout << "******************************\n";
    cout << "*    Radix Heap Operations   *\n";
    cout << "******************************\n";
    cout << endl;
}

void printMenu() {
    cout << "Available Operations:\n";
    cout << "1. Insert value\n";
    cout << "2. Extract minimum value\n";
    cout << "3. Delete minimum value\n";
    cout << "4. Merge with another heap\n";
    cout << "5. Print heap\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    RadixHeap heap1;
    RadixHeap heap2;
    int option;

    printWelcome();

    do {
        printMenu();
        cin >> option;

        switch (option) {
            case 1: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                heap1.insert(value);
                cout << "Value " << value << " inserted into the heap.\n";
                break;
            }
            case 2: {
                if (heap1.is_empty()) {
                    cout << "Heap is empty.\n";
                } else {
                    int min_value = heap1.extract_min();
                    cout << "Minimum value extracted: " << min_value << endl;
                }
                break;
            }
            case 3: {
                if (heap1.is_empty()) {
                    cout << "Heap is empty.\n";
                } else {
                    heap1.delete_min();
                    cout << "Minimum value deleted.\n";
                }
                break;
            }
            case 4: {
                int num_values;
                cout << "Enter the number of values to insert into the second heap: ";
                cin >> num_values;
                cout << "Enter the values:\n";
                for (int i = 0; i < num_values; i++) {
                    int value;
                    cin >> value;
                    heap2.insert(value);
                }
                heap1.merge(heap2);
                cout << "Heaps merged.\n";
                break;
            }
            case 5: {
                cout << "Heap contents: ";
                heap1.print_heap();
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
        cout << endl;
    } while (option != 6);

    return 0;
}
