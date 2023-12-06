import matplotlib.pyplot as plt

# Latency data
latency_sizes = [4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 524288]
latency_values = [1500.00, 0.00, 0.00, 500.00, 500.00, 500.00, 0.00, 500.00, 0.00, 0.00]

# Throughput data (converting "inf" to a large value for plotting)
throughput_sizes = [4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 524288]
throughput_values = [3.81, 15.26, 61.04, float('inf'), float('inf'), 3906.25, 15625.00, 62500.00, 250000.00, 500000.00]

# Plot Latency
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(latency_sizes, latency_values, marker='o')
plt.title('Latency vs Message Size')
plt.xlabel('Message Size (bytes)')
plt.ylabel('Latency (nanoseconds)')

# Plot Throughput
plt.subplot(1, 2, 2)
plt.plot(throughput_sizes, throughput_values, marker='o')
plt.title('Throughput vs Message Size')
plt.xlabel('Message Size (bytes)')
plt.ylabel('Throughput (MB/s)')

# Show the plots
plt.tight_layout()
plt.show()