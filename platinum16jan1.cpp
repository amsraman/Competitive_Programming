#include <fstream>
#include <iostream>

using namespace std;

int n, m, pre[200][201], ans = 1;
char z;

int main()
{
    ifstream infile("fortmoo.in");
    ofstream outfile("fortmoo.out");
    infile >> n >> m;
    for(int i = 0; i<n; i++)
    {
        for(int j = 1; j<=m; j++)
        {
            infile >> z;
            pre[i][j] = pre[i][j-1];
            if(z=='X') pre[i][j]++;
        }
    }
    for(int i = 0; i<m; i++)
    {
        for(int j = i; j<m; j++)
        {
            int rec = 1000;
            for(int k = 0; k<n; k++)
            {
                if(pre[k][j+1]-pre[k][i]==0)
                {
                    rec = min(rec,k);
                }
                if((pre[k][i+1]!=pre[k][i])||(pre[k][j+1]!=pre[k][j]))
                {
                    rec = 1000;
                }
                if((rec!=1000)&&(pre[k][j+1]-pre[k][i]==0))
                {
                    ans = max(ans,(j-i+1)*(k-rec+1));
                }
            }
        }
    }
    outfile << ans << endl;
}
