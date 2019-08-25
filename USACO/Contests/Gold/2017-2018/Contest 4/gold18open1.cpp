#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, pos[100000], bit[100001], ans;
pair<int,int> in[100000];

int sum(int k)
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

void update(int k)
{
    k++;
    while(k<=n)
    {
        bit[k]++;
        k+=(k&(-k));
    }
}

int main()
{
    ifstream infile("sort.in");
    ofstream outfile("sort.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first;
        in[i].second = i;
    }
    sort(in,in+n);
    for(int i = 0; i<n; i++)
    {
        pos[in[i].second] = i;
    }
    for(int i = 0; i<n; i++)
    {
        update(pos[i]);
        ans = max(ans,i-sum(i)+1);
    }
    outfile << max(ans,1) << endl;
}
