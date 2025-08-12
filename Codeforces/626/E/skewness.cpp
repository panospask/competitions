#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> x;
vector<ll> pref;

// Skewness by using median x, num numbers on either side
double skewness(int i, int num) {
    // Use the top num numbers and for low numbers, just put close to x
    ll high = pref[N] - pref[N - num];
    ll low = pref[i] - pref[i - num];

    double mean = (double)(high + low + x[i]) / (2 * num + 1);
    return mean - x[i];
}

int main(void) {
    scanf("%d", &N);

    x.resize(N);
    pref.resize(N + 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }
    sort(x.begin(), x.end());
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + x[i];
    }


    double ans = 0;
    int opt = 0, var = 0;
    for (int i = 0; i < N; i++) {

        int l = -1;
        int r = min(i, N - i - 1);
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (skewness(i, mid) < skewness(i, mid + 1)) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        if (skewness(i, r) > ans) {
            ans = skewness(i, r);
            opt = i;
            var = r;
        }
    }

    printf("%d\n", 2 * var + 1);
    for (int i = opt - var; i <= opt; i++) {
        printf("%d ", x[i]);
    }
    for (int i = N - var; i < N; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    return 0;
}