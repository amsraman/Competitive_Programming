/*
ID: adityasund1
TASK: race3
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, a, ph[51];
vector<int> g[51], v1, v2;
bool w, v[51];

void bfs(int x, int y, bool z)
{
    for(int i = 0; i<=n; i++){v[i] = false;}
    queue<int> q;
    v[y] = true;
    q.push(y);
    while(!q.empty())
    {
        int f = q.front();
        q.pop();
        if(z){ph[f] = 1;}
        else if(ph[f]==1){w = true;}
        for(int i = 0; i<g[f].size(); i++)
        {
            if((g[f][i]!=x)&&(!v[g[f][i]]))
            {
                v[g[f][i]] = true;
                q.push(g[f][i]);
            }
        }
    }
}

int main()
{
    ifstream infile("race3.in");
    ofstream outfile("race3.out");
    while(1)
    {
        infile >> a;
        if(a==-1)
        {
            break;
        }
        while(a!=-2)
        {
            g[n].push_back(a);
            infile >> a;
        }
        n++;
    }
    for(int i = 1; i<n-1; i++)
    {
        bfs(i,0,0);
        if(!v[n-1])
        {
            v1.push_back(i);
        }
    }
    for(int i = 0; i<v1.size(); i++)
    {
        w = false;
        for(int i = 0; i<n; i++){ph[i] = 0;}
        bfs(v1[i],0,1);
        bfs(-1,v1[i],0);
        if(!w)
        {
            v2.push_back(v1[i]);
        }
    }
    outfile << v1.size();
    for(int i = 0; i<v1.size(); i++)
    {
        outfile << " " << v1[i];
    }
    outfile << endl;
    outfile << v2.size();
    for(int i = 0; i<v2.size(); i++)
    {
        outfile << " " << v2[i];
    }
    outfile << endl;
}
