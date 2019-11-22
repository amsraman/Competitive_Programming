#include <fstream>
#include <iostream>

using namespace std;

int n, in[100000], ans = 0;
int v[100000] = {0};

void dfs(int a)
{
    int z = a;
    while(v[z]==0)
    {
        v[z] = a+1;
        z = in[z];
    }
    if(v[z]!=v[a])
    {
        return;
    }
    while(v[z]==a+1)
    {
        v[z] = -1;
        z = in[z];
    }
}

int main()
{
    ifstream infile("shuffle.in");
    ofstream outfile("shuffle.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        in[i]--;
    }
    for(int i = 0; i<n; i++)
    {
        if(v[i]==0)
        {
            dfs(i);
        }
        if(v[i]==-1)
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
