#include <iostream>
using namespace std;

class Team
{
private:
    string name;
    int wins,draws,losses;
    int goalsScored,goalsConceded;

public:
    static int totalTeams;

    void getData()
    {
        cout<<"Team Name: ";
        cin>>name;

        cout<<"Wins Draws Losses: ";
        cin>>wins>>draws>>losses;

        cout<<"Goals Scored: ";
        cin>>goalsScored;

        cout<<"Goals Conceded: ";
        cin>>goalsConceded;

        totalTeams++;
    }

    int getPoints()
    {
        return wins*3 + draws;
    }

    int goalDifference()
    {
        return goalsScored-goalsConceded;
    }

    string getName()
    {
        return name;
    }

    void display()
    {
        cout<<"\n"<<name;
        cout<<"\nPoints = "<<getPoints();
        cout<<"\nGoal Difference = "<<goalDifference();
    }
};

int Team::totalTeams=0;

int main()
{
    int groups;

    cout<<"Enter Number of Groups: ";
    cin>>groups;

    Team t[10][20];
    int size[10];

    string champion;
    int championPoints=-1;

    for(int i=0;i<groups;i++)
    {
        cout<<"\nTeams in Group "<<i+1<<": ";
        cin>>size[i];

        int bestPoints=-1;
        string winner;

        for(int j=0;j<size[i];j++)
        {
            t[i][j].getData();

            if(t[i][j].getPoints()>bestPoints)
            {
                bestPoints=t[i][j].getPoints();
                winner=t[i][j].getName();
            }
        }

        cout<<"\nGroup Winner: "<<winner<<endl;

        if(bestPoints>championPoints)
        {
            championPoints=bestPoints;
            champion=winner;
        }
    }

    cout<<"\nTournament Champion: "<<champion;
    cout<<"\nPoints: "<<championPoints;
    cout<<"\nTotal Teams: "<<Team::totalTeams;

    return 0;
}
