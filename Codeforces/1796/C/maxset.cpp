#include <bits/stdc++.h>
#define MOD 998244353

using namespace std;

int l, r;

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int x = 0; x < t; x++) {
        cin >> l >> r;

        int maxsize = 1;
        long long int two_pow = 1;
        long long int num = l;
        while (num * 2 <= r) {
            maxsize++;
            num *= 2;
            two_pow *= 2;
        }
        printf("%d ", maxsize);

        if (maxsize == 1) {
            printf("%d\n", r - l + 1);
            continue;
        }

        int left = l;
        int right = l * 2;
        while (right > left + 1) {
            auto m = (left + right) / 2;
            if (m * two_pow <= r)
                left = m;
            else 
                right = m;
        }

        long long int setsize = ((left - l + 1) % MOD);
        
        
    }
}