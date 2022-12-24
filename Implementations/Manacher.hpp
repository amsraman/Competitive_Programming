vector<int> Manacher(const string & s) { // generates 1-indexed odd palindrome radii
    int n = s.length();
    vector<int> pal(n, 0);
    for(int i = 0, l = 0, r = 0; i < n; i++) {
        pal[i] = max(0, min(r - i, pal[l + r - i]));
        while(i - pal[i] >= 0 && i + pal[i] < n && s[i - pal[i]] == s[i + pal[i]]) {
            ++pal[i];
        }
        if(i + pal[i] > r) {
            l = i - pal[i] + 1, r = i + pal[i] - 1;
        }
    }
    return pal;
}

vector<int> ManacherAll(const string & s) { // returns palindrome lengths for 2n-1 centers
    int n = s.length();
    string aug = "#"; // intersperse with # signs
    for(char c: s) {
        aug += c; aug += "#";
    }
    vector<int> pal(2 * n + 1, 0);
    for(int i = 0, l = 0, r = 0; i < 2 * n + 1; i++) {
        pal[i] = max(0, min(r - i, pal[l + r - i]));
        while(i - pal[i] >= 0 && i + pal[i] < 2 * n + 1 && aug[i - pal[i]] == aug[i + pal[i]]) {
            ++pal[i];
        }
        if(i + pal[i] > r) {
            l = i - pal[i] + 1, r = i + pal[i] - 1;
        }
    }
    for(int i = 1; i < 2 * n; i++) --pal[i];
    return {next(pal.begin()), prev(pal.end())};
}