/*
ID: adisund1
LANG: C++
TASK: milk
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int n, m, total = 0, ans = 0;
    ifstream infile("milk.in");
    ofstream outfile("milk.out");
    infile >> n >> m;
    int cost[m], num[m];
    int ma = 0, ml;
    for(int i = 0; i<m; i++)
    {
        infile >> cost[i] >> num[i];
        ma = max(ma,cost[i]);
        if(ma==cost[i])
        {
            ml = i;
        }
    }
    int d;
    while(total<n)
    {
        d = ml;
        for(int i = 0; i<m; i++)
        {
            if((cost[i]<cost[d])&&(num[i]!=0))
            {
                d = i;
            }
        }
        if(total+num[d]<n)
        {
            ans = ans+num[d]*cost[d];
        }
        else
        {
            ans = ans+(n-total)*cost[d];
        }
        total = total+num[d];
        if(total<n)
        {
            num[d] = 0;
        }
    }
    outfile << ans << endl;
}
