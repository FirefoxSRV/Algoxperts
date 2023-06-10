import math

class RadixHeap:
    def __init__(self):
        self.buckets = [[] for _ in range(64)]  # 64 buckets for 64-bit integers
        self.min_value = None

    def is_empty(self):
        return self.min_value is None

    def insert(self, value):
        # print(value & -value)
        # print(int(math.log2(value & -value)))
        self.buckets[int(math.log2(value & -value))].append(value)
        if self.min_value is None or value < self.min_value:
            self.min_value = value

    def extract_min(self):
        min_bucket = self.find_min_bucket()
        min_value = self.buckets[min_bucket].pop(0)
        if not self.buckets[min_bucket]:
            self.update_min_value()
        return min_value

    def delete(self,value):
        radix_pos=int(math.log2(value&-value))
        bucket=self.buckets[radix_pos]
        for i in range(len(bucket)):
            if bucket[i]==value:
                bucket.pop(i)
                if value==self.min_value:
                    self.update_min_value()
                return
        print("Element not found in radix heap")

    def merge_heap(self,other_heap):
        for i in range(len(self.buckets)):
            self.buckets[i].extend(other_heap.buckets[i])
        if other_heap.min_value is not None and (self.min_value is None or other_heap.min_value < self.min_value):
            self.min_value = other_heap.min_value

    def find_min_bucket(self):
        for i in range(len(self.buckets)):
            if self.buckets[i]:
                return i

    def update_min_value(self):
        self.min_value = None
        for i in range(len(self.buckets)):
            if self.buckets[i]:
                bucket_min = min(self.buckets[i])
                if self.min_value is None or self.min_value>bucket_min:
                    self.min_value = bucket_min


    def print_heap(self):
        for cont in self.buckets:
            if cont!=[]:
                print (cont)


heap = RadixHeap()
heap.insert(8)
heap.insert(5)
heap.insert(10)
heap.insert(3)
heap.insert(12)
heap.insert(2)
print(heap.min_value)
heap.delete(2)
print(heap.min_value)
heap.insert(4)
heap.delete(3)
print(heap.min_value)
heap.print_heap()
print(heap.extract_min())
while not heap.is_empty():
    print(heap.extract_min())
