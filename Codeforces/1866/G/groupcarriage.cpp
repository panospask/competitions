#include <bits/stdc++.h>

using namespace std;

const int MAXA = 1e9;

struct Carriage {
    int l, r;
    int people;
};

bool operator > (const Carriage& a, const Carriage& b)
{
    return a.r > b.r;
}
bool lsort (const Carriage& a, const Carriage& b)
{
    return a.l < b.l;
}

int N;
vector<Carriage> carriages;
priority_queue<Carriage, vector<Carriage>, greater<Carriage>> active;

bool is_valid(int K)
{
    while (!active.empty()) {
        active.pop();
    }

    int c_p = 0;
    for (int w = 0; w < N; w++) {
        while (c_p < N && carriages[c_p].l <= w) {
            if (carriages[c_p].people) {
                active.push(carriages[c_p]);
            }
            c_p++;
        }

        int rem = K;
        while (rem && active.size()) {
            Carriage cur = active.top();
            active.pop();

            if (cur.r < w) {
                return false;
            }

            int to_rm = min(rem, cur.people);
            rem -= to_rm;
            cur.people -= to_rm;

            if (cur.people) {
                active.push(cur);
            }
        }
    }
    if (!active.empty()) {
        return false;
    }

    return true;
}

int main(void)
{
    scanf("%d", &N);

    carriages.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &carriages[i].people);
    }
    for (int i = 0; i < N; i++) {
        int d;
        scanf("%d", &d);
        carriages[i].l = i - d;
        carriages[i].r = i + d;
    }

    sort(carriages.begin(), carriages.end(), lsort);

    int l = -1; //is_valid(l) == false
    int r = MAXA; //is_valid(r) == true
    while (l + 1 < r) {
        int mid = (l + r) / 2;

        if (!is_valid(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", r);

    return 0;
}