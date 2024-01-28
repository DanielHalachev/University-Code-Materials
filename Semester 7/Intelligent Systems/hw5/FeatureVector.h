
#ifndef IS_FEATUREVECTOR_H
#define IS_FEATUREVECTOR_H

#include <vector>
#include <string>
#include <iostream>

typedef std::string Label;


template<typename T>
class FeatureVector {
public:
    FeatureVector() = default;

    std::vector<T> coordinates;

    explicit FeatureVector(const std::vector<T> &coordinates);

    T operator[](size_t index) const;

    bool operator==(const FeatureVector<T> &other) const;

    bool operator<(const FeatureVector<T> &other) const;

    friend std::ostream &operator<<(std::ostream &os, const FeatureVector<T> &point);
};

namespace std {
    template<class T>
    struct hash<FeatureVector<T>> {
        size_t operator()(const FeatureVector<T> &vector) const {
            size_t hashValue = 0;
            for (auto coordinate: vector.coordinates) {
                hashValue ^= std::hash<T>{}(coordinate) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
            return hashValue;
        }
    };
}

template<typename T>
FeatureVector<T>::FeatureVector(const std::vector<T> &coordinates) {
    this->coordinates = coordinates;
}

template<typename T>
T FeatureVector<T>::operator[](size_t index) const {
    return this->coordinates[index];
}

template<typename T>
bool FeatureVector<T>::operator==(const FeatureVector<T> &other) const {
    return this->coordinates == other.coordinates;
}

template<typename T>
bool FeatureVector<T>::operator<(const FeatureVector<T> &other) const {
    return this->coordinates < other.coordinates;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const FeatureVector<T> &point) {
    os << "(";
    for (auto coordinate: point.coordinates) {
        os << coordinate << ", ";
    }
    os << ")";
    return os;
}


#endif //IS_FEATUREVECTOR_H
