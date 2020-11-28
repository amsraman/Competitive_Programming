#include <iostream>
#include <fstream>

using namespace std;

int t, n, x[50], y[50], r, c, ans;

int main()
{
    ifstream fin("fighting_the_zombies.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        ans = 0;
        fin >> n >> r;
        for(int i = 0; i<n; i++)
        {
            fin >> x[i] >> y[i];
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                for(int k = 0; k<n; k++)
                {
                    for(int l = 0; l<n; l++)
                    {
                        if((x[j]>=x[i])&&(x[j]-x[i]<=r)&&(y[j]>=y[i])&&(y[j]-y[i]<=r)&&(x[l]>=x[k])&&(x[l]-x[k]<=r)&&(y[l]>=y[k])&&(y[l]-y[k]<=r))
                        {
                            c = 0;
                            for(int m = 0; m<n; m++)
                            {
                                if(((x[m]-x[i]<=r)&&(x[m]>=x[i])&&(y[j]-y[m]<=r)&&(y[j]>=y[m]))||((x[m]-x[k]<=r)&&(x[m]>=x[k])&&(y[l]-y[m]<=r)&&(y[l]>=y[m])))
                                {
                                    c++;
                                }
                            }
                            ans = max(ans,c);
                        }
                    }
                }
            }
        }
        fout << "Case #" << z+1 << ": " << ans << endl;
    }
}
