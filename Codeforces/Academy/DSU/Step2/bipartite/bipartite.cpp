#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size = 0;
    vector<int> rep;
    vector<int> parity_w_rep;

    void init(int n) {
        size = n;
        rep.resize(n);
        parity_w_rep.assign(size, 0);

        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    // (x,y) is the rep and the parity to it
    pair<int, int> get(int a) {
        if (rep[a] != a) {
            auto ans = get(rep[a]);
            rep[a] = ans.first;
            parity_w_rep[a] = (parity_w_rep[a] + ans.second) % 2;
        }

        return make_pair(rep[a], parity_w_rep[a]);
    }

    // Add edge between a and b
    void unite(int a, int b) {
        auto p1 = get(a);
        auto p2 = get(b);
        if (p1.first == p2.first) {
            assert(p1.second == p2.second);
            return;
        }

        rep[p1.first] = p2.first;
        parity_w_rep[p1.first] = (p1.second + p2.second + 1) % 2;
    }
};

struct dsu graph;
int n, m;
int shift = 0;

int main()
{
    scanf("%d %d", &n, &m);
    graph.init(n);

    int op, a, b;
    while (m--) {
        scanf("%d %d %d", &op, &a, &b);
        a = (a + shift) % n;
        b = (b + shift) % n;
        if (op == 0) {
            graph.unite(a, b);
        }
        else {
            bool ans = (graph.get(a).second == graph.get(b).second);

            if (ans == 1) {
                printf("YES\n");
                shift++;
            }
            else
                printf("NO\n");
        }
    }

    return 0;
}
