#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

void solve(void)
{
    scanf("%d", &N);
    A.resize(N);

    ll sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
    }

    ll cur = 0;
    ll prv = 0;

    // How many you can add to current added value (negative points if it is negative)
    ll capacity = 0;

    int added = 0;
    for (int i = 0; i < N; i++) {
        cur += A[i];

        if (cur < 0) {
            if (capacity < 0 || capacity < abs(cur)) {
                added++;
                capacity = sum - prv;
            }

            capacity -= abs(cur);
            cur = 0;
        }
        else if (cur > sum) {
            if (capacity > 0 || abs(capacity) < cur - sum) {
                added++;
                capacity = -prv;
            }

            capacity += cur - sum;
            cur = sum;
        }

        prv = cur;

        // Update capacity due to current values
        if (capacity > 0) {
            capacity = min(capacity, sum - cur);
        }
        else {
            capacity = max(capacity, -cur);
        }
    }
    if (cur != sum) {
        if (capacity < 0 || capacity < sum - cur) {
            added++;
        }
    }

    printf("%d\n", N + added);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}