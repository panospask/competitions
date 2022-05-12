#include <bits/stdc++.h>

using namespace std;

struct node {
    long long int max;
    int value;
    int kid1;
    int kid2;
};
typedef struct node Node;
Node tree[5055];



int max_of_node(int node)
{
    Node* cur = &tree[node];
    if (cur->max != -1)
        return cur->max;
    
    cur->max = max(max_of_node(cur->kid1), max_of_node(cur->kid2)) + cur->value;
    return cur->max;
}

int main(void)
{
    freopen("numtri.in", "r", stdin);
    freopen("numtri.out", "w", stdout);

    int n;
    cin >> n;

    int num;
    int i, num_left = (n+1) * n / 2, curline = 1, num_in_line = 0;
    for (i = 1; i <= num_left; i++) {
        cin >> num;
        num_in_line++;
        tree[i].value = num;
        tree[i].max = -1;
        if (curline != n) {
            tree[i].kid1 = i + curline;
            tree[i].kid2 = tree[i].kid1 + 1;
        }
        else {
            tree[i].max = num;
        }
        if (num_in_line == curline) {
            num_in_line = 0;
            curline++;
        }

    }

    cout << max_of_node(1) << endl;
}