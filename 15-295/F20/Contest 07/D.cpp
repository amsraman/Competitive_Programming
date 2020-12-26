#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, ord[200000], bit[200000];
ll ans;
string s;
vector<int> pos[26];

int qry(int x)
{
    int ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret+=bit[x-1];
    return ret;
}

void upd(int x)
{
    for(x++; x<=n; x+=(x&(-x)))
        bit[x-1]++;
}

int main()
{
    cin >> n >> s;
    for(int i = 0; i<n; i++)
        pos[(s[i]-'a')].push_back(i);
    for(int i = 0; i<26; i++)
        for(int j = 0; j<pos[i].size(); j++)
            ord[pos[i][j]] = n-1-pos[i][pos[i].size()-j-1];
    for(int i = n-1; i>=0; i--)
        ans+=qry(ord[i]), upd(ord[i]);
    cout << ans << endl;
}