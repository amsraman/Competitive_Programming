/*
ID: adityasund1
TASK: vans
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> dp[1000][2];

vector<int> make(int a)
{
    vector<int> ret;
    ret.push_back(a);
    return ret;
}

vector<int> add(vector<int> a, vector<int> b)
{
    while(a.size()<b.size())
        a.push_back(0);
    while(b.size()<a.size())
        b.push_back(0);
    vector<int> ret;
    int carry = 0;
    for(int i = 0; i<a.size(); i++)
        ret.push_back((a[i]+b[i]+carry)%10), carry = (a[i]+b[i]+carry)/10;
    if(carry)
        ret.push_back(carry);
    return ret;
}

vector<int> sub(vector<int> a, vector<int> b)
{
    while(b.size()<a.size())
        b.push_back(0);
    vector<int> ret;
    int borrow = 0, cur;
    for(int i = 0; i<a.size(); i++)
    {
        cur = a[i]-borrow, borrow = 0;
        if(cur<b[i])
            borrow = 1, cur+=10;
        ret.push_back(cur-b[i]);
    }
    return ret;
}

int main()
{
    freopen("vans.in","r",stdin);
    freopen("vans.out","w",stdout);
    cin >> n;
    dp[0][0].push_back(2), dp[0][1].push_back(2);
    dp[1][0].push_back(2), dp[1][1].push_back(2);
    dp[2][0].push_back(4), dp[2][1].push_back(8);
    for(int i = 3; i<n; i++)
    {
        dp[i][0] = add(dp[i-1][1],dp[i-1][0]);
        dp[i][1] = sub(add(add(add(dp[i-1][0],dp[i-1][0]),dp[i-1][1]),dp[i-2][1]),dp[i-3][1]);
    }
    dp[0][0][0] = 0;
    for(int i = dp[n-1][0].size()-1; i>=0; i--)
        cout << dp[n-1][0][i];
    cout << endl;
}