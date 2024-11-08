#include <bits/stdc++.h>

using namespace std;

int N;
string s;

int main(void)
{
    cin >> s;
    N = s.size() / 2;
    vector<int> restored(2 * N, -1);

    vector<int> cnt(26, 0);
    for (int i = 0; i < 2 * N; i++) {
        cnt[s[i] - 'a']++;
    }

    int big = -1;
    int small = -1;
    int total = 0;
    for (int i = 0; i < 26; i++) {
        total += !(!cnt[i]);
        if (cnt[i] > N) {
            big = i;
        }
        else if (cnt[i]) {
            small = i;
        }
    }

    if (big != -1 && (cnt[big] + (total == 2) >= 2 * N - 1)) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");

    int p = 0;
    if (big != -1) {
        while (p < N) {
            restored[p] = big;
            p++;
            cnt[big]--;
        }
        restored[2 * N - 1] = small;
        cnt[small]--;
    }

    for (int i = 0; i < 26; i++) {
        if (i == big) {
            continue;
        }

        for (int v = 0; v < cnt[i]; v++) {
            restored[p] = i;
            p++;
        }
    }
    if (big != -1) {
        for (int v = 0; v < cnt[big]; v++) {
            restored[p] = big;
            p++;
        }
    }

    string t;
    t.resize(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        t[i] = restored[i] + 'a';
    }
    cout << t << endl;

    return 0;
}