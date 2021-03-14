# pragma once
# include <iostream>

class Complex{
private:
        double re;
        double im;
public:
        Complex(double re_, double im_);
        Complex(const Complex& rhs);
        Complex conjugate();
        Complex operator+(const Complex& rhs) const;
        friend Complex operator-(const Complex& rhs);
        Complex operator-(const Complex& rhs) const;
        Complex operator*(const Complex& rhs) const;
        Complex operator*(const double& rhs) const ;
        Complex operator/(Complex& rhs);
        const Complex operator=(const Complex& rhs);
        friend std::ostream& operator<<(std::ostream& os, const Complex& comp);
        Complex Complex::operator==(const Complex& rhs) const;
        friend double norm(const Complex& comp);
        friend double Real(const Complex& comp);
        friend double Imag(const Complex& comp);
};

