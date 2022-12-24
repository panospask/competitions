#include <bits/stdc++.h>
#define MAXN 100

using namespace std;

typedef pair<int, pair<string, int>> update;

int maxval = 100;
int n;
update logs[MAXN];
set<string> curans;
set<string> lastans;

int changed = 0;

map<string, int> milk;

void upd_ans(void)
{
    lastans = curans;

    int maxmilk = 0;
    for (auto cow : milk) {
        if (cow.second > maxmilk) {
            curans.clear();
            curans.insert(cow.first);
            maxmilk = cow.second;
        }
        else if (cow.second == maxmilk)
            curans.insert(cow.first);
    }

    if (lastans != curans)
        changed++;
}

int main(void) 
{
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &logs[i].first);
        cin >> logs[i].second.first;
        scanf("%d", &logs[i].second.second);
    }

    milk["Bessie"] = 100;
    milk["Elsie"] = 100;   
    milk["Mildred"] = 100;
    curans.insert("Bessie");
    curans.insert("Elsie");
    curans.insert("Mildred");
    sort(logs, logs + n);

    for (int i = 0; i < n; i++) {
        milk[logs[i].second.first] += logs[i].second.second;
        upd_ans();
    }

    printf("%d\n", changed);
    return 0;
}
