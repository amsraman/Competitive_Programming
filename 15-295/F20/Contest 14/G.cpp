#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007

using namespace std;

int n;
pair<int,int> boxes[100000];
set<pair<int,int>> hi;
map<pair<int,int>,int> dp;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> boxes[i].f >> boxes[i].s;
    sort(boxes,boxes+n);
    for(int i = 0; i<n; i++)
        hi.insert(boxes[i]);
    for(int i = n-1; i>=0; i--)
    {
        int cur = 0;
        bool done = false;
        if(hi.count({boxes[i].f+1,boxes[i].s}))
            cur = dp[{boxes[i].f+1,boxes[i].s}], done = true;
        if(hi.count({boxes[i].f,boxes[i].s+1}))
            cur = (cur+dp[{boxes[i].f,boxes[i].s+1}])%MOD, done = true;
        if(!done)
            cur = 1;
        dp[boxes[i]] = cur;
    }
    cout << dp[{1,1}];
}