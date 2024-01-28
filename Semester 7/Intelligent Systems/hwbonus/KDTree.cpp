

#include <cmath>
#include <algorithm>
#include <queue>
#include "KDTree.h"

Point::Point(const std::vector<double> &coordinates) {
    this->coordinates = coordinates;
}

double Point::operator-(const Point &other) const {
    double distance = 0;
    for (int i = 0; i < this->coordinates.size(); i++) {
        distance += (this->coordinates[i] - other.coordinates[i]) * (this->coordinates[i] - other.coordinates[i]);
    }
    return sqrt(distance);
}

double Point::operator[](size_t index) const {
    return this->coordinates[index];
}

bool Point::operator==(const Point &other) const {
    return this->coordinates == other.coordinates;
}

bool Point::operator<(const Point &other) const {
    return this->coordinates < other.coordinates;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(";
    for (auto coordinate: point.coordinates) {
        os << coordinate << ",";
    }
    os << ")";
    return os;
}

KDNode::KDNode(const Point &point) {
    this->point = point;
    this->left = nullptr;
    this->right = nullptr;
}

KDNode *KDTree::buildTree(size_t left, size_t right, size_t index) {
    if (right <= left) {
        return nullptr;
    }
    size_t n = left + (right - left) / 2;
    auto comparator = [index](const KDNode &a, const KDNode &b) {
        return (a.point[index] < b.point[index]);
    };
    std::nth_element(nodes.begin() + left, nodes.begin() + n, nodes.begin() + right, comparator);
    index = (index + 1) % this->nodes[0].point.coordinates.size();
    this->nodes[n].left = buildTree(left, n, index);
    this->nodes[n].right = buildTree(n + 1, right, index);
    return &nodes[n];
}

void KDTree::kNearestNeighboursUtil(const Point &queryPoint, KDNode *current, size_t index, int k,
                                    std::vector<std::pair<double, Point>> &nearestNeighbours) {
    if (current == nullptr) {
        return;
    }

    bool leftFirst = queryPoint[index] < current->point[index];
    KDNode *first = leftFirst ? current->left : current->right;
    KDNode *second = leftFirst ? current->right : current->left;

    size_t newIndex = (index + 1) % this->nodes[0].point.coordinates.size();

    double currentNodeDistance = queryPoint - current->point;
    if (nearestNeighbours.size() < k) {
        nearestNeighbours.emplace_back(currentNodeDistance, current->point);
        std::sort(nearestNeighbours.begin(), nearestNeighbours.end(), std::less());
    } else {
        if (currentNodeDistance < queryPoint - nearestNeighbours.back().second) {
            nearestNeighbours.back().first = currentNodeDistance;
            nearestNeighbours.back().second = current->point;
            std::sort(nearestNeighbours.begin(), nearestNeighbours.end(), std::less());
        }
    }

    kNearestNeighboursUtil(queryPoint, first, newIndex, k, nearestNeighbours);
    if (std::abs(queryPoint[index] - current->point[index]) <= (current->point - nearestNeighbours.front().second)) {
        kNearestNeighboursUtil(queryPoint, second, newIndex, k, nearestNeighbours);
    }
}

KDTree::KDTree(const std::vector<Point> &points) : nodes(points.begin(), points.end()) {
    this->root = buildTree(0, points.size() - 1, 0);
}

std::vector<std::pair<double, Point>> KDTree::kNearestNeighbours(const Point &point, int k) {
    std::vector<std::pair<double, Point>> nearestNeighbours;   // ordered from closest to farthest are last
    kNearestNeighboursUtil(point, this->root, 0, k, nearestNeighbours);
    return nearestNeighbours;
}




