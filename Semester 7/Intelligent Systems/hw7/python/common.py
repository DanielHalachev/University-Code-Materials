import math

import numpy as np
from matplotlib import pyplot as plt


def distance(point1, point2):
    return math.sqrt(((point1[0] - point2[0]) ** 2) + ((point1[1] - point2[1]) ** 2))


def read_points(file_path):
    with open(file_path, 'r') as file:
        points = []
        for line in file:
            x, y = map(float, line.strip().split())
            points.append([x, y])
        return np.array(points)


def intra_cluster_distance(cluster):
    centroid = np.mean(cluster, axis=0)
    return sum(distance(point, centroid) for point in cluster)


def visualize_clusters(clusters):
    colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k']
    for i, cluster in enumerate(clusters):
        plt.scatter(cluster[:, 0], cluster[:, 1], c=colors[i % len(colors)], label=f'Cluster {i+1}')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('KMeans Clustering')
    plt.legend()
    plt.show()


def calculate_centroids(clusters):
    centroids = list(map(lambda cluster: [sum(p[0] for p in cluster) / len(cluster),
                                          sum(p[1] for p in cluster) / len(cluster)], clusters))
    return np.array(centroids)


def assign_clusters(points, centroids):
    num_clusters = len(centroids)
    clusters = list(map(lambda _: [], range(num_clusters)))
    for point in points:
        distances = [distance(point, centroid) for centroid in centroids]
        closest_centroid_index = np.argmin(distances)
        clusters[closest_centroid_index].append(point)
    return [np.array(cluster) for cluster in clusters]


def k_means_pp_initialization(points, k):
    centroids = [points[np.random.randint(len(points))]]

    for _ in range(1, k):
        squared_distances = []
        for point in points:
            min_distance_sq = min(distance(point, centroid) ** 2 for centroid in centroids)
            squared_distances.append(min_distance_sq)

        distances = np.array(squared_distances)
        probabilities = distances / np.sum(distances)

        next_centroid_index = np.random.choice(len(points), p=probabilities)
        centroids.append(points[next_centroid_index])

    return np.array(centroids)
