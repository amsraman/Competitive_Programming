#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, in[100002], ans;
vector<int> g[100001], vec;
bool v[100001], v2[100001], cyc;

void dfs(int a, int b)
{
    v2[a] = true;
    ans = max(ans,b);
    for(int i = 0; i<g[a].size(); i++)
    {
        if(!v2[g[a][i]])
        {
            dfs(g[a][i],b+1);
        }
    }
}

int main()
{
    ifstream infile("art2.in");
    ofstream outfile("art2.out");
    infile >> n;
    in[0] = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i+1];
    }
    in[n+1] = 0;
    for(int i = 0; i<=n+1; i++)
    {
        if((!v[in[i]])&&(in[i+1]!=in[i]))
        {
            vec.push_back(in[i]);
            v[in[i]] = true;
        }
        else if((v[in[i]])&&((in[i+1]!=in[i])||(i==n+1)))
        {
            while(vec[vec.size()-1]!=in[i])
            {
                g[in[i]].push_back(vec[vec.size()-1]);
                vec.pop_back();
                if(vec.size()==0)
                {
                    cyc = true;
                    break;
                }
            }
        }
    }
    dfs(0,0);
    if(cyc)
    {
        outfile << -1 << endl;
    }
    else
    {
        outfile  << ans << endl;
    }
}
