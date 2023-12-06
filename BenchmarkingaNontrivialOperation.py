import matplotlib.pyplot as plt

# Data from C code results
system_calls = ['getpid', 'open', 'fork']
mean_runtimes = [0.000000, 0.000049, 0.000367]
stddevs = [0.000000, 0.000000, 0.000000]  # Replace with actual standard deviation values

# Plotting
fig, ax = plt.subplots()
bar_width = 0.35
opacity = 0.8

# Plotting bars with error bars
bars = ax.bar(system_calls, mean_runtimes, bar_width, alpha=opacity, label='Mean Runtime', yerr=stddevs)

ax.set_xlabel('System Calls')
ax.set_ylabel('Mean Runtime (seconds)')
ax.set_title('Mean Runtime of System Calls with Error Bars')
ax.legend()

plt.tight_layout()
plt.show()
