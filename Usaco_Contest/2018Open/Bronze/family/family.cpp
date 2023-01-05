#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200

using namespace std;

typedef pair<int, int> ii;

struct treenode {
    int id = 0;
    int father = -1;
    int rep = -1;
};
typedef struct treenode TreeNode;

TreeNode nodes[MAXN];
unordered_map<int, string> id_to_name; 
unordered_map<string, int> name_to_id;
int n;
string cow1, cow2;
int curcows = 0;

ii operator +(ii a, ii b)
{
    return mp(a.first + b.first, a.second + b.second);
}

ii node_rep(int node)
{
    if (nodes[node].father == -1)
        return mp(node, 0);
    else    
        return node_rep(nodes[node].father) + mp(0, 1);
}

void create_relationship(int i, int j)
{
    nodes[i].father = j;
}

void print_direct_dec(int kid, int father, int depth)
{
    string kidname = id_to_name[kid];
    string fathername = id_to_name[father];

    if (depth == 1)
        cout << fathername << " is the mother of " << kidname << endl;
    else {
        cout << fathername << " is the ";
        for (int i = 0; i < depth - 2; i++)
            cout << "great-";
        cout << "grand-mother of " << kidname << endl;
    }
}

void printf_aunt_niece(int kid, int aunt, int depth)
{
    string kidname = id_to_name[kid];
    string auntname = id_to_name[aunt];

    if (depth == 1) 
        cout << "SIBLINGS" << endl;
    else {
        cout << auntname << " is the ";
        for (int i = 0; i < depth - 2; i++)
            cout << "great-";
        cout << "aunt of " << kidname << endl;
    }
}

int test_relationship(int i, int j)
{
    ii irep = node_rep(i);
    ii jrep = node_rep(j);

    if (irep.first != jrep.first) {
        printf("NOT RELATED\n");
        return 0;
    }

    ii maxrep, minrep; 
    int maxcow, mincow;
    if (irep.second > jrep.second) {
        maxrep = irep;
        minrep = jrep;
        maxcow = i;
        mincow = j;
    }
    else {
        maxrep = jrep;
        minrep = irep;
        maxcow = j;
        mincow = i;
    }

    // Check if mincow is an ancestor of maxcow
    int fathercow = maxcow;
    int depth = 0;
    while (fathercow != -1 && fathercow != mincow) {
        fathercow = nodes[fathercow].father;
        depth++;
    }

    if (fathercow == mincow) {
        print_direct_dec(maxcow, mincow, depth);
        return 0;
    }

    // Check if mincow is an aunt of maxcow --> mother of mincow is a direct_ance of maxcow
    int connecting_cow = nodes[mincow].father;
    fathercow = maxcow;
    depth = 0;
    while (fathercow != -1 && fathercow != connecting_cow) {
        fathercow = nodes[fathercow].father;
        depth++;
    } 

    if (fathercow == connecting_cow) {
        printf_aunt_niece(maxcow, mincow, depth);
        return 0;
    }


    // They are just cousins
    printf("COUSINS\n");
    return 0;
}

int main(void)
{
    freopen("family.in", "r", stdin);
    freopen("family.out", "w", stdout);

    cin >> n >> cow1 >> cow2;
    string mother, kid;
    int moid, kdid;
    for (int i = 0; i < n; i++) {
        cin >> mother >> kid;

        if (name_to_id.count(mother) == 0) {
            name_to_id[mother] = curcows;
            id_to_name[curcows] = mother;
            curcows++;
        }
        moid = name_to_id[mother];
        if (name_to_id.count(kid) == 0) {
            name_to_id[kid] = curcows;
            id_to_name[curcows] = kid;
            curcows++;
        }
        kdid = name_to_id[kid];

        create_relationship(kdid, moid);
    } 

    test_relationship(name_to_id[cow1], name_to_id[cow2]);
    return 0;
}