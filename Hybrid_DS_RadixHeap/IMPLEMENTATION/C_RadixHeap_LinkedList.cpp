#include <iostream>
#include <cmath>

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node* head;
    Node* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    void push(int element) {
        Node* node = new Node(element);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void deleteElement(int element) {
        int flag = 0;
        Node* curr = head;
        if (curr->data == element) {
            head = head->next;
            delete curr;
        } else {
            while (curr->next) {
                if (curr->next->data == element) {
                    Node* temp = curr->next;
                    curr->next = curr->next->next;
                    delete temp;
                    size--;
                    if (tail->data == element) {
                        tail = curr;
                    }
                    flag = 1;
                    break;
                }
                curr = curr->next;
            }
            if (flag != 1) {
                std::cout << "Element not found!" << std::endl;
            }
        }
    }

    void pop() {
        Node* min_element_return = head;
        head = head->next;
        std::cout << "Element removed: " << min_element_return->data << std::endl;
        delete min_element_return;
    }

    void print() {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
    }

    int getSize() {
        return size;
    }
};

class RadixHeap {
private:
    Queue* buckets[32];
    int min_value;

public:
    RadixHeap() : min_value(0) {
        for (int i = 0; i < 32; i++) {
            buckets[i] = new Queue();
        }
    }

    void insert(int value) {
        int index = static_cast<int>(log2(value & -value));
        buckets[index]->push(value);
        if (min_value == 0 || value < min_value) {
            min_value = value;
        }
    }

    void deleteElement(int value) {
        int index = static_cast<int>(log2(value & -value));
        buckets[index]->deleteElement(value);
        min_value = findMinElement();
        updateMinValue();
    }

    void extractMinElement() {
        for (int i = 0; i < 32; i++) {
            if (buckets[i]->getSize() > 0) {
                buckets[i]->pop();
                break;
            }
        }
    }

    void heapMerge(RadixHeap* other) {
        for (int i = 0; i < 32; i++) {
            if (buckets[i]->getSize() > 0 && other->buckets[i]->getSize() > 0) {
                buckets[i]->tail->next = other->buckets[i]->head;
                buckets[i]->tail = other->buckets[i]->tail;
            }
            // No need to handle other cases since it's not mentioned in the original code
        }
    }

    void print() {
        for (int i = 0; i < 32; i++) {
            if (buckets[i]->getSize() > 0) {
                std::cout << "[ ";
                buckets[i]->print();
                std::cout << "]" << std::endl;
            }
        }
    }

    int findMinElement() {
        for (int i = 0; i < 32; i++) {
            if (buckets[i]->getSize() > 0) {
                return buckets[i]->head->data;
            }
        }
        return 0;  // Return a default value if no elements are found (e.g., 0 in this case)
    }

    void updateMinValue() {
        for (int i = 0; i < 32; i++) {
            if (buckets[i]->getSize() > 0) {
                Node* curr = buckets[i]->head;
                int min_ = min_value;
                while (curr) {
                    if (curr->data < min_) {
                        min_value = curr->data;
                    }
                    curr = curr->next;
                }
            }
        }
    }
};

int main() {
    RadixHeap heap;
    heap.insert(8);
    heap.insert(10);
    heap.insert(5);
    heap.insert(3);
    heap.insert(12);
    heap.insert(2);
    heap.print();
    std::cout << heap.findMinElement() << std::endl;
    std::cout << std::endl;
    heap.deleteElement(2);
    heap.print();
    std::cout << heap.findMinElement() << std::endl;
    heap.extractMinElement();
    heap.print();
    std::cout << "---" << std::endl;
    RadixHeap heap2;
    heap2.insert(8);
    heap2.insert(10);
    heap2.insert(5);
    heap2.insert(3);
    heap2.insert(12);
    heap2.insert(2);
    heap2.print();
    std::cout << "---" << std::endl;
    heap.heapMerge(&heap2);
    heap.print();

    return 0;
}
