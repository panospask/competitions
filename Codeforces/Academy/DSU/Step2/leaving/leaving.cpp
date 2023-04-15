#include <bits/stdc++.h>
 
using namespace std;
 
struct dsu {
 
    int size;
    vector<int> rep;
 
    void init(int n) {
        size = n;
        rep.resize(size + 2);
        for (int i = 0; i < size; i++)
            rep[i] = i;
        rep[size] = -1; // No spots left
    }
 
    int get(int a) {
        if (rep[a] != a && rep[a] != -1)
            rep[a] = get(rep[a]);
 
        return rep[a];
    }
 
    // Add a to the set of b, not vice versa
    void unite(int a, int b) {
        // Do not use rank heuristic, we always want lead b
 
        a = get(a);
        b = get(b);
 
        if (a == b)
            return;
 
        rep[a] = b;
    }
};
 
int n, m;
dsu People;
 
int main()
{
    scanf("%d %d", &n, &m);
    People.init(n);
 
    char op;
    while (m--) {
        scanf(" %c", &op);
        if (op == '-') {
            int a;
            scanf("%d", &a);
            a--;
 
            // The a-th person left, unite with the next to their right
            People.unite(a, a+1);
        }
        else {
            int a;
            scanf("%d", &a);
            a--;
 
            // The rightmost person standing will be the leader of the tree that a is in
            int ans = People.get(a);
            if (ans != -1)
                ans++;
            printf("%d\n", ans);
        }
    }
 
    return 0;
}
