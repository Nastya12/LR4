#include <iostream>
#include <stdlib.h>
#include "tree.h"

using namespace std;

class ConsoleSet:public Set
{
public:
    void output (ostream &out) const;
};

ostream &operator<<(ostream &out, const ConsoleSet &set)
{
    set.output(out);
    return out;
}

void ConsoleSet::output(ostream &out) const
{
    int datum;
    if (nextDatum(true, datum))
        out<<datum<<" ";
    while (nextDatum(false, datum))
        out<<datum<<" ";
}

int main()
{
    srand(time(NULL));
    int a, a1,a2, a3,A1,B1;
    int data;
    cout<<" \n Set \n";
    cout<<" Create set of A.\n";
    cout<<"enter number of elements of the set A.\n";
    cin>>A1;
    ConsoleSet A(A1);
    cout<<"\n Create set of B.\n";
    cout<<"enter number of elements of the set B.\n";
    cin>>B1;
    ConsoleSet B(B1);
    do
    {
        cout<<"\n\n Menu: \n";
        cout<<" 1 -> push element. \n";
        cout<<" 2 -> find. \n";
        cout<<" 3 -> unite. \n";
        cout<<" 4 -> intersection. \n";
        cout<<" 5 -> difference. \n";
        cout<<" 0 -> exit. \n";
        cout<<" action=";
        cin>>a;
        if (a>=0)
            switch(a)
            {
            case 1:
            {
                cout<<"     1 -> push in A:\n";
                cout<<"     2 -> push in B:\n";
                cout<<"action=";
                cin>>a1;
                if (a1>0)
                    switch(a1)
                    {
                    case 1:
                    {
                        cout<<"Enter number= \n";
                        cin>>data;
                        A.push(data);
                    }
                    break;
                    case 2:
                    {
                        cout<<"Enter number= \n";
                        cin>>data;
                        B.push(data);
                    }
                    break;
                    }
            }
            break;
            case 2:
            {
                cout<<"     1 -> find in A:\n";
                cout<<"     2 -> find in B:\n";
                cout<<"action=";
                cin>>a2;
                if (a2>0)
                    switch(a2)
                    {
                    case 1:
                    {
                        if (A.isEmpty())
                            cout<<" Set A is empty.\n";
                        else
                        {
                            int key;
                            cout<<" Enter the required number: ";
                            cin>>key;
                            if ((A.find(key))!=0)
                            {
                                cout<<"Element: ";
                                cout<<key;
                            }
                            else cout<<" Same element is not find.\n";
                        }
                    }
                    break;
                    case 2:
                    {
                        if (B.isEmpty())
                            cout<<" Set B is empty.\n";
                        else
                        {
                            int key;
                            cout<<" Enter the required number: ";
                            cin>>key;
                            if ((B.find(key))!=0)
                            {
                                cout<<"Element: ";
                                cout<<key;
                            }
                            else cout<<" Same element is not find.\n";
                        }
                    }
                    break;
                    }
            }
            break;
            case 3:
            {
                B.unite(A);
                output(B);
            }
            break;
            case 4:
            {
                ConsoleSet C;
                C.intersection(A);
                output(C);
            }
            case 5:
            {
                ConsoleSet C;
                C.difference(A);
                output(C);

            }
            break;
            case 0:
                return 0;
                break;
            default:
                cout<<"error: incorrect action \n";
            }
    }
    while (a);
    return 0;
}
