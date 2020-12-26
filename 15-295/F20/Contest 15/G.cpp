#include <bits/stdc++.h>

using namespace std;

int c, n, m;
set<pair<int,int>> edges;
vector<int> ans;

int main()
{
    cin >> c;
    while(c--)
    {
        cin >> n >> m;
        for(int i = 0, u, v; i<m; i++)
        {
            cin >> u >> v;
            edges.insert({u,v});
        }
        for(int i = 0; i<n; i++)
        {
            ans.push_back(i+1);
            for(int j = i; (j>0&&edges.count({ans[j-1],ans[j]})); j--)
                swap(ans[j-1],ans[j]);
        }
        for(int x: ans)
            cout << x << " ";
        cout << endl;
        edges.clear();
        ans.clear();
    }
}