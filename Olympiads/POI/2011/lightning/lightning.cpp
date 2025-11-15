#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

vector<int> ceilsqrt;
struct Func {
    /// a + sqrt(x - b)
    int a, b;

    // Returns ceil of evaluation
    double eval(int x) {
        return a + sqrt(x - b);
    }
};

int N;
vector<int> H;
vector<int> ans;

// Returns the intersection point x, rounded up
// We assume that f1 is better in (sth, x) and f2 is better in [x, +inf)
// In other words, it returns the first integer point in which f2 is better
int intersect(Func f1, Func f2) {
    int l = (f2.b) - 1;
    int r = N + 1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (f1.eval(mid) <= f2.eval(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    return r;
}

void precalculate(void) {
    ceilsqrt.resize(N + 2);
    int cur = 0;
    for (int i = 0; i <= N + 1; i++) {
        while (cur * cur < i) {
            cur++;
        }
        ceilsqrt[i] = cur;
    }
}

deque<Func> hull;

void process(vector<int>& H, vector<int>& ans) {
    hull.clear();

    hull.pb({0, 0});
    for (int i = 0; i < N; i++) {
        while (hull.size() >= 2) {
            if (hull[0].eval(i) <= hull[1].eval(i)) {
                hull.pop_front();
            }
            else {
                break;
            }
        }

        ans[i] = max(ans[i], (int)ceil(hull[0].eval(i)));

        if (hull.back().a >= H[i]) {
            // This is just a bad line
            continue;
        }

        Func cur = {H[i], i};
        int sz = hull.size();
        while (sz >= 2) {
            int x = intersect(hull[sz - 2], hull[sz - 1]);
            if (x >= i && hull[sz - 1].eval(x) <= cur.eval(x)) {
                hull.pop_back();
                sz--;
            }
            else {
                break;
            }
        }
        hull.push_back(cur);
    }
}

int main(void) {
    
    scanf("%d", &N);
    H.resize(N);
    ans.assign(N, 0);
    precalculate();

    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }

    process(H, ans);

    reverse(H.begin(), H.end());
    reverse(ans.begin(), ans.end());
    process(H, ans);
    reverse(H.begin(), H.end());
    reverse(ans.begin(), ans.end());

    for (int i = 0; i < N; i++) {
        printf("%d\n", max(0, ans[i] - H[i]));
    }
}