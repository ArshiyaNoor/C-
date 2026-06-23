#include <iostream>
using namespace std;

class Event
{
private:
    string eventName, participantName;
    int regID;

public:
    static int totalParticipants;

    void getData()
    {
        cout<<"Event Name: ";
        cin>>eventName;

        cout<<"Participant Name: ";
        cin>>participantName;

        cout<<"Registration ID: ";
        cin>>regID;

        totalParticipants++;
    }

    void display()
    {
        cout<<"\nEvent Name: "<<eventName;
        cout<<"\nParticipant Name: "<<participantName;
        cout<<"\nRegistration ID: "<<regID<<endl;
    }

    int getID()
    {
        return regID;
    }
};

int Event::totalParticipants=0;

int main()
{
    int n;
    cout<<"Enter number of registrations: ";
    cin>>n;

    Event e[100];

    for(int i=0;i<n;i++)
    {
        e[i].getData();

        for(int j=0;j<i;j++)
        {
            if(e[i].getID()==e[j].getID())
            {
                cout<<"Duplicate Registration ID!\n";
                i--;
                break;
            }
        }
    }

    cout<<"\nRegistration Details\n";

    for(int i=0;i<n;i++)
        e[i].display();

    cout<<"\nTotal Participants: "<<Event::totalParticipants;

    return 0;
}
