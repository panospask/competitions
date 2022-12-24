#include <bits/stdc++.h>
#define MAXN 100
#define MAXM 100

using namespace std;

vector<int> gave_ans[MAXN][2][2];
int testcases[MAXM];
int n, m;
bool used[MAXN][2];
int left_tcases;

bool check_empty(vector<int>& v)
{
    for (auto t : v)
        if (!testcases[t])
            return false;
    return true;
}

int check_special(int bit, bool bitval)
{
    // Check for outputval == 1
    if (!check_empty(gave_ans[bit][bitval][true])) {
        int g = true;
        for (auto res : gave_ans[bit][bitval][false])
            if (!testcases[res]) {
                g = false;
                break;
            }
        if (g) return 1;
    }

    if (!check_empty(gave_ans[bit][bitval][false])) {
        int g = true;
        for (auto res : gave_ans[bit][bitval][true])
            if (!testcases[res]) {
                g = false;
                break;
            }
        if (g) return 0;
    }

    return 2;
}

void modify_testcases(vector<int>& to_cancel, int mod_by)
{
    for (auto t : to_cancel) {
        testcases[t] += 1 * mod_by;
        if (testcases[t] == 1 && mod_by == 1)
            left_tcases--;
        else if (testcases[t] == 0)
            left_tcases++;
    }
}

int find_nth_case(int i)
{
    if (i == n || left_tcases == 0)
        return true;

    bool found_ans = false;

    for (int j = 0; j < n && !found_ans; j++) {
        if (!used[j][false]) {
            int v = check_special(j, false);
            if (v != 2) {
                modify_testcases(gave_ans[j][false][v], 1);
                used[j][false] = true;
                found_ans = find_nth_case(i + 1);
                break;
            }
        }
        if (!used[j][true] && !found_ans) {
            int v = check_special(j, true);
            if (v != 2) {
                modify_testcases(gave_ans[j][true][v], 1);
                used[j][true] = true;
                found_ans = find_nth_case(i + 1);
                break;
            }
        }
    }

    return found_ans;
}

int main(void)
{
    // freopen("reveng.in", "r", stdin);

    int t;
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                gave_ans[i][j][0].clear();
                gave_ans[i][j][1].clear();

            }
        }
        int curval[MAXN];
        int output;
        left_tcases = m;
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) 
                scanf("%1d", &curval[i]);
            scanf("%1d", &output);

            for (int i = 0; i < n; i++)
                gave_ans[i][curval[i]][output].push_back(j);
        }

        bool truth = find_nth_case(0);

        if (truth)
            printf("OK\n");
        else 
            printf("LIE\n");

        memset(used, false, sizeof(used));
        memset(testcases, false, sizeof(testcases));
    }

    return 0;
}