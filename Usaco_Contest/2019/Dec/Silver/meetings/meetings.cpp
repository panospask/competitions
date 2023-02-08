#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(1e4 * 5)

using namespace std;

struct cow
{
    int weight;
    int position;
    int direction;
    int index;

    void read_cow(int ind) {
        scanf("%d %d %d", &weight, &position, &direction);
        index = ind;
    }
};
typedef struct cow Cow;

bool operator < (Cow a, Cow b)
{
    return a.position < b.position;
}

Cow cows[MAXN];
int sz, n;
set<Cow> left_moving_cows;
set<Cow> right_moving_cows;
int weight_ttl;
int latest_time = 0;

vector<int> left_cow_pos;
vector<int> right_cow_pos;

int main(void)
{
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);

    scanf("%d %d", &sz, &n);
    for (int i = 0; i < n; i++) {
        cows[i].read_cow(i);
        weight_ttl += cows[i].weight;
        if (cows[i].direction == -1) {
            left_moving_cows.insert(cows[i]);
            left_cow_pos.pb(cows[i].position);
        }
        else {
            right_moving_cows.insert(cows[i]);
            right_cow_pos.pb(cows[i].position);
        }
    }

    sort(left_moving_cows.begin(), left_moving_cows.end());
    sort(right_moving_cows.rbegin(), right_moving_cows.rend());
    Cow leftcow, rightcow;
    int cur_weight = 0;
    Cow to_remove;
    while (2 * cur_weight < weight_ttl) {
        leftcow = *(left_moving_cows.begin());
        rightcow = *(right_moving_cows.rbegin());

        if (leftcow.position < sz - rightcow.position) {
            right_moving_cows.insert(leftcow);
            to_remove = *(right_moving_cows.begin());
            right_moving_cows.erase(to_remove);
            cur_weight += to_remove.weight;

            latest_time = to_remove.position;
        }
        else {
            left_moving_cows.insert(rightcow);
            to_remove = *(left_moving_cows.rbegin());
            left_moving_cows.erase(to_remove);
            cur_weight += to_remove.weight;

            latest_time = sz - to_remove.position;
        }
    }

    // Find the range of cows that every cow will collide with
    int dist_from = 2 * latest_time;
    int curval_low = 0;
    int curval_high = 0;
    long long int collisions;
    for (auto p : left_cow_pos) {
        while (curval_low < right_cow_pos.size() && right_cow_pos[curval_low] < p) {
            curval_low++;
        }
        curval_high = max(curval_high, curval_low);
        while (curval_high < right_cow_pos.size() && right_cow_pos[curval_high] + 2 * latest_time < p) {
            curval_high++;
        }

        collisions += curval_high - curval_low;
    }

    printf("%lld\n", collisions);
    return 0;
}