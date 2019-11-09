#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("bcount.in");
    ofstream outfile("bcount.out");
    int n, q;
    infile >> n >> q;
    int a, b;
    int t[n][3];
    t[0][0] = t[0][1] = t[0][2] = 0;
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<3; j++)
        {
            t[i][j] = t[i-1][j];
        }
        infile >> a;
        t[i][a-1]++;
    }
    for(int i = 0; i<q; i++)
    {
        infile >> a >> b;
        outfile << t[b][0]-t[a-1][0] << " " << t[b][1]-t[a-1][1] << " " << t[b][2]-t[a-1][2] << endl;
    }
}
