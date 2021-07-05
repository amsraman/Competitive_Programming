#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int l, m;
string name[100];
vector<pair<array<int,4>,string>> mowers;

bool works(int ind)
{
    ll tmp = 10080, c = mowers[ind].f[1], t = mowers[ind].f[2], r = mowers[ind].f[3];
    for(int i = 1; i<=10080; i++, tmp+=10080)
    {
        ll time_mowing = t*(tmp/(r+t))+min(t,tmp%(r+t));
        if(c*time_mowing<(ll)l*i)
            return false;
    }
    return true;
}

void solve()
{ 
    int cur_min = 0x3f3f3f3f;
    vector<string> ans;
    for(int i = 0; i<m; i++)
    {
        if(works(i)&&(mowers[i].f)[0]<cur_min)
        {
            ans.clear();
            ans.push_back(mowers[i].s);
            cur_min = (mowers[i].f)[0];
        }
        else if(works(i)&&(mowers[i].f)[0]==cur_min)
            ans.push_back(mowers[i].s);
    }
    if(ans.empty())
    {
        cout << "no such mower" << endl;
        return;
    }
    for(string i: ans)
        cout << i << endl;
}

int main()
{
    cin >> l >> m;
    cin.ignore();
    for(int i = 0, tmp[4]; i<m; i++)
    {
        getline(cin,name[i]);
        for(int j = 0; j<4; j++)
        {
            int ptr = name[i].length()-1;
            while(name[i][ptr]!=',')
                --ptr;
            tmp[j] = atoi(name[i].substr(ptr+1,name[i].length()-ptr-1).c_str());
            name[i] = name[i].substr(0,ptr);
        }
        mowers.push_back({{tmp[3],tmp[2],tmp[1],tmp[0]},name[i]});
    }
    solve();
}