#include <bits/stdc++.h>

using namespace std;

int t, n;
string s;

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> s;
        deque<int> dq;
        int ctr = 0, ans = 0;
        for(int i = 0; i<n; i++)
        {
            ctr++;
            if(i==n-1||s[i]!=s[i+1])
                dq.push_back(ctr), ctr = 0;
        }
        int p1 = 0, p2 = 0;
        while(p1<dq.size())
        {
            while(p2<dq.size()&&dq[p2]==1)
                p2++;
            if(p2<dq.size())
                dq[p2]--;
            else
                p1++;
            p1++, ans++, p2 = max(p2,p1);
        }
        cout << ans << endl;
    }
}