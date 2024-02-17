#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 26;

int Q;
string s;
vector<int> pref[LETTERS];

int main(void)
{
    cin >> s;

    for (int l = 0; l < LETTERS; l++) {
        pref[l].resize(s.size() + 1);
        pref[l][0] = 0;
    }

    for (int i = 0; i < s.size(); i++) {
        for (int l = 0; l < LETTERS; l++) {
            pref[l][i + 1] = pref[l][i] + (s[i] - 'a' == l);
        }
    }

    cin >> Q;
    while (Q--) {
        int lef, rig;
        cin >> lef >> rig;

        if (lef == rig) {
            printf("Yes\n");
            continue;
        }

        int let1 = s[lef - 1] - 'a';
        if (s[rig - 1] - 'a' != let1) {
            printf("Yes\n");
            continue;
        }

        bool found1 = false, found2 = false;
        for (int l = 0; l < LETTERS && !found2; l++) {
            if (let1 == l)
                continue;

            if (pref[l][rig - 1] - pref[l][lef]) {
                if (found1) {
                    found2 = true;
                    break;
                }
                found1 = true;
            }
        }

        if (found2) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }

    return 0;
}