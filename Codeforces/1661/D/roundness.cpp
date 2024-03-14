#include <bits/stdc++.h>
#define MAXN 200
#define MAXPOW (25 * MAXN)

using namespace std;

typedef pair<int, int> ii;

int max_two_pow[MAXN + 2][MAXPOW + 2];
int prev_addition[MAXN + 2][MAXPOW + 2];
int n, k;
vector<bool> mem[MAXN][MAXPOW];
vector<bool> isused[MAXN][MAXPOW];

ii numbers[MAXN + 2];

bool used(int ch, int fpow, int i)
{
    if (mem[ch][fpow][i])
        return isused[ch][fpow][i];

    mem[ch][fpow][i] = true;
    
    bool ans;
    if (prev_addition[ch][fpow] == 0)
        ans = false;
    else if (prev_addition[ch][fpow] == i)
        ans = true;
    else {
        ii to_rm = numbers[prev_addition[ch][fpow]];

        ans = used(ch - 1, fpow - to_rm.first, i);
    }

    return isused[ch][fpow][i] = ans;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        long long int num;
        scanf("%lld", &num);

        int fivepow = 0;
        while (num % 5 == 0) {
            fivepow++;
            num /= 5;
        }

        int twopow = 0;
        while (num % 2 == 0) {
            twopow++;
            num /= 2;
        }

        numbers[i+1] = make_pair(fivepow, twopow);
    }

    for (int i = 0; i < k; i++)
        for (int j = 0; j <= MAXPOW; j++) {
            isused[i][j].resize(n + 1, false);
            mem[i][j].resize(n + 1, false);
        }

    for (int i = 0; i <= k; i++)
        memset(max_two_pow[i], -1, sizeof(max_two_pow[i]));
    max_two_pow[0][0] = 0;

    for (int chosen = 0; chosen < k; chosen++) {
        for (int fpow = 0; fpow <= MAXPOW; fpow++) {
            
            if (max_two_pow[chosen][fpow] == -1) continue;

            for (int i = 1; i <= n; i++) {
                ii cur_select = numbers[i];
                if (max_two_pow[chosen][fpow] + cur_select.second > max_two_pow[chosen + 1][fpow + cur_select.first])
                    if (!used(chosen, fpow, i)) {
                        max_two_pow[chosen + 1][fpow + cur_select.first] = max_two_pow[chosen][fpow] + cur_select.second;
                        prev_addition[chosen + 1][fpow + cur_select.first] = i;
                    }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= MAXPOW; i++) 
        ans = max(ans, min(i, max_two_pow[k][i]));

    printf("%d\n", ans);
    return 0;
}