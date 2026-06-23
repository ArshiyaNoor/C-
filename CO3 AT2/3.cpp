#include <iostream>
using namespace std;

class Distance {
    int meters;
    int centimeters;
public:
    Distance(int m, int cm) {
        meters = m;
        centimeters = cm;
    }
    Distance operator+(const Distance& d) {
        int total_cm = centimeters + d.centimeters + (meters + d.meters) * 100;
        return Distance(total_cm / 100, total_cm % 100);
    }
    void display() const {
        cout << meters << "m " << centimeters << "cm" << endl;
    }
};

int main() {
    Distance d1(5, 80);
    Distance d2(3, 50);
    Distance d3 = d1 + d2;
    d3.display();
    return 0;
}
