#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXBASE 15000

using namespace std;

typedef pair<int, int> ii;

int k;
int n1, n2;
long long int dp[2][MAXBASE + 10];

long long int base_b_to_base_10(int n, int b, int v)
{
    if (dp[v][b] != 0)
        return dp[v][b];

    long long int num = 0;
    int i = 0;
    // It is three digits

    num = n % 10;
    n /= 10;
    num += (n % 10) * (long long int)b;
    n /= 10;
    num += (n % 10) * (long long int)b * b;

    dp[v][b] = num;
    return num;
}

ii pair_of_bases(int num1, int num2)
{
    memset(dp, 0, sizeof(dp));
    int b1, b2;
    long long int fnum1, fnum2;
    bool found = false;
    ii ans;

    for (b1 = 10; b1 <= MAXBASE && !found; b1++) {
        fnum1 = base_b_to_base_10(num1, b1, 0);
        for (b2 = b1 + 1; b2 <= MAXBASE && !found; b2++) {
            fnum2 = base_b_to_base_10(num2, b2, 1);
            if (fnum1 == fnum2) { 
                found = true;
                ans = mp(b1, b2);
            }
            else if (fnum1 < fnum2)
                break;
        }
    }

    return ans;
}

int main(void)
{
    freopen("whatbase.in", "r", stdin);
    freopen("whatbase.out", "w", stdout);

    scanf("%d", &k);
    int b1, b2;
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &n1, &n2);
        if (n1 > n2) {
            // The base of n1 is smaller than the one of n2

            tie(b1, b2) = pair_of_bases(n1, n2);
        }
        else {
            // The base of n1 is bigger than the one of n2

            tie(b2, b1) = pair_of_bases(n2, n1);
        }

        printf("%d %d\n", b1, b2);
    }

    return 0;
}