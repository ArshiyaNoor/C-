#include <iostream>
using namespace std;

class Violation
{
private:
    string vehicleNo, ownerName, violationType;
    float fineAmount;

public:
    static int totalViolations;

    void getData()
    {
        cout << "Vehicle Number: ";
        cin >> vehicleNo;

        cout << "Owner Name: ";
        cin >> ownerName;

        cout << "Violation Type (signal/speed/parking): ";
        cin >> violationType;

        calculateFine();
        totalViolations++;
    }

    void calculateFine()
    {
        if(violationType=="signal")
            fineAmount=1000;
        else if(violationType=="speed")
            fineAmount=1500;
        else if(violationType=="parking")
            fineAmount=500;
        else
        {
            cout<<"Invalid Violation Type\n";
            fineAmount=0;
        }
    }

    void display()
    {
        cout<<"\nVehicle No: "<<vehicleNo;
        cout<<"\nOwner Name: "<<ownerName;
        cout<<"\nViolation Type: "<<violationType;
        cout<<"\nFine Amount: "<<fineAmount<<endl;
    }
};

int Violation::totalViolations=0;

int main()
{
    int n;
    cout<<"Enter number of violations: ";
    cin>>n;

    Violation v[100];

    for(int i=0;i<n;i++)
        v[i].getData();

    cout<<"\nViolation Report\n";

    for(int i=0;i<n;i++)
        v[i].display();

    cout<<"\nTotal Violations: "<<Violation::totalViolations;

    return 0;
}
