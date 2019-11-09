#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("cbarn.in");
    ofstream outfile("cbarn.out");
    int n;
    infile >> n;
    int pos[n];
    int a, c = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        for(int j = 0; j<a; j++)
        {
            pos[c] = i;
            c++;
        }
    }
    int ans = INF;
    for(int i = 0; i<n; i++)
    {
        a = 0;
        for(int j = 0; j<n; j++)
        {
            c = j-pos[j]+i;
            if(c<0){c+=n;}
            a+=c*c;
        }
        ans=min(ans,a);
    }
    outfile << ans << endl;
}
