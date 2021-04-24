#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class Matrix  
{
	protected:
		int Rows, Cols;
		std::vector <double> mat;
	public:
		~Matrix();
		Matrix(int row, int col, const std::vector <double>);
		Matrix(const Matrix& rhs);
		Matrix& operator=(const Matrix& rhs);
		Matrix operator+(const Matrix& rhs) const;
		Matrix operator-(const Matrix& rhs) const;
		Matrix operator*(const Matrix& rhs) const;
		Matrix operator*(const double& rhs) const;
		Matrix Hadamard(const Matrix& rhs) const;
		Matrix transpose() const;
		Matrix& reshape(int, int);
		Matrix inverse() const;
		Matrix submatrix(int, int) const;
		void printMatrix() const; 
		const double operator()(const int, const int) const;
		double& operator()(const int, const int);
		friend Matrix operator-(const Matrix& rhs);
		friend double det(const Matrix& rhs);
		friend Matrix adj(const Matrix& rhs);
		friend Matrix solve(const Matrix& A, const Matrix& b);
};

class Eye : public Matrix{
	public:
		Eye(int size);
		~Eye();
		Eye inverse();
};