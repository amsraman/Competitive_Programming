/*
ID: adisund1
LANG: C++
TASK: crypt1
*/
#include <iostream>
#include <fstream>

using namespace std;

int exponent(int a, int b)
{
    int ret = 1;
    for(int i = 0; i<b; i++)
    {
        ret = ret*a;
    }
    return ret;
}

int valid(int a, int i[], int n)
{
    int u;
    while(a>0)
    {
        for(u = 0; u<n; u++)
        {
            if(i[u]==(a%10))
            {
                break;
            }
        }
        if(u==n)
        {
            return 0;
        }
        else
        {
           a = a/10;
        }
    }
    return 1;
}

int main()
{
    int n, ans = 0;
    ifstream infile("crypt1.in");
    ofstream outfile("crypt1.out");
    infile >> n;
    int inp[n];
    for(int i = 0; i<n; i++)
    {
        infile >> inp[i];
    }
    int a, b, z;
    for(int i = 0; i<exponent(n,5); i++)
    {
        a = inp[i/exponent(n,4)];
        a = a*10 + inp[(i%exponent(n,4))/exponent(n,3)];
        a = a*10 + inp[(i%exponent(n,3))/exponent(n,2)];
        b = inp[(i%exponent(n,2))/n];
        b = b*10 + inp[i%n];
        if(valid(a*b,inp,n)==1)
        {
            if(((valid(a*(b%10),inp,n)==1)&&(valid(a*(b/10),inp,n)==1))&&((a*(b%10)<1000)&&(a*(b/10)<1000)))
            {
                ans++;
            }
        }
    }
    outfile << ans << endl;
}
