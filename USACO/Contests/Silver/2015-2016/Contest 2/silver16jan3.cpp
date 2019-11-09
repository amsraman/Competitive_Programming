#include <fstream>
#include <iostream>

using namespace std;

bool v[2000][2000], hw[2000][2000], vw[2000][2000];
int maxa, maxb, mina = 2000, minb = 2000;

void dfs(int a, int b)
{
    v[a][b] = true;
    if(((!(vw[a][b]))&&(a>mina))&&(!v[a-1][b]))
    {
        dfs(a-1,b);
    }
    if(((!(hw[a][b+1]))&&(b<maxb-1))&&(!v[a][b+1]))
    {
        dfs(a,b+1);
    }
    if(((!(vw[a+1][b]))&&(a<maxa-1))&&(!v[a+1][b]))
    {
        dfs(a+1,b);
    }
    if(((!(hw[a][b]))&&(b>minb))&&(!v[a][b-1]))
    {
        dfs(a,b-1);
    }
}

int main()
{
    ifstream infile("gates.in");
    ofstream outfile("gates.out");
    int n;
    string in;
    infile >> n >> in;
    int pos[2] = {1000,1000};
    for(int i = 0; i<n; i++)
    {
        if(in[i]=='N')
        {
            vw[pos[0]][pos[1]] = true;
            pos[1]++;
        }
        else if(in[i]=='S')
        {
            pos[1]--;
            vw[pos[0]][pos[1]] = true;
        }
        else if(in[i]=='E')
        {
            hw[pos[0]][pos[1]] = true;
            pos[0]++;
        }
        else if(in[i]=='W')
        {
            pos[0]--;
            hw[pos[0]][pos[1]] = true;
        }
        maxa = max(maxa,pos[0]);
        maxb = max(maxb,pos[1]);
        mina = min(mina,pos[0]);
        minb = min(minb,pos[1]);
    }
    maxa+=1;
    maxb+=1;
    mina-=1;
    minb-=1;
    int ans = 0;
    for(int i = mina; i<maxa; i++)
    {
        for(int j = minb; j<maxb; j++)
        {
            if(!v[i][j])
            {
                dfs(i,j);
                ans++;
            }
        }
    }
    outfile << ans-1 << endl;
}
