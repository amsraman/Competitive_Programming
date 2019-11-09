/*
ID: adityasund1
TASK: concom
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, con[100][100] = {0};
vector<pair<int,int> > g[100];
bool v[100][100] = {false};

void dfs(int a, int b)
{
    v[a][b] = true;
    for(int i = 0; i<g[b].size(); i++)
    {
        con[a][g[b][i].first]+=g[b][i].second;
        if((con[a][g[b][i].first]>50)&&(!v[a][g[b][i].first]))
        {
            dfs(a,g[b][i].first);
        }
    }
}

int main()
{
    ifstream infile("concom.in");
    ofstream outfile("concom.out");
    infile >> n;
    int a, b, c;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b >> c;
        g[a-1].push_back({b-1,c});
    }
    for(int i = 0; i<100; i++)
    {
        dfs(i,i);
    }
    for(int i = 0; i<100; i++)
    {
        for(int j = 0; j<100; j++)
        {
            if((v[i][j])&&(i!=j))
            {
                outfile << i+1 << " " << j+1 << endl;
            }
        }
    }
}
