#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll a, b, c, d;

string string_mult(string x, int y)
{
    string ret = "";
    for(int i = 0; i<y; i++)
        ret+=x;
    return ret;
}

ll inv(ll x)
{
    ll ret = 1;
    while((ret*(ret-1)/2)<x)
        ++ret;
    return (x==ret*(ret-1)/2?ret:-1);
}

string solve()
{
    ll num0 = inv(a), num1 = inv(d);
    if(num0!=-1&&b==0&&c==0&&d==0)
        return string_mult("0",num0);
    if(a==0&&b==0&&c==0&&num1!=-1)
        return string_mult("1",num1);
    if(num0<=0||num1<=0||((num0+num1)*(num0+num1-1)/2!=a+b+c+d)||b>num0*num1)
        return "impossible";
    string tmp = string_mult("0",num0-c%num0)+(num1-c/num0>=1?"1":"")+string_mult("0",c%num0);
    string ret = string_mult("1",c/num0)+tmp+string_mult("1",num1-c/num0-1);
    return ret;
}

int main()
{
    cin >> a >> b >> c >> d;
    cout << solve() << endl;
}