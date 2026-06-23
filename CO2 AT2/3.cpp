#include <iostream>
using namespace std;

class Warehouse
{
private:
    int itemID;
    string name, location;
    int quantity;

public:
    static int totalItems;

    void getData()
    {
        cout<<"Item ID: ";
        cin>>itemID;

        cout<<"Item Name: ";
        cin>>name;

        cout<<"Quantity: ";
        cin>>quantity;

        if(quantity<0)
            quantity=0;

        cout<<"Location: ";
        cin>>location;

        totalItems++;
    }

    void display()
    {
        cout<<"\nItem ID: "<<itemID;
        cout<<"\nName: "<<name;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nLocation: "<<location<<endl;
    }
};

int Warehouse::totalItems=0;

int main()
{
    int n;
    cout<<"Enter number of items: ";
    cin>>n;

    Warehouse w[100];

    for(int i=0;i<n;i++)
        w[i].getData();

    cout<<"\nInventory Details\n";

    for(int i=0;i<n;i++)
        w[i].display();

    cout<<"\nTotal Items Stored: "<<Warehouse::totalItems;

    return 0;
}
