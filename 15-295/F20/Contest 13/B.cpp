#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int cu, tot = 0, mo[3] = {0,-1,-1}, dp[s.length()], ma = 0;
    for(int i = 0; i<s.length(); i++)
    {
        cu = (s[i]-'0')%3;
        tot+=cu;
        dp[i] = max(ma,mo[tot%3]+1);
        ma = max(ma,dp[i]);
        mo[tot%3] = dp[i];
    }
    cout << dp[s.length()-1] << endl;
}