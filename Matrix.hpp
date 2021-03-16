#pragma once
#include <iostream>
#include <vector>
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
		Matrix transpose() const;
		Matrix inverse() const;
		void printMatrix() const; 
		const double operator()(const int, const int) const;
		double& operator()(const int, const int);
		friend Matrix operator-(const Matrix& rhs);
		friend double det(const Matrix& rhs);

};

class Eye : public Matrix{
	public:
		Eye(int size);
		~Eye();
		Eye inverse();
};