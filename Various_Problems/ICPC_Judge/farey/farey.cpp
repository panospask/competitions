#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 1e6;

vector<int> f;
vector<ll> pref;
vector<int> primes;
vector<int> lpow;

int main(void)
{
    f.resize(MAXN + 1);
    pref.assign(MAXN + 1, 0);
    lpow.assign(MAXN + 1, -1);

    f[1] = 1;
    pref[1] = 0;
    for (int i = 2; i <= MAXN; i++) {
        if (lpow[i] == -1) {
            f[i] = i - 1;
            primes.push_back(i);
            lpow[i] = i;
        }

        for (int j = 0; j < primes.size() && primes[j] * i <= MAXN; j++) {
            if (i % primes[j]) {
                f[i * primes[j]] = f[i] * f[primes[j]];
                lpow[i * primes[j]] = primes[j];
            }
            else {
                if (i == lpow[i]) {
                    f[i * primes[j]] = i * primes[j] - i;
                }
                else {
                    f[i * primes[j]] = f[i / lpow[i]] * f[primes[j] * lpow[i]];
                }

                lpow[i * primes[j]] = lpow[i] * primes[j];
                break;
            }
        }

        pref[i] = pref[i - 1] + f[i];
    }

    int n;
    cin >> n;
    while (n) {
        cout << pref[n] << endl;
        cin >> n;
    }

    return 0;
}