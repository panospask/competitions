#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const string TARGET = "XMAS";

vector<string> text;
vector<string> inv;

int count(string s)
{
    int cnt = 0;

    for (int i = 0; i + 4 <= s.size(); i++) {
        if (s.substr(i, 4) == TARGET) {
            cnt++;
        }
    }

    reverse(s.begin(), s.end());
    for (int i = 0; i + 4 <= s.size(); i++) {
        if (s.substr(i, 4) == TARGET) {
            cnt++;
        }
    }

    return cnt;
}

int main(void)
{
    freopen("search.in", "r", stdin);
    freopen("search.out", "w", stdout);

    while (!cin.eof()) {
        string cur;
        getline(cin, cur);
        text.pb(cur);
    }

    int N = text.size();
    int M = text[0].size();
    inv.resize(M);

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        ans += count(text[i]);
        for (int j = 0; j < M; j++) {
            inv[j].pb(text[i][j]);
        }
    }
    for (int j = 0; j < M; j++) {
        ans += count(inv[j]);
    }

    // Count diagonals where i - j = const = diff
    for (int diff = -(M - 1); diff <= N - 1; diff++) {
        string s;
        for (int i = 0; i < N; i++) {
            if (i + diff >= 0 && i + diff < M) {
                s.pb(text[i][i + diff]);
            }
        }

        ans += count(s);
    }

    // Count diagonals where i + j = const = sum
    for (int sum = 0; sum <= N + M - 2; sum++) {
        string s;
        for (int i = 0; i < N; i++) {
            if (sum - i >= 0 && sum - i < M) {
                s.pb(text[i][sum - i]);
            }
        }

        ans += count(s);
    }

    printf("%lld\n", ans);

    return 0;
}