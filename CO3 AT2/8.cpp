#include <iostream>
using namespace std;

class Complex {
    double real;
    double imag;
public:
    Complex(double r, double i) {
        real = r;
        imag = i;
    }
    Complex operator+(const Complex& c) {
        return Complex(real + c.real, imag + c.imag);
    }
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3.5, 2.5);
    Complex c2(1.5, 4.5);
    Complex c3 = c1 + c2;
    c3.display();
    return 0;
}
