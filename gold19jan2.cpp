#include <fstream>
#include <iostream>

using namespace std;

int n, in[100000], bit[100001], ans = 1;

int sum(int k)
{
    int ret = 0;
    while(k>0)
    {
        ret+=bit[k];
        k-=(k&(-k));
    }
    return ret;
}

void update(int k)
{
    while(k<=n)
    {
        bit[k]++;
        k+=(k&(-k));
    }
}

int main()
{
    ifstream infile("sleepy.in");
    ofstream outfile("sleepy.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    update(in[n-1]);
    for(int i = n-2; i>=0; i--)
    {
        if(in[i]>in[i+1])
        {
            break;
        }
        ans++;
        update(in[i]);
    }
    ans = n-ans;
    outfile << ans << endl;
    for(int i = 0; i<ans; i++)
    {
        outfile << ans-i+sum(in[i])-1;
        if(i!=ans-1)
        {
            outfile << " ";
        }
        update(in[i]);
    }
    outfile << endl;
}
