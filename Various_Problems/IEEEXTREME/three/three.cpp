#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const double L3 = 0.47712125472;
const int STORE = 1e9;
typedef int T; 

struct BigNum {
    vector<T> blocks;

    int size(void) {
        return blocks.size();
    }

    void read(void) {
        string s;
        cin >> s;

        reverse(s.begin(), s.end());
        int i = 0;
        while (i < s.size()) {
            blocks.pb(0);
            int v = 1;
            for (int b = 0; b < 9 && i < s.size(); b++) {
                blocks.back() = blocks.back() + v * (s[i] - '0');
                i++;
                v *= 10;
            }
        }
    }
};

BigNum shift(BigNum b, int s)
{
    BigNum res;
    res.blocks.resize(b.size() + s);
    for (int i = 0; i < s; i++) {
        res.blocks[i] = 0;
    }
    for (int i = s; i < res.size(); i++) {
        res.blocks[i] = b.blocks[i - s];
    }

    return res;
}

BigNum operator + (BigNum a, BigNum b)
{
    BigNum res;
    int l = max(a.size(), b.size());
    res.blocks.resize(l);

    int carry = 0;
    for (int i = 0; i < l; i++) {
        res.blocks[i] = carry;
        if (a.size() > i) {
            res.blocks[i] += a.blocks[i];
        }
        if (b.size() > i) {
            res.blocks[i] += b.blocks[i];
        }
        carry = 0;
        if (res.blocks[i] > STORE) {
            carry = 1;
            res.blocks[i] -= STORE;
        }
    }
    if (carry) {
        res.blocks.pb(carry);
    }

    while (res.size() && res.blocks.back() == 0) {
        res.blocks.pop_back();
    }

    return res;
}

bool operator < (BigNum a, BigNum b)
{
    if (a.size() < b.size()) {
        return true;
    }
    else if (b.size() < a.size()) {
        return false;
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a.blocks[i] < b.blocks[i]) {
            return true;
        }
        else if (b.blocks[i] < a.blocks[i]) {
            return false;
        }
    }

    return false;
}

BigNum operator - (BigNum a, BigNum b)
{
    int l = a.size();
    BigNum res;

    int carry = 0;
    for (int i = 0; i < l; i++) {
        if (b.size() <= i) {
            b.blocks.pb(0);
        }
        int v = a.blocks[i] - b.blocks[i] - carry;
        carry = 0;
        if (v < 0) {
            carry = 1;
            v += STORE;
        }

        res.blocks.pb(v);
    }

    while (res.size() && res.blocks.back() == 0) {
        res.blocks.pop_back();
    }

    return res;
}

BigNum multiply(BigNum a, BigNum b)
{
    if (a.size() == 0) {
        return {{}};
    }
    if (b.size() == 0) {
        return {{}};
    }
    if (a.size() == 1 && b.size() == 1) {
        ll ans = (ll)a.blocks[0] * b.blocks[0];

        BigNum res;
        res.blocks.pb(ans % STORE);
        if (ans > STORE) {
            res.blocks.pb(ans / STORE);
        }

        return res;
    }

    int m = max(a.size(), b.size());
    int m2 = m / 2;

    BigNum a1, a2, b1, b2;
    for (int i = 0; i < m2; i++) {
        if (i < a.size()) {
            a2.blocks.pb(a.blocks[i]);
        }
        if (i < b.size()) {
            b2.blocks.pb(b.blocks[i]);
        }
    }
    for (int i = m2; i < m; i++) {
        if (i < a.size()) {
            a1.blocks.pb(a.blocks[i]);
        }
        if (i < b.size()) {
            b1.blocks.pb(b.blocks[i]);
        }
    }

    BigNum r1 = multiply(a1, b1);
    BigNum r2 = multiply(a2, b2);
    BigNum r3 = multiply(a1 + a2, b1 + b2);

    r3 = r3 - (r1 + r2);  
    r1 = shift(r1, 2 * m2);
    r3 = shift(r3, m2);

    BigNum res = r1 + r2 + r3;
    while (res.size() && res.blocks.back() == 0) {
        res.blocks.pop_back();
    }

    return res;
}

int main(void)
{
    ios::sync_with_stdio(false);

    BigNum N;
    N.read();

    if (N.size() == 1 && N.blocks[0] == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<BigNum> pows;
    pows.push_back({{3}});

    int x = 0;

    while (!(N < pows.back())) {
        pows.push_back(multiply(pows.back(), pows.back()));
    }

    BigNum a = pows[pows.size() - 2];
    x += (1 << (pows.size() - 2));
    int i = 1;
    while (i > 0) {
        i = 0;
        while (!(N < multiply(a, pows[i]))) {
            i++;
        }
        if (i == 0) {
            break;
        }

        x += (1 << (i - 1));
        a = multiply(a, pows[i - 1]);
    }

    if (!(a < N)) {
        cout << x << endl;
    }
    else {
        cout << -1 << endl;
    }
}