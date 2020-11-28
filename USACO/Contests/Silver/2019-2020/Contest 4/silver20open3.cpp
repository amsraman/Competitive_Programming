#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, mi[100000], ma[100000], ans = 1;
pair<int,int> points[100000];

int main()
{
    freopen("moop.in","r",stdin);
    freopen("moop.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> points[i].f >> points[i].s;
    sort(points,points+n);
    mi[0] = points[0].s, ma[n-1] = points[n-1].s;
    for(int i = 1; i<n; i++)
        mi[i] = min(mi[i-1],points[i].s);
    for(int i = n-2; i>=0; i--)
        ma[i] = max(ma[i+1],points[i].s);
    for(int i = 0; i<n-1; i++)
        if(mi[i]>ma[i+1])
            ans++;
    cout << ans << endl;
}
