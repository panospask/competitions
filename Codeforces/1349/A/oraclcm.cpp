#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<int> a;
int maxele = 0;

vector<int> primes;
vector<int> least_oc[2];
vector<int> maxdiv;
vector<bool> iscomp;

int main(void)
{
    scanf("%d", &n);
    a.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        maxele = max(maxele, a[i]);
    }

    maxdiv.assign(maxele + 2, 1);
    iscomp.assign(maxele + 2, false);
    for (int num = 2; num <= maxele; num++) {
        if (!iscomp[num]) {
            primes.push_back(num);
        }

        for (int j = 0; j < primes.size() && (ll)num * primes[j] <= maxele; j++) {
            if (num % primes[j] == 0)
                break;
            iscomp[num * primes[j]] = true;
        }
    }

    // Find for all primes the 2 times they appear the least
    least_oc[0].assign(primes.size(), INT_MAX);
    least_oc[1].assign(primes.size(), INT_MAX);

    for (int i = 0; i < primes.size(); i++) {
        least_oc[0][i] = least_oc[1][i] = 1e9;
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            while (a[j] % primes[i] == 0) {
                a[j] /= primes[i];
                cnt++;
            }

            if (cnt < least_oc[0][i]) {
                least_oc[1][i] = least_oc[0][i];
                least_oc[0][i] = cnt;
            }
            else if (cnt < least_oc[1][i]) {
                least_oc[1][i] = cnt;
            }

            if (least_oc[1][i] == 0)
                break;
        }
    }

    long long ans = 1;
    for (int i = 0; i < primes.size(); i++) {
        for (int j = 0; j < least_oc[1][i]; j++)
            ans *= primes[i];
    }

    printf("%lld\n", ans);
    return 0;
}