
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <unordered_set>

typedef std::vector<double> Point;

std::vector<Point> &readCSV(std::vector<Point> &data, const std::string &pathToFile) {
    std::ifstream file(pathToFile);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            Point point;
            while (std::getline(iss, token, ',')) {
                point.push_back(std::stod(token));
            }
            data.push_back(point);
        }
    }
    file.close();
    return data;
}

double distance(const Point &point1, const Point &point2) {
    double distance = 0;
    for (size_t i = 0; i < point1.size(); i++) {
        distance += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    return std::sqrt(distance);
}

void kMeansUtil(const std::vector<Point> &data,
                std::vector<std::vector<Point>> &clusters,
                std::vector<Point> &centroids) {
    clusters.resize(centroids.size());
    std::vector<Point> newCentroids = centroids;
    do {
        centroids = newCentroids;
        clusters.clear();
        for (const auto &instance: data) {
            double minDistance = INFINITY;
            size_t clusterIndex = 0;
            for (size_t centroidIndex = 0; centroidIndex < centroids.size(); centroidIndex++) {
                double temp = distance(instance, centroids[centroidIndex]);
                if (temp < minDistance) {
                    minDistance = temp;
                    clusterIndex = centroidIndex;
                }
            }
            clusters[clusterIndex].push_back(instance);
        }
        for (int centroidIndex = 0; centroidIndex < clusters.size(); centroidIndex++) {
            for (int attributeIndex = 0; attributeIndex < clusters[0].size(); attributeIndex++) {
                double attributeSum = 0;
                for (auto &instance: clusters[centroidIndex]) {
                    attributeSum += instance[attributeIndex];
                }
                newCentroids[centroidIndex][attributeIndex] =
                        (double) attributeSum / (double) clusters[centroidIndex].size();
            }
        }
    } while (newCentroids != centroids);

}

std::vector<Point> getRandomCentroids(const std::vector<Point> &data, unsigned int k) {
    std::random_device randomDevice;
    std::uniform_int_distribution<size_t> distribution(0, data.size());
    std::unordered_set<size_t> indexes;
    while (indexes.size() < k) {
        indexes.insert(distribution(randomDevice));
    }
    std::vector<Point> result;
    result.reserve(k);
    for (auto &index: indexes) {
        result.push_back(data[index]);
    }
    return result;
}

size_t getImprovedCentroidsUtil(const std::vector<Point> &data, const std::vector<Point> &centroids) {
    double totalDistance = 0;
    std::vector<double> distances(data.size(), INFINITY);
    // for every data point, compute the distance between it and the nearest already chosen centroid
    for (size_t i = 0; i < data.size(); i++) {
        for (auto &centroid: centroids) {
            distances[i] = std::min(distances[i], distance(data[i], centroid));
        }
        totalDistance += distances[i];
    }
    // choose a new data point at random using a weighted probability distribution
    std::random_device randomDevice;
    std::vector<double> squaredDistances(distances.size());
    std::transform(distances.begin(), distances.end(), squaredDistances.begin(),
                   [](double distance) { return distance * distance; });
    std::discrete_distribution<size_t> distribution(squaredDistances.begin(), squaredDistances.end());
    return distribution(randomDevice);
//    std::uniform_real_distribution<double> distribution(0, totalDistance);
//    double random = distribution(randomDevice);
//    double sum = 0;
//    for(size_t i = 0; i<data.size(); i++){
//        sum += distances[i];
//        if (sum >= random){
//            return i;
//        }
//    }
//    return 0;
}

std::vector<Point> getImprovedCentroids(const std::vector<Point> &data, unsigned int k) {
    std::random_device randomDevice;
    std::uniform_int_distribution<size_t> distribution(0, data.size());
    const Point &first = data[distribution(randomDevice)];
    std::vector<Point> result;
    result.reserve(k);
    result.push_back(first);
    for (size_t i = 1; i < k; i++) {
        result.push_back(data[getImprovedCentroidsUtil(data, result)]);
    }
    return result;
}

std::vector<std::vector<Point>> kMeans(const std::vector<Point> &data, bool useKMeansPlusPlus) {
//    std::random_device randomDevice;
//    std::shuffle(data.begin(), data.end(), randomDevice);
    int k = 10;
    std::vector<std::vector<Point>> clusters;
    std::vector<Point> centroids = useKMeansPlusPlus ? getImprovedCentroids(data, k) : getRandomCentroids(data, k);
    kMeansUtil(data, clusters, centroids);
    return clusters;
}

void writeClustersToFile(const std::vector<std::vector<Point>> &clusters, const std::string &pathToFile) {
    std::ofstream file(pathToFile);
    if (file.is_open()) {
        for (int clusterIndex = 0; clusterIndex < clusters.size(); clusterIndex++) {
            file << clusterIndex << ";";
            for (auto &point: clusters[clusterIndex]) {
                for (int attributeIndex = 0; attributeIndex < point.size() - 1; attributeIndex++) {
                    file << point[attributeIndex] << ";";
                }
                file << point[point.size() - 1];
            }
            file << std::endl;
        }
    }
    file.close();
}

int main(int argc, char *argv[]) {
    bool useKMeansPlusPlus = argc >= 3;
    std::vector<Point> data;
    readCSV(data, argv[1]);

    writeClustersToFile(kMeans(data, useKMeansPlusPlus), argv[2]);

    return 0;
}


