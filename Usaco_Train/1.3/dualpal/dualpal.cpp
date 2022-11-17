/*
ID: panos.p1
LANG: C++
TASK: dualpal
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

bool check_pal(vector<int>& num)
{
    bool isgood = true;
    for (int i = 0; i < num.size() / 2 && isgood; i++) {
        if (num[i] != num[num.size() - 1 - i])
            isgood = false;
    }

    return isgood;
}

vector<int> trans_to(int num, int base)
{
    vector<int> transformed;
    while (num > 0) {
        transformed.pb(num % base);
        num /= base;
    }

    reverse(transformed.begin(), transformed.end());
    return transformed;
}

int main(void)
{
    freopen("dualpal.in", "r", stdin);
    freopen("dualpal.out", "w", stdout);

    int n, s;
    scanf("%d %d", &n, &s);

    int curnum = 0;
    int cur_test = s + 1;
    while (curnum < n) {
        int pals =0;
        vector<int> deg;
        for (int i = 2; i <= 10 && pals < 2; i++) {
            deg = trans_to(cur_test, i);
            if (check_pal(deg))
                pals++;
        }

        if (pals >= 2) {
            curnum++;
            printf("%d\n", cur_test);
        }

        cur_test++;
    }
}