#include <bits/stdc++.h>
#define INGREDIENTS 3

using namespace std;

string s;
int takes[INGREDIENTS];
int stored[INGREDIENTS];
int price[INGREDIENTS];
long long int rubles;

bool can_make_x(long long int x)
{
    long long int total_cost = 0;
    for (int i = 0; i < INGREDIENTS && total_cost <= rubles; i++) {
        long long int would_take = x * takes[i];
        if (stored[i] < would_take)
            total_cost += price[i] * (would_take - stored[i]);
    }

    return total_cost <= rubles;
}

int main(void)
{
    ios::sync_with_stdio(0);

    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'B')
            takes[0]++;
        else if (s[i] == 'S')
            takes[1]++;
        else 
            takes[2]++;
    }

    for (int i = 0; i < INGREDIENTS; i++)
        cin >> stored[i];
    for (int i = 0; i < INGREDIENTS; i++)
        cin >> price[i];
    cin >> rubles;

    long long int l = 0; //can_make_x(l) = true
    long long int r = 1; //can_make_x(r) = false
    while (can_make_x(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        auto mid = (r + l) / 2;
        if (can_make_x(mid))
            l = mid;
        else 
            r = mid;
    }
    cout << l << endl;
    return 0;
}