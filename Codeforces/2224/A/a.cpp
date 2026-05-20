#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a, b;
void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);
    int cnt[2] = {0, 0};
    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);
        a[i] = c == '(';
        cnt[a[i]]++;
    }
    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);
        b[i] = c == '(';
        cnt[b[i]]++;
    }

    if (cnt[0] != N) {
        printf("NO\n");
        return;
    }

    int p1 = 0, p2 = 0;
    vector<int> s1, s2;
    for (int i = 0; i < N; i++) {
        if (a[i]) {
            p1++;
        }
        else {
            p1--;
        }

        if (b[i]) {
            p2++;
        }
        else {
            p2--;
        }

        if (p1 > 2 && a[i]) {
            s1.push_back(i);
        }
        if (p2 > 2 && b[i]) {
            s2.push_back(i);
        }

        if (p1 < 0) {
            if (p2 < 2 || s2.empty()) {
                printf("NO\n");
                return;
            }
            s2.pop_back();
            p1 += 2;
            p2 -= 2;
        }
        if (p2 < 0) {
            if (p1 < 2 || s1.empty()) {
                printf("NO\n");
                return;
            }
            s1.pop_back();
            p1 -= 2;
            p2 += 2;
        }
    }

    printf("YES\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}