/*
ID: adityasund1
TASK: preface
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int c[7];
string num[4][10] = {"","I","II","III","IV","V","VI","VII","VIII","IX","","X","XX","XXX","XL","L","LX","LXX","LXXX","XC","","C","CC","CCC","CD","D","DC","DCC","DCCC","CM","","M","MM","MMM"};
string l = "IVXLCDM";

int main()
{
    ifstream infile("preface.in");
    ofstream outfile("preface.out");
    int n, cur;
    string a;
    infile >> n;
    for(int i = 0; i<7; i++)
    {
        c[i] = 0;
    }
    for(int i = 1; i<=n; i++)
    {
        cur = i;
        for(int j = 0; j<4; j++)
        {
            a+=num[j][cur%10];
            cur-=(cur%10);
            cur/=10;
        }
        for(int j = 0; j<a.size(); j++)
        {
            if(a[j]=='I'){c[0]++;}
            if(a[j]=='V'){c[1]++;}
            if(a[j]=='X'){c[2]++;}
            if(a[j]=='L'){c[3]++;}
            if(a[j]=='C'){c[4]++;}
            if(a[j]=='D'){c[5]++;}
            if(a[j]=='M'){c[6]++;}
        }
        a = "";
    }
    int m = 0;
    for(int i = 0; i<7; i++)
    {
        if(c[i]!=0)
        {
            m=max(m,i+1);
        }
    }
    for(int i = 0; i<m; i++)
    {
        outfile << l[i] << " " << c[i] << endl;
    }
}
