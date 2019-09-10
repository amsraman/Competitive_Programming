#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("nocross.in");
    ofstream outfile("nocross.out");
    int n;
    infile >> n;
    int s1[n], s2[n], dp, ma[n], mn, ans = 0;
    for(int i = 0; i<n; i++)
    {
        ma[i] = 0;
    }
    for(int i = 0; i<n; i++)
    {
        infile >> s1[i];
    }
    for(int i = 0; i<n; i++)
    {
        infile >> s2[i];
    }
    for(int i = n-1; i>=0; i--)
    {
        mn = 0;
        dp = 0;
        for(int j = n-1; j>=0; j--)
        {
            if(max(s1[i],s2[j])-min(s1[i],s2[j])<=4)
            {
                dp = mn+1;
            }
            mn = max(mn,ma[j]);
            ma[j] = max(ma[j],dp);
            ans = max(ans,dp);
        }
    }
    outfile << ans << endl;
}
