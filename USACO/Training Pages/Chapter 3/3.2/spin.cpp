/*
ID: adityasund1
TASK: spin
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("spin.in");
    ofstream outfile("spin.out");
    bool o[360][5] = {false};
    int v[5], w, a, b, ans = -1;
    for(int i = 0; i<5; i++)
    {
        infile >> v[i] >> w;
        for(int j = 0; j<w; j++)
        {
            infile >> a >> b;
            for(int k = a; k<=a+b; k++)
            {
                o[k%360][i] = true;
            }
        }
    }
    for(int i = 0; i<=360; i++)
    {
        for(int j = 0; j<360; j++)
        {
            if((o[(360*306+j-v[0]*i)%360][0])&&(o[(360*306+j-v[1]*i)%360][1])&&(o[(360*306+j-v[2]*i)%360][2])&&(o[(360*306+j-v[3]*i)%360][3])&&(o[(360*306+j-v[4]*i)%360][4]))
            {
                ans = i;
                i = 361;
                break;
            }
        }
    }
    if(ans==-1)
    {
        outfile << "none" << endl;
    }
    else
    {
        outfile << ans << endl;
    }
}
