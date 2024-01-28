#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "KDTree.h"


inline Label kNNClassify(const std::unordered_map<Point, Label> &pointToLabelMap,
                         const std::vector<std::pair<double, Point>> &kNearest) {
    std::map<double, Label> kNearestLabels;
    std::unordered_map<Label, int> occurrences;
    std::unordered_map<Label, double> smallestDistances;
    for (const auto &distanceLabelPair: kNearest) {
        double distance = distanceLabelPair.first;
        const Point &point = distanceLabelPair.second;
        const Label &label = pointToLabelMap.at(point);
        kNearestLabels[distance] = label;
        occurrences[label]++;
        if (smallestDistances.find(label) != smallestDistances.end()) {
            smallestDistances[label] = std::min(smallestDistances[label], distance);
        } else {
            smallestDistances[label] = distance;
        }
    }

    std::vector<Label> mostOccurredLabels;
    int mostOccurences = 0;
    for (auto &labelOccurrencePair: occurrences) {
        Label label = labelOccurrencePair.first;
        int currentOccurs = labelOccurrencePair.second;
        if (currentOccurs > mostOccurences) {
            mostOccurences = currentOccurs;
            mostOccurredLabels.clear();
            mostOccurredLabels.push_back(label);
        } else if (currentOccurs == mostOccurences) {
            mostOccurredLabels.push_back(label);
        }
    }

    double smallestDistance = INFINITY;
    Label labelWithSmallestDistance;
    for (auto &label: mostOccurredLabels) {
        double distance = smallestDistances[label];
        if (distance < smallestDistance) {
            smallestDistance = distance;
            labelWithSmallestDistance = label;
        }
    }

    return labelWithSmallestDistance;
}

inline void
readCSV(std::vector<Point> &points, std::unordered_map<Point, Label> &pointToLabelMap, const std::string &pathToFile) {
    std::ifstream file(pathToFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> segments;
            std::string token;
            std::istringstream iss(line);
            while (std::getline(iss, token, ',')) {
                segments.push_back(token);
            }
            if (segments.size() > 1) {
                segments.resize(segments.size() - 1);
            }

            std::vector<double> coordinates;
            coordinates.reserve(segments.size());
            for (auto &str: segments) {
                coordinates.push_back(std::stod(str));
            }
            Point point(coordinates);
            pointToLabelMap[point] = token;
            points.push_back(point);
        }
    }
    file.close();
}


inline void
crossValidation(std::vector<Point> &startingData, const std::unordered_map<Point, Label> &pointToLabelMap, int k) {
    std::random_device randomDevice;
    std::mt19937 distribution(randomDevice());
    std::shuffle(startingData.begin(), startingData.end(), distribution);
    size_t partitionSize = startingData.size() / 10;

    long validationDataStartingIndex = 0;
    long validationDataEndingIndex = (long) partitionSize;

    int totalSuccesses = 0;
    int totalFails = 0;
    for (int i = 0; i < 9; i++) {
        int successes = 0;
        int fails = 0;
        std::vector<Point> trainData = std::vector<Point>(startingData.begin(),
                                                          startingData.begin() + validationDataStartingIndex);
        trainData.insert(trainData.end(), startingData.begin() + validationDataEndingIndex, startingData.end());
        std::vector<Point> validationData = std::vector<Point>(startingData.begin() + validationDataStartingIndex,
                                                               startingData.begin() + validationDataEndingIndex);
        validationDataStartingIndex = validationDataEndingIndex;
        validationDataEndingIndex += (long) partitionSize;

        KDTree tree(trainData);
        for (const auto &point: validationData) {
            const Label resultLabel = kNNClassify(pointToLabelMap, tree.kNearestNeighbours(point, k));
            if (resultLabel == pointToLabelMap.at(point)) {
                successes++;
            } else {
                // std::cout << "Point" << point << "was categorized as " << resultLabel << std::endl;
                fails++;
            }
        }

        totalSuccesses += successes;
        totalFails += fails;

        std::cout << "Attempt " << (i + 1) << ":  "
                  << ((double) successes / (double) (successes + fails)) * 100.0 << "% success, "
                  << successes << " : " << fails << std::endl;
    }
    int successes = 0;
    int fails = 0;
    std::vector<Point> trainData = std::vector<Point>(startingData.begin(),
                                                      startingData.begin() + validationDataStartingIndex);
    std::vector<Point> validationData = std::vector<Point>(startingData.begin() + validationDataStartingIndex,
                                                           startingData.end());

    KDTree tree(trainData);
    for (const auto &point: validationData) {
        const Label resultLabel = kNNClassify(pointToLabelMap, tree.kNearestNeighbours(point, k));
        if (resultLabel == pointToLabelMap.at(point)) {
            successes++;
        } else {
            // std::cout << "Point" << point << "was categorized as " << resultLabel << std::endl;
            fails++;
        }
    }

    totalSuccesses += successes;
    totalFails += fails;

    std::cout << "Attempt 10: " 
      << ((double) successes / (double) validationData.size()) * 100.0 << "% success, " 
      << successes << " : " << fails << std::endl;

    std::cout<< "Total: " << ((double) totalSuccesses / (double) (totalSuccesses + totalFails)) * 100.0 << "% success, " << totalSuccesses << " : " << totalFails << std::endl;
}

int main(int argc, char *argv[]) {

    std::vector<Point> points;
    std::unordered_map<Point, Label> pointToLabelMap;

    // std::cout << "Path:";
    // std::string pathToFile;
    // std::cin >> pathToFile;
    // std::cout << "k:";
    // int k;
    // std::cin >> k;

    // readCSV(points, pointToLabelMap, pathToFile);
    // crossValidation(points, pointToLabelMap, k);

    std::cout<< argv[0] << std::endl << argv[1] << std::endl << argv[2] << std::endl;

    readCSV(points, pointToLabelMap, argv[1]);
    crossValidation(points, pointToLabelMap, std::stoi(argv[2]));
    return 0;
}
