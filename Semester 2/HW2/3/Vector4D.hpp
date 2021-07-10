#pragma once

// Add all other required methods and fields of the class.

#include <iostream>

#define SIZE 4

class Vector4D {

public:

    Vector4D(double, double, double, double);

    friend Vector4D operator+(const Vector4D &lhs, const Vector4D &rhs);

    friend Vector4D operator-(const Vector4D &lhs, const Vector4D &rhs);

    friend Vector4D operator*(const Vector4D &lhs, const Vector4D &rhs);

    friend Vector4D operator*(const Vector4D &lhs, const double &rhs);

    friend Vector4D operator/(const Vector4D &lhs, const Vector4D &rhs);

    friend Vector4D operator/(const Vector4D &lhs, const double &rhs);

    Vector4D &operator+=(const Vector4D &rhs);

    Vector4D &operator-=(const Vector4D &rhs);

    Vector4D &operator*=(const Vector4D &rhs);

    Vector4D &operator*=(const double &rhs);

    Vector4D &operator/=(const Vector4D &rhs);

    Vector4D &operator/=(const double &rhs);

    Vector4D operator-() const;

    bool operator==(const Vector4D &other) const;

    bool operator!=(const Vector4D &other) const;

    bool operator<(const Vector4D &other) const;

    bool operator>(const Vector4D &other) const;

    bool operator<=(const Vector4D &other) const;

    bool operator>=(const Vector4D &other) const;

    bool operator!() const;

    friend std::ostream &operator<<(std::ostream &out, const Vector4D &vector);

    double &operator[](const int &index);

    double operator[](const int &index) const;


private:
    double values[SIZE]{};
};
