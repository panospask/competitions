#include <bits/stdc++.h>

using namespace std;

int N;
string s;

vector<int> t;

int cnt[3];
int code[3] = {0, 1, 2};
int goes[3];

void twomove(void)
{
    int p = 0, a = 0, b = 0, c = 0;
    while (max(a, b) < N) {
        a += t[p] == 0;
        b += t[p] == 1;
        c += t[p] == 2;
        p++;
    }

    int idx_b = 1;
    if (b == N) {
        swap(a, b);
        idx_b = 0;
    }

    int r_b = N - b;
    int r_c = N - c;

    printf("2\n");
    printf("%d %d %c\n", p + 1, p + r_b, code[idx_b] + 'A');
    printf("%d %d %c\n", p + r_b + 1, 3 * N, code[2] + 'A');

    exit(0);
}

int main(void)
{
    cin >> N >> s;

    t.resize(3 * N);

    for (int i = 0; i < 3 * N; i++) {
        t[i] = s[i] - 'A';
        cnt[t[i]]++;
    }

    if (cnt[0] == cnt[1] && cnt[1] == cnt[2]) {
        printf("0\n");
        return 0;
    }

    if (cnt[1] > cnt[0]) {
        swap(cnt[1], cnt[0]);
        swap(code[1], code[0]);
    }
    if (cnt[2] > cnt[1]) {
        swap(cnt[2], cnt[1]);
        swap(code[2], code[1]);
    }
    if (cnt[1] > cnt[0]) {
        swap(cnt[1], cnt[0]);
        swap(code[1], code[0]);
    }

    for (int i = 0; i < 3; i++) {
        goes[code[i]] = i;
    }

    for (int i = 0; i < 3 * N; i++) {
        t[i] = goes[t[i]];
    }

    if (cnt[1] < N) {
        twomove();
    }

    int a1 = cnt[0] - N;
    int b1 = cnt[1] - N;
    int a = 0, b = 0, p = 0;

    while (b < b1) {
        a += t[p] == 0;
        b += t[p] == 1;
        p++;
    }

    int l = 0;
    for (p; p < 3 * N; p++) {
        if (a == a1) {
            printf("1\n");
            printf("%d %d %c\n", l + 1, p, code[2] + 'A');
            exit(0);
        }
        
        if (t[p] == 1) {
            // REMOVE PREVIOUS
            while (b == b1) {
                a -= t[l] == 0;
                b -= t[l] == 1;
                l++;
            }
        }
        a += t[p] == 0;
        b += t[p] == 1;
    }
    if (a == a1) {
        printf("1\n");
        printf("%d %d %c\n", l + 1, p, goes[2] + 'A');
        exit(0);
    }

    twomove();

    return 0;
}