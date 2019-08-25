#include <fstream>
#include <iostream>
#include <vector>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, m, tk, x, y, a, b, c, cnt;
ll ans;
pair<ll,ll> tot[2505], cur[2505], down[1500][2505], up[1500][2505];
vector<int> dist;
vector<pair<int,int> > g[1500];
bool v[1500], used[2505];

ll modx(ll z){return ((z%MOD)+MOD)%MOD;}

void dfs(int z, int prev)
{
    v[z] = true, cnt++;
    for(int i = 0; i<=y; i++)
    {
        cur[i].first = modx(cur[i].first+down[z][i].first);
        cur[i].second = modx(cur[i].second+down[z][i].second);
        if((cur[i].second>0)&&(!used[i])) used[i] = true, dist.push_back(i);
    }
    for(int i = 0; i<g[z].size(); i++)
    {
        if(g[z][i].first!=prev)
        {
            for(int j = 0; j<=y; j++)
            {
                if(down[z][j].second>0)
                {
                    down[g[z][i].first][min(y,j+g[z][i].second)].first = modx(down[g[z][i].first][min(y,j+g[z][i].second)].first+down[z][j].first+modx(ll(g[z][i].second)*down[z][j].second));
                    down[g[z][i].first][min(y,j+g[z][i].second)].second = modx(down[g[z][i].first][min(y,j+g[z][i].second)].second+down[z][j].second);
                }
            }
            dfs(g[z][i].first,z);
            for(int j = 0; j<=y; j++)
            {
                if(up[g[z][i].first][j].second>0)
                {
                    up[z][min(y,j+g[z][i].second)].first = modx(up[z][min(y,j+g[z][i].second)].first+up[g[z][i].first][j].first+modx(ll(g[z][i].second)*up[g[z][i].first][j].second));
                    up[z][min(y,j+g[z][i].second)].second = modx(up[z][min(y,j+g[z][i].second)].second+up[g[z][i].first][j].second);
                    down[z][min(y,j+g[z][i].second)].first = modx(down[z][min(y,j+g[z][i].second)].first+up[g[z][i].first][j].first+modx(ll(g[z][i].second)*up[g[z][i].first][j].second));
                    down[z][min(y,j+g[z][i].second)].second = modx(down[z][min(y,j+g[z][i].second)].second+up[g[z][i].first][j].second);
                }
            }
        }
    }
}

int main()
{
    ifstream infile("mooriokart.in");
    ofstream outfile("mooriokart.out");
    infile >> n >> m >> x >> y;
    tk = n-m;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b >> c;
        g[a-1].push_back({b-1,c});
        g[b-1].push_back({a-1,c});
    }
    for(int i = 0; i<n; i++) down[i][0] = up[i][0] = {0,1};
    tot[0] = {0,1};
    for(int i = 0; i<n; i++)
    {
        if(!v[i])
        {
            pair<ll,ll> temp[y+1];
            used[0] = false, cur[0] = {0,0}, cnt = 0;
            for(int j = 1; j<=y; j++) cur[j] = {0,0}, used[j] = false;
            dfs(i,i);
            cur[0].second-=cnt;
            for(int j = 0; j<=y; j++)
            {
                for(int l = 0; l<dist.size(); l++)
                {
                    int k = dist[l];
                    temp[min(y,j+k)] = {modx(temp[min(y,j+k)].first+modx(tot[j].first*cur[k].second+tot[j].second*cur[k].first)),modx(temp[min(y,j+k)].second+modx(tot[j].second*cur[k].second))};
                }
            }
            dist.clear();
            for(int j = 0; j<=y; j++) tot[j] = temp[j];
        }
    }
    for(int i = y; i>=0; i--)
    {
        if(i+tk*x>=y) ans = modx(ans+tot[i].first+modx(ll(tk*x))*(tot[i].second));
    }
    for(int i = 0; i<tk-1; i++) ans = modx(ans*2*ll(i+1));
    outfile << ans << endl;
}
