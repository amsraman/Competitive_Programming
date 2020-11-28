#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("lazy.in");
    ofstream outfile("lazy.out");
    int n, k;
    infile >> n >> k;
    int ar[2*n-1][2*n-1];
    for(int i = 0; i<2*n-1; i++)
    {
        for(int j = 0; j<2*n-1; j++)
        {
            ar[i][j] = 0;
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> ar[n-1+j-i][j+i];
        }
    }
    int pre[2*n][2*n];
    for(int i = 0; i<2*n; i++)
    {
        for(int j = 0; j<2*n; j++)
        {
            pre[i][j] = 0;
            if(i>0)
            {
                pre[i][j]+=pre[i-1][j];
            }
            if(j>0)
            {
                pre[i][j]+=pre[i][j-1];
            }
            if((i>0)&&(j>0))
            {
                pre[i][j]+=ar[i-1][j-1];
                pre[i][j]-=pre[i-1][j-1];
            }
        }
    }
    int ans = 0;
    for(int i = 0; i<2*n; i++)
    {
        for(int j = 0; j<2*n; j++)
        {
            ans = max(ans,pre[min(i+2*k+1,2*n-1)][min(j+2*k+1,2*n-1)]-pre[min(i+2*k+1,2*n-1)][j]-pre[i][min(j+2*k+1,2*n-1)]+pre[i][j]);
        }
    }
    outfile << ans << endl;
}
