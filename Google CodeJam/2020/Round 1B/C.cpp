#include <bits/stdc++.h>

using namespace std;

int t, r, s, cur[1600];

void upd(int a, int b)
{
    vector<int> vec;
    for(int i = 0; i<a; i++)
        vec.push_back(cur[i]);
    for(int i = 0; i<b; i++)
        cur[i] = cur[i+a];
    for(int i = b; i<a+b; i++)
        cur[i] = vec[i-b];
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> r >> s;
        cout << "Case #" << _ << ": " << (r*s-r+1)/2 << endl;
        for(int i = 0; i<r*s; i++)
            cur[i] = i%r;
        for(int i = 0; i<(r*s-r+1)/2; i++)
        {
            int a = 1, b = r*s;
            if(i!=(r*s-r-1)/2)
                while(cur[b-1]==cur[0])
                    --b;
            while(cur[b-1]!=cur[0])
                b--;
            int c = (b==r*s?r-1:cur[b]);
            while(cur[a-1]!=c||cur[a]==c)
                a++;
            b-=a;
            upd(a,b);
            cout << a << " " << b << endl;
        }
        for(int i = 0; i<r*s-1; i++)
            assert(cur[i]<=cur[i+1]);
    }
}
