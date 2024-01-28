#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include "NaiveBayesClassifier.h"


#define FEATURE_COUNT 16

inline void
readCSV(std::vector<std::pair<FeatureVector<char>, Label>> &featureVectorToLabelMap, const std::string &pathToFile) {
    std::vector<std::unordered_map<char, int>> counts(FEATURE_COUNT, std::unordered_map<char, int>{{'y', 0},
                                                                                                   {'n', 0}});
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::ifstream file(pathToFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            std::vector<std::string> segments;
            std::string token;
            std::istringstream iss(line);
            while (std::getline(iss, token, ',')) {
                segments.push_back(token);
            }

            std::vector<char> features(segments.size() - 1);
            for (int i = 1; i < segments.size(); i++) {
                features[i - 1] = (segments[i][0]);
                if (features[i - 1] != '?') {
                    counts[i - 1][features[i - 1]]++;
                }
            }
            FeatureVector<char> featureVector(features);
            featureVectorToLabelMap.emplace_back(featureVector, segments[0]);
        }
    }
    file.close();
    std::vector<double> probabilities(counts.size());
    for (size_t i = 0; i < counts.size(); i++) {
        probabilities[i] = (double) counts[i]['y'] / (double) (counts[i]['y'] + counts[i]['n']);
    }
    for (auto &&vectorLabelPair: featureVectorToLabelMap) {
        for (size_t i = 0; i < vectorLabelPair.first.coordinates.size(); i++) {
            if (vectorLabelPair.first.coordinates[i] == '?') {
                std::bernoulli_distribution distribution(probabilities[i]);
                if (distribution(gen)) {
                    vectorLabelPair.first.coordinates[i] = 'y';
                } else {
                    vectorLabelPair.first.coordinates[i] = 'n';
                }
            }
        }
    }
}

inline void
readCSV(std::vector<std::pair<FeatureVector<bool>, Label>> &featureVectorToLabelMap, const std::string &pathToFile) {
    std::vector<std::pair<FeatureVector<char>, Label>> map;
    readCSV(map, pathToFile);
    featureVectorToLabelMap.reserve(map.size());
    std::transform(
            map.begin(),
            map.end(),
            std::back_inserter(featureVectorToLabelMap),
            [](std::pair<FeatureVector<char>, Label> &pair) {
                std::vector<bool> newFeatures(pair.first.coordinates.size());
                std::transform(
                        pair.first.coordinates.begin(),
                        pair.first.coordinates.end(),
                        newFeatures.begin(),
                        [](char c) {
                            return (c == 'y');
                        });
                return std::make_pair(FeatureVector<bool>(newFeatures), pair.second);
            });
}

template<typename T>
inline void
crossValidation(std::vector<std::pair<FeatureVector<T>, Label>> &startingData) {
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
        std::vector<std::pair<FeatureVector<T>, Label>> trainData = std::vector<std::pair<FeatureVector<T>, Label>>(
                startingData.begin(),
                startingData.begin() + validationDataStartingIndex);
        trainData.insert(trainData.end(), startingData.begin() + validationDataEndingIndex, startingData.end());
        std::vector<std::pair<FeatureVector<T>, Label>> validationData = std::vector<std::pair<FeatureVector<T>, Label>>(
                startingData.begin() + validationDataStartingIndex,
                startingData.begin() + validationDataEndingIndex);
        validationDataStartingIndex = validationDataEndingIndex;
        validationDataEndingIndex += (long) partitionSize;

        NaiveBayesClassifier classifier(trainData);
        for (const auto &pair: validationData) {
            const Label resultLabel = classifier.classify(pair.first);
            if (resultLabel == pair.second) {
                successes++;
            } else {
                fails++;
            }
        }

        totalSuccesses += successes;
        totalFails += fails;

        std::cout << "Attempt " << (i + 1) << ": "
                  << ((double) successes / (double) (successes + fails)) * 100.0 << "% success, "
                  << successes << " : " << fails << std::endl;
    }
    int successes = 0;
    int fails = 0;
    std::vector<std::pair<FeatureVector<T>, Label>> trainData = std::vector<std::pair<FeatureVector<T>, Label>>(
            startingData.begin(),
            startingData.begin() + validationDataStartingIndex);
    trainData.insert(trainData.end(), startingData.begin() + validationDataEndingIndex, startingData.end());
    std::vector<std::pair<FeatureVector<T>, Label>> validationData = std::vector<std::pair<FeatureVector<T>, Label>>(
            startingData.begin() + validationDataStartingIndex,
            startingData.begin() + validationDataEndingIndex);
    NaiveBayesClassifier classifier(trainData);
    for (const auto &pair: validationData) {
        const Label resultLabel = classifier.classify(pair.first);
        if (resultLabel == pair.second) {
            successes++;
        } else {
            fails++;
        }
    }
    totalSuccesses += successes;
    totalFails += fails;

    std::cout << "Attempt 10: "
              << ((double) successes / (double) (successes + fails)) * 100.0 << "% success, "
              << successes << " : " << fails << std::endl;
    std::cout << "Total: "
              << ((double) totalSuccesses / (double) (totalSuccesses + totalFails)) * 100.0 << "% success, "
              << totalSuccesses << " : " << totalFails << std::endl;
}

int main(int argc, char *argv[]) {
    bool useBool = (argc > 2);
    if (useBool) {
        std::vector<std::pair<FeatureVector<bool>, Label>> featureVectorToLabelMap;
        readCSV(featureVectorToLabelMap, argv[1]);
        crossValidation(featureVectorToLabelMap);
    } else {
        std::vector<std::pair<FeatureVector<char>, Label>> featureVectorToLabelMap;
        readCSV(featureVectorToLabelMap, argv[1]);
        crossValidation(featureVectorToLabelMap);
    }

    return 0;
}
