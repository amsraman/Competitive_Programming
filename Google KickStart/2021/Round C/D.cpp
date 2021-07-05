#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll A = 100594677, B = 254452523, C = 842188890, D = 900099649, M = 1000050131;

int t, n, val[100], ans[100];
string e[100];

ll oper(ll x, ll y, char op)
{
    if(op=='+') return (x+y)%M;
    if(op=='*') return (x*y)%M;
    assert(op=='#');
    return (((A*x+B)%M) ^ ((C*y+D)%M));
}

ll eval(string exp)
{
    vector<ll> val;
    vector<char> op;
    for(int i = 0; i<exp.length(); i++)
    {
        if(exp[i]=='(')
            op.push_back(exp[i]);
        else if(isdigit(exp[i]))
        {
            ll cval = 0;
            while((i<exp.length())&&(isdigit(exp[i])))
                cval = (cval*10+(exp[i]-'0'))%M, i++;
            i--;
            val.push_back(cval);
        }
        else if(exp[i]==')')
        {
            while((op.size()>0)&&(op.back()!='('))
            {
                ll val2 = val.back(); val.pop_back();
                ll val1 = val.back(); val.pop_back();
                char curop = op.back(); op.pop_back();
                val.push_back(oper(val1,val2,curop));
            }
            op.pop_back();
        }
        else
        {
            while(op.size()>0&&op.back()!='(')
            {
                ll val2 = val.back(); val.pop_back();
                ll val1 = val.back(); val.pop_back();
                char curop = op.back(); op.pop_back();
                val.push_back(oper(val1,val2,curop));
            }
            op.push_back(exp[i]);
        }
    }
    while(op.size()>0)
    {
        ll val2 = val.back(); val.pop_back();
        ll val1 = val.back(); val.pop_back();
        char curop = op.back(); op.pop_back();
        val.push_back(oper(val1,val2,curop));
    }
    return val[0];
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> e[i];
        for(int i = 0; i<n; i++)
            val[i] = eval(e[i]), ans[i] = -1;
        int eq = 0;
        for(int i = 0; i<n; i++)
            if(ans[i]==-1)
            {
                ans[i] = ++eq;
                for(int j = i+1; j<n; j++)
                    if(ans[j]==-1&&val[j]==val[i])
                        ans[j] = eq;
            }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i<n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}