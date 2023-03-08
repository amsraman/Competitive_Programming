#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    for(int _ = 1; _ <= n; _++) {
        int ang, hr; string tp; cin >> ang >> tp >> hr;
        hr %= 12;
        int hr_ang = (360 - hr * 30) % 360, disp;
        if(tp == "til") { // this makes hr_ang small
            if(hr_ang <= ang) hr_ang += 360;
            disp = -(((hr_ang - ang) * 120 + 5) / 11);
        } else { // this makes hr_ang big
            if(hr_ang >= ang) ang += 360;
            disp = ((ang - hr_ang) * 120 + 5) / 11;
        }
        int ans = 3600 * hr + disp;
        if(ans < 0) ans += 24 * 3600;
        ans %= (24 * 3600);
        int res_hr = (ans / 3600) % 12, res_mn = (ans % 3600) / 60, res_sc = ans % 60;
        cout << "Case " << _ << ": " << (res_hr == 0 ? 12 : res_hr) << ":" << res_mn / 10 << res_mn % 10 << ":" << res_sc / 10 << res_sc % 10 << '\n';
    }
}