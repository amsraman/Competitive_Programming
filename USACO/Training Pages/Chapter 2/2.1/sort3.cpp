/*
ID: adityasund1
LANG: C++
TASK: sort3
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, x, ans = 0;
    int c[3] = {0,0,0};
    ifstream infile("sort3.in");
    ofstream outfile("sort3.out");
    infile >> n;
    int a[n];
    for(int i = 0; i<n; i++)
    {
        infile >> a[i];
        c[a[i]-1]++;
    }
    x = 0;
    vector<int> z;
    for(int i = 0; i<c[0]; i++)
    {
        if(a[i]!=1)
        {
            x++;
            z.push_back(a[i]);
            a[i] = 1;
        }
    }
    ans = ans+x;
    sort(z.begin(),z.end());
    for(int i = c[0]; i<n; i++)
    {
        if(a[i]==1)
        {
            a[i] = z[0];
            z.erase(z.begin(),z.begin()+1);
        }
    }
    x = 0;
    for(int i = c[0]; i<c[0]+c[1]; i++)
    {
        if(a[i]==3)
        {
            x++;
        }
    }
    ans = ans+x;
    outfile << ans << endl;
}
