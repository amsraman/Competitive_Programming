#include <bits/stdc++.h>

using namespace std;

int n, enc[10][10], v1[10], v2[10];
string init, ans;

int conv(char c)
{
    if(c>='A'&&c<='Z')
        return (c-'A');
    if(c>='0'&&c<='9')
        return 26+(c-'0');
    return 36;
}

char iconv(int i)
{
    if(i<26)
        return char('A'+i);
    if(i<36)
        return char('0'+(i-26));
    return ' ';
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> enc[i][j];
    cin.ignore();
    getline(cin,init);
    while(init.length()%n!=0)
        init+=' ';
    for(int i = 0; i<init.length(); i+=n)
    {
        for(int j = 0; j<n; j++)
            v1[j] = conv(init[i+j]), v2[j] = 0;
        for(int j = 0; j<n; j++)
            for(int k = 0; k<n; k++)
                v2[j] = (v2[j]+enc[j][k]*v1[k])%37;
        for(int j = 0; j<n; j++)
            ans+=iconv(v2[j]);
    }
    cout << ans << endl;
}