#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll g;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> g;
        set<int> ks;
        g*=2;
        for(int i = 1; i*i<=g; i++)
            if(g%i==0)
            {
                if((g/i-i+1)%2==0&&(g/i-i+1)>0)
                    ks.insert((g/i-i+1)/2);
                if((i-g/i+1)%2==0&&(i-g/i+1)>0)
                    ks.insert((i-g/i+1)/2);
            }
        cout << "Case #" << _ << ": " << ks.size() << endl;
    }
}