#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, ans;
array<ll,3> lines[300];
pair<ll,ll> p[2];

bool place(int a, int b)
{
    return (lines[a][0]*p[b].f+lines[a][1]*p[b].s>-lines[a][2]);
}

int main()
{
    cin >> p[0].f >> p[0].s >> p[1].f >> p[1].s >> n;
    for(int i = 0; i<n; i++)
        cin >> lines[i][0] >> lines[i][1] >> lines[i][2];
    for(int i = 0; i<n; i++)
        ans+=int(place(i,0)^place(i,1));
    cout << ans << endl;
}