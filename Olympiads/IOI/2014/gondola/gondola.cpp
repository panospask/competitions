#include "gondola.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9 + 1;
const int MOD = 1e9 + 9;

int valid(int N, int inputSeq[])
{
    set<int> input;

    int mn = INF;
    int mpos = -1;

    for (int i = 0; i < N; i++) {
        inputSeq[i]--;
        if (input.count(inputSeq[i])) {
            return false;
        }
        input.insert(inputSeq[i]);

        if (inputSeq[i] < mn) {
            mn = inputSeq[i];
            mpos = i;
        }
    }

    if (mn >= N) {
        return true;
    }

    for (int i = mpos + 1; i != mpos; i = (i + 1) % N) {
        int target_diff = ((i - mpos) % N + N) % N;
        if (inputSeq[i] < N && inputSeq[i] - mn != target_diff) {
            return false;
        }
    }

    return true;
}

void move(int N, int seq[], int shift)
{
    vector<int> v1(shift);
    vector<int> v2(N - shift);

    for (int i = 0; i < v2.size(); i++) {
        v2[i] = seq[i];
    }
    for (int i = 0; i < v1.size(); i++) {
        v1[i] = seq[i + v2.size()];
    }

    for (int i = 0; i < v1.size(); i++) {
        seq[i] = v1[i];
    }
    for (int i = 0; i < v2.size(); i++) {
        seq[i + v1.size()] = v2[i];
    }
}

int replacement(int N, int gondolaSeq[], int replacementSeq[])
{
    map<int, int> pos;
    int mn = INF;
    int mn_pos = -1;
    int L = 0;

    for (int i = 0; i < N; i++) {
        L = max(L, gondolaSeq[i] - N);
        gondolaSeq[i]--;

        if (gondolaSeq[i] < mn) {
            mn = gondolaSeq[i];
            mn_pos = i;
        }
    }

    int shift = 0;
    if (mn < N) {
        shift = mn - mn_pos;
        shift = (shift % N + N) % N;
    }

    // Shift the gondolasequence 
    move(N, gondolaSeq, shift);
    if (shift && gondolaSeq[mn] != mn) {
        return 0;
    }

    int mx = -1;
    int mx_pos = -1;
    for (int i = 0; i < N; i++) {
        pos[gondolaSeq[i]] = i;

        if (mx < gondolaSeq[i]) {
            mx = gondolaSeq[i];
            mx_pos = i;
        }
    }

    if (mx != N + L - 1) {
        return 0;
    }
    
    vector<int> initial(N);
    for (int i = 0; i < N; i++) {
        initial[i] = i;
    }

    for (int i = N; i < N + L; i++) {
        if (pos.count(i)) {
            replacementSeq[i - N] = initial[pos[i]];
            initial[pos[i]] = i;
        }
        else {
            replacementSeq[i - N] = initial[mx_pos];
            initial[mx_pos] = i;
        }
    }
    for (int i = 0; i < L; i++) {
        replacementSeq[i]++;
    }
    return L;
}

ll calc_pow(ll a, int b)
{
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

int countReplacement(int N, int inputSeq[])
{
    if (!valid(N, inputSeq)) {
        return 0;
    }

    ll res = 1;
    set<int> pos;
    int remaining = N;
    for (int i = 0; i < N; i++) {
        pos.insert(inputSeq[i]);
        if (inputSeq[i] < N) {
            remaining--;
        }
    }
    bool mul = remaining == N;

    int prv = N - 1;
    auto it = pos.upper_bound(prv);

    while (it != pos.end()) {
        int cur = *it;
        res = res * calc_pow(remaining, cur - prv - 1) % MOD;

        prv = cur;
        remaining--;
        it++;
    }

    if (mul) {
        res = res * N % MOD;
    }

    return res;
}
