#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> cards(52);
    for(int i = 0; i < 52; i++) {
        cin >> cards[i];
    }
    vector<string> deck;
    for(int i = 0; i < 52; i++) {
        deck.push_back(cards[i]);
        while(true) {
            int m1 = -1;
            for(int j = deck.size() - 1; j >= 3; j--) {
                if(deck[j][0] == deck[j - 3][0]) {
                    m1 = j;
                    break;
                }
            }
            if(m1 != -1) {
                deck.erase(deck.begin() + m1);
                deck.erase(deck.begin() + m1 - 1);
                deck.erase(deck.begin() + m1 - 2);
                deck.erase(deck.begin() + m1 - 3);
                continue;
            }
            int m2 = -1;
            for(int j = deck.size() - 1; j >= 3; j--) {
                if(deck[j][1] == deck[j - 3][1]) {
                    m2 = j;
                    break;
                }
            }
            if(m2 != -1) {
                deck.erase(deck.begin() + m2);
                deck.erase(deck.begin() + m2 - 3);
                continue;
            }
            break;
        }
    }
    cout << deck.size() << " ";
    for(string d: deck) {
        cout << d << " ";
    }
    cout << '\n';
}