#include <bits/stdc++.h>

using namespace std;

int n, k, b[100000], p1, p2 = -1, ans;
multiset<int> mincounts;
map<int,int> counts;

int main()
{
    freopen("lineup.in","r",stdin);
    freopen("lineup.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
    {
        cin >> b[i];
    }
    while(p1<n)
    {
        if(mincounts.size()<=k+1)
        {
            if(mincounts.size()!=0) ans = max(ans,*(--mincounts.end()));
            if(p2<n-1)
            {
                p2++;
                if(counts[b[p2]]!=0) mincounts.erase(mincounts.find(counts[b[p2]]));
                counts[b[p2]]++;
                mincounts.insert(counts[b[p2]]);
            }
            else
            {
                mincounts.erase(mincounts.find(counts[b[p1]]));
                counts[b[p1]]--;
                mincounts.insert(counts[b[p1]]);
                p1++;
            }
        }
        else
        {
            mincounts.erase(mincounts.find(counts[b[p1]]));
            counts[b[p1]]--;
            if(counts[b[p1]]!=0) mincounts.insert(counts[b[p1]]);
            p1++;
        }
    }
    cout << ans << endl;
}
