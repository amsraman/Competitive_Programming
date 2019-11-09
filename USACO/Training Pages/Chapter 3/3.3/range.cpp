/*
ID: adityasund1
TASK: range
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    ifstream infile("range.in");
    ofstream outfile("range.out");
    int n, ans;
    infile >> n;
    int pre[251][251] = {0};
    string a;
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        for(int j = 0; j<n; j++)
        {
            pre[i+1][j+1] = pre[i][j+1]+pre[i+1][j]-pre[i][j]+(a[j]-'0');
        }
    }
    for(int i = 2; i<=n; i++)
    {
        ans = 0;
        for(int j = i; j<=n; j++)
        {
            for(int k = i; k<=n; k++)
            {
                if(pre[j][k]-pre[j-i][k]-pre[j][k-i]+pre[j-i][k-i]==i*i)
                {
                    ans++;
                }
            }
        }
        if(ans!=0)
        {
            outfile << i << " " << ans << endl;
        }
    }
}
