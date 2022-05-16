/*
USER: 34pdppaskp
LANG: C++
TASK: filiki
*/

#include <bits/stdc++.h>

using namespace std;

bool mod_kid[200005] = {false};
int parents[200005];
vector<int> kids[200005];
int time_taken[200005];
int value [200005];
bool selected[200005] = {false};
int true_i;

void change_kids(int i, bool modify) {
    for (auto kid : kids[i]) {
        time_taken[kid] = time_taken[i] + value[kid];
        change_kids(kid, modify);
        if (modify) 
                mod_kid[kid] = true;
    }
}

int find_max_mod(int n)
{
    int max = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (max < time_taken[i] && mod_kid[i])
            max = time_taken[i];
    }

    return max;
}

int find_max(int n)
{
    int max = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (max < time_taken[i])
            max = time_taken[i];
    }

    return max;
}

int minimize_max(int i, int n) {
    if (selected[i])
        return INT_MAX;

    int max_parent = INT_MAX;
    if (parents[i] != 1)
        max_parent = minimize_max(parents[i], n);
        
    int old_time = time_taken[i];
    time_taken[i] = 0;
    change_kids(i, true);
    int max = find_max_mod(n);
    time_taken[i] = old_time;
    change_kids(i, true);


    if (max_parent > max) {
        true_i = i;
        return max;
    }

    return max_parent;
}

int main(void)
{
    freopen("filiki.in", "r", stdin);
    freopen("filiki.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    time_taken[1] = 0;
    parents[1] = 1;
    int father, time;
    for (int i = 2; i <= n; i++) {
        scanf("%d %d", &father, &time);
        time_taken[i] = time_taken[father] + time;
        kids[father].push_back(i);
        value[i] = time;
        parents[i] = father;
    }

    for (int x = 0; x < k - 1; x++) {
        memset(mod_kid, false, sizeof(mod_kid));
        int max = INT_MIN;
        int maxi = 0;
        for (int i = 2; i <= n; i++) {
            if (time_taken[i] > max) {
                maxi = i;
                max = time_taken[i];
            }
        }
        minimize_max(maxi, n);
        selected[true_i] = true;
        time_taken[true_i] = 0;
        change_kids(true_i, false);

    }

    cout << find_max(n);
}