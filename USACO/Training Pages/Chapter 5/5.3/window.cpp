/*
ID: adityasund1
TASK: window
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

pair<pair<int,int>,pair<int,int> > rect[62];
int rnk[62], rid[63], wc;

int f(char a)
{
    if(a>='a') return 36+(a-'a');
    if(a>='A') return 10+(a-'A');
    return a-'0';
}

int see(int r, int a, int b, int c, int d)
{
    if(r==wc+1){return ((c-a)*(d-b));}
    if((c<=rect[rid[r]].first.first)||(a>=rect[rid[r]].second.first)||(b>=rect[rid[r]].second.second)||(d<=rect[rid[r]].first.second)){return see(r+1,a,b,c,d);}
    int ret = 0;
    if(a<rect[rid[r]].first.first){ret+=see(r+1,a,b,rect[rid[r]].first.first,d);}
    if(c>rect[rid[r]].second.first){ret+=see(r+1,rect[rid[r]].second.first,b,c,d);}
    if(b<rect[rid[r]].first.second){ret+=see(r+1,max(a,rect[rid[r]].first.first),b,min(c,rect[rid[r]].second.first),rect[rid[r]].first.second);}
    if(d>rect[rid[r]].second.second){ret+=see(r+1,max(a,rect[rid[r]].first.first),rect[rid[r]].second.second,min(c,rect[rid[r]].second.first),d);}
    return ret;
}

int main()
{
    ifstream infile("window.in");
    ofstream outfile("window.out");
    string s;
    while(infile>>s)
    {
        if(s[0]=='w')
        {
            int in[5], cnt = 0;
            in[0] = 0;
            for(int i = 4; i<s.length(); i++)
            {
                if((s[i]>='0')&&(s[i]<='9'))
                {
                    in[cnt]*=10;
                    in[cnt]+=(s[i]-'0');
                }
                else
                {
                    cnt++;
                    in[cnt] = 0;
                }
            }
            wc++;
            rect[f(s[2])] = make_pair(make_pair(min(in[0],in[2]),min(in[1],in[3])),make_pair(max(in[0],in[2]),max(in[1],in[3])));
            rnk[f(s[2])] = wc;
            rid[wc] = f(s[2]);
        }
        if(s[0]=='t')
        {
            for(int i = rnk[f(s[2])]; i<wc; i++)
            {
                rid[i] = rid[i+1];
                rnk[rid[i+1]] = i;
            }
            rid[wc] = f(s[2]);
            rnk[f(s[2])] = wc;
        }
        if(s[0]=='b')
        {
            for(int i = rnk[f(s[2])]; i>1; i--)
            {
                rid[i] = rid[i-1];
                rnk[rid[i-1]] = i;
            }
            rid[1] = f(s[2]);
            rnk[f(s[2])] = 1;
        }
        if(s[0]=='d')
        {
            for(int i = rnk[f(s[2])]; i<wc; i++)
            {
                rid[i] = rid[i+1];
                rnk[rid[i+1]] = i;
            }
            wc--;
        }
        if(s[0]=='s')
        {
            outfile << fixed << setprecision(3) << 100*double(see(rnk[f(s[2])]+1,rect[f(s[2])].first.first,rect[f(s[2])].first.second,rect[f(s[2])].second.first,rect[f(s[2])].second.second))/double((rect[f(s[2])].second.first-rect[f(s[2])].first.first)*(rect[f(s[2])].second.second-rect[f(s[2])].first.second)) << endl;
        }
    }
}
