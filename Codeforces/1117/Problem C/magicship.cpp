#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

long long int p_hor[MAXN + 5];
long long int p_ver[MAXN + 5];

int n;
string s;
ii beg, ending;

bool can_reach(long long int days)
{
    long long int v_dist = abs(beg.second + p_ver[n] * (days / n) + p_ver[days % n] - ending.second);
    long long int h_dist = abs(beg.first + p_hor[n] * (days / n) + p_hor[days % n] - ending.first);

    return v_dist + h_dist <= days;
}

int main(void)
{
    cin >> beg.first >> beg.second >> ending.first >> ending.second;
    cin >> n;
    cin >> s;

    p_hor[0] = 0;
    p_ver[0] = 0;
    for (int i = 1; i <= n; i++) {
        p_hor[i] = p_hor[i-1];
        p_ver[i] = p_ver[i-1];
        if (s[i-1] == 'U')
            p_ver[i]++;
        else if (s[i-1] == 'D')
            p_ver[i]--;
        else if (s[i-1] == 'L')
            p_hor[i]--;
        else 
            p_hor[i]++;
    }

    long long int l = 0; //can_reach(l) = false
    long long int r = 1; //can_reach(r) = true
    bool isgood = true;
    while (!can_reach(r)) {
        l = r;
        r *= 2;

        if (r > (long long int)n * (abs(beg.first - ending.first) + abs(beg.second - ending.second))) {
            isgood = false;
            r = -1;
            break;
        }
    }
    while (r > l + 1 && isgood) {
        auto m = (l + r) / 2;
        if (can_reach(m))
            r = m;
        else 
            l = m;
    }

    cout << r << '\n';
    return 0;
}