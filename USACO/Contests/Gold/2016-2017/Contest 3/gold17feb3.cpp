#include <fstream>
#include <iostream>

using namespace std;

int n, ng[100001], bit[100001] = {0};
pair<int,int> num[50000];

int sum(int a)
{
    a++;
    int ret = 0;
    while(a>0)
    {
        int k = a&(-a);
        ret+=bit[a];
        a-=k;
    }
    return ret;
}

void update(int a, int b)
{
    a++;
    while(a<=2*n)
    {
        int k = a&(-a);
        bit[a]+=b;
        a+=k;
    }
}

int main()
{
    ifstream infile("circlecross.in");
    ofstream outfile("circlecross.out");
    int ans = 0;
    infile >> n;
    for(int i = 0; i<n; i++){num[i] = {-1,-1};}
    for(int i = 0; i<2*n; i++)
    {
        infile >> ng[i];
        ng[i]--;
        if(num[ng[i]].first==-1)
        {
            num[ng[i]].first = i;
        }
        else
        {
            num[ng[i]].second = i;
        }
    }
    for(int i = 0; i<2*n; i++)
    {
        if(i==num[ng[i]].first)
        {
            update(i,1);
        }
        else
        {
            update(num[ng[i]].first,-1);
            ans+=(sum(num[ng[i]].second)-sum(num[ng[i]].first));
        }
    }
    outfile << ans << endl;
}
