#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

int main(void) {
    scanf("%d", &N);

    int cnt[5] = {0, 0, 0, 0, 0};

    A.resize(N);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        cnt[A[i]]++;
        sum += A[i];
    }

    if (sum < 3 || sum == 5) {
        printf("-1\n");
        return 0;
    }

    int ans = 0;

    // Merge 1's and 2's
    while (cnt[1] && cnt[2]) {
        cnt[1]--;
        cnt[2]--;
        cnt[3]++;
        ans++;
    }

    if (cnt[2]) {
        while (cnt[2] >= 3) {
            cnt[2] -= 3;
            cnt[3] += 2;
            ans += 2;
        }

        if (cnt[2] == 1 && cnt[4]) {
            ans++;
        }
        else if (cnt[2]) {
            ans += 2;
        }
    }
    else {
        while (cnt[1] >= 3) {
            cnt[1] -= 3;
            cnt[3]++;
            ans += 2;
        }

        if (cnt[1] > cnt[3]) {
            ans += 2;
        }
        else {
            ans += cnt[1];
        }
    }

    printf("%d\n", ans);
}