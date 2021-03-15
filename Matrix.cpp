#include "Matrix.hpp"  
		
Matrix::Matrix(int row = 0, int col = 0, const std::vector <double> vec = {}): Rows(row), Cols(col)
{
    if ((Rows * Cols) != vec.size()) {
        std::cerr << "Dimension error!\n";
        std::cerr << "Expected size " << mat.size() << " but got " << vec.size() << std::endl;
        exit(EXIT_FAILURE);
    }
    mat = vec;
}

Matrix::Matrix(const Matrix& rhs): Rows(rhs.Rows), Cols(rhs.Cols)
{
    mat = rhs.mat;
}

Matrix::~Matrix() {}

Matrix& Matrix::operator=(const Matrix& rhs){
    if(mat.size() != rhs.mat.size()){
        Rows = rhs.Rows; Cols = rhs.Cols;
        mat.resize(Rows * Cols);
    }
    mat = rhs.mat;
    return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const{
    if (mat.size() != rhs.mat.size()){
        std::cerr << "CANNOT ADD MATRICES OF DIFFERENT SIZE!\n";
        exit(EXIT_FAILURE);
    }
    
    Matrix sol(Rows, Cols, std::vector<double>(Rows * Cols));
    for ( int j = 0; j < Cols; j++ ) {
        for ( int i = 0; i < Rows; i++ ) {
            sol.mat[i + j * Rows] = mat[i + j * Rows] + rhs.mat[i + j * Rows];
        }
    }
    return sol;
}

Matrix Matrix::operator-(const Matrix& rhs) const{
    return *this + (-rhs);
}

Matrix Matrix::operator*(const Matrix& rhs) const{
    if (Cols != rhs.Rows){
        std::cerr << "Dimension Error!\n";
        exit (EXIT_FAILURE);
    }
    Matrix sol(Rows, rhs.Cols, std::vector <double> (Rows * rhs.Cols));
    int size = Rows * rhs.Cols;
    double sum;
    for (int j = 0; j < Cols; j++){

    }
    for (int k = 0; k < size; k++){
        sum = 0;
        for (int j = 0; j < Cols; j ++){
            for (int i = 0; i < Rows; i++){
                sum += mat [i + j * Rows] * rhs.mat [i + j * Rows];
            }
        }
        sol.mat[k] = sum;
    }
    return sol;
}

Matrix Matrix::operator*(const double& rhs) const {
    Matrix sol(Rows, Cols, std::vector <double>(Rows * Cols));
    for ( int j = 0; j < Cols; j++ )
    {
        for ( int i = 0; i < Rows; i++ )
        {
            sol.mat [i + j * Rows] = mat [i + j * Rows]*rhs;
        }
    }
    return sol;
}

Matrix Matrix::transpose() const {
    std::vector <double> new_mat(Rows * Cols);
    for (int j = 0; j < Rows; j++){
        for (int i = 0; i < Cols; i++){
            new_mat[j + i * Rows] = mat[i + j * Cols];
        }
    }
    return Matrix(Cols, Rows, new_mat);
}

void Matrix::printMatrix() const {
    for (int j = 0; j < Rows; j++){
        for (int i = 0; i < Cols; i++){
            std::cout << mat[i + j * Cols] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

const double Matrix::operator()(const int i, const int j) const {
    return mat[i + j * Cols];
}

double& Matrix::operator()(const int i, const int j){
    return mat[i + j * Cols];
}

Matrix operator-(const Matrix& rhs){
    std::vector<double> new_mat(rhs.Rows * rhs.Cols);
    for (int i = 0; i < rhs.mat.size(); i++){
        new_mat[i] = -rhs.mat[i];
    }
    return Matrix(rhs.Rows, rhs.Cols, new_mat);
}

double det(const Matrix& rhs){
    if (rhs.Rows != rhs.Cols){
        std::cerr << "Can't calculate Determinant of non-square matrix\n";
        exit(EXIT_FAILURE);
    }
}
