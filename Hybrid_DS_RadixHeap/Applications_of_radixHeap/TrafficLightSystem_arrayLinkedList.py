import time
class Node:
    def __init__(self, key, config):
        self.key = key
        self.config = config
        self.next = None

class TrafficLightSystem:
    def __init__(self):
        self.waiting_times = [0] * 10  # List to store waiting times for each configuration

    def apply_configuration(self, config):
        # Apply the configuration to the traffic light system
        # This could involve adjusting signal timings, setting patterns, etc.
        print(f"Applying configuration: {config}")

    def monitor_effectiveness(self):
        # Monitor the effectiveness of the current configuration
        # This could involve measuring traffic flow, wait times, etc.
        # and updating the waiting times for each configuration accordingly
        print("Monitoring effectiveness")

    def calculate_keys(self):
        # Recalculate keys for each configuration based on the waiting times
        # This could involve applying a specific formula or algorithm
        print("Calculating keys")

class RadixHeap:
    def __init__(self):
        self.min_key = float('inf')
        self.buckets = [None] * 10

    def insert(self, key, config):
        node = Node(key, config)
        if key < self.min_key:
            self.min_key = key
        if self.buckets[key] is None:
            self.buckets[key] = node
        else:
            curr = self.buckets[key]
            while curr.next is not None:
                curr = curr.next
            curr.next = node

    def extract_min(self):
        if self.min_key == float('inf'):
            return None

        min_config = self.buckets[self.min_key].config
        self.buckets[self.min_key] = self.buckets[self.min_key].next

        if self.buckets[self.min_key] is None:
            self.update_min_key()

        return min_config

    def update_min_key(self):
        for i in range(len(self.buckets)):
            if self.buckets[i] is not None:
                self.min_key = i
                return
        self.min_key = float('inf')

# Example usage:
start_time = time.perf_counter()

radix_heap = RadixHeap()
traffic_system = TrafficLightSystem()

# Step 1: Initialize
traffic_configurations = [5, 3, 8, 2, 7]
for key, config in enumerate(traffic_configurations):
    radix_heap.insert(key, config)

# Step 5: Signal Selection and Timing Adjustment
while True:
    selected_config = radix_heap.extract_min()
    if selected_config is None:
        break

    # Apply selected_config to the intersection
    traffic_system.apply_configuration(selected_config)

    # Monitor the effectiveness of the current configuration
    traffic_system.monitor_effectiveness()

    # Update waiting time values and recalculate keys based on feedback
    traffic_system.calculate_keys()

    # Insert updated configurations into the radix heap (optional)
    # radix_heap.insert(new_key, new_config)

# Repeat Steps 5-6 until termination condition is met
end_time = time.perf_counter()

# Calculate the duration in milliseconds
duration_ms = (end_time - start_time) * 1000

# Print the execution time in milliseconds
print("Execution time:", duration_ms, "milliseconds")