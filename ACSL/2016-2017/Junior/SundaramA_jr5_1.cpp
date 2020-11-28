#include <iostream>

using namespace std;

int main()
{
    int ln, m1;
    char ls;
    char m = '.';
    int x[5];
    char y[5];
    for(int a=1; a<=5; a++)
    {
        cout << "Line " << a << ": ";
        cout << "Lead Card (Number, Suit)\n";
        cin >> ln;
        cin >> ls;
        m1=0;
        m='.';
        cout << "Enter 5 cards:\n";
        for(int b=0; b<=4; b++)
        {
            cin >> x[b];
            cin >> y[b];
        }
        for(int c=0; c<=4; c++)
        {
            if(y[c]==ls)
            {
                m = y[c];
                if(x[c]>=ln)
                {
                    if(0<x[c]-ln<m1-ln) // <<<<< RIP BUG
                    {
                        m1 = x[c];
                    }
                }
            }
        }
        if(m1==0)
        {
            m1 = 100;
            for(int d=0; d<=4; d++)
            {
                if (y[d]==ls)
                {
                    if(x[d]<m1)
                    {
                        m1 = x[d];
                    }
                }
            }
        }
        if(m=='.')
        {
            cout << "\nDealer's Card:" << "\nNONE\n\n";
        }
        else
        {
            cout << "\nDealer's Card:" << endl << m1 << "," << m << endl << endl;
        }
    }
    return 0;
}
