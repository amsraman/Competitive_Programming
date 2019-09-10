/*
ID: adityasund1
LANG: C++
TASK: holstein
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int v, g, ans = 16, zc, c = 0;
int vc[25], val[15][25];
vector<int> se;
vector<int> fs;

int s(int k)
{
    if(k==0)
    {
        zc = 0;
        for(int i = 0; i<v; i++)
        {
            if(vc[i]<=0)
            {
                zc++;
            }
        }
        if(zc==v)
        {
            if(c<ans)
            {
                ans = c;
                fs.erase(fs.begin(),fs.begin()+fs.size());
                for(int i = 0; i<ans; i++)
                {
                    fs.push_back(se[i]);
                }
            }
        }
    }
    else
    {
        s(k-1);
        c++;
        se.push_back(k);
        for(int i = 0; i<v; i++)
        {
            vc[i]-=val[k-1][i];
        }
        s(k-1);
        se.pop_back();
        c--;
        for(int i = 0; i<v; i++)
        {
            vc[i]+=val[k-1][i];
        }
    }
}

int main()
{
    ifstream infile("holstein.in");
    ofstream outfile("holstein.out");
    infile >> v;
    for(int i = 0; i<v; i++)
    {
        infile >> vc[i];
    }
    infile >> g;
    for(int i = 0; i<g; i++)
    {
        for(int j = 0; j<v; j++)
        {
            infile >> val[i][j];
        }
    }
    s(g);
    sort(fs.begin(),fs.end());
    outfile << ans;
    for(int i = 0; i<ans; i++)
    {
        outfile << " " << fs[i];
    }
    outfile << endl;
}
