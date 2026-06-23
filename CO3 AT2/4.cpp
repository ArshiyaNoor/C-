#include <iostream>
using namespace std;

class Box {
    double volume;
public:
    Box(double v) {
        volume = v;
    }
    bool operator>(const Box& b) {
        return volume > b.volume;
    }
    void display() const {
        cout << "Box Volume: " << volume << endl;
    }
};

int main() {
    Box b1(120.5);
    Box b2(85.3);
    if (b1 > b2) {
        cout << "Box 1 has greater volume." << endl;
    } else {
        cout << "Box 2 has greater volume or they are equal." << endl;
    }
    return 0;
}
