/*
ID: adityasund1
TASK: subset
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("subset.in");
    ofstream outfile("subset.out");
    int n;
    infile >> n;
    long long sub[n+1][(n*(n+1)/2)+1] = {0};
    sub[0][0] = 1;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=(i*(i+1)/2); j++)
        {
            sub[i+1][j]+=sub[i][j];
            sub[i+1][j+i+1]+=sub[i][j];
        }
    }
    if((n%4==1)||(n%4==2))
    {
        outfile << 0 << endl;
    }
    else
    {
        outfile << sub[n][n*(n+1)/4]/2 << endl;
    }
}
