//
// Created by daniel on 08.12.23.
//

#ifndef IS_RANDOMFOREST_H
#define IS_RANDOMFOREST_H


#include "DecisionTree.h"

class RandomForest {
private:
    std::vector<DecisionTree> trees;
    int numberOfTrees;
    int instancesPerTree;
    int numberOfFeatures;

    static std::vector<Instance> getRandomSubset(const std::vector<Instance> &data, int subsetSize);

    static std::unordered_set<size_t> getRandomFeatures(int totalFeatures, int limit);

public:
    RandomForest(int numberOfTrees, int instancesPerTree, int numberOfFeatures, const std::vector<Instance> &data);

    Label classify(const FeatureVector &query);

};


#endif //IS_RANDOMFOREST_H
