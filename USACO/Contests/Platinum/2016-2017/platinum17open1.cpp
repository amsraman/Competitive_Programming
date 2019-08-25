#include <fstream>
#include <iostream>

using namespace std;

int n, in[1000][1000], pre[1001][1001], minx[1000001], miny[1000001], maxx[1000001], maxy[1000001], usedc, ans;
bool used[1000001], impos[1000001];

int main()
{
    ifstream infile("art.in");
    ofstream outfile("art.out");
    for(int i = 0; i<1000001; i++) minx[i] = miny[i] = 0x3f3f3f3f;
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> in[i][j];
            minx[in[i][j]] = min(minx[in[i][j]],i);
            maxx[in[i][j]] = max(maxx[in[i][j]],i);
            miny[in[i][j]] = min(miny[in[i][j]],j);
            maxy[in[i][j]] = max(maxy[in[i][j]],j);
            if((!used[in[i][j]])&&(in[i][j]!=0)) usedc++;
            used[in[i][j]] = true;
        }
    }
    for(int i = 1; i<=n*n; i++)
    {
        if(used[i])
        {
            pre[minx[i]][miny[i]]++;
            pre[maxx[i]+1][maxy[i]+1]++;
            pre[minx[i]][maxy[i]+1]--;
            pre[maxx[i]+1][miny[i]]--;
        }
    }
    for(int i = 0; i<=n; i++)
    {
        for(int j = 1; j<=n; j++)
        {
            pre[i][j]+=pre[i][j-1];
        }
    }
    for(int i = 0; i<=n; i++)
    {
        for(int j = 1; j<=n; j++)
        {
            pre[j][i]+=pre[j-1][i];
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(pre[i][j]>1)
            {
                impos[in[i][j]] = true;
            }
        }
    }
    for(int i = 1; i<=n*n; i++)
    {
        if(impos[i]) ans++;
    }
    ans = (usedc==1)?(n*n-1):(n*n-ans);
    outfile << ans << endl;
}
