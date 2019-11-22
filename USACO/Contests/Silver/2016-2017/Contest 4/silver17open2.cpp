#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("cownomics.in");
    ofstream outfile("cownomics.out");
    int n, m, ans = 0;
    infile >> n >> m;
    string sp[n], pl[n];
    bool v[64];
    for(int i = 0; i<n; i++)
    {
        infile >> sp[i];
    }
    for(int i = 0; i<n; i++)
    {
        infile >> pl[i];
    }
    for(int i = 0; i<m; i++)
    {
        for(int j = i+1; j<m; j++)
        {
            for(int k = j+1; k<m; k++)
            {
                for(int l = 0; l<64; l++)
                {
                    v[l] = false;
                }
                for(int l = 0; l<n; l++)
                {
                    int w, x, y, z = 0;
                    if(sp[l][i]=='A'){w = 0;}
                    if(sp[l][i]=='T'){w = 1;}
                    if(sp[l][i]=='C'){w = 2;}
                    if(sp[l][i]=='G'){w = 3;}
                    if(sp[l][j]=='A'){x = 0;}
                    if(sp[l][j]=='T'){x = 1;}
                    if(sp[l][j]=='C'){x = 2;}
                    if(sp[l][j]=='G'){x = 3;}
                    if(sp[l][k]=='A'){y = 0;}
                    if(sp[l][k]=='T'){y = 1;}
                    if(sp[l][k]=='C'){y = 2;}
                    if(sp[l][k]=='G'){y = 3;}
                    z = w*16+x*4+y;
                    v[z] = true;
                }
                for(int l = 0; l<n; l++)
                {
                    int w, x, y, z = 0;
                    if(pl[l][i]=='A'){w = 0;}
                    if(pl[l][i]=='T'){w = 1;}
                    if(pl[l][i]=='C'){w = 2;}
                    if(pl[l][i]=='G'){w = 3;}
                    if(pl[l][j]=='A'){x = 0;}
                    if(pl[l][j]=='T'){x = 1;}
                    if(pl[l][j]=='C'){x = 2;}
                    if(pl[l][j]=='G'){x = 3;}
                    if(pl[l][k]=='A'){y = 0;}
                    if(pl[l][k]=='T'){y = 1;}
                    if(pl[l][k]=='C'){y = 2;}
                    if(pl[l][k]=='G'){y = 3;}
                    z = w*16+x*4+y;
                    if(v[z])
                    {
                        ans--;
                        break;
                    }
                }
                ans++;
            }
        }
    }
    outfile << ans << endl;
}
