#include <iostream>
using namespace std;

class Number {
    int value;
public:
    Number(int v) {
        value = v;
    }
    void operator-() {
        value = -value;
    }
    void display() const {
        cout << "Value: " << value << endl;
    }
};

int main() {
    Number n(25);
    -n;
    n.display();
    return 0;
}
