/*
ID: adisund1
LANG: C++
TASK: combo
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int n;
    int combo[3][2], sub[3];
    ifstream infile("combo.in");
    ofstream outfile("combo.out");
    infile >> n;
    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<3; j++)
        {
            infile >> combo[j][i];
        }
    }
    for(int i = 0; i<3; i++)
    {
        if((((combo[i][0]+4)%n)==(combo[i][1]%n))||(((combo[i][1]+4)%n)==(combo[i][0]%n)))
        {
            sub[i] = 1;
        }
        else if((((combo[i][0]+3)%n)==(combo[i][1]%n))||(((combo[i][1]+3)%n)==(combo[i][0]%n)))
        {
            sub[i] = 2;
        }
        else if((((combo[i][0]+2)%n)==(combo[i][1]%n))||(((combo[i][1]+2)%n)==(combo[i][0]%n)))
        {
            sub[i] = 3;
        }
        else if((((combo[i][0]+1)%n)==(combo[i][1]%n))||(((combo[i][1]+1)%n)==(combo[i][0]%n)))
        {
            sub[i] = 4;
        }
        else if(combo[i][0]==combo[i][1])
        {
            sub[i] = 5;
        }
        else
        {
            sub[i] = 0;
        }
    }
    int ans = 250 - (sub[0]*sub[1]*sub[2]);
    if(n<=5)
    {
        ans = n*n*n;
    }
    outfile << ans << endl;
}
