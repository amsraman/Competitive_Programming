#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("slowdown.in");
    ofstream outfile("slowdown.out");
    vector<int> dist;
    vector<int> tim;
    double d = 0, t = 0, s = 1;
    char c;
    int n, a, cd = 0, ct = 0;
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> c >> a;
        if(c=='D')
        {
            dist.push_back(a);
        }
        else
        {
            tim.push_back(a);
        }
    }
    sort(dist.begin(),dist.end());
    dist.push_back(INF);
    sort(tim.begin(),tim.end());
    tim.push_back(INF);
    while(d<1000)
    {
        if((cd==dist.size()-1)&&(ct==tim.size()-1))
        {
            break;
        }
        if((d+double(tim[ct]-t)/s>dist[cd])&&(cd<dist.size())&&(ct<tim.size()))
        {
            t+=(dist[cd]-d)*s;
            d = dist[cd];
            cd++;
            s++;
        }
        else
        {
            d+=double(tim[ct]-t)/s;
            t = tim[ct];
            ct++;
            s++;
        }
    }
    if(d<1000)
    {
        t+=(1000-d)*s;
    }
    if(d>1000)
    {
        s--;
        t-=(d-1000)*s;
    }
    outfile << int(t+0.5) << endl;
}
