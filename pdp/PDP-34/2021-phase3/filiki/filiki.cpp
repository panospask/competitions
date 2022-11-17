/*
USER: 34pdppaskp
LANG: C++
TASK: filiki
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> kids[200005];
int fathers[200005];
int time_taken[200005];
int value [200005];

void change_kids(int i) {
    for (auto kid : kids[i]) {
        time_taken[kid] = time_taken[i] + value[kid];
        change_kids(kid);
    }
}

int bfs(int latest_rep, int reps_remaining, int n)
{
    if (reps_remaining == 0) {
        int max = 0;
        for (int i = 1; i <= n; i++) {
            if (time_taken[i] > max)
                max = time_taken[i];
        }

        return max;
    }

    int min = INT_MAX;

    for (int i = latest_rep + 1; i <= n; i++) {
        int old_time = time_taken[i];
        time_taken[i] = 0;
        change_kids(i);
        int result = bfs(i, reps_remaining - 1, n);
        if (result < min)
            min = result;
        time_taken[i] = old_time;
        change_kids(i);
    }

    return min;
}


int main(void)
{
    freopen("filiki.in", "r", stdin);
    freopen("filiki.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    time_taken[1] = 0;
    fathers[1] = 1;
    int father, time;
    for (int i = 2; i <= n; i++) {
        scanf("%d %d", &father, &time);
        time_taken[i] = time_taken[father] + time;
        kids[father].push_back(i);
        value[i] = time;
        fathers[i] = father;
    }


    cout << bfs(1, k - 1, n);


}