#include <bits/stdc++.h>

using namespace std;

int t, n, q, res, ans[50];

int qry(int x, int y, int z)
{
    int ret;
    cout << x << " " << y << " " << z << endl;
    cin >> ret;
    return ret;
}

void solve(int x, int y)
{
    if(y-x<2)
        return;
    vector<int> num[3];
    for(int i = x+2; i<=y; i++)
    {
        int k = qry(ans[x],ans[x+1],ans[i]);
        if(k==ans[x])
            num[0].push_back(ans[i]);
        if(k==ans[i])
            num[1].push_back(ans[i]);
        if(k==ans[x+1])
            num[2].push_back(ans[i]);
    }
    ans[x+num[0].size()+num[1].size()+1] = ans[x+1], ans[x+num[0].size()] = ans[x];
    for(int i = 0; i<num[0].size(); i++)
        ans[x+i] = num[0][i];
    for(int i = 0; i<num[1].size(); i++)
        ans[x+num[0].size()+i+1] = num[1][i];
    for(int i = 0; i<num[2].size(); i++)
        ans[x+num[0].size()+num[1].size()+i+2] = num[2][i];
    solve(x,x+num[0].size()-1);
    solve(x+num[0].size()+1,x+num[0].size()+num[1].size());
    solve(x+num[0].size()+num[1].size()+2,y);
    if(num[0].size()>1&&qry(ans[x+num[0].size()-2],ans[x+num[0].size()-1],ans[x+num[0].size()])!=ans[x+num[0].size()-1])
        reverse(ans+x,ans+x+num[0].size());
    if(num[1].size()>1&&qry(ans[x+num[0].size()],ans[x+num[0].size()+1],ans[x+num[0].size()+2])!=ans[x+num[0].size()+1])
        reverse(ans+x+num[0].size()+1,ans+x+num[0].size()+num[1].size()+1);
    if(num[2].size()>1&&qry(ans[x+num[0].size()+num[1].size()+1],ans[x+num[0].size()+num[1].size()+2],ans[x+num[0].size()+num[1].size()+3])!=ans[x+num[0].size()+num[1].size()+2])
        reverse(ans+x+num[0].size()+num[1].size()+2,ans+y+1);
}

int main()
{
    cin >> t >> n >> q;
    for(int _ = 1; _<=t; _++)
    {
        for(int i = 0; i<n; i++)
            ans[i] = i+1;
        solve(0,n-1);
        for(int i = 0; i<n; i++)
            cout << ans[i] << " ";
        cout << endl;
        cin >> res;
    }
}