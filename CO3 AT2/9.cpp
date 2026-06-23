#include <iostream>
using namespace std;

class Demo {
    int x;
public:
    Demo(int a) { 
        x = a; 
        cout << "Construct "; 
    }
    Demo(const Demo &d) {
        x = d.x;
        cout << "Copy ";
    }
    ~Demo() { 
        cout << "Destruct "; 
    }
    Demo operator+(Demo d) {
        cout << "Add ";
        return Demo(x + d.x);
    }
};

int main() {
    Demo d1(5);
    Demo d2(10);
    Demo d3 = d1 + d2;
    cout << endl;
    return 0;
}
