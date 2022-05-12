#include <bits/stdc++.h>

using namespace std;

int n, m, k, restrictions[10][12], ans = 0;

bool check_true (int sequence[])
{
    for (int i = 0; i < n; i++) {
        int correct = 0, wrong_place = 0;
        int could_be_misplaced[m];
        for (int x = 0; x < m; x++)
            could_be_misplaced[x] = 0;

        for (int j = 0; j < k; j++) {
            if (sequence[j] == restrictions[i][j])
                correct++;
            else 
                could_be_misplaced[restrictions[i][j]]++;
        }
        for (int j = 0; j < k; j++) {
            if (sequence[j] == restrictions[i][j])
                continue;
            else if (could_be_misplaced[sequence[j]] > 0) {
                wrong_place++;
                could_be_misplaced[sequence[j]]--;
            }
        }

        if (correct != restrictions[i][k] || wrong_place != restrictions[i][k+1])
            return false;
    }
    return true;
}

void try_all_combos(int current_pos, int sequence[])
{
    if (current_pos == k) {
        if (check_true(sequence))
            ans++;
    }
    else {
        for (int i = 0; i < m; i++) {
            sequence[current_pos] = i;
            try_all_combos(current_pos + 1, sequence);
        }
    }
    

}

int main(void)
{
    freopen("mastermind.in", "r", stdin);
    freopen("mastermind.out", "w", stdout);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k + 2; j++) {
            cin >> restrictions[i][j];
            if (j < k)
                restrictions[i][j]--;
        }

    int sequence[k];
    try_all_combos(0, sequence);
    cout << ans << endl;
}