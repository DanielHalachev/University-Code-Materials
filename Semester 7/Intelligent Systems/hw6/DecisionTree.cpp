

#include "DecisionTree.h"
#include <cmath>
#include <random>


DecisionTree::DecisionTree(const std::vector<Instance> &data) {
    std::unordered_set<size_t> attributeIndexes;
    for (size_t i = 0; i < data.begin()->featureVector.size(); i++) {
        attributeIndexes.insert(i);
    }
    this->root = this->buildTree(data, attributeIndexes);
}

DecisionTree::DecisionTree(const std::vector<Instance> &data, std::unordered_set<size_t> &attributeIndexes) {
    this->root = this->buildTree(data, attributeIndexes);
}

Label DecisionTree::classify(const FeatureVector &query) const {
    return this->classify(this->root, query);
}

double DecisionTree::entropy(const std::vector<Instance> &data) {
    size_t totalInstances = data.size();
    std::unordered_map<Label, int> labelCounts;
    for (const auto &instance: data) {
        labelCounts[instance.label]++;
    }

    double totalEntropy = 0;
    for (const auto &labelCountPair: labelCounts) {
        double probability = (double) labelCountPair.second / (double) totalInstances;
        totalEntropy -= probability * log2(probability);
    }
    return totalEntropy;
}

std::pair<size_t, double>
DecisionTree::bestAttribute(const std::vector<Instance> &data, const std::unordered_set<size_t> &attributeIndexes) {
    // Gain(Subset, Attribute) = entropy (Tree) - SUM(P(AttributeValue) * entropy(SubsetWithSameValueAttribute))
    // entropy(Tree) is constant here
    // the smaller is the sum, the better the information gain
    double minimumEntropy = INFINITY;
    size_t bestAttributeIndex = 0;
    for (auto attributeIndex: attributeIndexes) {
        std::unordered_set<Value> uniqueValues;
        for (auto instance: data) {
            uniqueValues.insert(instance.featureVector[attributeIndex]);
        }

        double totalEntropy = 0;
        for (const auto &value: uniqueValues) {
            std::vector<Instance> sameValueSubset;
            for (auto instance: data) {
                if (instance.featureVector[attributeIndex] == value) {
                    sameValueSubset.push_back(instance);
                }
            }
            double attributeValueProbability = (double) sameValueSubset.size() / (double) data.size();
            totalEntropy += attributeValueProbability * entropy(sameValueSubset);
        }

        if (totalEntropy < minimumEntropy) {
            minimumEntropy = totalEntropy;
            bestAttributeIndex = attributeIndex;
        }
    }
    return std::make_pair(bestAttributeIndex, minimumEntropy);
}

Label DecisionTree::classify(Node node, const FeatureVector &query) const {
    // no branches -> leaf
    if (node.branches.empty()) {
        return node.result;
    }

    const Value &attributeValue = query[node.attributeIndex];
    // no branch with the same value as supplied
    if (node.branches.find(attributeValue) == node.branches.end()) {
        std::unordered_map<Label, int> labelCounts;
        for(auto pair : node.branches){
            labelCounts[classify(node.branches[attributeValue], query)]++;
        }
        std::vector<int> counts;
        std::vector<Label> labels;
        counts.reserve(labelCounts.size());
        labels.reserve(labelCounts.size());
        for(auto pair : labelCounts){
            labels.push_back(pair.first);
            counts.push_back(pair.second);
        }
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::discrete_distribution<> distribution(counts.begin(), counts.end());
        return labels[distribution(gen)];
    }
    return this->classify(node.branches[attributeValue], query);
}

Node DecisionTree::buildTree(const std::vector<Instance> &data, std::unordered_set<size_t> &attributeIndexes) {

    Node node;
    Label label = data[0].label;
    bool allTheSame = true;
    for (auto &instance: data) {
        if (instance.label != label) {
            allTheSame = false;
            break;
        }
    }
    if (allTheSame) {
        node.result = label;
        return node;
    }

    if (attributeIndexes.empty()) {
        // majority label
        std::unordered_map<Label, int> labelCounts;
        for(auto instance : data){
            labelCounts[instance.label]++;
        }
        std::vector<int> counts;
        std::vector<Label> labels;
        counts.reserve(labelCounts.size());
        labels.reserve(labelCounts.size());
        for(auto pair : labelCounts){
            labels.push_back(pair.first);
            counts.push_back(pair.second);
        }
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::discrete_distribution<> distribution(counts.begin(), counts.end());
        node.result = labels[distribution(gen)];
        return node;
    }

    std::pair<size_t, double> bestAttribute = this->bestAttribute(data, attributeIndexes);
    node.attributeIndex = (long) bestAttribute.first;
    std::unordered_set<Value> uniqueValues;
    for (auto &instance: data) {
        uniqueValues.insert(instance.featureVector[bestAttribute.first]);
    }

    for (const auto &value: uniqueValues) {
        std::vector<Instance> subset;
        for (auto instance: data) {
            if (instance.featureVector[bestAttribute.first] == value) {
                subset.push_back(instance);
            }
        }
        if (subset.empty()) {
            node.branches[value] = {-1, {}, label};
        } else {
            attributeIndexes.erase(bestAttribute.first);
            node.branches[value] = buildTree(subset, attributeIndexes);
        }
    }

    return node;
}
