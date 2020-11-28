#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int n, b;
int breed[20], value[100001];
bool vi[100001] = {false};

int solve(int a)
{
    if(a<0)
    {
        return INF;
    }
    else if(a==0)
    {
        return 0;
    }
    else if(vi[a])
    {
        return value[a];
    }
    else
    {
        int ret = INF;
        for(int i = 0; i<b; i++)
        {
            ret = min(ret,solve(a-breed[i])+1);
        }
        return ret;
    }
}

int main()
{
    ifstream infile("mooomoo.in");
    ofstream outfile("mooomoo.out");
    infile >> n >> b;
    for(int i = 0; i<b; i++)
    {
        infile >> breed[i];
    }
    int in[n], maxv = 0, ans = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int i = n-1; i>=1; i--)
    {
        if(in[i-1]!=0)
        {
            in[i]-=(in[i-1]-1);
        }
        maxv = max(maxv,in[i]);
    }
    for(int i = 0; i<=maxv; i++)
    {
        value[i] = solve(i);
        vi[i] = true;
    }
    for(int i = 0; i<n; i++)
    {
        if(value[in[i]]>=INF)
        {
            outfile << -1 << endl;
            return 0;
        }
        ans+=value[in[i]];
    }
    outfile << ans << endl;
}
