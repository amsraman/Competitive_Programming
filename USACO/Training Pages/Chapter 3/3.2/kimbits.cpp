/*
ID: adityasund1
TASK: kimbits
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

long long co[32][32] = {0};
string ans;

void solve(int a, int b, unsigned long long k)
{
    if(a==0)
    {
        return;
    }
    if(co[a-1][min(b,a-1)]>=k)
    {
        ans+="0";
        solve(a-1,b,k);
    }
    else
    {
        ans+="1";
        solve(a-1,b-1,k-co[a-1][min(b,a-1)]);
    }
}

int main()
{
    ifstream infile("kimbits.in");
    ofstream outfile("kimbits.out");
    int n, l;
    unsigned long long k;
    infile >> n >> l >> k;
    co[0][0] = co[1][0] = co[1][1] = 1;
    for(int i = 2; i<=n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            co[i][j] = co[i-1][j];
            if(j!=0)
            {
                co[i][j]+=co[i-1][j-1];
            }
        }
    }
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j!=0)
            {
                co[i][j]+=co[i][j-1];
            }
        }
    }
    solve(n,l,k);
    outfile << ans << endl;
}
