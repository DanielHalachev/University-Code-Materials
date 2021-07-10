//
// Created by User on 13.6.2021 г..
//

#ifndef EXERCISES_MATRIX_HPP
#define EXERCISES_MATRIX_HPP

#include <stdexcept>
#include <iostream>

template<class T>
class Matrix;

template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix);

template<class T>
class Matrix {
public:
    Matrix(const unsigned int &n = 2, const unsigned int &m = 2, const T &defaultValue = T());

    Matrix(const Matrix &other);

    Matrix &operator=(const Matrix &other);

    ~Matrix();

    void setAt(const unsigned int &x, const unsigned int &y, const T &element);

    T getAt(const unsigned int &x, const unsigned int &y) const;

    Matrix transpose() const;

    friend std::ostream &operator
    <<<>(
    std::ostream &out,
    const Matrix<T> &matrix
    );

private:
    unsigned int n;
    unsigned int m;
    T **array;
};

template<class T>
Matrix<T>::Matrix(const unsigned int &n, const unsigned int &m, const T &defaultValue)
        :n(n), m(m) {
    this->array = new T *[n];
    for (int i = 0; i < n; i++) {
        this->array[i] = new T[m];
        for (int j = 0; j < m; j++) {
            this->array[i][j] = defaultValue;
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix &other) {
    this->n = other.n;
    this->m = other.m;
    this->array = new T *[n];
    for (int i = 0; i < n; i++) {
        this->array[i] = new T[m];
        for (int j = 0; j < m; j++) {
            this->array[i][j] = other.array[i][j];
        }
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
    if (this != &other) {
        this->n = other.n;
        this->m = other.m;
        for (int i = 0; i < n; i++) {
            delete[] this->array[i];
        }
        this->array = new T *[n];
        for (int i = 0; i < n; i++) {
            this->array[i] = new T[m];
            for (int j = 0; j < m; j++) {
                this->array[i][j] = other.array[i][j];
            }
        }
    }
    return *this;
}

template<class T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[] this->array[i];
    }
    delete[] this->array;
}

template<class T>
void Matrix<T>::setAt(const unsigned int &x, const unsigned int &y, const T &element) {
    if (x > this->n || y > this->m) {
        return;
    }
    this->array[x - 1][y - 1] = element;
}

template<class T>
T Matrix<T>::getAt(const unsigned int &x, const unsigned int &y) const {
    if (x > this->n || y > this->m) {
        throw std::out_of_range("Invalid index");
    }
    return this->array[x - 1][y - 1];
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> newMatrix;
    for (int i = 0; i < newMatrix.n; i++) {
        delete[] newMatrix.array[i];
    }
    for (int i = 0; i < m; i++) {
        newMatrix.array[i] = new T[n];
        for (int j = 0; j < n; j++) {
            newMatrix.array[i][j] = this->array[j][i];
        }
    }
    return newMatrix;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++) {
            out << matrix.array[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}


#endif //EXERCISES_MATRIX_HPP
