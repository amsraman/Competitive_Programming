#include <bits/stdc++.h>

using namespace std;

int n, k, d[1000], p1 = 1000, p2 = 1000;

int main()
{
    freopen("nfc.in","r",stdin);
    freopen("nfc.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> d[i];
    for(int i = n-1; i>=0; i--)
        for(int j = i+1; j<n; j++)
            if((d[i]+d[j]==k)&&(i+j<=p1+p2))
                p1 = i, p2 = j;
    cout << p1+1 << " " << p2+1 << endl;
}
