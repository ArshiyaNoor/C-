#include <iostream>
#include <string>
using namespace std;

class Mobile {
    string brand;
    double price;
public:
    Mobile() {
        brand = "Unknown";
        price = 0.0;
        cout << "Default Constructor" << endl;
    }
    Mobile(string b, double p) {
        brand = b;
        price = p;
        cout << "Parameterized Constructor" << endl;
    }
    Mobile(const Mobile& m) {
        brand = m.brand;
        price = m.price;
        cout << "Copy Constructor" << endl;
    }
};

int main() {
    Mobile m1;
    Mobile m2("BrandX", 999.99);
    Mobile m3 = m2;
    return 0;
}
