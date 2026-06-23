#include <iostream>
#include <cstring>
using namespace std;

class Student {
    char* name;
    int marks;
public:
    Student(const char* n, int m) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        marks = m;
    }
    Student(const Student& s) {
        name = new char[strlen(s.name) + 1];
        strcpy(name, s.name);
        marks = s.marks;
    }
    ~Student() {
        delete[] name;
    }
    void setName(const char* n) {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    void display() const {
        cout << "Name: " << name << ", Marks: " << marks << endl;
    }
};

int main() {
    Student s1("Alice", 85);
    Student s2 = s1;
    s2.setName("Bob");
    s1.display();
    s2.display();
    return 0;
}
