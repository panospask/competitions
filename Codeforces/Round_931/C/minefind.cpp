#include <bits/stdc++.h>

using namespace std;

int N, M;

int query(int x, int y)
{
    printf("? %d %d\n", x, y);
    fflush(stdout);
    int a;
    scanf("%d", &a);
    return a;
}

void give_ans(int x, int y)
{
    printf("! %d %d\n", x, y);
    fflush(stdout);
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    // Find the diagonal of one of the mines
    int xysum = query(1, 1) + 2;

    int leftdown_x = min(N, xysum - 1);
    int rightup_y = min(M, xysum - 1);

    // Try leftmost first
    int ans2 = query(leftdown_x, xysum - leftdown_x);

    int possible = leftdown_x - ans2 / 2;
    int ans3 = query(possible, xysum - possible);
    if (ans3 == 0) {
        give_ans(possible, xysum - possible);
        return;
    }

    int ans4 = query(xysum - rightup_y, rightup_y);

    possible = rightup_y - ans4 / 2;
    give_ans(xysum - possible, possible);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}