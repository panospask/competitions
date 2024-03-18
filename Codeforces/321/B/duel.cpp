#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int N, M;
vector<int> a;

vector<int> atk;
vector<int> def;

// Using EXACTLY the cards in the set, what is optimal play
int calculate(multiset<int> cards)
{
    int damage = 0;

    // Clear defensive ones first
    for (int i = 0; i < def.size() && cards.size() > atk.size(); i++) {
        auto it = cards.upper_bound(def[i]);
        if (it == cards.end()) {
            return damage;
        }
        cards.erase(it);
    }

    // Then attacking ones
    int startpos = min(atk.size(), cards.size()) - 1;
    for (int i = startpos; i >= 0; i--) {
        if (*cards.rbegin() < atk[i]) {
            return damage;
        }

        damage += *cards.rbegin() - atk[i];
        cards.erase(cards.find(*cards.rbegin()));
    }

    // Use remnants
    while (cards.size()) {
        damage += *cards.begin();
        cards.erase(cards.begin());
    }

    return damage;
}

int main(void)
{
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        string pos;
        int stren;
        cin >> pos >> stren;

        if (pos == "ATK") {
            atk.pb(stren);
        }
        else {
            def.pb(stren);
        }
    }
    a.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    sort(atk.begin(), atk.end());
    sort(def.begin(), def.end());

    int ans = 0;
    multiset<int> cards;
    for (int i = a.size() - 1; i >= 0; i--) {
        cards.insert(a[i]);
        ans = max(ans, calculate(cards));
    }

    printf("%d\n", ans);

    return 0;
}