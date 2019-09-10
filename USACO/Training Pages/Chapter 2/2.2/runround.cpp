/*
ID: adityasund1
TASK: runround
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

bool valid(int a)
{
    bool u[10] = {false}, v[10] = {false};
    int ar[9] = {0,0,0,0,0,0,0,0,0};
    int c = 0;
    while(a!=0)
    {
        c++;
        if((a%10==0)||(u[a%10]))
        {
            return false;
        }
        u[a%10] = true;
        ar[9-c] = a%10;
        a/=10;
    }
    int cu = 9-c;
    for(int i = 9-c; i<9; i++)
    {
        cu=9-c+(cu-9+c+ar[cu])%c;
        if(v[cu])
        {
            return false;
        }
        v[cu] = true;
    }
    if(cu==9-c)
    {
        return true;
    }
    return false;
}

int main()
{
    ifstream infile("runround.in");
    ofstream outfile("runround.out");
    int m;
    infile >> m;
    m++;
    while(!valid(m))
    {
        m++;
    }
    outfile << m << endl;
}
