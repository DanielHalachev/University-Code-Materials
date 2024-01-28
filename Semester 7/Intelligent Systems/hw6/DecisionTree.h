

#ifndef IS_DECISIONTREE_H
#define IS_DECISIONTREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

typedef std::string Label;
typedef std::string Value;
typedef std::vector<Value> FeatureVector;

struct Instance {
    FeatureVector featureVector;
    Label label;
};

struct Node {
    long attributeIndex;
    std::unordered_map<Value, Node> branches;
    Label result;
};

class DecisionTree {
private:

    Node root;

    Node buildTree(const std::vector<Instance> &data, std::unordered_set<size_t> &attributeIndexes);

    static double entropy(const std::vector<Instance> &data);

    static std::pair<size_t, double>
    bestAttribute(const std::vector<Instance> &data, const std::unordered_set<size_t> &attributeIndexes);

    Label classify(Node node, const FeatureVector &query) const;


public:
    explicit DecisionTree(const std::vector<Instance> &data);

    Label classify(const FeatureVector &query) const;

    DecisionTree(const std::vector<Instance> &data, std::unordered_set<size_t> &attributeIndexes);
};


#endif //IS_DECISIONTREE_H
