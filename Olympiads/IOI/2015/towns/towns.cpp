#include "towns.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int N;
int diameter = 0;
int hubdist = 0;

int v, s, t;

vector<int> d1;
vector<int> d2;

void findAll(int u, vector<int>& d)
{
    d.resize(N);

    d[u] = 0;
    for (int i = 0; i < N; i++) {
        if (i != u) {
            d[i] = getDistance(u, i);
        }
    }
}

int getPos(vector<int>& d)
{
    int m_i = -1;
    int m_v = -1;

    for (int i = 0; i < N; i++) {
        if (d[i] > m_v) {
            m_i = i;
            m_v = d[i];
        }
    }

    return m_i;
}

int distance(int i, int j)
{
    if (i == v) {
        return d1[j];
    }
    else if (j == v) {
        return d1[i];
    }
    else if (i == s) {
        return d2[j];
    }
    else if (j == s) {
        return d2[i];
    }

    return getDistance(i, j);
}

int distFromS(int node)
{
    int commonpath = 0;

    if (node != v) {
        commonpath = (distance(node, v) + distance(node, s) - distance(v, s)) / 2;
    }
    else {
        commonpath = (distance(node, t) + distance(node, s) - diameter) / 2;
    }

    return distance(s, node) - commonpath;
}

bool sameBranch(int a, int b)
{
    return distance(s, a) + distance(s, b) - distance(a, b) > 2 * hubdist;
}

int hubDistance(int n, int sub) 
{
    N = n;

    v = 0;
    findAll(v, d1);
    s = getPos(d1);
    findAll(s, d2);
    t = getPos(d2);


    diameter = d2[t];

    int ans1 = -1;
    int ans2 = 1e6 + 1;

    int u1 = -1;
    int u2 = -1;

    for (int i = 0; i < N; i++) {
        int res = distFromS(i);

        if (2 * res < diameter) {
            if (ans1 < res) {
                ans1 = res;
                u1 = i;
            }
        }
        else {
            if (ans2 > res) {
                ans2 = res;
                u2 = i;
            }
        }
    }

    int opt = min(ans2, diameter - ans1);
    if (ans2 != opt) {
        u2 = -1;
    }
    if (diameter - ans1 != opt) {
        u1 = -1;
    }

    if (u1 != -1 && u2 != -1) {
        // Find the best
        int bef = 0, at = 0, aft = 0;

        for (int i = 0; i < N; i++) {
            int res = distFromS(i);
            if (res < ans1) {
                bef++;
            }
            else if (res == ans1) {
                at++;
            }
            else {
                aft++;
            }
        }

        if (at + bef <= N / 2) {
            u1 = -1;
        }
        else {
            u2 = -1;
        }
    }

    // The hub is the projection of small town i into the diameter
    int hub = u1 != -1 ? u1 : u2;
    hubdist = distFromS(hub);
    assert(hubdist == ans1 || hubdist == ans2);

    bool balanced;
    vector<int> special;
    for (int i = 0; i < N; i++) {
        int res = distFromS(i);
        if (res >= hubdist) {
            special.push_back(i);
        }
    }
    balanced = (N - special.size()) <= N / 2;
    if (!balanced) {
        return -opt;
    }

    vector<int> bucket, row;

    for (auto u : special) {
        if (row.empty()) {
            row.push_back(u);
            continue;
        }

        int last = row.back();
        if (sameBranch(last, u)) {
            bucket.push_back(u);
        }
        else {
            row.push_back(u);
            if (!bucket.empty()) {
                row.push_back(bucket.back());
                bucket.pop_back();
            }
        }
    }

    int T = row.back();
    row.pop_back();

    int cnt = 1;
    while (row.size() >= 2 && cnt >= 0 && cnt <= N / 2) {
        int a = row.back();
        row.pop_back();

        if (!sameBranch(a, T)) {
            if (bucket.size()) {
                bucket.pop_back();
            }
            else {
                cnt = -1e6;
            }
        }
        else {
            row.pop_back();
        }
        cnt++;
    }
    if (row.size()) {
        cnt += sameBranch(row.back(), T);
    }
    cnt += bucket.size();

    return cnt <= N / 2 ? opt : -opt;
}