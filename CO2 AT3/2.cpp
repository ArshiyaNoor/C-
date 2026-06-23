#include <iostream>
using namespace std;

class Candidate
{
private:
    string name;
    int votes;

public:
    static int totalCandidates;

    void getData()
    {
        cout<<"Candidate Name: ";
        cin>>name;

        cout<<"Votes: ";
        cin>>votes;

        if(votes<0)
            votes=0;

        totalCandidates++;
    }

    int getVotes()
    {
        return votes;
    }

    string getName()
    {
        return name;
    }
};

int Candidate::totalCandidates=0;

int main()
{
    int regions,candidates;

    cout<<"Regions: ";
    cin>>regions;

    cout<<"Candidates per region: ";
    cin>>candidates;

    Candidate c[20][20];
    int total[20]={0};

    for(int i=0;i<regions;i++)
    {
        int maxVotes=-1;
        string winner;

        cout<<"\nRegion "<<i+1<<endl;

        for(int j=0;j<candidates;j++)
        {
            c[i][j].getData();

            total[j]+=c[i][j].getVotes();

            if(c[i][j].getVotes()>maxVotes)
            {
                maxVotes=c[i][j].getVotes();
                winner=c[i][j].getName();
            }
        }

        cout<<"Regional Winner: "<<winner<<endl;
    }

    int overallMax=-1;
    int pos=-1;

    for(int i=0;i<candidates;i++)
    {
        if(total[i]>overallMax)
        {
            overallMax=total[i];
            pos=i;
        }
    }

    cout<<"\nOverall Winner Candidate Position: "<<pos+1;
    cout<<"\nVotes: "<<overallMax;

    return 0;
}
