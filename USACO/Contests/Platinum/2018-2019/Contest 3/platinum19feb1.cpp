#include <fstream>
#include <iostream>

using namespace std;

int n, p1;
double in[1000000], prod, cur, ans;

int main()
{
    ifstream infile("cowdate.in");
    ofstream outfile("cowdate.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        in[i]*=.000001;
    }
    prod = 1;
    for(int i = 0; i<n; i++)
    {
        while((p1<n)&&(cur<1))
        {
            cur+=(in[p1]/(1-in[p1])), prod*=(1-in[p1]);
            p1++;
        }
        ans = max(ans,cur*prod);
        cur-=(in[i]/(1-in[i]));
        prod/=(1-in[i]);
    }
    outfile << int(ans*1000000) << endl;
}
