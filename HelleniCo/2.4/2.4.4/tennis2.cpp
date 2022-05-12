#include <bits/stdc++.h>

using namespace std;

long long int sum;
long long int arr[100003], prefix_arr[100003];

bool myfunction (int i,int j) { return (i>j); }

int main(void)
{
    freopen("tennis.in", "r", stdin);
    freopen("tennis.out", "w", stdout);

    int t;
    cin >> t;

    for (int x = 0; x < t; x++) {
        bool istrue = true;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &arr[i]);
        }
        sort(arr + 1, arr + n + 1, greater<int>());
        
        prefix_arr[1] = arr[1];
        for (int i = 2; i <= n; i++) {
            prefix_arr[i] = arr[i] + prefix_arr[i - 1];
        }
        if (prefix_arr[n] % 2) {
            istrue = false;
        }

        long long int lower = n;
        for (int k = 1; k <= n && istrue; k++) {
            while (arr[lower] <= k && lower > k)
                lower--;
            lower++;

            long long int post_sum = k * (lower - k - 1) + prefix_arr[n] - prefix_arr[lower - 1];

            if (prefix_arr[k] > ((long long int)k)*(k-1) + post_sum)
                istrue = false;
        }

        if (istrue)
            printf("Possible\n");
        else 
            printf("Not possible\n");

    }
}