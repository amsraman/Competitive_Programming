/*
ID: adityasund1
TASK: fence9
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if((a==0)||(b==0))
    {
        return a+b;
    }
    return gcd(max(a,b)%min(a,b),min(a,b));
}

int main()
{
    ifstream infile("fence9.in");
    ofstream outfile("fence9.out");
    int n, m, p, b;
    infile >> n >> m >> p;
    double area = double(p*m)/2;
    b = gcd(n,m)+gcd(max(p-n,n-p),m)+p;
    int ans = int(area-(b/2)+1);
    outfile << ans << endl;
}
