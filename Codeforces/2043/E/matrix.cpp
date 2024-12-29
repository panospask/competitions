#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(var, pos) (((var) & (1 << pos)) > 0)

using namespace std;

const int MAXLOG = 30;

int N, M;
bool good;

bool solve_bit(vector<vector<int>>& A, vector<vector<int>>& B)
{
    vector<int> rows(N, 0);
    vector<int> tot_rows(N, 0);
    vector<bool> used_rows(N, 0);

    vector<int> columns(M, 0);
    vector<int> tot_columns(M, 0);
    vector<bool> used_columns(M, 0);

    vector<int> r_moves;
    vector<int> c_moves;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            rows[i] += B[i][j];
            columns[j] += B[i][j];
            tot_rows[i]++;
            tot_columns[j]++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (rows[i] == tot_rows[i] || rows[i] == 0) {
            used_rows[i] = true;
            r_moves.pb(i);
        }
    }
    for (int j = 0; j < M; j++) {
        if (columns[j] == tot_columns[j] || columns[j] == 0) {
            used_columns[j] = true;
            c_moves.pb(j);
        }
    }

    int p1 = 0, p2 = 0;
    vector<tuple<int, int, int>> total;
    while (p1 < r_moves.size() || p2 < c_moves.size()) {
        if (p1 < r_moves.size()) {
            int i = r_moves[p1];
            p1++;

            int setbit = 0;
            if (rows[i] == tot_rows[i]) {
                setbit = 1;
            }
            total.pb({0, i, setbit});

            for (int j = 0; j < M; j++) {
                if (used_columns[j]) {
                    continue;
                }

                columns[j] -= B[i][j];
                tot_columns[j]--;

                if (columns[j] == tot_columns[j] || columns[j] == 0) {
                    used_columns[j] = true;
                    c_moves.pb(j);
                }
            }
        }
        else {
            int j = c_moves[p2];
            p2++;

            int setbit = 0;
            if (columns[j] == tot_columns[j]) {
                setbit = 1;
            }
            total.pb({1, j, setbit});

            for (int i = 0; i < N; i++) {
                if (used_rows[i]) {
                    continue;
                }
                
                rows[i] -= B[i][j];
                tot_rows[i]--;

                if (rows[i] == tot_rows[i] || rows[i] == 0) {
                    used_rows[i] = true;
                    r_moves.pb(i);
                }
            }
        }
    }

    reverse(total.begin(), total.end());
    for (auto [is_col, i, setbit] : total) {
        if (is_col) {
            for (int j = 0; j < N; j++) {
                A[j][i] = setbit;
            }
        }
        else {
            for (int j = 0; j < M; j++) {
                A[i][j] = setbit;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    vector<vector<int>> A;
    vector<vector<int>> B;
    A.assign(N, vector<int>(M));
    B.assign(N, vector<int>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    vector<vector<int>> bitA(N, vector<int>(M));
    vector<vector<int>> bitB(N, vector<int>(M));
    good = true;
    for (int b = 0; b < MAXLOG; b++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                bitA[i][j] = CHECK_BIT(A[i][j], b);
                bitB[i][j] = CHECK_BIT(B[i][j], b);
            }
        }

        good = good && solve_bit(bitA, bitB);
    }

    if (good) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
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