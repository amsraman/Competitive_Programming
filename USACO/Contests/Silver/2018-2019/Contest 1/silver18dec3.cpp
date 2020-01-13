#include <fstream>
#include <iostream>

using namespace std;

int n, k, ar[100][10], group[100][10], gn, gc[1000], maxg = 10001, minz[10];

void dfs(int a, int b, int g)
{
    gc[g]++;
    group[a][b] = g;
    if((a>0)&&(ar[a-1][b]==ar[a][b])&&(group[a-1][b]==-1)){dfs(a-1,b,g);}
    if((b>0)&&(ar[a][b-1]==ar[a][b])&&(group[a][b-1]==-1)){dfs(a,b-1,g);}
    if((a<n-1)&&(ar[a+1][b]==ar[a][b])&&(group[a+1][b]==-1)){dfs(a+1,b,g);}
    if((b<9)&&(ar[a][b+1]==ar[a][b])&&(group[a][b+1]==-1)){dfs(a,b+1,g);}
}

int main()
{
    ifstream infile("mooyomooyo.in");
    ofstream outfile("mooyomooyo.out");
    infile >> n >> k;
    char z;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<10; j++)
        {
            infile >> z;
            ar[i][j] = z-'0';
        }
    }
    while(maxg>=k)
    {
        maxg = gn = 0;
        for(int i = 0; i<1000; i++)
        {
            gc[i] = 0;
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<10; j++)
            {
                group[i][j] = minz[j] = -1;
            }
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<10; j++)
            {
                if((group[i][j]==-1)&&(ar[i][j]!=0))
                {
                    dfs(i,j,gn);
                    gn++;
                    maxg = max(maxg,gc[gn-1]);
                }
            }
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<10; j++)
            {
                if(gc[group[i][j]]>=k)
                {
                    ar[i][j] = 0;
                }
            }
        }
        for(int i = n-1; i>=0; i--)
        {
            for(int j = 0; j<10; j++)
            {
                if(ar[i][j]!=0)
                {
                    minz[j] = -1;
                    for(int k = 0; k<n; k++)
                    {
                        if(ar[k][j]==0)
                        {
                            minz[j] = max(minz[j],k);
                        }
                    }
                    if((minz[j]!=-1)&&(minz[j]>i))
                    {
                        ar[minz[j]][j] = ar[i][j];
                        ar[i][j] = 0;
                    }
                }
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<10; j++)
        {
            outfile << ar[i][j];
        }
        outfile << endl;
    }
}
