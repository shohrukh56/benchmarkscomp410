import matplotlib.pyplot as plt

# Iteration counts
iterations_original = list(range(1, 11))
iterations_modified = list(range(1, 11))  # Start from 1 for Modified Method

# Original Method results
original_means = [0.32039, 0.31851, 0.31719, 0.31820, 0.32103, 0.32416, 0.32083, 0.31911, 0.32344, 0.32050]
original_stddevs = [0.00762, 0.00069, 0.00243, 0.00212, 0.00947, 0.01394, 0.00770, 0.00121, 0.01712, 0.00674]

# Modified Method results
modified_means = [0.32150, 0.31946, 0.32176, 0.32254, 0.32050, 0.31892, 0.32163, 0.32139, 0.31896, 0.31603]
modified_stddevs = [0.00654, 0.00155, 0.01002, 0.01366, 0.00599, 0.00090, 0.01042, 0.01467, 0.00359, 0.00257]

# Plotting
plt.figure(figsize=(10, 6))

plt.errorbar(iterations_original, original_means, yerr=original_stddevs, label='Original Method', marker='o', linestyle='-', capsize=5)
plt.errorbar(iterations_modified, modified_means, yerr=modified_stddevs, label='Modified Method', marker='s', linestyle='--', capsize=5)

plt.xlabel('Iteration')
plt.ylabel('Mean Runtime (seconds)')
plt.title('Runtime Comparison: Original vs. Modified Method')
plt.legend()
plt.grid(True)
plt.show()
