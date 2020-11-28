#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

string k;
int d, dp[10000][100][2];

int main()
{
    cin >> k >> d;
    for(int i = 0; i<(k[0]-'0'); i++)
        dp[0][i%d][0]++;
    dp[0][(k[0]-'0')%d][1]++;
    for(int i = 1; i<k.length(); i++)
    {
        for(int dig = 0; dig<(k[i]-'0'); dig++)
            for(int j = 0; j<d; j++)
                dp[i][(j+dig)%d][0] = (dp[i][(j+dig)%d][0]+dp[i-1][j][0]+dp[i-1][j][1])%MOD;
        for(int j = 0; j<d; j++)
           dp[i][(j+(k[i]-'0'))%d][1] = dp[i-1][j][1];
        for(int dig = (k[i]-'0'); dig<10; dig++)
            for(int j = 0; j<d; j++)
                dp[i][(j+dig)%d][0] = (dp[i][(j+dig)%d][0]+dp[i-1][j][0])%MOD;
    }
    cout << (dp[k.length()-1][0][0]+dp[k.length()-1][0][1]+MOD-1)%MOD << endl;
}
