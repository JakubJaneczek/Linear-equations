#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <iostream>
#include <chrono>
#include <fstream>
#define f 1
#define a1A 11.0
#define a1C 3.0
#define a2 -1.0
#define a3 -1.0
#define e 1e-9

class Equation {
private:
	Matrix A;
	Vector b;
	Vector x;
	int N;

public:

	Equation(int n) : A(n, n), x(n), b(n) {
		N = n;
	}

	double JacobiMethod() {
		auto start_time = std::chrono::high_resolution_clock::now();
		std::ofstream jacobi_iterations("jacobi_iterations.txt", std::ios_base::app);
		std::ofstream jacobi_residuum("jacobi_residuum.txt", std::ios_base::app);
		std::ofstream jacobi_times("jacobi_times.txt", std::ios_base::app);
		Vector xtemp(x);
		for (int t = 1; ; t++) {
			for (int i = 0; i < N; i++) {
				double val = b.data[i];
				for (int k = 0; k < N; k++) {
					if (k != i)
						val -= A.data[i][k] * x.data[k];
				}
				val /= A.data[i][i];
				xtemp.data[i] = val;
			}
			x = xtemp;
			jacobi_iterations << t << "\n";
			jacobi_residuum << Vector::norm(A * x - b) << "\n";
			if (Vector::norm(A * x - b) <= e)
			{
				auto end_time = std::chrono::high_resolution_clock::now();
				auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
				jacobi_times << elapsed_time.count() << "\n \n";
				jacobi_residuum << "\n";
				jacobi_iterations << "\n";
				jacobi_times.close();
				jacobi_residuum.close();
				jacobi_iterations.close();
				return t;			
			}
		}
	}

	double GaussSeidelMethod() {
		auto start_time = std::chrono::high_resolution_clock::now();
		std::ofstream gauss_iterations("gauss_iterations.txt", std::ios_base::app);
		std::ofstream gauss_residuum("gauss_residuum.txt", std::ios_base::app);
		std::ofstream gauss_times("gauss_times.txt", std::ios_base::app);
		for (int t = 1; ; t++) {
			for (int i = 0; i < N; i++) {
				double val = b.getValue(i);
				for (int k = 0; k < N; k++) {
					if (k != i)
						val -= A.getValue(i, k) * x.getValue(k);
				}
				val /= A.getValue(i, i);
				x.setValue(i, val);
			}

			gauss_iterations << t << "\n";
			gauss_residuum << Vector::norm(A * x - b) << "\n";
			if (Vector::norm(A * x - b) <= e)
			{
				auto end_time = std::chrono::high_resolution_clock::now();
				auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
				gauss_times << elapsed_time.count() << "\n \n";
				gauss_residuum << "\n";
				gauss_iterations << "\n";
				gauss_times.close();
				gauss_residuum.close();
				gauss_iterations.close();
				return t;
			}
		}
	}

	double LUMethod() {
		auto start_time = std::chrono::high_resolution_clock::now();
		std::ofstream LU_iterations("LU_iterations.txt", std::ios_base::app);
		std::ofstream LU_residuum("LU_residuum.txt", std::ios_base::app);
		std::ofstream LU_times("LU_times.txt", std::ios_base::app);
		Matrix L(N,N);
		Matrix U(N,N);

		for (int i = 0; i < N; i++)
			L.setValue(i, i, 1.0);

		for (int j = 0; j < N; j++) {
			for (int i = 0; i <= j; i++) {
				U.setValue(i,j, (U.getValue(i,j)+A.getValue(i,j)));
				for (int k = 0; k <= i - 1; k++)
					U.setValue(i, j, (U.getValue(i, j) - L.getValue(i, k) * U.getValue(k, j)));
			}

			for (int i = j + 1; i < N; i++) {
				for (int k = 0; k <= j - 1; k++)
					L.setValue(i, j, (L.getValue(i, j) - L.getValue(i, k) * U.getValue(k, j)));

				L.setValue(i, j, (L.getValue(i, j) + A.getValue(i, j)));
				L.setValue(i, j, (L.getValue(i, j) / U.getValue(j, j)));
			}
		}
		Vector y(N);
		for (int i = 0; i < N; i++) {
			double val = b.getValue(i);
			for (int j = 0; j < i; j++) {
				if (j != i) val -= L.getValue(i,j) * y.getValue(j);
			}

			y.setValue(i, val / L.getValue(i, i));
		}

		for (int i = N - 1; i >= 0; i--) {
			double val = y.getValue(i);
			for (int j = i; j < N; j++) {
				
				if (j != i) val -= U.getValue(i, j) * x.getValue(j);
			}
			x.setValue(i, val / U.getValue(i, i));
		}
		LU_residuum << Vector::norm(A * x - b) << "\n";

		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		LU_times << elapsed_time.count() << "\n \n";
		LU_residuum << "\n";
		LU_iterations << "\n";
		LU_times.close();
		LU_residuum.close();
		LU_iterations.close();
		return Vector::norm(A * x - b);
	}
	void Print()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				std::cout << A.getValue(i, j) << " ";
			}
			std::cout << "\n";
		}
		for (int i = 0; i < b.getSize(); i++)
		{
			std::cout << b.data[i] << " ";
		}
		std::cout << "\n";
	}
	void initA() {
		x.init(1.0);
		b.init(f, std::sin);
		A.init(a1A, a2, a3);
	}

	void initC() {
		A.init(a1C, a2, a3);
		x.init(1.0);
		b.init(f, std::sin);
	}
};