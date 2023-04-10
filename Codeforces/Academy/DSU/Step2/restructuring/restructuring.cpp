#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size;
    vector<int> rep;

    void init(int n) {
        size = n;
        rep.resize(size);

        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int get(int a) {
        if (a != rep[a])
            rep[a] = get(rep[a]);

        return rep[a];
    }

    // Make a child of b
    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        rep[a] = b;
    }
};

struct dsu Company;
struct dsu Type2Queries;
int n, q;

int main()
{
    scanf("%d %d", &n, &q);
    Company.init(n);
    Type2Queries.init(n);

    int op, x, y;
    while (q--) {
        scanf("%d %d %d", &op, &x, &y);
        // Make 0-based
        op--; x--; y--;

        if (op == 0) {
            Company.unite(x, y);
        }
        else if (op == 1) {
            int cur = Type2Queries.get(x); // If we have already done some range query, return the maximum of it
            while (cur < y) {
                Company.unite(cur, cur + 1);
                Type2Queries.unite(cur, cur + 1); // Unite for future use
                cur = Type2Queries.get(cur); // Get the highest value
            }
        }
        else {
            int ans = Company.get(x) == Company.get(y);
            if (ans) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
    }
    return 0;
}
