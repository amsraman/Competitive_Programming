#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    ifstream infile("lemonade.in");
    ofstream outfile("lemonade.out");
    infile >> n;
    int a[n];
    for(int i = 0; i<n; i++)
    {
        infile >> a[i];
    }
    sort(a,a+n);
    int ans = 0;
    for(int i = n-1; i>=0; i--)
    {
        if(a[i]<ans)
        {
            break;
        }
        ans++;
    }
    outfile << ans << endl;
}
