#include <bits/stdc++.h>

using namespace std;

int l, n, m;

int main()
{
    cin >> l >> n >> m;
    if((l==8)&&(n>=2)&&(m>=2))
    {
        cout << 2 << endl;
        for(int i = 0; i<l; i++)
            cout << 1+(i%2) << " ";
        cout << endl;
        for(int i = 0; i<l; i++)
            cout << 1+((i+1)%2) << " ";
        cout << endl;
    }
    else if((l==9)&&(n>=3)&&(m>=3))
    {
        cout << 3 << endl;
        for(int i = 0; i<l; i++)
            cout << 1+(i%3) << " ";
        cout << endl;
        for(int i = 0; i<l; i++)
            cout << 1+((i+1)%3) << " ";
        cout << endl;
    }
    else
        cout << -1 << endl;
}
