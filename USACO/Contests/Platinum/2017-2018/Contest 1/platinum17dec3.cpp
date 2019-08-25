#include <fstream>
#include <iostream>

using namespace std;

int n, l, g, in[100000], pre[100001];

bool valid(int a)
{
    for(int i = 0; i<=n; i++) pre[i] = 0;
    for(int i = 0; i<a; i++) pre[in[i]]++;
    for(int i = 1; i<=n; i++)
    {
        pre[i]+=pre[i-1];
        if(pre[i]==i)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream infile("greedy.in");
    ofstream outfile("greedy.out");
    infile >> n;
    g = n-1;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        in[i] = n-in[i];
    }
    while(l<g)
    {
        int mid = (l+g)/2;
        if(valid(mid)) g = mid;
        else l = mid+1;
    }
    outfile << n-g << endl;
}
