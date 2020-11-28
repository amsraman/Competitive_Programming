#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 0xfffffffffffffff

using namespace std;

int main()
{
    ifstream infile("cowroute.in");
    ofstream outfile("cowroute.out");
    int a, b, n;
    long long cn[1000], pn[1000];
    for(int i = 0; i<1000; i++){cn[i] = pn[i] = INF;}
    bool v[1000] = {false};
    vector<pair<pair<int,int>,int> > g[1000];
    infile >> a >> b >> n;
    for(int i = 0; i<n; i++)
    {
        int c, k;
        infile >> c >> k;
        int ar[k];
        for(int j = 0; j<k; j++)
        {
            infile >> ar[j];
        }
        for(int j = 0; j<k; j++)
        {
            for(int l = j+1; l<k; l++)
            {
                g[ar[j]-1].push_back({{c,l-j},ar[l]-1});
            }
        }
    }
    priority_queue<pair<pair<long long,int>,int> > q;
    q.push({{0,0},a-1});
    cn[a-1] = pn[a-1] = 0;
    while(!q.empty())
    {
        int pos = q.top().second;
        q.pop();
        if(!v[pos])
        {
            v[pos] = true;
            for(int i = 0; i<g[pos].size(); i++)
            {
                if((!v[g[pos][i].second])&&((cn[pos]+g[pos][i].first.first<cn[g[pos][i].second])||((cn[pos]+g[pos][i].first.first==cn[g[pos][i].second])&&(pn[pos]+g[pos][i].first.second<pn[g[pos][i].second]))))
                {
                    cn[g[pos][i].second] = cn[pos]+g[pos][i].first.first;
                    pn[g[pos][i].second] = pn[pos]+g[pos][i].first.second;
                    q.push({{-cn[g[pos][i].second],-pn[g[pos][i].second]},g[pos][i].second});
                }
            }
        }
    }
    if(!v[b-1])
    {
        outfile << -1 << " " << -1 << endl;
    }
    else
    {
        outfile << cn[b-1] << " " << pn[b-1] << endl;
    }
}
