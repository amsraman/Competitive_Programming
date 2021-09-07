#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int t, n, a[500000], dp[500000], seg[(1<<20)];
vector<int> events[500000];

int qry(int low, int high)
{
    low+=(1<<19), high+=(1<<19);
    int ret = 0;
    while(low<=high)
    {
        if(high%2==0) ret = max(ret,seg[high]), high--;
        if(low%2==1) ret = max(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void upd(int k, int x)
{
    k+=(1<<19), seg[k] = x;
    while(k>1)
    {
        k/=2;
        seg[k] = max(seg[2*k],seg[2*k+1]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<n; i++)
            upd(i,0), dp[i] = 1;
        stack<int> st;
        for(int i = 0; i<n; i++)
        {
            while(!st.empty()&&a[st.top()]<a[i])
                st.pop();
            if(!st.empty())
                events[st.top()].push_back(i);
            st.push(i);
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<events[i].size(); j++)
                dp[events[i][j]] = qry(0,a[events[i][j]]-1)+2;
            dp[i] = max(dp[i],qry(0,a[i]-1)+1);
            upd(a[i] - 1, dp[i]);
        }
        cout << qry(0,n-1) << endl;
        for(int i = 0; i<n; i++)
            events[i].clear();
    }
}
