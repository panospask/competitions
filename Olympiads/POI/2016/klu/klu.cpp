#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N;

// match[level][i]: The assigned match for i for every level of the recursion
vector<vector<int>> match;
vector<vector<int>> pos;

void assign_positions(vector<int>& c, int l)
{
    for (int i = 0; i < c.size(); i++) {
        pos[l][c[i]] = i;
    }
}

bool is_solo(int i, int l)
{
    return match[l][i] != match[l + 1][i];
}

// Returns true if there exists a fake match between i and j at level l
bool is_fake(int i, int j, int l)
{
    return match[l][i] == j && is_solo(i, l - 1);
}

// Given a set of 2^i nodes and a perfect matching between them, turn it into a cycle
// using the rules in the problem statement
vector<int> compute(vector<int> nums, int level)
{
    if (nums.size() == 2) {
        return nums;
    }
    // Split the nodes into 2 disjoint sets and solve recursively

    // Ensure there is always at least one edge of the matching between the two sides
    int split = -1;
    for (int b = 0; b < N && split == -1; b++) {
        if (CHECK_BIT(nums[0], b) ^ CHECK_BIT(match[level][nums[0]], b)) {
            split = b;
        }
    }

    // Split and create arbitrary fake edges for the first half
    vector<int> n[2];
    int prv = -1;
    int fake_count = 0;
    for (int i = 0; i < nums.size(); i++) {
        bool v1 = CHECK_BIT(nums[i], split);
        bool v2 = CHECK_BIT(match[level][nums[i]], split);

        n[v1].pb(nums[i]);
        if (v2 == v1) {
            match[level + 1][nums[i]] = match[level][nums[i]];
        }
        else if (!v1) {
            // We are at the first half
            if (prv != -1) {
                // Create fake edge
                match[level + 1][nums[i]] = prv;
                match[level + 1][prv] = nums[i];
                prv = -1;
                fake_count++;
            }
            else {
                prv = nums[i];
            }
        }
    }

    auto r1 = compute(n[0], level + 1);
    assign_positions(r1, level + 1);

    // Create the fake edges for the second half by uniting matches of nodes of the first half that are connected by REAL edges only

    prv = -1;
    for (int i = 0; i < r1.size(); i++) {
        if (is_solo(r1[i], level)) {
            if (prv != -1 && !is_fake(prv, r1[i], level + 1)) {
                match[level + 1][match[level][r1[i]]] = match[level][prv];
                match[level + 1][match[level][prv]] = match[level][r1[i]];
                prv = -1;
            }
            else {
                prv = r1[i];
            }    
        }
    }
    if (prv != -1) {
        int i = 0;
        while (!is_solo(r1[i], level)) {
            i++;
        }

        match[level + 1][match[level][r1[i]]] = match[level][prv];
        match[level + 1][match[level][prv]] = match[level][r1[i]];
    }

    auto r2 = compute(n[1], level + 1);
    if (is_fake(r2.front(), r2.back(), level + 1)) {
        r2.insert(r2.begin(), r2.back());
        r2.pop_back();
    }
    assign_positions(r2, level + 1);

    vector<int> tot;
    tot.pb(r2.front());

    for (int i = 1; i < r2.size(); i++) {
        if (is_fake(r2[i - 1], r2[i], level + 1)) {
            int p = pos[level + 1][match[level][r2[i - 1]]];
            int mod = 1;
            if (is_fake(r1[p], r1[(p + 1) % r1.size()], level + 1)) {
                mod = -1;
            }

            for (int j = p; r1[j] != match[level][r2[i]]; j = (j + mod + r1.size()) % r1.size()) {
                tot.pb(r1[j]);
            }
            tot.pb(match[level][r2[i]]);
        }

        tot.pb(r2[i]);
    }

    return tot;
}

int main(void)
{
    scanf("%d", &N);

    pos.assign(N, vector<int>(1 << N, 0));
    match.assign(N, vector<int>(1 << N, 0));

    vector<int> init;

    for (int i = 0; i < 1 << (N - 1); i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        match[0][u] = v;
        match[0][v] = u;

        init.pb(u);
        init.pb(v);
    }

    auto ans = compute(init, 0);

    for (auto u : ans) {
        printf("%d ", u);
    }
    printf("\n");

    return 0;
}