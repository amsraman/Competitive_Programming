/*
ID: adityasund1
TASK: hamming
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int dist(int a, int b)
{
    bitset<8> bit(a^b);
    return bit.count();
}

int main()
{
    ifstream infile("hamming.in");
    ofstream outfile("hamming.out");
    int n, b, d;
    infile >> n >> b >> d;
    vector<int> ans;
    for(int i = 0; i<(1<<b); i++)
    {
        bool valid = true;
        for(int j = 0; j<ans.size(); j++)
        {
            if(dist(ans[j],i)<d)
            {
                valid = false;
            }
        }
        if(valid)
        {
            ans.push_back(i);
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(i%10!=0)
        {
            outfile << " ";
        }
        outfile << ans[i];
        if(i%10==9)
        {
            outfile << endl;
        }
    }
    if(n%10!=0)
    {
        outfile << endl;
    }
}
