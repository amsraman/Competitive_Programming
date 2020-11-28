#include <iostream>

using namespace std;

int right(int a[5])
{
    int n = 0;
    int maxi = 0;
    for(int i = 4; i>=0; i--)
    {
        if(a[i]>maxi)
        {
            n++;
            maxi = a[i];
        }
    }
    return n;
}

int left(int a[5])
{
    int n = 0;
    int maxi = 0;
    for(int i = 0; i<5; i++)
    {
        if(a[i]>maxi)
        {
            n++;
            maxi = a[i];
        }
    }
    return n;
}

int main()
{
    int lc, rc, a[5], n;
    for(int BeeMovie = 0; BeeMovie<5; BeeMovie++)
    {
    n=0;
    cout << "Enter left clue: ";
    cin >> lc;
    cout << "Enter right clue: ";
    cin >> rc;
    for(int i = 1; i<=5; i++)
    {
        a[0] = i;
        for(int j = 1; j<=5; j++)
        {
            if(j!=a[0])
            {
                a[1] = j;
                for(int k = 1; k<=5; k++)
                {
                    if((k!=a[0])&&(k!=a[1]))
                    {
                        a[2] = k;
                        for(int l = 1; l<=5; l++)
                        {
                            if((l!=a[0])&&(l!=a[1])&&(l!=a[2]))
                            {
                                a[3] = l;
                                for(int m = 1; m<=5; m++)
                                {
                                    if((m!=a[0])&&(m!=a[1])&&(m!=a[2])&&(m!=a[3]))
                                    {
                                        a[4] = m;
                                        if((left(a)==lc)&&(right(a)==rc))
                                        {
                                            n++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    cout << n << endl;
    }
    return 0;
}
