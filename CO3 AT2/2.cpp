#include <iostream>
#include <cstring>
using namespace std;

class Employee {
    char* name;
    double salary;
public:
    Employee(const char* n, double s) {
        cout << "Constructor called" << endl;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        salary = s;
    }
    ~Employee() {
        cout << "Destructor called" << endl;
        delete[] name;
    }
    void display() const {
        cout << "Name: " << name << ", Salary: " << salary << endl;
    }
};

int main() {
    Employee e1("John", 50000);
    e1.display();
    return 0;
}
