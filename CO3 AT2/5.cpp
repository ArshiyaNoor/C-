#include <iostream>
using namespace std;

class Test {
    int id;
public:
    Test(int i) {
        id = i;
        cout << "Construct " << id << endl;
    }
    ~Test() {
        cout << "Destruct " << id << endl;
    }
};

int main() {
    Test t1(1);
    {
        Test t2(2);
        {
            Test t3(3);
        }
    }
    return 0;
}
