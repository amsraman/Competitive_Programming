#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

const int block = 450;

int n, cur[200000], num[550][400010], delta[550];
ll ans;
pair<int,int> p[200000];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i].f;
    for(int i = 0; i<n; i++)
        p[i].s = i;
    sort(p,p+n);
    for(int i = 0; i<n; i++)
        cur[i] = 2e5-i-1, num[i/block][cur[i]]++;
    for(int i = 0; i<n; i++)
    {
        for(int j = p[i].s; j/block==p[i].s/block&&j<n; j++)
            num[j/block][cur[j]]--, num[j/block][cur[j]+2]++, cur[j]+=2;
        for(int j = p[i].s/block+1; j<=(n-1)/block; j++)
            delta[j]+=2;
        int pref = cur[p[i].s]+delta[p[i].s/block];
        for(int j = p[i].s/block+1; j<=(n-1)/block; j++)
            if(pref>=delta[j])
                ans+=num[j][pref-delta[j]];
        for(int j = p[i].s; j/block==p[i].s/block&&j<n; j++)
            if(cur[j]+delta[j/block]==pref)
                ans++;
    }
    cout << ans << endl;
}
