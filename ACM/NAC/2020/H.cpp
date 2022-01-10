#include <bits/stdc++.h>

using namespace std;

int n, ans = 1e5;
string s[3];
bool xdif[5000], ydif[5000], zdif[5000];

int main()
{
    for(int i = 0; i<3; i++)
        cin >> s[i];
    n = s[0].length();
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(s[0][i]==s[1][j])
                xdif[(i-j+n)%n] = true;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(s[0][i]==s[2][j])
                ydif[(i-j+n)%n] = true;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(s[1][i]==s[2][j])
                zdif[(i-j+n)%n] = true;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(!xdif[i]&&!ydif[j]&&!zdif[(j-i+n)%n])
                ans = min(ans,min({min(i,n-i)+min(j,n-j),min(i,n-i)+min(abs(i-j),n-abs(i-j)),min(abs(i-j),n-abs(i-j))+min(j,n-j)}));
    cout << (ans==1e5?-1:ans) << endl;
}
