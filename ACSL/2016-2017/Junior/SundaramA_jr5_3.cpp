#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int a[8][8], x[2], r, n;
    string z;
    for(int reeee = 0; reeee<5; reeee++)
    {
    n = 0;
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            a[i][j] = 0;
        }
    }
    cout << "Enter number of rows: ";
    cin >> r;
    for(int i = 0; i<r; i++)
    {
        cout << "Enter Row: ";
        cin >> z;
        for(int j = 1; j<z.length(); j++)
        {
            a[atoi(z.substr(0,1).c_str())-1][atoi(z.substr(j,1).c_str())-1] = 1;
        }
    }
    cout << "Enter Position: ";
    cin >> z;
    x[0] = atoi(z.substr(0,1).c_str());
    x[1] = atoi(z.substr(1,1).c_str());
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if((i-x[0]+1)*(i-x[0]+1)+(j-x[1]+1)*(j-x[1]+1)<=4)
            {
                a[i][j] = (a[i][j]+1)%2;
            }
        }
    }
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            if(a[i][j]==1)
            {
                n++;
            }
        }
    }
    cout << endl << n << endl << endl;
    }
    return 0;
}

