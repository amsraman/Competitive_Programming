#include <bits/stdc++.h>

using namespace std;

int t, n, cpow, cur, leftover;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n;
        cout << "Case #" << cs+1 << ": " << endl;
        n-=30, leftover = 30, cur = 0;
        for(cpow = 0; (1<<cpow)<=n; cpow++)
        {
            if((1<<cpow)&n)
            {
                if(cur>0)
                    for(; cur>=0; cur--)
                        cout << cpow+1 << " " << cur+1 << endl;
                else
                    for(; cur<cpow+1; cur++)
                        cout << cpow+1 << " " << cur+1 << endl;
                cur = max(cur,0);
            }
            else
            {
                cout << cpow+1 << " " << cur+1 << endl;
                leftover--, cur+=bool(cur);
            }
        }
        if(n>0)
            for(int i = 0; i<leftover; i++)
                cout << cpow+i+1 << " " << cur+(bool(cur)*i)+1 << endl;
        else
            for(int i = 0; i<(n+30); i++)
                cout << i+1 << " " << 1 << endl;
    }
}
