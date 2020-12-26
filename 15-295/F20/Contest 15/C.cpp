#include <bits/stdc++.h>

using namespace std;

int c, z;

int main()
{
    cin >> c;
    while(c--)
    {
        cin >> z;
        int cur;
        for(int i = 1; i*i<=z; i++)
            if(z%i==0)
                cur = i;
        cout << (2*cur>=z/cur?1:0) << endl;
    }
}