#include <bits/stdc++.h>

using namespace std;

struct listnode {
    int kid;
    int value;
    listnode* nextnode;
};
typedef struct listnode* ListNode;

void insert_in_list(ListNode from, int to, int value)
{
    while (from->nextnode != NULL) {
        from = from->nextnode;
    }

    from->nextnode = (ListNode) malloc(sizeof(*from->nextnode));
    from->nextnode->kid = to;
    from->nextnode->value = value;
    from->nextnode->nextnode = NULL;
}

int find_best_path(ListNode kids[], int node)
{
    int max = 0;
    for (ListNode kid = kids[node]; kid != NULL; kid = kid->nextnode) {
        int path = find_best_path(kids, kid->kid) + kid->value;
        if (path > max)
            max = path;
    }

    return max;
}

int main(void)
{
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);

    int n;
    cin >> n;

    ListNode kids[n];
    for (int i = 0; i < n; i++) {
        kids[i] = NULL;
    }

    for (int i = 0; i < n - 1; i++) {
        int from, to, value;
        cin >> from >> to >> value;
        from--;
        to--;

        if (kids[from] != NULL) {
            insert_in_list(kids[from], to, value);
        }
        else {
            kids[from] = (ListNode) malloc(sizeof(*kids[from]));
            kids[from]->value = value;
            kids[from]->kid = to;
            kids[from]->nextnode = NULL;
        }
    }

    cout << find_best_path(kids, 0) << endl;
}