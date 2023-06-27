#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#define pb push_back

using namespace std;

typedef long long ll;

int CHUNK = 1e9;
int MAXPOW = 9;
int pwr[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

struct LongNum {

    vector<int> number;


    int res_mod(int x, int pos = 0) {
        if (pos == number.size())
            return 0;

        int mul = CHUNK % x;

        ll res = number[pos] + (ll)mul * res_mod(x, pos + 1);
        res %= x;
        return res;
    }

    void readnumber(void) {
        number.clear();

        string s;
        cin >> s;

        int curp = s.size() - 1;
        while (curp >= 0) {
            int curadd = 0;
            int curv = 0;
            while (curadd < MAXPOW && curp >= 0) {
                curv += (s[curp--] - '0') * pwr[curadd++];
            }

            number.push_back(curv);
        }
    }
};

LongNum k;
int l;

vector<bool> iscomp;
vector<int> primes;

bool solve_case(void)
{
    k.readnumber();
    cin >> l;

    if (l == 0)
        return false;

    iscomp.assign(l, false);
    for (int i = 2; i < l; i++) {
        if (!iscomp[i]) {
            primes.pb(i);
            if (k.res_mod(i) == 0) {
                cout << "BAD " << i << "\n";
                return true;
            }
        }

        for (int j = 0; j < primes.size() && primes[j] * i < l; j++) {
            iscomp[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }

    cout << "GOOD\n";
    return true;
}

int main(void)
{
    ios::sync_with_stdio(false);

    while (solve_case())
        ;

    return 0;
}