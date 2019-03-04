#include <fstream>
#include <iostream>

using namespace std;

int n, in1[100000], in2[100000], pos1[100000], pos2[100000];
long long bit[100001], cur, ans = 0xfffffffffffffff;

long long sum(int k)
{
    k++;
    int ret = 0;
    while(k>0)
    {
        ret+=bit[k];
        k-=(k&(-k));
    }
    return ret;
}

void update(int k, int v)
{
    k++;
    while(k<=n)
    {
        bit[k]+=v;
        k+=(k&(-k));
    }
}

int main()
{
    ifstream infile("mincross.in");
    ofstream outfile("mincross.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in1[i];
        pos1[in1[i]-1] = i;
        update(i,1);
    }
    for(int i = 0; i<n; i++)
    {
        infile >> in2[i];
        pos2[in2[i]-1] = i;
    }
    for(int i = 0; i<n; i++)
    {
        cur+=sum(pos2[in1[i]-1]-1);
        update(pos2[in1[i]-1],-1);
    }
    for(int i = n-1; i>=0; i--)
    {
        cur+=(2*pos1[in2[i]-1]-n+1);
        ans = min(ans,cur);
    }
    for(int i = n-1; i>=0; i--)
    {
        cur+=(2*pos2[in1[i]-1]-n+1);
        ans = min(ans,cur);
    }
    outfile << ans << endl;
}
