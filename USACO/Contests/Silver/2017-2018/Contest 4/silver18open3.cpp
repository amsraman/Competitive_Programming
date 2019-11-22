#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
int n, rc = 0;
int id[250][250], group[250][250], idg[62500], gco[62500];
bool v[250][250] = {false};
vector<int> g[62500];
map<pair<pair<int,int>,int>,bool> m;

void dfs(int a, int b, int &c, int d)
{
    if(v[a][b])
    {
        return;
    }
    v[a][b] = true;
    group[a][b] = d;
    c++;
    if((a<n-1)&&(id[a+1][b]==id[a][b]))
    {
        dfs(a+1,b,c,d);
    }
    if((b<n-1)&&(id[a][b+1]==id[a][b]))
    {
        dfs(a,b+1,c,d);
    }
    if((a>0)&&(id[a-1][b]==id[a][b]))
    {
        dfs(a-1,b,c,d);
    }
    if((b>0)&&(id[a][b-1]==id[a][b]))
    {
        dfs(a,b-1,c,d);
    }
}

void dfs2(int a, int b, int c, int &s)
{
    s+=gco[c];
    for(int i = 0; i<g[c].size(); i++)
    {
        if((!m.count({{min(a,b),max(a,b)},g[c][i]}))&&((idg[g[c][i]]==a)||(idg[g[c][i]]==b)))
        {
            m[{{min(a,b),max(a,b)},g[c][i]}] = true;
            dfs2(a,b,g[c][i],s);
        }
    }
}

int main()
{
    ifstream infile("multimoo.in");
    ofstream outfile("multimoo.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> id[i][j];
        }
    }
    int co, ans1 = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(!v[i][j])
            {
                co = 0;
                dfs(i,j,co,rc);
                idg[rc] = id[i][j];
                gco[rc] = co;
                rc++;
                ans1 = max(ans1,co);
            }
        }
    }
    map<pair<int,int>,bool> paired;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if((i>0)&&!(paired.count({group[i][j],group[i-1][j]}))&&(id[i-1][j]!=id[i][j]))
            {
                paired[{group[i][j],group[i-1][j]}] = true;
                g[group[i][j]].push_back(group[i-1][j]);
            }
            if((i<n-1)&&!(paired.count({group[i][j],group[i+1][j]}))&&(id[i+1][j]!=id[i][j]))
            {
                paired[{group[i][j],group[i+1][j]}] = true;
                g[group[i][j]].push_back(group[i+1][j]);
            }
            if((j>0)&&!(paired.count({group[i][j],group[i][j-1]}))&&(id[i][j-1]!=id[i][j]))
            {
                paired[{group[i][j],group[i][j-1]}] = true;
                g[group[i][j]].push_back(group[i][j-1]);
            }
            if((j<n-1)&&!(paired.count({group[i][j],group[i][j+1]}))&&(id[i][j+1]!=id[i][j]))
            {
                paired[{group[i][j],group[i][j+1]}] = true;
                g[group[i][j]].push_back(group[i][j+1]);
            }
        }
    }
    int s, ans2 = 0;
    for(int i = 0; i<rc; i++)
    {
        for(int j = 0; j<g[i].size(); j++)
        {
            if(!m.count({{min(idg[i],idg[g[i][j]]),max(idg[i],idg[g[i][j]])},i}))
            {
                s = 0;
                m[{{min(idg[i],idg[g[i][j]]),max(idg[i],idg[g[i][j]])},i}] = true;
                dfs2(idg[i],idg[g[i][j]],i,s);
                ans2 = max(s,ans2);
            }
        }
    }
   outfile << ans1 << endl << ans2 << endl;
}
