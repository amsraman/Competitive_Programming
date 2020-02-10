/*
ID: adityasund1
LANG: C++
TASK: sprime
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int a[4] = {1,3,7,9};
vector<int> ans;

bool prime(int n)
{
    for(int i = 2; i*i<=n; i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}

bool sprime(int z)
{
    while(z!=0)
    {
        if(prime(z))
        {
            z = z/10;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void dfs(int z, int i)
{
    if(i==0)
    {
        if(sprime(z))
        {
            ans.push_back(z);
        }
        return;
    }
    for(int j = 0; j<4; j++)
    {
        dfs(10*z+a[j],i-1);
    }
}

int main()
{
    int n;
    ifstream infile("sprime.in");
    ofstream outfile("sprime.out");
    infile >> n;
    int b[4] = {2,3,5,7};
    int s;
    for(int i = 0; i<4; i++)
    {
        s = b[i];
        dfs(s,n-1);
    }
    for(int i = 0; i<ans.size(); i++)
    {
        outfile << ans[i] << endl;
    }
    return 0;
}
