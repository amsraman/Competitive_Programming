#include <bits/stdc++.h>

using namespace std;

int t, b, pos[10][2], gen[2], qb[10];
bool ans[50], sw[50], block[10][2], fluc[3][2];
string res;

bool qry(int pos)
{
    bool ret;
    cout << pos << endl;
    cin >> ret;
    return ret;
}

int main()
{
    cin >> t >> b;
    while(t--)
    {
        memset(pos,0,sizeof(pos));
        gen[0] = gen[1] = 0;
        for(int i = 0; i<b/2; i++)
            ans[i] = qry(i+1), sw[i] = ans[i]^qry(b-i);
        for(int i = 0; i<b/2; i++)
            pos[i/5][sw[i]] = gen[sw[i]] = i;
        for(int i = 0, qc = 0; i<b/10; i++, qc+=2)
        {
            block[i][0] = ans[pos[i][0]]^qry(pos[i][0]+1);
            block[i][1] = ans[pos[i][1]]^qry(pos[i][1]+1);
            qb[i] = qc/10;
            if(qc%10==6)
            {
                fluc[qc/10][0] = qry(gen[0]+1), fluc[qc/10][1] = qry(gen[1]+1);
                fluc[qc/10][0]^=qry(gen[0]+1), fluc[qc/10][1]^=qry(gen[1]+1);
                qc+=4;
            }
        }
        for(int i = 1; i>=0; i--)
            fluc[i][0]^=fluc[i+1][0], fluc[i][1]^=fluc[i+1][1];
        for(int i = 0; i<b/10; i++)
            block[i][0]^=fluc[qb[i]][0], block[i][1]^=fluc[qb[i]][1];
        for(int i = 0; i<b/2; i++)
            ans[i]^=block[i/5][sw[i]];
        for(int i = 0; i<b/2; i++)
            cout << ans[i];
        for(int i = 0; i<b/2; i++)
            cout << (ans[b/2-i-1]^sw[b/2-i-1]);
        cout << endl;
        cin >> res;
    }
}
