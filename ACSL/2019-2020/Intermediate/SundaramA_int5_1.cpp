#include <bits/stdc++.h>

using namespace std;

string n;
int p;

int main()
{
    freopen("intdata.txt","r",stdin);
    for(int z = 0; z<5; z++)
    {
        cin >> n >> p;
        p = n.length()-p;
        for(int i = 0; i<n.length(); i++)
        {
            if(i<p) n[i] = ('0'+((n[i]-'0')+(n[p]-'0'))%10);
            else if(i>p) n[i] = ('0'+abs((n[i]-'0')-(n[p]-'0')));
        }
        cout << n << endl;
    }
}
