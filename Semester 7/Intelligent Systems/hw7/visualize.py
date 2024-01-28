import matplotlib.pyplot as plt
import sys

def plot_clusters(filename):
    clusters = {}
    
    with open(filename, 'r') as file:
        for line in file:
            if line.strip():  # Non-empty line
                cluster_index, x, y = map(float, line.split())
                if cluster_index not in clusters:
                    clusters[cluster_index] = []
                clusters[cluster_index].append((x, y))

    # Plotting clusters
    for cluster_index, cluster_points in clusters.items():
        x_vals = [point[0] for point in cluster_points]
        y_vals = [point[1] for point in cluster_points]
        plt.scatter(x_vals, y_vals, label=f'Cluster {int(cluster_index)}')

    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Cluster Visualization')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script_name.py input_file.txt")
    else:
        input_file = sys.argv[1]
        plot_clusters(input_file)

