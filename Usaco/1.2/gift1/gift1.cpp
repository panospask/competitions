/*
ID: panos.p1
LANG: C++
TASK: gift1
*/

#include <bits/stdc++.h>

using namespace std;

map<string, int> balance;
string names[15];
map<string, bool> have_seen;

void make_with_donor(void)
{
    string don;
    int l, money;
    cin >> don;
    scanf("%d %d", &money, &l);

    if (l != 0)
        balance[don] -= (money / l) * l;

    string rec;
    for (int j = 0; j < l; j++) {
        cin >> rec;
        balance[rec] += money / l;
    }

    return;
}

int main(void)
{
    freopen("gift1.in", "r", stdin);
    freopen("gift1.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        cin >> names[i];
    
    for (int i = 0; i < n; i++) {
        make_with_donor();
    }

    for (int i = 0; i < n; i++) {
        cout << names[i] << ' ' << balance[names[i]];
        printf("\n");
    }

    return 0;
}