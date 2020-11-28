#include <bits/stdc++.h>
#define sz(a) a.length()

using namespace std;

int t = 5, grid[4][4];
string in, dig = "0123456789ABCDEF", new1[4] = {"A","C","~A","~C"}, new2[4] = {"B","D","~B","~D"}, term[4], ans;

void rem(int a, int b, int c, int d)
{
    if((b-a+1)*(d-c+1)==8)
    {
        if(b-a==3) ans+=(new1[c%4]+"+");
        else ans+=(new2[a%4]+"+");
    }
    else if((b-a+1)*(d-c+1)==4)
    {
        if((b-a+4)%4==3) term[0] = new1[c%4], term[1] = new1[(c+3)%4];
        else if((d-c+4)%4==3) term[0] = new2[a%4], term[1] = new2[(a+3)%4];
        else term[0] = new1[c%4], term[1] = new2[a%4];
        if(term[0][sz(term[0])-1]>term[1][sz(term[1])-1]) swap(term[0],term[1]);
        ans+=(term[0]+term[1]+"+");
    }
    else if((b-a+1)*(d-c+1)==2)
    {
        if(b-a==1) term[0] = new1[c%4], term[1] = new2[a%4], term[2] = new1[(c+3)%4];
        else term[0] = new2[a%4], term[1] = new1[c%4], term[2] = new2[(a+3)%4];
        if(term[0][sz(term[0])-1]>term[1][sz(term[1])-1]) swap(term[0],term[1]);
        if(term[0][sz(term[0])-1]>term[2][sz(term[2])-1]) swap(term[0],term[2]);
        if(term[1][sz(term[1])-1]>term[2][sz(term[2])-1]) swap(term[1],term[2]);
        ans+=(term[0]+term[1]+term[2]+"+");
    }
    else
    {
        term[0] = new1[c%4], term[1] = new2[a%4], term[2] = new1[(c+3)%4], term[3] = new2[(a+3)%4];
        if(term[0][sz(term[0])-1]>term[2][sz(term[2])-1]) swap(term[0],term[2]);
        if(term[1][sz(term[1])-1]>term[3][sz(term[3])-1]) swap(term[1],term[3]);
        ans+=(term[0]+term[1]+term[2]+term[3]+"+");
    }
    for(int i = a; i<=b; i++)
        for(int j = c; j<=d; j++)
            grid[i%4][j%4]--;
}

bool full(int a, int b, int c, int d)
{
    for(int i = a; i<=b; i++)
        for(int j = c; j<=d; j++)
            if(!grid[i%4][j%4])
                return false;
    return true;
}

void check(int a, int b)
{
    for(int i = a-1; i<4; i++)
        for(int j = b-1; j<4; j++)
            if(full(i-a+1,i,j-b+1,j))
                rem(i-a+1,i,j-b+1,j);
}

void ends1(int x)
{
    for(int i = 0; i<5-x; i++)
        if(full(3,4,i,i+x-1))
            rem(3,4,i,i+x-1);
}

void ends2(int x)
{
    for(int i = 0; i<5-x; i++)
        if(full(i,i+x-1,3,4))
            rem(i,i+x-1,3,4);
}

int main()
{
    //freopen("sr3sample.txt","r",stdin);
    freopen("D:/3sr.txt","r",stdin);
    while(t--)//todo: maybe optimize code a bit better, debug
    {
        cin >> in;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                grid[i][3-j] = bool((dig.find(in[i]))&(1<<j));
        check(2,4), check(4,2), ends1(4), ends2(4), check(1,4), check(4,1), check(2,2), ends2(2), ends1(2);
        if(grid[0][0]&&grid[0][3]&&grid[3][0]&&grid[3][3])
            ans+=("~C~D+"), grid[0][0]--, grid[0][3]--, grid[3][0]--, grid[3][3]--;
        check(1,2), check(2,1), ends2(1), ends1(1), check(1,1);
        if(ans.length()==0)
            cout << 0 << endl;
        else
            cout << ans.substr(0,sz(ans)-1) << endl;
        ans = "";
    }
}
