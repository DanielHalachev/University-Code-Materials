

#ifndef IS_KDTREE_H
#define IS_KDTREE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

typedef std::string Label;

struct Point {
public:
    Point() = default;

    std::vector<double> coordinates;

    explicit Point(const std::vector<double> &coordinates);

    double operator-(const Point &other) const;

    double operator[](size_t index) const;

    bool operator==(const Point &other) const;

    bool operator<(const Point &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

struct PointComparator {
    Point point;

    explicit PointComparator(const Point &point) {
        this->point = point;
    }

    bool operator()(const Point &a, const Point &b) const {
        return a - point < b - point;
    }
};

namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point &point) const {
            size_t hashValue = 0;
            for (auto coordinate: point.coordinates) {
                hashValue ^= std::hash<double>{}(coordinate) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
            return hashValue;
        }
    };
}

class KDNode {
public:
    Point point;
    KDNode *left;
    KDNode *right;

    explicit KDNode(const Point &point);
};

class KDTree {
private:
    KDNode *root = nullptr;
    std::vector<KDNode> nodes;

    KDNode *buildTree(size_t left, size_t right, size_t index);

    void
    kNearestNeighboursUtil(const Point &queryPoint, KDNode *current, size_t index, int k,
                           std::vector<std::pair<double, Point>> &nearestNeighbours);

public:
    explicit KDTree(const std::vector<Point> &points);

    KDTree& operator=(const KDTree &other) = delete;

    KDTree(const KDTree &other) = delete;

    std::vector<std::pair<double, Point>> kNearestNeighbours(const Point &point, int k);
};

#endif //IS_KDTREE_H
