#include <bits/stdc++.h>
#define test (over_front == UNDER || (over_front == AT && !(over_back == OVER)))
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1e9 + 7;
const int MAXN = 300;
const int MAXDIGITS = 19;

const int SMALLER = 0;
const int EQUAL = 1;
const int BIGGER = 2;

int N, Q;
ll A, B;
vector<int> a;
vector<int> targetnum;

vector<pi> queries;
vector<int> ans;

/* dp[start][i][l][r][cmp]:
 * We have used the first i papers, starting from start
 * Building a number with r - l digits
 * 
 * cmp denotes if that number is less than, equal to, or more than B[l..r)
 */
int dp[MAXN + 1][MAXDIGITS + 1][MAXDIGITS + 1][3];
int prf[MAXN + 1][MAXN + 1];

inline void add(int& a, int b)
{
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    if (a < 0) {
        a += MOD;
    }
}

void process_dp(int start, int i, int l, int r, int cmp)
{
    if (dp[i][l][r][cmp] == 0) {
        return;
    }

    int pos = start + i;
    if (pos == N) {
        return;
    }

    // Skip current paper
    add(dp[i + 1][l][r][cmp], dp[i][l][r][cmp]);

    if (l != 0) {
        // Add paper to the front (to position l - 1)
        int new_cmp;
        if (a[pos] > targetnum[l - 1]) {
            new_cmp = BIGGER;
        }
        else if (a[pos] == targetnum[l - 1]) {
            new_cmp = cmp;
        } 
        else {
            new_cmp = SMALLER;
        }

        add(dp[i + 1][l - 1][r][new_cmp], dp[i][l][r][cmp]);
    }
    if (r != targetnum.size()) {
        // Add paper to the back (to positioin r)
        int new_cmp;
        if (cmp != EQUAL) {
            new_cmp = cmp;
        }
        else {
            if (a[pos] > targetnum[r]) {
                new_cmp = BIGGER;
            }
            else if (a[pos] == targetnum[r]) {
                new_cmp = EQUAL;
            }
            else {
                new_cmp = SMALLER;
            }
        }

        add(dp[i + 1][l][r + 1][new_cmp], dp[i][l][r][cmp]);
    }
}

void make_target(ll target) 
{
    targetnum.clear();
    while (target) {
        targetnum.push_back(target % 10);
        target /= 10;
    }
    reverse(targetnum.begin(), targetnum.end());
}

void init_dp(int start)
{
    for (int j = 0; j + start <= N; j++) {
        for (int l = 0; l <= targetnum.size(); l++) {
            for (int r = l; r <= targetnum.size(); r++) {
                for (int cmp = 0; cmp < 3; cmp++) {
                    dp[j][l][r][cmp] = 0;
                }
            }
        }
    }
    

    for (int l = 0; l <= targetnum.size(); l++) {
        dp[0][l][l][EQUAL] = 1;
    }
}

void calculate(void)
{
    for (int s = 0; s < N; s++) {
        init_dp(s);

        for (int p = 0; p + s < N; p++) {
            for (int l = 0; l <= targetnum.size(); l++) {
                for (int len = 0; len <= targetnum.size(); len++) {
                    int r = l + len;
                    if (r <= targetnum.size()) {
                        for (int c = 0; c < 3; c++) {
                            process_dp(s, p, l, r, c);
                        }
                    }
                }
            }
        }

        for (int p = 0; p + s <= N; p++) {
            prf[s][p] = (dp[p][0][targetnum.size()][EQUAL] + dp[p][0][targetnum.size()][SMALLER]) % MOD;
            for (int digits = 0; digits < targetnum.size(); digits++) {
                for (int c = 0; c < 3; c++) {
                    add(prf[s][p], dp[p][0][digits][c]);
                }
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin >> N >> A >> B;

    a.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    cin >> Q;
    queries.resize(Q);
    ans.assign(Q, 0);
    for (int q = 0; q < Q; q++) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        queries[q] = mp(l, r - l + 1);
    }

    make_target(B);
    calculate();
    for (int q = 0; q < Q; q++) {
        add(ans[q], prf[queries[q].first][queries[q].second]);
    }

    make_target(A - 1);
    calculate();
    for (int q = 0; q < Q; q++) {
        add(ans[q], -prf[queries[q].first][queries[q].second]);
    }

    for (int q = 0; q < Q; q++) {
        cout << ans[q] << endl;
    }

    return 0;
}