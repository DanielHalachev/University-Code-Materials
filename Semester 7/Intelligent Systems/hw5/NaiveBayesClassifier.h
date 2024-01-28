//
// Created by daniel on 29.11.23.
//

#ifndef IS_NAIVEBAYESCLASSIFIER_H
#define IS_NAIVEBAYESCLASSIFIER_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
#include "FeatureVector.h"


template<class T>
class NaiveBayesClassifier {
private:
    std::unordered_map<Label, int> labelCounts;
    std::unordered_map<Label, std::unordered_map<size_t, std::unordered_map<T, int>>> attributeValueCounts;
    size_t instanceCount = 0;
public:
    explicit NaiveBayesClassifier(const std::vector<std::pair<FeatureVector<T>, Label>> &data);

    Label classify(const FeatureVector<T> &query) const;
};


template<typename T>
NaiveBayesClassifier<T>::NaiveBayesClassifier(const std::vector<std::pair<FeatureVector<T>, Label>> &data) {
    instanceCount = data.size();
    for (auto &vectorLabelPair: data) {
        FeatureVector vector = vectorLabelPair.first;
        Label label = vectorLabelPair.second;
        // update label map
        if (this->labelCounts.find(label) == this->labelCounts.end()) {
            this->labelCounts[label] = 0;
        }
        this->labelCounts[label]++;
        // update features map
        if (this->attributeValueCounts.find(label) == this->attributeValueCounts.end()) {
            this->attributeValueCounts[label] = std::unordered_map<size_t, std::unordered_map<T, int>>();
        }
        for (size_t attribute = 0; attribute < vector.coordinates.size(); attribute++) {
            if (this->attributeValueCounts[label].find(attribute) == this->attributeValueCounts[label].end()) {
                this->attributeValueCounts[label][attribute] = std::unordered_map<T, int>();
            }
            if (this->attributeValueCounts[label][attribute].find(vector[attribute]) ==
                this->attributeValueCounts[label][attribute].end()) {
                this->attributeValueCounts[label][attribute][vector[attribute]] = 0;
            }
            this->attributeValueCounts[label][attribute][vector[attribute]]++;
        }
    }
}

template<typename T>
Label NaiveBayesClassifier<T>::classify(const FeatureVector<T> &query) const {
    std::map<double, Label> probabilities;
    for (const auto &labelCountPair: this->labelCounts) {
        Label label = labelCountPair.first;
        double probability = std::log((double) labelCountPair.second / (double) this->instanceCount);
        for (size_t feature = 0; feature < query.coordinates.size(); feature++) {
            int totalAttributeValues = 0; // all the values (true and false) of this feature for the given class
            for (auto &attributeValueCountPair: this->attributeValueCounts.at(label).at(feature)) {
                totalAttributeValues += attributeValueCountPair.second;
            }
            // the number of other occurences of the same value
            int sameValueAttributeCount = 0;
            if (this->attributeValueCounts.at(label).at(feature).find(query[feature]) !=
                this->attributeValueCounts.at(label).at(feature).end()) {
                sameValueAttributeCount = this->attributeValueCounts.at(label).at(feature).at(query[feature]);
            }
            int alpha = 1;
            probability += std::log(
                    (double) (sameValueAttributeCount + alpha) / (double) (this->labelCounts.at(label) + alpha * 2));
//            probability +=std::log((double)(sameValueAttributeCount)/(double)(totalAttributeValues));

        }
        probabilities[probability] = label;
    }
    return (probabilities.end().operator--())->second;
}

#endif //IS_NAIVEBAYESCLASSIFIER_H
