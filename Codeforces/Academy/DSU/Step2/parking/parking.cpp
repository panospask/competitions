#include <bits/stdc++.h>
#define MAXN 300000

using namespace std;

struct dsu {

    int size;
    vector<int> rep;

    void init(int n) {
        size = n;
        rep.resize(size + 2);
        for (int i = 0; i <= size; i++)
            rep[i] = i;
    }

    int get(int a) {
        if (rep[a] != a && rep[a] != -1)
            rep[a] = get(rep[a]);

        return rep[a];
    }

    // Add a to b, not vice versa
    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        rep[a] = b;
    }
};

int n;
int a[MAXN + 2];
struct dsu Parking;

int main(void)
{
    scanf("%d", &n);
    Parking.init(n);
    Parking.unite(n, 0);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    for (int i = 0; i < n; i++) {
        int ans = Parking.get(a[i]);
        printf("%d\n", ans + 1); // 1-based

        // Remove the current spot
        Parking.unite(ans, ans + 1);
    }

    return 0;
}
