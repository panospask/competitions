/*
ID: panos.p1
LANG: C++
TASK: crypt1
*/

#include <bits/stdc++.h>

#define pb push_back

using namespace std;

map<int, bool> dig_exist;
vector<int> diglist;

bool cor(int num1, int num2)
{
    int d1 = num2 % 10;
    int d2 = num2 / 10;

    int first_check = num1 * d1;
    bool istrue = true;
    int cnt = 0;
    for (int x = first_check; x > 0 && istrue; x /= 10) {
        int dig = x % 10;
        cnt++;
        if (!dig_exist[dig] || cnt > 3)
            istrue = false;
    }

    if (!istrue || cnt != 3)
        return false;

    int second_check = num1 * d2;
    istrue = true;
    cnt = 0;
    for (int x = second_check; x > 0 && istrue; x /= 10) {
        int dig = x % 10;
        cnt++;
        if (!dig_exist[dig] || cnt > 3)
            istrue = false;
    }

    if (!istrue || cnt != 3)
        return false;

    int third_check = first_check + 10 * second_check;
    cnt = 0;
    istrue = true;
    for (int x = third_check; x > 0 && istrue; x /= 10) {
        int dig = x % 10;
        cnt++;
        if (!dig_exist[dig] || cnt > 4)
            istrue = false;
    }

    if (!istrue || cnt != 4)
        return false;

    return true;
}

int main(void)
{
    freopen("crypt1.in", "r", stdin);
    freopen("crypt1.out", "w", stdout);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        diglist.pb(num);
        dig_exist[num] = true;
    }

    long long int total = 0;
    for (auto dig1 : diglist)
        for (auto dig2 : diglist)
            for (auto dig3 : diglist)
                for (auto dig4 : diglist)
                    for (auto dig5 : diglist) {
                        if (cor(dig1 * 100 + dig2 * 10 + dig3, dig4 * 10 + dig5))
                            total++;
                    }

    printf("%lld\n", total);
    return 0;
}