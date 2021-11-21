#include <bits/stdc++.h>

using namespace std;

int n, a[15], x = -1, y, tot;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> a[i];
    }
    for(int i = 0; i<n; i++)
    {
        y+=a[i];
        if(tot+y>=80)
        {
            cout << "Touchdown" << endl;
            return 0;
        }
        if(tot+y<=-20)
        {
            cout << "Safety" << endl;
            return 0;
        }
        if((y<10)&&(i-x==4))
        {
            cout << "Nothing" << endl;
            return 0;
        }
        if(y>=10)
        {
            tot+=y, x = i, y = 0;
        }
    }
    cout << "Nothing" << endl;
}
