/*
ID: panos.p1
LANG: C++
TASK: pprime
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int maxnum, minnum;
bool topreach = false;
vector<int> pprimes;

bool isprime(int a)
{
    if (a == 2 || a == 3 || a % 2 == 0 || a % 3 == 0)
        return false;

    if (a > maxnum) {
        topreach = true;
        return false;
    }
    else if (a < minnum)
        return false;

    for (int i = 5; i * i <= a; i += 2)
        if (a % i == 0)
            return false;

    return true;
}

void pal_gen(int size)
{
    bool isodd = size % 2;
    int half = size / 2;
    
    int low = pow(10, half - 1);
    int high = pow(10, half) - 1;
    int num;

    for (int n = low; n <= high && !topreach; n ++) {
        string a = to_string(n);
        string b(a);

        reverse(b.begin(), b.end());

        if (!isodd) {
            a = a + b;
            num = stoi(a);

            if (isprime(num))
                pprimes.pb(num);
        }
        else {
            string s;
            for (int i = 0; i < 10; i++) {
                s = a + to_string(i) + b;
                num = stoi(s);

                if (isprime(num))
                    pprimes.pb(num);
            }
        }
    }
}

int main(void)
{
    freopen("pprime.in", "r", stdin);
    freopen("pprime.out", "w", stdout);

    scanf("%d %d", &minnum, &maxnum);

    string smol = to_string(minnum);
    string big = to_string(maxnum);

    int sm_sz = smol.size();
    int bg_sz = big.size();

    if (minnum <= 5)
        pprimes.pb(5);
    if (minnum <= 7 && maxnum >= 7)
        pprimes.pb(7);

    for (int i = sm_sz; i <= bg_sz; i++)
        pal_gen(i);

    for (auto& num : pprimes)
        printf("%d\n", num);

    return 0;
}