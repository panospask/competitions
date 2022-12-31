#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int cowplace[MAXN];
vector<int> before[MAXN + 2];
int must_place[MAXN + 2];
int stubborn_no_hierarchy_cows_ahead[MAXN + 2];
bool in_hier[MAXN + 2];
int n, m, k;
int cur_place;

int find_earliest_spot(int cow)
{
    if (must_place[cow] != -1) {
        cur_place = must_place[cow];
        return must_place[cow];
    }

    for (int i = cur_place + 1; i < n; i++) 
        if (cowplace[i] == -1) {
            cur_place = i;
            return i;
        }

    return -1;
}


int main(void)
{
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        must_place[i] = -1;
        cowplace[i] = -1;
    }

    int prev;
    scanf("%d", &prev);
    prev--;
    cur_place = -1;
    int cur;
    for (int i = 0; i < m - 1; i++) {
        scanf("%d", &cur);
        before[--cur] = before[prev];
        before[cur].pb(prev);
        prev = cur;
        in_hier[prev] = true;
        in_hier[cur] = true;
    }

    int spot;
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &cur, &spot);
        must_place[--cur] = --spot;
        cowplace[spot] = cur;
    }
    stubborn_no_hierarchy_cows_ahead[0] = 0;
    for (int i = 1; i < n; i++) {
        stubborn_no_hierarchy_cows_ahead[i] = stubborn_no_hierarchy_cows_ahead[i - 1];
        if (cowplace[i - 1] != -1 && !in_hier[i - 1])
            stubborn_no_hierarchy_cows_ahead[i]++;
    }

    int ans;
    if (before[0].size() != 0) {
        // Find earliest spot for all before cow 0(1 in the question)
        for (auto cow : before[0])
            find_earliest_spot(cow);
        ans = find_earliest_spot(0);
    }
    else {
        bool can_place = true;
        int free_spot_ahead = 0;
        for (int i = n - 1; i >= 0 && can_place; i--) {
            if (cowplace[i] == -1) {
                if (i - free_spot_ahead >= 0) {
                    ans = i;
                    free_spot_ahead--;
                }
                else 
                    can_place = false;
            }
            else {
                free_spot_ahead = before[cowplace[i]].size() + stubborn_no_hierarchy_cows_ahead[i];
            }
        }

        if (must_place[0] != -1)
            ans = must_place[0];
    }

    printf("%d\n", ans + 1);
    return 0;
}