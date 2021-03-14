#include "Complex.hpp"
#include <cmath>

Complex::Complex(double re_ = 0.0, double im_ = 0.0): re(re_), im(im_){
}

Complex::Complex(const Complex& rhs): re(rhs.re), im(rhs.im){}

Complex Complex::conjugate() 
{
    return Complex(re, -im);
}

const Complex Complex::operator=(const Complex& rhs){
    return Complex(rhs.re, rhs.im);
}

Complex Complex::operator+(const Complex& rhs) const {
    return Complex(re + rhs.re, im + rhs.im);
}

Complex operator-(const Complex& rhs){
    return Complex(-rhs.re, -rhs.im);
}

Complex Complex::operator-(const Complex& rhs) const
{
    return Complex(re - rhs.re, im - rhs.im);
}


Complex Complex::operator*(const Complex& rhs) const {
    return Complex(re*rhs.re - im*rhs.im, re*rhs.im + im*rhs.re);
}

Complex Complex::operator*(const double& rhs) const {
    return Complex(re*rhs, im*rhs);
}

Complex Complex::operator/(Complex& rhs) 
{
    double denominator = Real(rhs*rhs.conjugate());
    Complex comp = Complex(re, im)*rhs.conjugate();
    return comp*(1.0/denominator);
}

std::ostream& operator<<(std::ostream &os, const Complex &comp)
{
    if (comp.im >= 0) {
        os << comp.re << " + " << comp.im << "i";
    }
    else{
        os << comp.re << " " << comp.im << "i";
    }
    return os;
}

Complex Complex::operator==(const Complex& rhs) const
{
    if (re == rhs.re || im == rhs.im){
        return true;
    }
    return false;
}

double norm(const Complex& comp){
    return sqrt(pow(comp.re, 2) + pow(comp.im, 2));
}
double Real(const Complex& comp){
    return comp.re;
}
double Imag(const Complex& comp){
    return comp.im;
}