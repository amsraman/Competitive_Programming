/*
ID: adityasund1
TASK: fracdec
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("fracdec.in");
    ofstream outfile("fracdec.out");
    int n, d, cp = 0, par = -1, charc = -1, in;
    infile >> n >> d;
    in = n/d;
    outfile << n/d << ".";
    n%=d;
    int pos[100001];
    bool v[100001] = {false};
    vector<int> dig;
    while(n!=0)
    {
        n*=10;
        if(n<100000)
        {
            if(v[n])
            {
                par = pos[n];
                break;
            }
        }
        if(n<100000)
        {
            v[n] = true;
            pos[n] = cp;
        }
        dig.push_back(n/d);
        n%=d;
        cp++;
    }
    if(dig.size()==0)
    {
        outfile << 0;
    }
    else
    {
        charc = 2;
        if(in>9)
        {
            charc++;
        }
        for(int i = 0; i<dig.size(); i++)
        {
            charc++;
            if(i==par)
            {
                outfile << '(';
                charc++;
            }
            outfile << dig[i];
            if((charc%76==0)&&(charc>0))
            {
                outfile << endl;
            }
        }
        if(par!=-1)
        {
            outfile << ')';
        }
    }
    if(charc%76!=0)
    {
        outfile << endl;
    }
}
