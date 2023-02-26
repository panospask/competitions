#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

bool rcomp(long int a, long int b)
{
    return a > b;
}

int n;
multiset<long int> cowpos;
multiset<long int, decltype(rcomp)*> rev_cowpos(rcomp);

bool can_reach_full_right(long int startpos, long int power)
{
    // if (power == 4 && startpos == 6)
    //     cerr << "here";

    bool reached = false;
    int curpos = startpos;
    while (power > 0 && !reached) {
        auto it = cowpos.upper_bound(curpos + power);
        if (it == cowpos.end())
            return true;
        if (*--it == curpos) 
            return false;

        curpos = *it;
        power -= 2;
    }

    return reached;
}

bool can_reach_full_left(long int startpos, long int power)
{
    bool reached = false;
    int curpos = startpos;
    while (power > 0 && !reached) {
        auto it = rev_cowpos.upper_bound(curpos - power);
        if (it == rev_cowpos.end())
            return true;
        if (*--it == curpos) 
            return false;

        curpos = *it;
        power -= 2;
    }

    return reached;  
}

bool can_reach_with_power(long int power)
{
    long int l = 0; //can_reach_full_right(l, power) = false
    long int r = 2000000000; //can_reach_full_right(r, power) = true

    // if (power == 4)
    //     cerr << "here";

    while (r > l + 1) {
        auto m = (l + r) / 2;
        if (can_reach_full_right(m, power))
            r = m;
        else 
            l = m;
    }

    return can_reach_full_left(r, power);
}

int main(void)
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    scanf("%d", &n);
    int cpos;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cpos);
        cowpos.insert(cpos * 2);
        rev_cowpos.insert(cpos * 2);
    }

    long int l = 0; //can_reach_full_power(l) = false
    long int r = 1000000000; //can_reach_full_power(r) = true
    while (r > l + 1) {
        auto m = (l + r) / 2;
        if (can_reach_with_power(m))
            r = m;
        else 
            l = m;
    }

    printf("%.1lf\n", (double)r/2);
    return 0;
}