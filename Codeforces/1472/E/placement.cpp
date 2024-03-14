#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Friend {
    int height;
    int weight;
    int id;
};
const Friend DEFAULT = {INT_MAX, INT_MAX, -2};

bool h_comp(const Friend& a, const Friend& b)
{
    return a.height < b.height;
}
bool w_comp(const Friend& a, const Friend& b)
{
    return a.weight < b.weight;
}

int N;
vector<Friend> heights;
vector<Friend> weights;
vector<Friend> friends;
vector<Friend> ans;
vector<Friend> h_pref;

Friend invert(Friend a)
{
    return {a.weight, a.height, a.id};
}

void solve(void)
{
    scanf("%d", &N);

    friends.resize(N);
    heights.resize(N);
    weights.resize(N);
    ans.assign(N, DEFAULT);
    h_pref.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &friends[i].height, &friends[i].weight);
        friends[i].id = i;
        heights[i] = weights[i] = friends[i];
    }
    sort(heights.begin(), heights.end(), h_comp);
    sort(weights.begin(), weights.end(), w_comp);

    h_pref[0] = DEFAULT;
    for (int i = 0; i < N; i++) {
        h_pref[i + 1] = min(h_pref[i], heights[i], w_comp);
    }

    for (int i = 0; i < N; i++) {
        // Check H-H, W-W first
        int pos = lower_bound(heights.begin(), heights.end(), friends[i], h_comp) - heights.begin();
        if (w_comp(h_pref[pos], friends[i])) {
            ans[i] = h_pref[pos];
        }

        // Check H-W, W-H second
        pos = lower_bound(heights.begin(), heights.end(), invert(friends[i]), h_comp) - heights.begin();
        if (w_comp(h_pref[pos], invert(friends[i]))) {
            ans[i] = h_pref[pos];
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i].id + 1);
    }
    printf("\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}