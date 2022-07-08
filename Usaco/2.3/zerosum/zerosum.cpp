/*
ID: panos.p1
LANG: C++
TASK: zerosum
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n;
string symbols;

set<string> ans;

void sim_array(int sum, bool add, int latest_val, int next_num)
{
    if (next_num > n) {
        if (sum == 0)
            ans.insert(symbols);

        return;
    }

    //Make_next_digit_last
    symbols.pb(' ');
    int to_add = latest_val * 10 + next_num;
    int new_sum = sum;
    if (add) {
        new_sum -= latest_val;
        new_sum += to_add;
    }
    else {
        new_sum += latest_val;
        new_sum -= to_add;
    }
    sim_array(new_sum, add, to_add, next_num + 1);
    symbols.pop_back();

    //Add last digit
    symbols.pb('+');
    sim_array(sum + next_num, true, next_num, next_num + 1);
    symbols.pop_back();

    //Subtract last digit
    symbols.pb('-');
    sim_array(sum - next_num, false, next_num, next_num + 1);
    symbols.pop_back();

    return;
}

int main(void)
{
    freopen("zerosum.in", "r", stdin);
    freopen("zerosum.out", "w", stdout);

    scanf("%d", &n);

    sim_array(1, true, 1, 2);

    for (auto vals : ans) {
        for (int i = 1; i < n; i++)
            printf("%d%c",i, vals[i - 1]);
        printf("%d\n", n);
    }

    return 0;
}