#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include "DecisionTree.h"


inline void readCSV(std::vector<Instance> &data, const std::string &pathToFile) {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
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


inline void crossValidation(std::vector<Instance> &startingData) {
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

        DecisionTree decisionTree(trainData);
        for (const auto &instance: validationData) {
            const Label resultLabel = decisionTree.classify(instance.featureVector);
            if (resultLabel == instance.label) {
                successes++;
            } else {
                fails++;
            }
        }

        totalSuccesses += successes;
        totalFails += fails;

        std::cout << "Attempt " << (i + 1) << ": "
                  << ((double) successes / (double) (successes + fails)) * 100.0 << "% success, "
                  << successes << " : " << fails <<
                  std::endl;
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

    std::cout << "Attempt 10: "
              << ((double) successes / (double) (successes + fails)) * 100.0 << "% success, "
              << successes << " : " << fails <<
              std::endl;
    std::cout << "Total: "
              << ((double) totalSuccesses / (double) (totalSuccesses + totalFails)) * 100.0 << "% success, "
              << totalSuccesses << " : " << totalFails <<
              std::endl;
}

int main(int argc, char *argv[]) {
    std::vector<Instance> data;
    readCSV(data, argv[1]);
    crossValidation(data);
    return 0;
}
