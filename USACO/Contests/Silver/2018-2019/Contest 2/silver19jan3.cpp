#include <bits/stdc++.h>

using namespace std;

int n, maxs, ans;
pair<int,int> peaks[100000];
bool seen[100000][2];

int main()
{
    freopen("mountains.in","r",stdin);
    freopen("mountains.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> peaks[i].first >> peaks[i].second;
    }
    sort(peaks,peaks+n);
    for(int i = 0; i<n; i++)
    {
        if(peaks[i].first+peaks[i].second>maxs)
        {
            seen[i][0] = true;
            maxs = peaks[i].first+peaks[i].second;
        }
    }
    maxs = -10000000000;
    for(int i = n-1; i>=0; i--)
    {
        if(peaks[i].second-peaks[i].first>maxs)
        {
            seen[i][1] = true;
            maxs = peaks[i].second-peaks[i].first;
        }
    }
    for(int i = 0; i<n; i++)
    {
        if((seen[i][0])&&(seen[i][1]))
        {
            ans++;
        }
    }
    cout << ans << endl;
}
