#include <iostream>
using namespace std;

class Product
{
private:
    string productName;
    float price;
    int quantity;

public:
    static int totalProducts;

    void getData()
    {
        cout<<"Product Name: ";
        cin>>productName;

        cout<<"Price: ";
        cin>>price;

        cout<<"Quantity: ";
        cin>>quantity;

        if(price<0 || quantity<0)
        {
            cout<<"Invalid Input\n";
            price=0;
            quantity=0;
        }

        totalProducts++;
    }

    float calculateTotal()
    {
        return price * quantity;
    }

    void display()
    {
        cout<<"\nProduct Name: "<<productName;
        cout<<"\nPrice: "<<price;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nCost: "<<calculateTotal()<<endl;
    }
};

int Product::totalProducts=0;

int main()
{
    int n;
    float bill=0;

    cout<<"Enter number of products: ";
    cin>>n;

    Product p[100];

    for(int i=0;i<n;i++)
        p[i].getData();

    cout<<"\nProduct Details\n";

    for(int i=0;i<n;i++)
    {
        p[i].display();
        bill += p[i].calculateTotal();
    }

    cout<<"\nTotal Products: "<<Product::totalProducts;
    cout<<"\nTotal Bill: "<<bill;

    return 0;
}
