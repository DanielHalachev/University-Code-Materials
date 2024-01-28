import sys

import numpy as np

from common import read_points, visualize_clusters, intra_cluster_distance, calculate_centroids, assign_clusters, \
    k_means_pp_initialization


def kmeansWithoutIterationsLimit(points, k, use_k_means_plus_plus=False, max_iterations=5):
    best_solution = None
    best_distance = float('inf')

    for _ in range(max_iterations):
        if use_k_means_plus_plus:
            centroids = k_means_pp_initialization(points, k)
        else:
            centroids = points[np.random.choice(len(points), k, replace=False)]

        while True:
            clusters = assign_clusters(points, centroids)
            if any(len(cluster) == 0 for cluster in clusters):
                break
            new_centroids = calculate_centroids(clusters)
            if np.array_equal(centroids, new_centroids):
                break
            centroids = new_centroids

        total_distance = sum(intra_cluster_distance(cluster) for cluster in clusters)
        if total_distance < best_distance:
            best_distance = total_distance
            best_solution = clusters

    return best_solution


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python kmeans_clustering.py <file_path> <k> <useKmeans++>")
        sys.exit(1)

    file_path = sys.argv[1]
    k = int(sys.argv[2])
    if len(sys.argv) == 4:
        use_k_means_plus_plus = bool(int(sys.argv[3]))
    else:
        use_k_means_plus_plus = False

    points = read_points(file_path)
    clusters = kmeansWithoutIterationsLimit(points, k, use_k_means_plus_plus)
    visualize_clusters(clusters)
