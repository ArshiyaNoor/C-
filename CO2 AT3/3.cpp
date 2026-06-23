#include <iostream>
using namespace std;

class Product
{
private:
    string name;
    float price;
    int quantity;

public:
    static float overallSales;

    void getData()
    {
        cout<<"Product Name: ";
        cin>>name;

        cout<<"Price: ";
        cin>>price;

        cout<<"Quantity: ";
        cin>>quantity;
    }

    float calculateSales()
    {
        return price*quantity;
    }

    string getName()
    {
        return name;
    }

    void display()
    {
        cout<<name<<"  Sales = "<<calculateSales()<<endl;
    }
};

float Product::overallSales=0;

int main()
{
    int stores;

    cout<<"Enter Stores: ";
    cin>>stores;

    Product p[10][20];
    int count[10];

    float bestStoreSales=-1;
    int bestStore=0;

    float bestProductSales=-1;
    string bestProduct;

    for(int i=0;i<stores;i++)
    {
        cout<<"\nProducts in Store "<<i+1<<": ";
        cin>>count[i];

        float storeSales=0;

        for(int j=0;j<count[i];j++)
        {
            p[i][j].getData();

            float sales=p[i][j].calculateSales();

            storeSales+=sales;
            Product::overallSales+=sales;

            if(sales>bestProductSales)
            {
                bestProductSales=sales;
                bestProduct=p[i][j].getName();
            }
        }

        cout<<"Store "<<i+1<<" Sales = "<<storeSales<<endl;

        if(storeSales>bestStoreSales)
        {
            bestStoreSales=storeSales;
            bestStore=i+1;
        }
    }

    cout<<"\nOverall Sales = "<<Product::overallSales;
    cout<<"\nBest Store = "<<bestStore;
    cout<<"\nBest Product = "<<bestProduct;

    return 0;
}
