#include <iostream>
using namespace std;

class Student
{
private:
    string name;
    int marks;

public:
    static int totalStudents;

    void getData()
    {
        cout<<"Student Name: ";
        cin>>name;

        cout<<"Marks: ";
        cin>>marks;

        if(marks<0 || marks>100)
            marks=0;

        totalStudents++;
    }

    int getMarks()
    {
        return marks;
    }

    string getName()
    {
        return name;
    }

    void display()
    {
        cout<<name<<"  "<<marks<<endl;
    }
};

int Student::totalStudents=0;

int main()
{
    int depts;

    cout<<"Enter number of departments: ";
    cin>>depts;

    Student dept[10][50];
    int size[10];

    int overallTop=-1;
    string overallName;

    for(int i=0;i<depts;i++)
    {
        cout<<"\nStudents in Department "<<i+1<<": ";
        cin>>size[i];

        int deptTop=-1;
        string deptName;
        int pass=0;

        for(int j=0;j<size[i];j++)
        {
            dept[i][j].getData();

            if(dept[i][j].getMarks()>deptTop)
            {
                deptTop=dept[i][j].getMarks();
                deptName=dept[i][j].getName();
            }

            if(dept[i][j].getMarks()>=50)
                pass++;

            if(dept[i][j].getMarks()>overallTop)
            {
                overallTop=dept[i][j].getMarks();
                overallName=dept[i][j].getName();
            }
        }

        if(size[i]>0)
        {
            cout<<"\nDepartment Topper: "<<deptName;
            cout<<"\nMarks: "<<deptTop;

            float passPercent=(float)pass/size[i]*100;
            cout<<"\nPass Percentage: "<<passPercent<<"%\n";
        }
        else
            cout<<"\nEmpty Department\n";
    }

    cout<<"\nOverall University Topper: "<<overallName;
    cout<<"\nMarks: "<<overallTop;

    return 0;
}
