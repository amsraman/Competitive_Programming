#include <iostream>
#define A 911382323
#define B 972663749
typedef long long ll;

using namespace std;

int n, lp;
ll hsh[1000001], exp[1000001];
string w, ans;

ll modx(ll a)
{
    return ((a%B)+B)%B;
}

int main()
{
    exp[0] = 1;
    for(int i = 1; i<1000001; i++)
        exp[i] = modx(exp[i-1]*A);
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> w;
        ll cur = 0, wp = -1;
        for(int j = 0; j<w.length(); j++)
        {
            cur = modx(cur*A+(w[j]-'A'));
            if((lp>j)&&(modx(hsh[lp]-hsh[lp-j-1]*exp[j+1])==cur))
                wp = j;
        }
        for(int j = wp+1; j<w.length(); j++)
            ans+=w[j], lp++, hsh[lp] = modx(hsh[lp-1]*A+(w[j]-'A'));
    }
    cout << ans << endl;
}