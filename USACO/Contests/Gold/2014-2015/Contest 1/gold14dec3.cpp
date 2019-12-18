#include <fstream>
#include <iostream>
#include <vector>
#define INF 0xfffffffffffffff

using namespace std;

int n;
long long t, a, b, ans;
vector<long long> seq;

int main()
{
    ifstream infile("cowjog.in");
    ofstream outfile("cowjog.out");
    infile >> n >> t;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        a = -(a+t*b);
        if((seq.size()==0)||(a>=seq[seq.size()-1]))
        {
            seq.push_back(a);
        }
        else
        {
            int l = 0, g = seq.size()-1;
            while(l<g)
            {
                int mid = (l+g)/2;
                if(seq[mid]<=a) l = mid+1;
                if(seq[mid]>a) g = mid;
            }
            seq[l] = a;
        }
    }
    outfile << seq.size() << endl;
}
