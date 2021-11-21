#include <bits/stdc++.h>

using namespace std;

int a, b;
vector<int> ans;

bool solve(int x, int y)
{
    int ret = 1, exp = 0;
    if(x==0)
        return (y==0);
    while(ret<=y)
    {
        ans.push_back(exp);
        if((ret%10==y%10)&&(solve(x/10,(y-ret)/10)))
            return true;
        ans.pop_back();
        ret*=(x%10), exp++;
    }
    return false;
}

int main()
{
    cin >> a >> b;
    solve(a,b);
    for(int i = ans.size()-1; i>=0; i--)
        cout << ans[i] << " ";
    cout << endl;
}
