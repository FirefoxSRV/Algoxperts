import math


class Node:
    def __init__(self, value):
        self.data = value
        self.next = None


class Queue:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def push(self, element):
        node = Node(element)
        if self.head is None:
            self.head = node
            self.tail = node

        else:
            self.tail.next = node
            self.tail = node

        self.size += 1

    def delete(self, element):
        flag = 0
        curr = self.head
        if curr.data == element:
            self.head = self.head.next

        # if self.tail.data == element:

        while curr.next:
            if curr.next.data == element:
                curr.next = curr.next.next
                self.size -= 1
                if self.tail.data == element:
                    self.tail = curr
                flag = 1

                break
            curr = curr.next
        if flag != 1:
            print("Element not found!")

    def pop(self):
        min_element_return = self.head
        self.head = self.head.next
        print("Element removed: ", min_element_return.data)

    def print(self):
        curr = self.head
        while curr:
            print(curr.data, end=" ")
            curr = curr.next


class RadixHeap:
    def __init__(self):
        self.buckets = [Queue() for _ in range(32)]
        self.min_value = None

    def insert(self, value):
        self.buckets[int(math.log2(value & -value))].push(value)
        if self.min_value is None or value < self.min_value:
            self.min_value = value

    def delete(self, value):
        self.buckets[int(math.log2(value & -value))].delete(value)
        self.min_value = self.min_element()
        self.update_min_value()

    def extract_min_element(self):
        for cont in self.buckets:
            if cont.size > 0:
                cont.pop()
                return

    def heap_merge(self, other):
        for i in range(len(self.buckets)):
            if self.buckets[i].size > 0 and other.buckets[i].size > 0:
                self.buckets[i].tail.next = other.buckets[i].head
                self.buckets[i].tail = other.buckets[i].tail

            else:
                if self.buckets[i].size == 0 and self.buckets[i].size > 0:
                    self.buckets[i].head = other.buckets[i].head
                    self.buckets[i].tail = other.buckets[i].tail

                if self.buckets[i].size > 0 and self.buckets[i].size == 0:
                    pass

    def print(self):
        for cont in self.buckets:
            if cont.size > 0:
                print("[", end=" ")
                cont.print()
                print("]")

    def min_element(self):
        for cont in self.buckets:
            if cont.size > 0:
                return cont.head.data

    def update_min_value(self):
        for cont in self.buckets:
            if cont.size > 0:
                curr = cont.head
                min_ = self.min_value
                while curr:
                    if curr.data < min_:
                        self.min_value = curr.data
                    curr = curr.next


heap = RadixHeap()
heap.insert(8)
heap.insert(10)
heap.insert(5)
heap.insert(3)
heap.insert(12)
heap.insert(2)
heap.print()
print(heap.min_element())
print()
heap.delete(2)
heap.print()
print(heap.min_value)
heap.extract_min_element()
heap.print()
print("---")
heap2 = RadixHeap()
heap2.insert(8)
heap2.insert(10)
heap2.insert(5)
heap2.insert(3)
heap2.insert(12)
heap2.insert(2)
heap2.print()
print("---")
heap.heap_merge(heap2)
heap.print()
