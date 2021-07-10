//
// Created by User on 14.4.2021 г..
//

#include "Vector4D.hpp"

Vector4D::Vector4D(double a, double b, double c, double d) {
    this->values[0] = a;
    this->values[1] = b;
    this->values[2] = c;
    this->values[3] = d;
}

Vector4D operator+(const Vector4D &lhs, const Vector4D &rhs) {
    return Vector4D(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]);
}

Vector4D operator-(const Vector4D &lhs, const Vector4D &rhs) {
    return Vector4D(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]);
}


Vector4D operator*(const Vector4D &lhs, const Vector4D &rhs) {
    return Vector4D(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
}

Vector4D operator*(const Vector4D &lhs, const double &rhs) {
    return Vector4D(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs);
}


Vector4D operator/(const Vector4D &lhs, const Vector4D &rhs) {
    if (rhs[0] == 0 && rhs[1] == 0 && rhs[2] == 0 && rhs[3] == 0) {
        return lhs;
    }
    return Vector4D(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]);
}

Vector4D operator/(const Vector4D &lhs, const double &rhs) {
    if (rhs == 0) {
        return lhs;
    }
    return Vector4D(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs);
}

bool Vector4D::operator==(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] != other.values[i]) {
            return false;
        }
    }
    return true;
}

bool Vector4D::operator!=(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] != other.values[i]) {
            return true;
        }
    }
    return false;
}

Vector4D &Vector4D::operator+=(const Vector4D &rhs) {
    this->values[0] += rhs.values[0];
    this->values[1] += rhs.values[1];
    this->values[2] += rhs.values[2];
    this->values[3] += rhs.values[3];
    return *this;
}

Vector4D &Vector4D::operator-=(const Vector4D &rhs) {
    this->values[0] -= rhs.values[0];
    this->values[1] -= rhs.values[1];
    this->values[2] -= rhs.values[2];
    this->values[3] -= rhs.values[3];
    return *this;
}

Vector4D &Vector4D::operator*=(const Vector4D &rhs) {
    this->values[0] *= rhs.values[0];
    this->values[1] *= rhs.values[1];
    this->values[2] *= rhs.values[2];
    this->values[3] *= rhs.values[3];
    return *this;
}

Vector4D &Vector4D::operator*=(const double &rhs) {
    this->values[0] *= rhs;
    this->values[1] *= rhs;
    this->values[2] *= rhs;
    this->values[3] *= rhs;
    return *this;
}

Vector4D &Vector4D::operator/=(const Vector4D &rhs) {
    if (rhs[0] == 0 && rhs[1] == 0 && rhs[2] == 0 && rhs[3] == 0) {
        return *this;
    }
    this->values[0] /= rhs.values[0];
    this->values[1] /= rhs.values[1];
    this->values[2] /= rhs.values[2];
    this->values[3] /= rhs.values[3];
    return *this;
}

Vector4D &Vector4D::operator/=(const double &rhs) {
    if (rhs == 0) {
        return *this;
    }
    this->values[0] /= rhs;
    this->values[1] /= rhs;
    this->values[2] /= rhs;
    this->values[3] /= rhs;
    return *this;
}

Vector4D Vector4D::operator-() const {
    return Vector4D(-this->values[0], -this->values[1], -this->values[2], -this->values[3]);
}

bool Vector4D::operator<(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] < other[i]) {
            return true;
        }
    }
    return false;
}

bool Vector4D::operator>(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] > other[i]) {
            return true;
        }
    }
    return false;
}

bool Vector4D::operator<=(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] > other[i]) {
            return false;
        }
    }
    return true;
}

bool Vector4D::operator>=(const Vector4D &other) const {
    for (int i = 0; i < SIZE; i++) {
        if (this->values[i] < other[i]) {
            return false;
        }
    }
    return true;
}

bool Vector4D::operator!() const {
    return (this->values[0] == 0 && this->values[1] == 0 && this->values[2] == 0 && this->values[3] == 0);
}

std::ostream &operator<<(std::ostream &out, const Vector4D &vector) {
    out << "(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ", " << vector[3] << ")";
    return out;
}

double &Vector4D::operator[](const int &index) {
    if (index < 0 || index > SIZE - 1) {
        return this->values[0];
    }
    return this->values[index];
}

double Vector4D::operator[](const int &index) const {
    if (index < 0 || index > SIZE - 1) {
        return this->values[0];
    }
    return this->values[index];
}
