#include <bits/stdc++.h>

using namespace std;

const int MAXLOG = 31;

typedef long long ll;
typedef pair<int, int> pi;

int gcd(int a, int b);

struct SparseTable {
    int size;
    vector<vector<int>> table;
    vector<int> lg;

    void build_table(vector<int>& v) {
        for (int i = 0; i < size; i++) {
            table[0][i] = v[i];
        }

        for (int up = 1; up < MAXLOG; up++) {
            for (int i = 0; i < size; i++) {
                int nxt = i + (1 << (up - 1));
                nxt = min(nxt, size - 1);

                table[up][i] = gcd(table[up - 1][i], table[up - 1][nxt]);
            }
        }

        lg[1] = 0;
        for (int i = 2; i <= size; i++) {
            lg[i] = lg[i / 2] + 1;
        }
    }

    void init(vector<int>& v) {
        size = v.size();
        table.assign(MAXLOG, vector<int>(size, 0));
        lg.resize(size + 1);

        build_table(v);
    }

    int calc(int l, int r) {
        if (l == r) {
            return 0;
        }

        int diff = r - l;
        int pwr = lg[diff];

        return gcd(table[pwr][l], table[pwr][r - (1 << pwr)]);
    }
};

int N;
vector<int> A, B;

SparseTable s1, s2;

int gcd(int a, int b)
{
    if (a < b) {
        swap(a, b);
    }

    while (b > 0) {
        a = a % b;
        swap(a, b);        
    }

    return a;
}

int gcd(int a, int b, int c)
{
    return gcd(gcd(a, b), c);
}

tuple<int, int, int, int> answer(int l, int r)
{
    r++;
    return make_tuple(s2.calc(l, r), s1.calc(r, N), s1.calc(l, r), s2.calc(r, N));
}

void solve(void) 
{
    scanf("%d", &N);

    A.resize(N);
    B.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    s1.init(A);
    s2.init(B);

    int ans = 0;
    ll ways = 0;

    for (int l = 0; l < N; l++) {
        int cur = l;
        while (cur < N) {
            auto val = answer(l, cur);

            // Find the last position such that answer(l, r) = answer(l, cur)
            int rmin = cur;
            int rmax = N;
            while (rmin + 1 < rmax) {
                int mid = (rmin + rmax) / 2;

                if (answer(l, mid) == val) {
                    rmin = mid;
                }
                else {
                    rmax = mid;
                }
            }

            int res = gcd(s1.calc(0, l), s2.calc(l, rmax), s1.calc(rmax, N)) + gcd(s2.calc(0, l), s1.calc(l, rmax), s2.calc(rmax, N));

            if (res > ans) {
                ans = res;
                ways = 0;
            }
            if (res == ans) {
                ways += (rmax - cur);
            }

            cur = rmax;
        }
    }

    printf("%d %lld\n", ans, ways);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}