/*
ID: adityasund1
TASK: fact4
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("fact4.in");
    ofstream outfile("fact4.out");
    int n;
    infile >> n;
    int cur = 1;
    for(int i = 1; i<=n; i++)
    {
        cur*=i;
        while(cur%10==0)
        {
            cur/=10;
        }
        cur%=1000;
    }
    outfile << cur%10 << endl;
}
