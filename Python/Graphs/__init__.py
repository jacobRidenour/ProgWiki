import os
import numpy as np
import matplotlib.pyplot as plt

def __init__():
    csv_path = os.path.join(os.path.dirname(__file__), 'bugs.csv')
    
    data = np.genfromtxt(csv_path, delimiter=',', names=True, dtype=None)

    # Extract run and time columns
    runs = data['Run']
    times = data['Time']

    # Scatter plot
    plt.scatter(runs, times)
    plt.xlabel('Run')
    plt.ylabel('Time (Frames)')
    plt.title('Time vs. Run (Scatter Plot)')
    plt.show()
    
    # Bell curve
    plt.hist(times, bins=20, density=True, alpha=0.6, color='g')
    plt.xlabel('Time (frames)')
    plt.ylabel('Frequency')
    plt.title('Distribution of Times (Bell Curve)')
    plt.show()
    
    # Show statistics
    min_time = np.min(times)
    max_time = np.max(times)
    std_dev = np.std(times)
    variance = np.var(times)
    mean_time = np.mean(times)
    median_time = np.median(times)
    mode_time = float(np.argmax(np.bincount(times)))

    # Display the statistics
    print(f"Minimum Time: {min_time:.2f}")
    print(f"Maximum Time: {max_time:.2f}")
    print(f"Standard Deviation: {std_dev:.2f}")
    print(f"Variance: {variance:.2f}")
    print(f"Mean Time: {mean_time:.2f}")
    print(f"Median Time: {median_time:.2f}")
    print(f"Mode Time: {mode_time:.2f}")
    


__init__()

