#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, q, d[100000], par[100000][17], root, sz[100000];
pair<int,int> rg[100000];
vector<int> nxt[100000];

void dfs(int x)
{
    sz[x] = 1;
    for(int i = 0; i<nxt[x].size(); i++)
        dfs(nxt[x][i]), sz[x]+=sz[nxt[x][i]];
}

int qry(int x, int k)
{
    for(int i = 16; i>=0; i--)
        if(sz[par[x][i]]<k)
            x = par[x][i];
    return x;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> q;
        for(int i = 0; i<n-1; i++)
            cin >> d[i];
        stack<int> ind1, ind2;
        for(int i = 0; i<n; i++)
        {
            while((!ind1.empty())&&(d[ind1.top()]<d[i]))
                ind1.pop();
            rg[i].f = (ind1.empty()?-1:ind1.top());
            ind1.push(i);
        }
        for(int i = n-1; i>=0; i--)
        {
            while((!ind2.empty())&&(d[ind2.top()]<d[i]))
                ind2.pop();
            rg[i].s = (ind2.empty()?n-1:ind2.top());
            ind2.push(i);
        }
        for(int i = 0; i<n-1; i++)
        {
            if((rg[i].f!=-1)&&((rg[i].s==n-1)||(d[rg[i].f]<d[rg[i].s])))
                par[i][0] = rg[i].f, nxt[rg[i].f].push_back(i);
            else if(rg[i].s!=n-1)
                par[i][0] = rg[i].s, nxt[rg[i].s].push_back(i);
            else
                par[i][0] = i, root = i;
        }
        for(int j = 1; j<17; j++)
            for(int i = 0; i<n; i++)
                par[i][j] = par[par[i][j-1]][j-1];
        dfs(root);
        cout << "Case #" << _ << ": ";
        for(int i = 0, s, k; i<q; i++)
        {
            cin >> s >> k;
            if(k==1)
            {
                cout << s << " ";
                continue;
            }
            s--, k--;
            bool flag = false;
            if((s==n-1)||((s>0)&&(d[s-1]<d[s])))
                flag = true, s--;
            if(sz[s]>=k)
            {
                if(!flag)
                    cout << s+k+1 << " ";
                else
                    cout << s-k+2 << " ";
            }
            else
            {
                s = qry(s,k);
                if(s<par[s][0])
                    cout << par[s][0]+(k-sz[s])+1 << " ";
                else
                    cout << par[s][0]-(k-sz[s])+2 << " ";
            }
        }
        cout << endl;
        for(int i = 0; i<n-1; i++)
            nxt[i].clear();
    }
}
