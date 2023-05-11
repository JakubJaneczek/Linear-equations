#pragma once
#include <iostream>
class Matrix{

public:
	double** data;
	int rows, cols;
	void init(double a1, double a2, double a3) {
		for (int i = 0; i < rows - 2; i++) {
			for (int j = 0; j < cols - 2; j++) {
				if (i == j) {
					data[i][j] = a1;
					data[i + 1][j] = data[i][j + 1] = a2;
					data[i + 2][j] = data[i][j + 2] = a3;
				}
			}
		}
		data[rows - 2][cols - 2] = data[rows - 1][cols - 1] = a1;
		data[rows - 1][cols - 2] = data[rows - 2][cols - 1] = a2;
	}

	int getRows() const {
		return rows;
	}

	int getCols() const {
		return cols;
	}

	double getValue(int row, int col) const {
		return data[row][col];
	}

	void setValue(int row, int col, double value) {
		data[row][col] = value;
	}

	Matrix() {};

	Matrix(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = 0.0;
			}
		}
	}

	Matrix(const Matrix& m) {
		this->rows = m.rows;
		this->cols = m.cols;
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}
	////////////////////////////////////////////////////////////
	/////////////////// Operators //////////////////////////////
	////////////////////////////////////////////////////////////

	static void Tril(const Matrix& m, int offset) {
		for (int i = 0; i < m.getCols(); i++) {
			for (int j = i + offset + 1; j < m.getCols(); j++) {
				m.data[i][j] = 0.0;
			}
		}
	}
	
	static void Triu(const Matrix& m, int offset) {
		for (int i = 0; i < m.getCols(); i++) {
			for (int j = 0; j < m.getCols(); j++) {
				if (i + offset > j)
					m.data[i][j] = 0.0;
			}
		}
	}

	Matrix& operator+=(const Matrix& m) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				data[i][j] += m.getValue(i, j);
			}
		}
		return *this;
	}

	Matrix& operator-=(const Matrix& m) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				data[i][j] -= m.getValue(i, j);
			}
		}
		return *this;
	}

	Matrix& operator*=(const Matrix& m) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				data[i][j] *= m.getValue(i, j);
			}
		}
		return *this;
	}
};

inline Matrix operator+(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp += m2);
}

inline Matrix operator-(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp -= m2);
}
inline Matrix operator*(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp *= m2);
}