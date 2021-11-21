#include <bits/stdc++.h>

using namespace std;

int n, s, h[15], b[15], sum[(1<<15)], pre[(1<<15)], ans;
vector<int> sets;
bool dp[(1<<15)][15];

int main()
{
    cin >> n >> s;
    for(int i = 0; i<n; i++)
        cin >> h[i];
    for(int i = 0; i<s; i++)
        cin >> b[i];
    for(int i = 1; i<s; i++)
        b[i]+=b[i-1];
    for(int i = 0; i<(1<<n); i++)
        for(int j = 0; j<n; j++)
            if(i&(1<<j))
                sum[i]+=h[j];
    for(int i = 0; i<(1<<n); i++)
        dp[i][0] = (sum[i]==b[0]);
    for(int i = 1; i<s; i++)
        for(int j = 0; j<(1<<n); j++)
            if(sum[j]==b[i])
                for(int k = j; k>0; k = (k-1)&j)
                    if(dp[k][i-1])
                        dp[j][i] = true, ans = j, pre[j] = k;
    if(!dp[ans][s-1])
    {
        cout << -1 << endl;
        return 0;
    }
    while(ans!=0)
        sets.push_back(ans-pre[ans]), ans = pre[ans];
    for(int i = s-1; i>=0; i--) //I don't like these dumb impl details but whatever
    {
        int cnt = 0;
        for(int j = 0; j<n; j++)
            if(sets[i]&(1<<j))
                cnt++;
        cout << cnt << " ";
        for(int j = 0; j<n; j++)
            if(sets[i]&(1<<j))
                cout << j+1 << " ";
        cout << endl;
    }
}
