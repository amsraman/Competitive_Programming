#include <bits/stdc++.h>

using namespace std;

int n, m, t, num;
vector<int> id;
deque<int> q;
string rq;
bool ok;

int conv(string s)
{
    int hr = 10*(s[0]-'0')+(s[1]-'0'), mn = 10*(s[3]-'0')+(s[4]-'0'), sc = 10*(s[6]-'0')+(s[7]-'0');
    return 3600*hr+60*mn+sc;
}

int main()
{
    cin >> n >> m >> t;
    for(int i = 0, rqt; i<n; i++)
    {
        cin >> rq;
        rqt = conv(rq);
        while((!q.empty())&&(q.front()<rqt))
            q.pop_front();
        if(q.size()==m)
            num--, q.pop_back();
        num++, q.push_back(rqt+t-1);
        ok|=(q.size()==m);
        id.push_back(num);
    }
    if(!ok)
        cout << "No solution" << endl;
    else
    {
        cout << num << endl;
        for(auto x: id)
            cout << x << endl;
    }
}