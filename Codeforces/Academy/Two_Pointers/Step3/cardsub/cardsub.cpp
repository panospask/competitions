#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 26;

typedef long long ll;

int N, M;
string s, t;
vector<int> cnt;

int code(char c)
{
    return c - 'a';
}

int main(void)
{
    cin >> N >> M >> s >> t;

    cnt.assign(LETTERS, 0);
    for (int i = 0; i < M; i++) {
        cnt[code(t[i])]++;
    }

    int r = 0;
    ll ans = 0;

    for (int l = 0; l < N; l++) {
        // Count the number of substrings starting at l that can be made

        while (r < N && cnt[code(s[r])]) {
            cnt[code(s[r])]--;
            r++;
        }

        ans += r - l;

        cnt[code(s[l])]++;
    }

    printf("%lld\n", ans);

    return 0;
}