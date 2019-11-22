#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("rental.in");
    ofstream outfile("rental.out");
    int n, m, r;
    infile >> n >> m >> r;
    int c[n], re[r];
    long long val[n];
    pair<int,int> s[m];
    for(int i = 0; i<n; i++)
    {
        infile >> c[i];
        val[i] = 0;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> s[i].second >> s[i].first;
    }
    for(int i = 0; i<r; i++)
    {
        infile >> re[i];
    }
    int counter = 0;
    sort(c,c+n);
    reverse(c,c+n);
    sort(re,re+r);
    reverse(re,re+r);
    sort(s,s+m);
    reverse(s,s+m);
    for(int i = 0; i<m; i++)
    {
        while(s[i].second!=0)
        {
            int t = min(c[counter],s[i].second);
            val[counter]+=t*s[i].first;
            c[counter]-=t;
            s[i].second-=t;
            if(c[counter]==0)
            {
                counter++;
            }
            if(counter==n)
            {
                break;
            }
        }
        if(counter==n)
        {
            break;
        }
    }
    counter = 0;
    long long ans = 0;
    for(int i = n-1; i>=0; i--)
    {
        if((counter==r)||(re[counter]<val[i]))
        {
            ans+=val[i];
        }
        else
        {
            ans+=re[counter];
            counter++;
        }
    }
    outfile << ans << endl;
}
