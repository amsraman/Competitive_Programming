/*
ID: adisund1
LANG: C++
TASK: ride
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string m, n, alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ifstream infile("ride.in");
    ofstream outfile("ride.out");
    infile >> m >> n;
    int p1 = 1, p2 = 1;
    for(int i = 0; i<m.length(); i++)
    {
        p1 = p1*(alpha.find(m[i])+1);
    }
    for(int i = 0; i<n.length(); i++)
    {
        p2 = p2*(alpha.find(n[i])+1);
    }
    if((p1%47)==(p2%47))
    {
        outfile << "GO" << endl;
    }
    else
    {
        outfile << "STAY" << endl;
    }
}
