#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 24

using namespace std;

string order;
unordered_map<char, bool> found;
unordered_map<char, set<char>> before_cross;
int ans;
set<char> cur_cows;

int main(void)
{
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    cin >> order;
    cur_cows.clear();

    bool alr_crossed;
    for (auto c : order) {
        alr_crossed = found[c];
        if (!alr_crossed) {
            before_cross[c] = cur_cows;
            cur_cows.insert(c);
            found[c] = true;
        }
        else {
            found[c] = false;
            cur_cows.erase(c);
            for (auto bef : before_cross[c])
                if (cur_cows.find(bef) == cur_cows.end())
                    ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}