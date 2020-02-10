/*
ID: adityasund1
TASK: gift1
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int np, amt, ng, ind, money[10];
string names[10], cur;

int main()
{
    freopen("gift1.in","r",stdin);
    freopen("gift1.out","w",stdout);
    cin >> np;
    for(int i = 0; i<np; i++)
        cin >> names[i];
    for(int i = 0; i<np; i++)
    {
        cin >> cur >> amt >> ng;
        for(int j = 0; j<np; j++)
            if(names[j]==cur)
                ind = j;
        if(ng!=0)
            money[ind]-=(amt-amt%ng);
        for(int j = 0; j<ng; j++)
        {
            cin >> cur;
            for(int k = 0; k<np; k++)
                if(names[k]==cur)
                    ind = k;
            money[ind]+=(amt/ng);
        }
    }
    for(int i = 0; i<np; i++)
        cout << names[i] << " " << money[i] << endl;
}
