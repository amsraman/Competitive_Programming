/*
ID: adityasund1
LANG: C++
TASK: pprime
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

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

int main()
{
    int l, m;
    ifstream infile("pprime.in");
    ofstream outfile("pprime.out");
    infile >> l >> m;
    vector<int> ans;
    ans.push_back(2);
    ans.push_back(3);
    ans.push_back(5);
    ans.push_back(7);
    ans.push_back(11);
    int a, b, c, d, n;
    for(a = 1; a<=9; a++)
    {
        for(b = 0; b<=9; b++)
        {
            n = 100*a+10*b+a;
            if(prime(n))
            {
                ans.push_back(n);
            }
        }
    }
    for(a = 1; a<=9; a++)
    {
        for(b = 0; b<=9; b++)
        {
            for(c = 0; c<=9; c++)
            {
                n = 10000*a+1000*b+100*c+10*b+a;
                if(prime(n))
                {
                    ans.push_back(n);
                }
            }
        }
    }
    for(a = 1; a<=9; a++)
    {
        for(b = 0; b<=9; b++)
        {
            for(c = 0; c<=9; c++)
            {
                for(d = 0; d<=9; d++)
                {
                    n = 1000000*a+100000*b+10000*c+1000*d+100*c+10*b+a;
                    if(prime(n))
                    {
                        ans.push_back(n);
                    }
                }
            }
        }
    }
    for(int i = 0; i<ans.size(); i++)
    {
        if((ans[i]>=l)&&(ans[i]<=m))
        {
            outfile << ans[i] << endl;
        }
    }
    return 0;
}
