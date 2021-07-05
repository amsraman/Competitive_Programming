#include <bits/stdc++.h>
#define f first
#define s second
typedef long double ld;

using namespace std;

int n, cur = 1;
ld k, h[100002], ans;
pair<ld,ld> hull[100002];


int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> h[i+1];
    for(int i = 0; i<n+2; i++)
        h[i]+=((ld)i*i*k);
    hull[0] = {0,h[0]};
    hull[1] = {1,h[1]};
    for(int i = 2; i<n+2; i++)
    {
        while(cur>0&&((hull[cur].f-hull[cur-1].f)*(h[i]-hull[cur].s)-(hull[cur].s-hull[cur-1].s)*(i-hull[cur].f)>0))
            cur--;
        hull[++cur] = {i,h[i]};
    }
    for(int i = 0; i<cur; i++)
    {
        ans = max(ans,hull[i].s-hull[i].f*hull[i].f*k);
        for(ld j = hull[i].f+1; j<hull[i+1].f; j++)
            ans = max(ans,hull[i].s+(j-hull[i].f)*(hull[i+1].s-hull[i].s)/(hull[i+1].f-hull[i].f)-j*j*k);
    }
    cout << fixed << setprecision(10) << ans << endl;
}