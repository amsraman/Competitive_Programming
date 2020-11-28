#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int t, k, n, a, b, tot, up[2000], down[2000], ans[2000];
vector<int> g[2000], pre, post;
bool v[2000];

void fpre(int a)
{
    pre.push_back(a);
    for(int i = 0; i<g[a].size(); i++) fpre(g[a][i]);
}

void fpost(int a)
{
    for(int i = 0; i<g[a].size(); i++) fpost(g[a][i]);
    post.push_back(a);
}

void dfs(int a)
{
    v[a] = true, ans[a] = (tot%k)+1;
    if(!v[up[a]]) dfs(up[a]);
    if(!v[down[a]]) dfs(down[a]);
}

int main()
{
    ifstream fin("ethan_traverses_a_tree.txt");
    ofstream fout("out.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> k;
        for(int i = 0; i<n; i++)
        {
            fin >> a >> b;
            if(a!=0) g[i].push_back(a-1);
            if(b!=0) g[i].push_back(b-1);
        }
        fpre(0), fpost(0);
        for(int i = 0; i<n; i++) up[pre[i]] = post[i], down[post[i]] = pre[i];
        for(int i = 0; i<n; i++)
        {
            if(!v[i])
            {
                tot++;
                dfs(i);
            }
        }
        if(tot<k)
        {
            fout << "Case #" << z+1 << ": Impossible" << endl;
        }
        else
        {
            fout << "Case #" << z+1 << ": ";
            for(int i = 0; i<n; i++)
            {
                fout << ans[i] << " ";
            }
            fout << endl;
        }
        pre.clear(), post.clear(), tot = 0;
        for(int i = 0; i<n; i++) v[i] = false, g[i].clear();
    }
}
