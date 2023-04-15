#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rep_parity;

    void init(int n) {
        size = n;
        rep.resize(n);
        rep_parity.assign(n, 0);
        
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    ii get(int a) {
        if (a != rep[a]) {
            ii ans = get(rep[a]);
            rep[a] = ans.first;
            rep_parity[a] = (rep_parity[a] + ans.second) % 2;
        }

        return make_pair(rep[a], rep_parity[a]);
    }

    bool unite(int a, int b) {
        ii r1 = get(a);
        ii r2 = get(b);

        if (r1.first == r2.first) {
            // This edge is at an arleady connected component
            // We need to check if it connects nodes of different colour

            if (r1.second == r2.second) {
                // Connects nodes of same colour
                return false;
            }
            else {
                // Connects nodes of different colour
                return true;
            }
        }

        rep[r1.first] = r2.first;
        rep_parity[r1.first] = (r1.second + r2.second + 1) % 2;

        return true;
    }
};

int n, m;
int ans = -1;
struct dsu graph;

int main(void)
{
    scanf("%d %d", &n, &m);
    graph.init(n);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
    
        if (!graph.unite(a, b)) {
            ans = i + 1;
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}