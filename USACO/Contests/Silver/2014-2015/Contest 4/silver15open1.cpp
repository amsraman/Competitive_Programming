#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long st[7][7], var[7];
long long ans = 0;

void check(int a)
{
    if(a==7)
    {
        if(((var[0]+2*var[1]+2*var[2]+var[3])%7==0)||((var[1]+var[2]+var[4]+var[5])%7==0)||((2*var[5]+var[6])%7==0))
        {
            ans+=st[0][var[0]]*st[1][var[1]]*st[2][var[2]]*st[3][var[3]]*st[4][var[4]]*st[5][var[5]]*st[6][var[6]];
        }
        return;
    }
    for(int i = 0; i<7; i++)
    {
        if(st[a][i]!=0)
        {
            var[a] = i;
            check(a+1);
        }
    }
}

int main()
{
    ifstream infile("bgm.in");
    ofstream outfile("bgm.out");
    int n, b;
    infile >> n;
    char a;
    for(int i = 0; i<7; i++)
    {
        for(int j = 0; j<7; j++)
        {
            st[i][j] = 0;
        }
    }
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        b%=7;
        if(b<0){b+=7;}
        if(a=='B'){st[0][b]++;}
        if(a=='E'){st[1][b]++;}
        if(a=='S'){st[2][b]++;}
        if(a=='I'){st[3][b]++;}
        if(a=='G'){st[4][b]++;}
        if(a=='O'){st[5][b]++;}
        if(a=='M'){st[6][b]++;}
    }
    check(0);
    outfile << ans << endl;
}
