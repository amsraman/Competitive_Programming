#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("balancing.in");
    ofstream outfile("balancing.out");
    int n;
    infile >> n;
    pair<int,int> p[n];
    vector<int> y;
    int a, b;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        y.push_back(b+1);
        p[i] = {a,b};
    }
    sort(y.begin(),y.end());
    sort(p,p+n);
    for(int i = 0; i<y.size(); i++)
    {
        if((y[i]==y[i+1])&&(i!=y.size()-1))
        {
            y.erase(y.begin()+i);
        }
    }
    int left[n+1][2], right[n+1][2];
    int ans = INF;
    for(int i = 0; i<y.size(); i++)
    {
        int c = 0;
        left[0][0] = left[0][1] = 0;
        for(int j = 0; j<n; j++)
        {
            if((p[j].first!=p[j-1].first)||(j==0))
            {
                c++;
                left[c][0] = left[c-1][0];
                left[c][1] = left[c-1][1];
            }
            if(p[j].second<y[i])
            {
                left[c][0]++;
            }
            else
            {
                left[c][1]++;
            }
        }
        right[c][0] = right[c][1] = 0;
        int nu = c;
        for(int j = n-1; j>=0; j--)
        {
            if((p[j].first!=p[j+1].first)||(j==n-1))
            {
                c--;
                right[c][0] = right[c+1][0];
                right[c][1] = right[c+1][1];
            }
            if(p[j].second<y[i])
            {
                right[c][0]++;
            }
            else
            {
                right[c][1]++;
            }
        }
        for(int j = 0; j<=nu; j++)
        {
            ans = min(ans,max(max(left[j][0],left[j][1]),max(right[j][0],right[j][1])));
        }
    }
    outfile << ans << endl;
}
