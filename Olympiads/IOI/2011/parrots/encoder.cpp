#include "encoder.h"
#include "encoderlib.h"
#include <vector>
#include <iostream>

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

// dp[i][j]: Number of sequences of length i + 1 that start with j
static vector<vector<BigNum>> dp;

// pref[i][j]: Number of sequences of length i + 1 and first number at most j
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

void construct_sequence(BigNum num, int MAXC, int r)
{
    if (r == 0) {
        send(num.num[0] - 1);
        return;
    }

    int c = MAXC;

    while (c >= 0 && pref[r][c] >= num)
        c--;
    if (c >= 0) {
        num = num - pref[r][c];
    }
    c++;

    send(c);

    construct_sequence(num, c, r - 1);

}

void encode(int N, int M[])
{
    if (!done) {
        calculate_dp();
        done = true;
    }

    int i;
    vector<int> v;
    for(i=0; i<N; i++)
        v.push_back(M[i]);

    while (v.size() && v.back() == 0)
        v.pop_back();

    BigNum num(v);
    BigNum b(1);
    num = num + b;

    BigNum tot(0);
    int r = 0;
    int c = 0;
    while (tot + pref[r][BASE - 1] < num) {
        tot = tot + pref[r][BASE - 1];
        r++;
    }

    while (tot + dp[r][c] < num) {
        tot = tot + dp[r][c];
        c++;
    }

    num = num - tot;
    send(c);

    if (r != 0)
        construct_sequence(num, c, r - 1);
}
