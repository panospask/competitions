#include <bits/stdc++.h>
#define MAXP 200
#define MAXN 10000

using namespace std;

// The log of the max number we can create using the first p primes with a permutaion of i length 
bool saved[MAXP][MAXN + 2];
long double maxvalue[MAXP][MAXN + 2];
int backtrack[MAXP][MAXN + 2];
int d; 
int queries[11];
int maxq;
vector<int> primes;
bool iscomposite[MAXN + 2];

long double find_ans(int primes_allowed, int sum)
{
    if (saved[primes_allowed][sum])
        return maxvalue[primes_allowed][sum];

    if (primes_allowed == 0) return 0;

    maxvalue[primes_allowed][sum] = find_ans(primes_allowed-1, sum);
    backtrack[primes_allowed][sum] = 0;

    int curp = primes[primes_allowed - 1];
    int expo = 1;
    while (curp <= sum) {
        if (maxvalue[primes_allowed][sum] < find_ans(primes_allowed - 1, sum - curp) + log(primes[primes_allowed-1]) * expo) {
            maxvalue[primes_allowed][sum] = find_ans(primes_allowed - 1, sum - curp) + log(primes[primes_allowed-1]) * expo;
            backtrack[primes_allowed][sum] = curp;
        }

        curp *= primes[primes_allowed - 1];
        expo++;
    }

    saved[primes_allowed][sum] = true;
    return maxvalue[primes_allowed][sum];
}

int main(void)
{
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        scanf("%d", &queries[i]);
        maxq = max(maxq, queries[i]);
    }

    for (int i = 2; i <= maxq; i++)
        if (!iscomposite[i]) {
            primes.push_back(i);

            for (int j = 2 * i; j <= maxq; j += i)
                iscomposite[j] = true;
        }

    for (int q = 0; q < d; q++) {
        int cur = queries[q];

        find_ans(min((int)primes.size(), 80), cur);

        vector<int> ans;

        for (int i = min((int)primes.size(), 80); i >= 0; i--) {
            if (backtrack[i][cur])
                ans.push_back(backtrack[i][cur]);
            
            cur -= backtrack[i][cur];
        }
        while (cur) {
            ans.push_back(1);
            cur--;
        }

        sort(ans.begin(), ans.end());

        int curind = 1;
        for (auto cycle : ans) {
            int orind = curind;
            for (int i = 0; i < cycle - 1; i++)
                printf("%d ", ++curind);
            printf("%d ", orind);
            curind = cycle + orind;
        }
        printf("\n");
    }
    return 0;

    return 0;
}