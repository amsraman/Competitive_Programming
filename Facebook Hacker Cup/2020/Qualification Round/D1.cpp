#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

int t, n, m;
ll c[1000000], dp[1000000], ans;

int main()
{
    freopen("running_on_fumes_chapter_1_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> m;
        for(int i = 0; i<n; i++)
            cin >> c[i];
        deque<ll> dq;
        for(int i = 0; i<n; i++)
        {
            dp[i] = ((dq.empty()||c[i]==0)?-1:dq[0]+c[i]);
            if(i==0)
                dp[i] = 0;
            if((i>=m)&&(!dq.empty())&&(dp[i-m]==dq.front()))
                dq.pop_front();
            if(dp[i]!=-1)
            {
                while(!dq.empty()&&dq.back()>dp[i])
                    dq.pop_back();
                dq.push_back(dp[i]);
            }
        }
        ans = INF;
        for(int i = 0; i<min(m,n-1); i++)
            if(dp[n-i-2]!=-1)
                ans = min(ans,dp[n-i-2]);
        cout << "Case #" << _+1 << ": " << (ans==INF?-1:ans) << endl;
    }
}
