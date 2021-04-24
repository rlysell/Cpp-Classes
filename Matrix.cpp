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
    for ( int j = 0; j < Rows; j++ ) {
        for ( int i = 0; i < Cols; i++ ) {
            sol.mat[i + j * Cols] = mat[i + j * Cols] + rhs.mat[i + j * Cols];
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
    for (int j = 0; j < Rows; j ++){
        for (int k = 0; k < rhs.Cols; k++){
            sum = 0;
            for ( int i = 0; i < Cols; i++ ){
                sum += mat [i + j * Cols] * rhs.mat [k + i * rhs.Cols];
            }
            sol.mat [k + j * rhs.Cols] = sum;
        }
       
    }
   
    return sol;
}

Matrix Matrix::Hadamard(const Matrix& rhs) const{
    if (mat.size() != rhs.mat.size()) {
        std::cerr << "DIMENSION ERROR\n";
        exit (EXIT_FAILURE);
    }
    std::vector <double> new_mat = std::vector <double>(mat.size());
    for (int i = 0; i < mat.size(); i++){
        new_mat[i] = mat[i] * rhs.mat[i];
    }
    return Matrix(Rows, Cols, new_mat);
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

Matrix& Matrix::reshape(int new_Rows, int new_Cols){
    if (!(new_Rows * new_Cols == Rows*Cols)){
        std::cerr << "Dimension erroe!\n";
        exit(EXIT_FAILURE);
    }
    Rows = new_Rows; Cols = new_Cols;
    return *this;
}

Matrix Matrix::inverse() const{
    if(!(Rows == Cols)){
        std::cerr << "Dimensin error\n";
        exit(EXIT_FAILURE);
    }
    return adj(*this) * (1.0 / det(*this));
}

Matrix Matrix::submatrix(int row, int col) const {
    std::vector <double> new_mat ({});
    for ( int j = 0; j < Rows; j++ ){
        for ( int i = 0; i < Cols; i++ ){
            if ( i == col || j == row ) continue;
            new_mat.push_back (mat [i + j * Cols]);
        }
    }
    return Matrix(Rows - 1, Cols - 1, new_mat);
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
    if (rhs.Rows == 1 && rhs.Cols == 1)
        return rhs(0,0);
    if (rhs.Rows == 2 && rhs.Cols == 2) {
        return rhs(0, 0)*rhs(1, 1) - rhs(0, 1)*rhs(1, 0);
    }
    double det_sum = 0;
    
    for (int k = 0; k < rhs.Cols; k++) {
        std::vector <double> new_mat ({});
        /*
        for ( int j = 1; j < rhs.Rows; j++ ) {
            for ( int i = 0; i < rhs.Cols; i++ ) {
                if (i == k ) continue;
                new_mat.push_back (rhs.mat [i + j * rhs.Cols]);
            }
        }
        //Matrix submatrix (rhs.Rows - 1, rhs.Cols - 1, new_mat);
        */
        Matrix sub_mat = rhs.submatrix(0, k);
        sub_mat.printMatrix();
        det_sum += pow(-1, k) * rhs.mat[k] * det(sub_mat);
    }
    return det_sum;
}

Matrix adj(const Matrix& rhs){
    if(!(rhs.Rows == rhs.Cols)){
        std::cerr << "Dimension error!\n";
        exit(EXIT_FAILURE);
    }
    std::vector <double> new_mat({});
    for (int j = 0; j < rhs.Rows; j ++){
        for (int i = 0; i < rhs.Cols; i++){
            new_mat.push_back (pow(-1, (i + j)) * det(rhs.submatrix(i, j)));
        }

    }
    return Matrix(rhs.Rows, rhs.Cols, new_mat);
}

Eye::Eye(int size) {
    Rows = size;
    Cols = size;
    mat = std::vector<double>(size * size);
    for (int i = 0; i < size * size; i += (size + 1)){
        mat[i] = 1;
    }
}

Eye::~Eye() {}

Eye Eye::inverse(){
    return *this;
}