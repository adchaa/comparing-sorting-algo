import pandas as pd
import matplotlib.pyplot as plt

# Configure the size and layout of the plot
plt.rcParams["figure.figsize"] = [7.00, 7.00]  # Keep the figure size
plt.rcParams["figure.autolayout"] = True

# Load Bubble Sort data
df_bubble = pd.read_csv("benchmark_result/bubble.csv", usecols=["size", "time"])
df_bubble = df_bubble.rename(columns={"time": "Bubble Sort"}).set_index('size')

# Load Insertion Sort data
df_insertion = pd.read_csv("benchmark_result/inseration.csv", usecols=["size", "time"])
df_insertion = df_insertion.rename(columns={"time": "Insertion Sort"}).set_index('size')

# Plot both datasets with points
ax = df_bubble.plot(style='-o', color='blue')
df_insertion.plot(style='-o', color='green', ax=ax)  # Use the same axes for both plots

# Set x-axis ticks explicitly based on the unique sizes from both datasets
plt.xticks(list(sorted(set(df_bubble.index).union(set(df_insertion.index)))), rotation=45, ha='right')

# Label the axes
plt.ylabel("Time (ms)")
plt.xlabel("n")

# Add a legend to distinguish the two plots
plt.legend()

# Display the plot
plt.show()
