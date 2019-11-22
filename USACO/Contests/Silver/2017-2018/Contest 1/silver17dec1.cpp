#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    ifstream infile("homework.in");
    ofstream outfile ("homework.out");
    infile >> n;
    int s[n];
    for(int i = 0; i<n; i++)
    {
        infile >> s[n-1-i];
    }
    int mi = min(s[0],s[1]);
    int total = s[0];
    double maxavg = double(max(s[0],s[1]));
    for(int i = 1; i<n-1; i++)
    {
        total = total+s[i];
        mi = min(mi,s[i]);
        if((double(total-mi)/i)>maxavg)
        {
            maxavg = (double(total-mi)/i);
        }
    }
    total = s[0];
    mi = min(s[0],s[1]);
    vector<int> ans;
    int cnt = 0;
    for(int i = 1; i<n-1; i++)
    {
        total = total+s[i];
        mi = min(mi,s[i]);
        if((double(total-mi)/i)==maxavg)
        {
            ans.push_back(n-1-i);
            cnt++;
        }
    }
    sort(ans.begin(),ans.end());
    for(int i = 0; i<cnt; i++)
    {
        outfile << ans[i] << endl;
    }
}
