#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll p10[19], ans;
string d;
map<array<int,10>,ll> memo;

ll minimax(array<int,10> dig, bool zer) {
    vector<int> dig_vec;
    for(int i = 0; i<10; i++) {
        for(int j = 0; j<dig[i]; j++) {
            dig_vec.push_back(i);
        }
    }
    if(zer) {
        int ptr = 0;
        while(ptr<dig_vec.size()&&dig_vec[ptr]==0)
            ++ptr;
        if(ptr<dig_vec.size())
            swap(dig_vec[0],dig_vec[ptr]);
    }
    ll num1 = 0, num2 = 0;
    for(int i = 0; i<(dig_vec.size()+1)/2; i++)
        num1 = 10*num1+dig_vec[i];
    for(int i = 0; i<dig_vec.size()/2; i++)
        num2 = 10*num2+dig_vec[dig_vec.size()-i-1];
    return num1-num2;
}

ll solve(array<int,10> dig, int sz, bool init) {
    if(sz == 0) {
        return 0;
    }
    if(memo.count(dig)) {
        return memo[dig];
    }
    ll ret = 0xfffffffffffffff;
    for(int i = 0; i<10; i++) {
        if((i>0||!init)&&dig[i]>1) {
            dig[i]-=2;
            ret = min(ret,solve(dig,sz-1,false));
            dig[i]+=2;
        }
    }
    for(int i = 0; i<10; i++) {
        for(int j = i+1; j<10; j++) {
            if((i>0||!init)&&dig[i]>0&&dig[j]>0) {
                --dig[i], --dig[j];
                ret = min(ret,p10[sz-1]*(j-i)+minimax(dig,false));
                ++dig[i], ++dig[j];
            }
        }
    }
    return memo[dig] = ret;
}

int main() {
    p10[0] = 1;
    for(int i = 1; i<19; i++)
        p10[i] = p10[i-1]*10;
    cin >> t;
    for(int _ = 1; _<=t; _++) {
        cin >> d;
        array<int,10> dig;
        for(int i = 0; i<10; i++) {
            dig[i] = 0;
        }
        for(int i = 0; i<d.length(); i++) {
            ++dig[(d[i]-'0')];
        }
        if(d.length()%2==1) {
            ans = minimax(dig,true);
        } else {
            ans = solve(dig,d.length()/2,true);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        memo.clear();
    }
}