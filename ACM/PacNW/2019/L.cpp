#include <bits/stdc++.h>

using namespace std;

int len;
string n;
vector<int> ans;

bool works()
{
    for(int i = 0; i<len; i++)
    {
        int cur = 0;
        for(int j = max(0,i-((int)ans.size()-1)); j<=min((int)ans.size()-1,i); j++)
            cur = (cur+ans[j]*ans[i-j])%10;
        if(cur!=(n[i]-'0'))
            return false;
    }
    return true;
}

bool try_pos(int x)
{
    if(x==(len+1)/2)
        return works();
    for(int i = 0; i<10; i++)
    {
        ans.push_back(i);
        int cur = 0;
        for(int i = 0; i<ans.size(); i++)
            cur = (cur+ans[i]*ans[ans.size()-i-1])%10;
        if(cur==(n[x]-'0')&&try_pos(x+1))
            return true;
        ans.pop_back();
    }
    return false;
}

int main()
{
    cin >> n;
    len = n.length();
    if(try_pos(0))
        for(int i: ans)
            cout << i;
    else
        cout << -1;
    cout << endl;
}