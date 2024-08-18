#include <bits/stdc++.h>
#include "friend.h"
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;

int N;
vector<int> conf, h, prot;
vector<vector<int>> kids;
vector<vector<int>> friends;
vector<int> par;

vector<vector<int>> dp;

void make_friend(int i, int j)
{
    friends[i].pb(j);
    friends[j].pb(i);
}

int brute_force(void)
{
    friends.resize(N);

    for (int i = 1; i < N; i++) {
        int p = h[i];
        if (prot[i] == 0) {
            make_friend(i, p);
        }
        else if (prot[i] == 1) {
            for (auto v : friends[p]) {
                make_friend(i, v);
            }
        }
        else {
            for (auto v : friends[p]) {
                make_friend(i, v);
            }
            make_friend(i, p);
        }
    }

    int ans = 0, sum = 0;
    vector<int> cur;
    set<int> banned;
    for (int mask = 0; mask < (1 << N); mask++) {
        sum = 0;
        cur.clear();
        banned.clear();

        bool invalid = false;
        for (int i = 0; i < N && !invalid; i++) {
            if (CHECK_BIT(mask, i)) {
                sum += conf[i];
                if (banned.count(i)) {
                    invalid = true;
                    break;
                }
                else {
                    for (auto v : friends[i]) {
                        banned.insert(v);
                    }
                }
            }
        }

        if (!invalid) {
            ans = max(ans, sum);
        }
    }

    return ans;
}

void dfs(int node)
{
    dp[node][0] = 0;
    dp[node][1] = conf[node];

    for (auto kid : kids[node]) {
        dfs(kid);

        dp[node][0] += max(dp[kid][1], dp[kid][0]);
        dp[node][1] += dp[kid][0];
    }
}

int findSample(int n,int confidence[],int host[],int protocol[])
{
    N = n;

    conf.resize(N);
    prot.resize(N);
    h.resize(N);

    bool c0 = true, c1 = true, c2 = true;
    conf[0] = confidence[0];
    for (int i = 1; i < N; i++) {
        conf[i] = confidence[i];
        prot[i] = protocol[i];
        h[i] = host[i];

        c0 = c0 && protocol[i] == 0;
        c1 = c1 && protocol[i] == 1;
        c2 = c2 && protocol[i] == 2;
    }

    if (N <= 10) {
        return brute_force();
    }

    if (c2) {
        sort(conf.begin(), conf.end());
        return conf.back();
    }

    kids.resize(N);

    for (int i = 1; i < N; i++) {
        kids[h[i]].pb(i);
    }

    if (c1) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += confidence[i];
        }

        return sum;
    }
    if (c0) {
        dp.resize(N, vector<int>(2));
        dfs(0);
        return max(dp[0][0], dp[0][1]);
    }

    return 0;
}