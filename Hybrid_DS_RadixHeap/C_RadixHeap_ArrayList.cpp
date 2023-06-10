
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

int main() {
    RadixHeap heap1;
    heap1.insert(8);
    heap1.insert(5);
    heap1.insert(10);
    heap1.insert(3);
    heap1.insert(12);
    heap1.insert(2);
    heap1.print_heap();

    RadixHeap heap2;
    heap2.insert(15);
    heap2.insert(1);
    heap2.insert(7);
    heap2.insert(9);
    heap2.insert(4);
    heap2.print_heap();

    heap1.merge(heap2);
    heap1.print_heap();

    while (!heap1.is_empty()) {
        cout << heap1.extract_min() << " ";
    }
    cout << endl;

    return 0;
}
