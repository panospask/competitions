#include <bits/stdc++.h>
#include "holiday.h"

using namespace std;

typedef long long ll;

const ll INF = 2e18;

vector<ll> dp1;
vector<ll> dp2;

void makemax(ll& a, ll b)
{
    if (a < b) {
        a = b;
    }
}

long long int findMaxAttraction(int N, int start, int d, int attraction[])
{
    if (start == 0) {
        priority_queue<int, vector<int>, greater<int>> q;

        ll ans = 0;
        ll sum = 0;

        for (int i = 0; i < N && i <= d; i++) {
            q.push(attraction[i]);
            sum += attraction[i];

            int rem = d - i;

            while (q.size() > rem) {
                sum -= q.top();
                q.pop();
            }

            makemax(ans, sum);
        }

        return ans;
    }

    d++;

    vector<ll> pref1(d, -INF), suff1(d, -INF);
    vector<ll> pref2(d, -INF), suff2(d, -INF);

    dp1.assign(d, 0);
    for (int i = start + 1; i < N; i++) {
        for (int k = d - 1; k >= 0; k--) {
            dp1[k] = -INF;
            if (k < 2 || dp1[k - 2] == -INF) {
                continue;
            }
            makemax(dp1[k], dp1[k - 2]);

            if (k >= 3 && dp1[k - 3] != -INF) {
                makemax(dp1[k], dp1[k - 3] + attraction[i]);
            }
            makemax(pref1[k], dp1[k]);
        }
    }

    dp1.assign(d, 0);
    for (int i = start - 1; i >= 0; i--) {
        for (int k = d - 1; k >= 0; k--) {
            dp1[k] = -INF;
            if (k < 2 || dp1[k - 2] == -INF) {
                continue;
            }
            makemax(dp1[k], dp1[k - 2]);

            if (k >= 3 && dp1[k - 3] != -INF) {
                makemax(dp1[k], dp1[k - 3] + attraction[i]);
            }

            makemax(suff1[k], dp1[k]);
        }
    }

    dp2.assign(d, 0);
    for (int i = start + 1; i < N; i++) {
        for (int k = d - 1; k >= 0; k--) {
            dp2[k] = -INF;
            if (k < 1 || dp2[k - 1] == -INF) {
                continue;
            }
            makemax(dp2[k], dp2[k - 1]);

            if (k >= 2 && dp2[k - 2] != -INF) {
                makemax(dp2[k], dp2[k - 2] + attraction[i]);
            }

            makemax(pref2[k], dp2[k]);
        }
    }

    dp2.assign(d, 0);
    for (int i = start - 1; i >= 0; i--) {
        for (int k = d - 1; k >= 0; k--) {
           dp2[k] = -INF;
            if (k < 1 || dp2[k - 1] == -INF) {
                continue;
            }
            makemax(dp2[k], dp2[k - 1]);

            if (k >= 2 && dp2[k - 2] != -INF) {
                makemax(dp2[k], dp2[k - 2] + attraction[i]);
            }

            makemax(suff2[k], dp2[k]);
        }
    }

    suff1[0] = 0;
    suff2[0] = 0;
    pref1[0] = 0;
    pref2[0] = 0;


    d--;
    ll res = 0;
    for (int p1 = 0; p1 <= d; p1++) {
        int p2 = d - p1;

        makemax(res, suff1[p1] + pref2[p2]);
        makemax(res, suff2[p1] + pref1[p2]);
        if (p1) {
            makemax(res, suff1[p1 - 1] + attraction[start] + pref2[p2]);
            makemax(res, suff2[p1 - 1] + attraction[start] + pref1[p2]);
        }
        if (p2) {
            makemax(res, suff1[p1] + attraction[start] + pref2[p2 - 1]);
            makemax(res, suff1[p1] + attraction[start] + pref1[p2 - 1]);
        }
    }

    return res;
}