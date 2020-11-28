#include <bits/stdc++.h>

using namespace std;

int t = 5, pos[6], r, roll, mn;
int tp[18] = {0,1,6,11,16,21,22,23,24,26,27,28,29,34,39,44,49,50}, row[52];
bool bad[52], blocked[52];

bool isPrime(int x)
{
    for(int i = 2; i*i<=x; i++)
        if(!(x%i))
            return false;
    return true;
}

int keep_going(int x, int y)
{
    int ctr = 0;
    while((!blocked[x+(y/abs(y))]||(x==50))&&(ctr<abs(y))&&(x>0)&&(x<51))
        x+=(y/abs(y)), ctr++;
    return x;
}

bool ok2(int x, int y)
{
    if(((x==1)||(x==6)||(x==11)||(x==16)||(x==29)||(x==34)||(x==39)||(x==44))&&(y==6))
        return true;
    if(((x==21)||(x==22)||(x==23)||(x==24))&&(x+y>=27))
        return true;
    return false;
}

int main()
{
    for(int i = 0; i<18; i++)
        bad[tp[i]] = true, row[tp[i]+1]++;
    for(int i = 1; i<52; i++)
        row[i]+=row[i-1];
    while(t--)
    {
        memset(blocked,false,sizeof(blocked));
        for(int i = 0; i<6; i++)
            cin >> pos[i];
        for(int i = 0; i<6; i++)
            pos[i]--, blocked[pos[i]] = true;
        cin >> r;
        for(int i = 0; i<r; i++)
        {
            cin >> roll;
            mn = 3;
            for(int j = 3; j<6; j++)
                if(pos[j]<pos[mn])
                    mn = j;
            blocked[pos[mn]] = false;
            if(pos[mn]+roll>=51)
                pos[mn] = 51;
            else if(blocked[pos[mn]+roll])
                blocked[pos[mn]] = true;
            else if(isPrime(pos[mn]+roll+1))
                pos[mn] = keep_going(pos[mn]+roll,6);
            else if((pos[mn]+roll>4)&&(int(sqrt(pos[mn]+roll+1))==sqrt(pos[mn]+roll+1)))
                pos[mn] = keep_going(pos[mn]+roll,-6);
            else if(((!bad[pos[mn]])||ok2(pos[mn],roll))&&(row[pos[mn]]!=row[pos[mn]+roll]))
            {
                int temp = pos[mn]+roll+1;
                while(((temp%roll)||(blocked[temp-1]))&&(temp>pos[mn]+1))
                    temp--;
                pos[mn] = temp-1;
            }
            else
                pos[mn]+=roll;
            blocked[pos[mn]] = true;
        }
        sort(pos+3,pos+6);
        if((pos[3]==51)&&(pos[4]==51)&&(pos[5]==51))
            cout << "GAME OVER" << endl;
        else
            cout << pos[3]+1 << " " << pos[4]+1 << " " << pos[5]+1 << endl;
    }
}
