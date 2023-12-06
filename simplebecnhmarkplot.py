import matplotlib.pyplot as plt

# Iteration counts, mean times, and standard deviations from your C code
iteration_counts = [2, 3, 4, 5, 6, 7, 8, 9, 10]
mean_times = [0.000004, 0.000026, 0.000255, 0.001695, 0.008671, 0.085743, 0.857511, 8.583411, 85.890244]
std_deviations = [0.000001, 0.000000, 0.000040, 0.000529, 0.000135, 0.000285, 0.002904, 0.010822, 0.226863]

# Plotting
plt.errorbar(iteration_counts, mean_times, yerr=std_deviations, fmt='o-', label='Mean Time')
plt.xscale('log')  # Logarithmic scale for better visualization
plt.yscale('log')  # Logarithmic scale for better visualization
plt.xlabel('Iteration Count (log scale)')
plt.ylabel('Mean Time (log scale)')
plt.title('Runtime vs Iteration Count')
plt.legend()
plt.show()
