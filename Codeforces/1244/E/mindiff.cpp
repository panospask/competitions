#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll K;
vector<int> a;

bool close_to(int x)
{
    int l_p = 0;
    int r_p = N - 1;
    ll cost = 0;

    while (a[r_p] > a[l_p] + x) {
        int l_num = l_p + 1;
        int r_num = N - r_p;
        if (l_p + 1 < N - r_p) {
            // Move the left pointer
            int target = min(a[r_p] - x, a[l_p + 1]);

            cost += l_num * (ll)(target - a[l_p]);
            l_p++;
        }
        else {
            // Move the right pointer
            int target = max(a[l_p] + x, a[r_p - 1]);

            cost += r_num * (ll)(a[r_p] - target);
            r_p--;
        }
    }

    return cost <= K;
}

int main(void)
{
    scanf("%d %lld", &N, &K);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());

    int l = -1; // close_to(l) == false
    int r = a[N - 1] - a[0]; // clost to (r) == true
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (close_to(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%d\n", r);

    return 0;
}