#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("hps.in");
    ofstream outfile("hps.out");
    int n;
    infile >> n;
    char in[n];
    int f[3] = {0,0,0}, s[3] = {0,0,0};
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        if(in[i]=='H')
        {
            s[0]++;
        }
        else if(in[i]=='P')
        {
            s[1]++;
        }
        else if(in[i]=='S')
        {
            s[2]++;
        }
    }
    int ans = 0;
    for(int i = 0; i<n; i++)
    {
        if(in[i]=='H')
        {
            f[0]++;
            s[0]--;
        }
        else if(in[i]=='P')
        {
            f[1]++;
            s[1]--;
        }
        else if(in[i]=='S')
        {
            f[2]++;
            s[2]--;
        }
        ans = max(ans,max(max(f[0],f[1]),f[2])+max(max(s[0],s[1]),s[2]));
    }
    outfile << ans << endl;
}
