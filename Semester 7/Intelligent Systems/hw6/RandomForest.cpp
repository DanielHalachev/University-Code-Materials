
#include <random>
#include "RandomForest.h"

std::vector<Instance> RandomForest::getRandomSubset(const std::vector<Instance> &data, int subsetSize) {
    if (subsetSize > data.size()) {
        subsetSize = data.size();
    }
    if (subsetSize == data.size()) {
        return data;
    }
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    std::uniform_int_distribution<size_t> distribution(0, data.size() - 1);

    std::vector<Instance> subset;

    subset.reserve(subsetSize);
    std::unordered_set<size_t> selectedInstanceIndexes;

    while (subset.size() < subsetSize) {
        size_t instanceIndex = distribution(gen);
        if (selectedInstanceIndexes.find(instanceIndex) == selectedInstanceIndexes.end()) {
            subset.push_back(data[instanceIndex]);
            selectedInstanceIndexes.insert(instanceIndex);
        }
    }
    return subset;
}

std::unordered_set<size_t> RandomForest::getRandomFeatures(int totalFeatures, int limit) {
    if (limit > totalFeatures) {
        limit = totalFeatures;
    }

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

    std::uniform_int_distribution<size_t> distribution(0, totalFeatures - 1);

    std::unordered_set<size_t> selectedFeatures;

    if (limit == totalFeatures) {
        for (size_t i = 0; i < limit; i++) {
            selectedFeatures.insert(i);
        }
        return selectedFeatures;
    }

    while (selectedFeatures.size() < limit) {
        size_t featureIndex = distribution(gen);
        if (selectedFeatures.find(featureIndex) == selectedFeatures.end()) {
            selectedFeatures.insert(featureIndex);
        }
    }
    return selectedFeatures;
}

RandomForest::RandomForest(int numberOfTrees, int instancesPerTree, int numberOfFeatures,
                           const std::vector<Instance> &data) : numberOfTrees(numberOfTrees),
                                                                instancesPerTree(instancesPerTree),
                                                                numberOfFeatures(numberOfFeatures) {
    for (size_t i = 0; i < this->numberOfTrees; i++) {
        std::vector<Instance> subset = this->getRandomSubset(data, this->instancesPerTree);
        std::unordered_set<size_t> selectedFeatures = this->getRandomFeatures(data[0].featureVector.size(),
                                                                              this->numberOfFeatures);
        DecisionTree tree(subset, selectedFeatures);
        this->trees.push_back(tree);
    }
}

Label RandomForest::classify(const FeatureVector &query) {
    std::unordered_map<Label, int> predictions;
    int maxCount = -1;
    Label result;
    for (const auto &tree: this->trees) {
        Label prediction = tree.classify(query);
        predictions[prediction]++;
    }

    for (const auto &pair: predictions) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            result = pair.first;
        }
    }
    return result;
}


