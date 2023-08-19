#include "decoder.h"
#include "decoderlib.h"
#include <bits/stdc++.h>

using namespace std;

struct BigNum {
    const int BASE = 256;

    // The higher order is back to front
    vector<int> num;

    BigNum(vector<int>& a) {
        num = a;
    }
    BigNum(int a) {
        while (a) {
            num.push_back(a % BASE);
            a /= BASE;
        }
    }
    BigNum(void) {
        ;
    }

    int size(void) {
        return this->num.size();
    }

    bool operator < (const BigNum& L) {
        if (this->num.size() < L.num.size())
            return true;
        else if (this->num.size() > L.num.size())
            return false;

        for (int i = L.num.size() - 1; i >= 0; i--) {
            int a = this->num[i];
            int b = L.num[i];

            if (a < b)
                return true;
            if (b < a)
                return false;
        }

        return false;
    }
    bool operator == (BigNum& L) {
        return !(*this < L) && !(L < *this);
    }
    bool operator <= (BigNum& L) {
        return (*this < L) || (*this == L);
    }
    bool operator > (BigNum& L) {
        return !(*this <= L);
    }
    bool operator >= (BigNum& L) {
        return !(*this < L);
    }

    void operator = (BigNum L) {
        this->num = L.num;
    }

    BigNum operator + (BigNum& L) {
        BigNum c;
        int keep = 0;
        for (int i = 0; i < max(L.size(), this->size()); i++) {
            int v = keep;
            keep = 0;
            if (i < L.size())
                v += L.num[i];
            if (i < this->size())
                v += this->num[i];

            if (v >= BASE) {
                keep = 1;
                v -= BASE;
            }
            c.num.push_back(v);
        }
        if (keep)
            c.num.push_back(keep);

        return c;
    }

    BigNum operator - (BigNum& L) {
        BigNum c;
        int rem = 0;
        for (int i = 0; i < this->size(); i++) {
            int v = this->num[i] - rem;
            rem = 0;
            if (i < L.size())
                v -= L.num[i];

            if (v < 0) {
                v += BASE;
                rem = 1;
            }

            c.num.push_back(v);
        }
        while (c.size() && c.num.back() == 0)
            c.num.pop_back();

        return c;
    }
};

static int BASE = 256;
static int TOP = 400;

// dp[i][j] : Number of sequences of length i with the first number beeing AT MOST
static vector<vector<BigNum>> dp;
static vector<vector<BigNum>> pref;

static bool done = false;

static void calculate_dp(void)
{
    dp.assign(TOP, vector<BigNum>(BASE, (BigNum)(0)));
    pref.resize(TOP, vector<BigNum>(BASE));
    for (int i = 0; i < TOP; i++) {
        for (int j = 0; j < BASE; j++) {
            if (i) {
                dp[i][j] = pref[i - 1][j];
            }
            else {
                dp[0][j] = 1;
            }
        }
        pref[i][0] = dp[i][0];
        for (int j = 1; j < BASE; j++) {
            pref[i][j] = dp[i][j] + pref[i][j - 1];
        }
    }
}

// Returns the number of all sequences of length r with maximum number LESS THAN c
BigNum count(int r, int c)
{
    if (!c)
        return BigNum(0);
    return pref[r][c - 1];
}

void decode(int N, int L, int X[])
{
    if (!done) {
        calculate_dp();
        done = true;
    }


    sort(X, X + L);
    reverse(X, X + L);

    BigNum num(0);
    for (int r = 0; r < L - 1; r++)
        num = num + pref[r][BASE - 1];
    if (X[0])
        num = num + pref[L - 1][X[0] - 1];

    for (int i = 1; i < L; i++) {
        BigNum c = count(L - i - 1, X[i]);
        num = num + c;
    }

    // BigNum b(1);
    // num = num - b;

    while (num.size() < N)
        num.num.push_back(0);
    for (int i = 0; i < N; i++)
        output(num.num[i]);
}