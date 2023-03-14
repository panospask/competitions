#include <bits/stdc++.h>
#define MODBY (1000000007)

using namespace std;

unsigned long long int n;

const long long int TWO_MOD_INV = 500000004;

int main(void)
{
    scanf("%lld", &n);

    unsigned long long int ans = 0;
    unsigned long long int last_num = 0;
    while (last_num < n) {
        auto cur_first = last_num + 1;
        auto add_val = n / cur_first;
        auto cur_last = n / add_val;

        ans = (ans + ((((((cur_last - cur_first + 1) % MODBY ) * (cur_first % MODBY + cur_last % MODBY) % MODBY) * TWO_MOD_INV % MODBY) % MODBY) * (add_val % MODBY)) % MODBY) % MODBY;
        ans %= MODBY;

        last_num = cur_last;
    }


    printf("%llu\n", ans);
    return 0;
}