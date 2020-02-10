/*
ID: adityasund1
LANG: C++
TASK: numtri
*/
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    int n;
    ifstream infile("numtri.in");
    ofstream outfile("numtri.out");
    infile >> n;
    int arra[n][n];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            infile >> arra[i][j];
        }
    }
    for(int i = n-2; i>=0; i--)
    {
        for(int j = 0; j<=i; j++)
        {
            arra[i][j] = arra[i][j] + max(arra[i+1][j],arra[i+1][j+1]);
        }
    }
    outfile << arra[0][0] << endl;
    return 0;
}
