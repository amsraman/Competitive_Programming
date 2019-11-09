/*
ID: adityasund1
TASK: rockers
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, t, m, ar[20], ans = 0;
vector<int> v;

void gen(int a)
{
    if(a==n)
    {
        int cur = 0, cdc = 0, k = v.size();
        for(int i = 0; i<k; i++)
        {
            if((v[i]>t)||(cdc==m))
            {
                return;
            }
            if(cur+v[i]<=t)
            {
                cur+=v[i];
            }
            else
            {
                cdc++;
                if(cdc==m)
                {
                    return;
                }
                cur = v[i];
            }
        }
        ans = max(ans,k);
        return;
    }
    v.push_back(ar[a]);
    gen(a+1);
    v.pop_back();
    gen(a+1);
}

int main()
{
    ifstream infile("rockers.in");
    ofstream outfile("rockers.out");
    infile >> n >> t >> m;
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
    }
    gen(0);
    outfile << ans << endl;
}
