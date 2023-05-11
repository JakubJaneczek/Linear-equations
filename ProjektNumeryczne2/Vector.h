#pragma once
#include "Matrix.h"
class Vector {

public:

    int size;
    double* data;
    Vector(int size = 0) {
        this->size = size;
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }

    Vector(const Vector& other) {
        size = other.size;
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    void init(double val)
    {
        for (int i = 0; i < size; i++) {
            data[i] = val;
        }
    }

    void init(double val, double (*func)(double))
    {
        for (int i = 0; i < size; i++) {
            data[i] = func(i * val);
        }
    }
    static double norm(Vector m) {
        double val = 0.0;
        for (int i = 0; i < m.getSize(); i++) {
            val += pow(m.getValue(i), 2);
        }
        return sqrt(val);
    }

    virtual ~Vector() {
        delete[] data;
    }

    int getSize() const {
        return size;
    }

    double getValue(int index) const {
        return data[index];
    }

    void setValue(int index, double value) {
        data[index] = value;
    }

    ////////////////////////////////////////////////////////////
    /////////////////// Operators //////////////////////////////
    ////////////////////////////////////////////////////////////

    double dot(const Vector& other) {
        double sum = 0.0;
        for (int i = 0; i < getSize(); i++) {
            sum += data[i] * other.data[i];
        }
        return sum;
    }

    Matrix& outer(const Vector& other) {
        Matrix* temp = new Matrix(getSize(), other.getSize());
        for (int i = 0; i < temp->getRows(); i++) {
            for (int j = 0; j < temp->getCols(); j++) {
                temp->data[i][j] = data[i] * other.data[j];
            }
        }
        return *temp;
    }

    Vector& operator *=(const Matrix& m) {
        Vector temp(getSize());
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; ++j) {   
                temp.data[i] += this->data[j] * m.data[i][j];
            }
        }
        return (*this = temp);
    }

    Vector& operator-=(const Vector& v) {
        for (int i = 0; i < size; i++) {
            
            data[i] -= v.data[i];  
        }
        return *this;
    }

    Vector& operator=(const Vector& v) {
        if (this == &v)
        {
            return *this;
        }
        this->~Vector();
        this->size = v.getSize();
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = v.data[i];
        } 
        return *this;
    }


};

inline Vector operator-(const Vector& v1, const Vector& v2)
{
    Vector temp(v1);
    return (temp -= v2);
}
 Vector operator*(const Vector& v, const Matrix& m)
{
    Vector temp(v);
    return (temp *= m);
}

inline Vector operator*(const Matrix& m, const Vector& v)
{
    Vector temp(v);
    return (temp *= m);
}
class VerticalVector : public Vector {
public:
    VerticalVector(int size = 0) : Vector(size) {}
};

class HorizontalVector : public Vector {
public:
    HorizontalVector(int size = 0) : Vector(size) {}
};