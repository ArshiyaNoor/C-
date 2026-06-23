#include <iostream>
using namespace std;

class Member
{
private:
    int memberID;
    string name, planType;
    float fee;

public:
    static int totalMembers;

    void getData()
    {
        cout<<"Member ID: ";
        cin>>memberID;

        cout<<"Name: ";
        cin>>name;

        cout<<"Plan Type (basic/premium/vip): ";
        cin>>planType;

        calculateFee();
        totalMembers++;
    }

    void calculateFee()
    {
        if(planType=="basic")
            fee=1000;
        else if(planType=="premium")
            fee=2000;
        else if(planType=="vip")
            fee=3000;
        else
        {
            cout<<"Invalid Plan\n";
            fee=0;
        }
    }

    void display()
    {
        cout<<"\nID: "<<memberID;
        cout<<"\nName: "<<name;
        cout<<"\nPlan: "<<planType;
        cout<<"\nFee: "<<fee<<endl;
    }
};

int Member::totalMembers=0;

int main()
{
    int n;
    cout<<"Enter number of members: ";
    cin>>n;

    Member m[100];

    for(int i=0;i<n;i++)
        m[i].getData();

    cout<<"\nMember Details\n";

    for(int i=0;i<n;i++)
        m[i].display();

    cout<<"\nTotal Active Members: "<<Member::totalMembers;

    return 0;
}
