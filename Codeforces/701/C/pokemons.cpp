#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 'z' - 'A' + 1;

int N;
vector<char> s;
vector<int> cnt;

int code(int i)
{
    return s[i] - 'A';
}

int main(void)
{
    scanf("%d", &N);

    s.resize(N);
    cnt.assign(LETTERS, 0);

    int rem = 0;
    for (int i = 0; i < N; i++) {
        scanf(" %c", &s[i]);
        cnt[code(i)]++;
        if (cnt[code(i)] == 1) {
            rem++;
        }
    }

    cnt.assign(LETTERS, 0);
    int ans = INT_MAX;
    int r = 0;
    while (rem && r < N) {
        cnt[code(r)]++;
        if (cnt[code(r)] == 1) {
            rem--;
        }
        r++;
    }

    for (int l = 0; l < N; l++) {
        ans = min(ans, r - l);

        cnt[code(l)]--;
        if (cnt[code(l)] == 0) {
            rem++;
        }

        while (rem && r < N) {
            cnt[code(r)]++;
            if (cnt[code(r)] == 1) {
                rem--;
            }
            r++;
        }

        if (rem) {
            break;
        }
    }

    printf("%d\n", ans);

    return 0;
}