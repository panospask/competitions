#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll C;
string s;
int a_cnt = 0, b_cnt = 0;
ll rudeness = 0;

void add(char c)
{
    if (c == 'a') {
        a_cnt++;
    }
    else if (c == 'b') {
        b_cnt++;
        rudeness += a_cnt;
    }

}

void remove(char c)
{
    if (c == 'a') {
        a_cnt--;
        rudeness -= b_cnt;
    }
    else if (c == 'b') {
        b_cnt--;
    }

}

int main(void)
{
    scanf("%d %lld", &N, &C);

    s.resize(N);
    for (int i = 0; i < N; i++) {
        scanf(" %c", &s[i]);
    }

    int l = 0;
    int ans = 0;
    for (int r = 0; r < N; r++) {
        // Find the maximum segment ending at r

        add(s[r]);
        while (rudeness > C) {
            remove(s[l]);
            l++;
        }

        ans = max(ans, r - l + 1);
    }

    printf("%d\n", ans);

    return 0;
}