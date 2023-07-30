#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct Cow {
    int p, x, c;
};

int N, A, B;
vector<int> cones;
vector<int> mooney;
vector<Cow> cows;

int main(void)
{
    // freopen("bribe.in", "r", stdin);
    // freopen("bribe.out", "w", stdout);

    scanf("%d %d %d", &N, &A, &B);

    cows.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &cows[i].p, &cows[i].c, &cows[i].x);
    }

    sort(cows.begin(), cows.end(), [] (const Cow& a, const Cow& b) {return a.x < b.x;});

    cones.resize(B + 1);
    mooney.resize(A + 1);

    for (auto& cur : cows) {
        // Process in reverse => Mooney first, cones after

        for (int v = A - cur.c; v >= 0; v--) {
            mooney[v + cur.c] = max(mooney[v + cur.c], mooney[v] + cur.p);
        }

        for (int v = B; v >= 0; v--) {
            int rem = B - v;

            int discounts = rem / cur.x;
            if (discounts >= cur.c) {
                int res = v + cur.x * cur.c;
                cones[res] = max(cones[res], cones[v] + cur.p);
            }
            else {
                // Apply these discounts and add some mooney
                int res = cur.c - discounts;
                mooney[res] = max(mooney[res], cones[v] + cur.p);
            }
        }

        // Propagate these changes
        for (int v = 1; v <= B; v++) {
            cones[v] = max(cones[v], cones[v - 1]);
        }
        mooney[0] = max(mooney[0], cones[B]);
        for (int v = 1; v <= A; v++) {
            mooney[v] = max(mooney[v], mooney[v - 1]);
        }
    }

    printf("%d\n", mooney[A]);

    return 0;
}