/*
ID: panos.p1
LANG: C++11
TASK: buylow
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 5000
#define MAXB 200

using namespace std;

const int base = (int)10;

struct bignum {
    int num[MAXB];
    int len;

    bignum(void) { len = 1; num[0] = 0;}

    void clear(void) {len = 1; num[0] = 0;}

    void operator += (bignum& b) {
        int maxl = max(this->len, b.len), temp = 0, rem = 0;

        int templ;
        for (int i = 0; i < maxl || rem != 0; i++) {
            temp = rem;

            if (this->len > i) 
                temp += this->num[i];
            if (b.len > i)
                temp += b.num[i];

            this->num[i] = temp % base;
            rem = temp / base;
            templ = i + 1;
        }
        this->len = templ;
    }

    void operator = (bignum& b) {
        int l = b.len;

        for (int i = 0; i < l; i++)
            this->num[i] = b.num[i];
        
        this->len = l;
    }

    void print(void) {
        int l = this->len;

        for (int i = l - 1; i >= 0; i--)
            printf("%d", this->num[i]);
        printf("\n");
    }

}sum, g[MAXN];

int dp[MAXN + 2];
int val[MAXN + 2];
int n;
int maxdp_cnt;
vector<int> maxdp_start;
map<int, bool> found;

int main(void)
{
    freopen("buylow.in", "r", stdin);
    freopen("buylow.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    // Going from front to back because every dp value is depentent on the previous ones
    int maxdp = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;

        for (int j = i - 1; j >= 0; j--) 
            if (dp[j] + 1 > dp[i] && val[j] > val[i])
                dp[i] = dp[j] + 1;

        maxdp = max(maxdp, dp[i]);
    }

    for (int i = 0; i < n; i++) {
        if (dp[i] == 1)
            g[i].len = g[i].num[0] = 1;
        else {
            int goal = dp[i] - 1;
            int last = -1;

            for (int j = i - 1; j >= 0; j--) 
                if (dp[j] == goal && val[j] > val[i] && val[j] != last) {
                    g[i] += g[j];
                    last = val[j];
                }
        }
    }

    int last = -1;
    sum.clear();
    // We need to go backwards in order to find the biggest combinations in case of a tie
    for (int i = n; i >= 0; i--)
        if (dp[i] == maxdp && val[i] != last) {
            sum += g[i];
            last = val[i];
        }

    printf("%d ", maxdp);
    sum.print();
    return 0;
}