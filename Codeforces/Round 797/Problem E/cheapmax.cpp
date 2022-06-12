#include <bits/stdc++.h>

using namespace std;

int remaining[1000];
int n, k;
int arr[200000];

long long int saving_by_i(int i) {
    int start = k - i;
    long long int saved = 0;

    for (int j = start; remaining[i] > 0; j++) {
        if (j == k)
            j = 0;

        if (i != j) {
            int to_remove = min(remaining[i], remaining[j]);
            remaining[i] -= to_remove;
            remaining[j] -= to_remove;
            saved += ((i + j) % k) * to_remove;
        }
        else {
            int to_remove = remaining[i] / 2;
            remaining[i] -= to_remove * 2;
            saved += ((i + j) % k) * to_remove;
        }
    }

    return saved;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &n, &k);

        long long int s = 0;

        for (int j = 0; j < k; j++)
            remaining[k] == 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            remaining[arr[i] % k]++;
            s += arr[i];
        }

        long long int saved = 0;
        for (int i = 0; i < k; i++) {
            saved += saving_by_i(i);
        }

        long long int act = (s - saved) / k;
        printf("%lld\n", act);
    }

    return 0;
}