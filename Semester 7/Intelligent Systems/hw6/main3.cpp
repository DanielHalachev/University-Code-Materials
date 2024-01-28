#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include <map>
#include "DecisionTree.h"
#include "RandomForest.h"


inline void readCSV(std::vector<Instance> &data, const std::string &pathToFile) {
    std::ifstream file(pathToFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            bool hasEmptyValues = false;
            if (line.empty()) {
                continue;
            }
            std::vector<std::string> segments;
            std::string token;
            std::istringstream iss(line);
            while (std::getline(iss, token, ',')) {
                if (token == "?") {
                    hasEmptyValues = true;
                    break;
                }
                segments.push_back(token);
            }
            if (hasEmptyValues) {
                continue;
            }
            segments.resize(segments.size() - 1);
            data.push_back({segments, token});
        }
    }
    file.close();
}


inline double
crossValidation(std::vector<Instance> &startingData, int numberOfTrees, int instancesPerTree, int numberOfFeatures) {
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
        std::vector<Instance> trainData = std::vector<Instance>(startingData.begin(),
                                                                startingData.begin() + validationDataStartingIndex);
        trainData.insert(trainData.end(), startingData.begin() + validationDataEndingIndex, startingData.end());
        std::vector<Instance> validationData = std::vector<Instance>(startingData.begin() + validationDataStartingIndex,
                                                                     startingData.begin() + validationDataEndingIndex);
        validationDataStartingIndex = validationDataEndingIndex;
        validationDataEndingIndex += (long) partitionSize;

        RandomForest forest(numberOfTrees, instancesPerTree, numberOfFeatures, trainData);
        for (const auto &instance: validationData) {
            const Label resultLabel = forest.classify(instance.featureVector);
            if (resultLabel == instance.label) {
                successes++;
            } else {
                fails++;
            }
        }

        totalSuccesses += successes;
        totalFails += fails;
    }
    int successes = 0;
    int fails = 0;
    std::vector<Instance> trainData = std::vector<Instance>(startingData.begin(),
                                                            startingData.begin() + validationDataStartingIndex);
    trainData.insert(trainData.end(), startingData.begin() + validationDataEndingIndex, startingData.end());
    std::vector<Instance> validationData = std::vector<Instance>(startingData.begin() + validationDataStartingIndex,
                                                                 startingData.begin() + validationDataEndingIndex);
    DecisionTree decisionTree(trainData);
    for (
        const auto &instance
            : validationData) {
        const Label resultLabel = decisionTree.classify(instance.featureVector);
        if (resultLabel == instance.label) {
            successes++;
        } else {
            fails++;
        }
    }
    totalSuccesses += successes;
    totalFails += fails;

    return ((double) totalSuccesses / (double) (totalSuccesses + totalFails)) * 100.0;
}

int main(int argc, char *argv[]) {
    std::vector<Instance> data;
    readCSV(data, argv[1]);
    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    outputFile << "Trees;InstancesPerTree;Features;MAX;AVG" << std::endl;

    std::map<std::tuple<int, int, int>, std::tuple<double, double>> results;
    for (int numberOfTrees = 1; numberOfTrees <= 9; numberOfTrees++) {
        for (int instancesPerTree = 5; instancesPerTree < 390; instancesPerTree += 5) {
            for (int numberOfFeatures = 2; numberOfFeatures <= 9; numberOfFeatures++) {
                std::vector<double> temp(3);
                for (int i = 0; i < 3; i++) {
                    temp[i] = crossValidation(data, numberOfTrees, instancesPerTree, numberOfFeatures);
                }
                std::pair<std::tuple<int, int, int>, std::tuple<double, double>> pair = { {numberOfTrees, instancesPerTree, numberOfFeatures}, {
                        *std::max_element(
                                temp.begin(),
                                temp.end()
                        ),
                        ((double) (std::accumulate(temp.begin(), temp.end(), 0)) / temp.size())
                }};
//                results.insert(pair);
                const auto& indices = pair.first;
                const auto& values = pair.second;

                std::cout << std::get<0>(indices) << "       | ";
                std::cout << std::get<1>(indices) << "       | ";
                std::cout << std::get<2>(indices) << "       | ";
                std::cout << std::get<0>(values)  << "       | ";
                std::cout << std::get<1>(values) << std::endl;

                outputFile << std::get<0>(indices) << ";";
                outputFile << std::get<1>(indices) << ";";
                outputFile << std::get<2>(indices) << ";";
                outputFile << std::get<0>(values) << ";";
                outputFile << std::get<1>(values) << std::endl;
            }
        }
    }

    return 0;
}
