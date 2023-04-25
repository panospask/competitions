#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct dishstack {
    stack<int> s;
    int minelement;
    int maxelement;

    dishstack(void) {
        minelement = INT_MAX;
        maxelement = INT_MAX;
    }
};
typedef struct dishstack Dishstack;

int n;
vector<Dishstack> soapy;
vector<int> order;
set<int> nums;

bool pop_soapy(int i)
{
    if (soapy[i].s.empty())
        return false;

    while (!soapy[i].s.empty()) {
        soapy[i].minelement = soapy[i].s.top();
        if (soapy[i].s.top() == *nums.begin()) {
            nums.erase(soapy[i].s.top());
            soapy[i].s.pop();
        }
        else
            return false;
    }

    soapy[i].minelement = soapy[i].maxelement = INT_MIN;
    return true;
}

bool can_satisfy(int x)
{
    soapy.clear();
    soapy.resize(x);
    nums.clear();
    for (int i = 0; i <= x; i++)
        nums.insert(order[i]);

    int first_stack = 0;
    for (int i = 0; i <= x; i++) {
        // Place in a stack
        int l = -1;
        int r = x-1;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (soapy[mid].minelement < order[i])
                l = mid;
            else
                r = mid;
        }

        // Place in stack r
        if (r != first_stack && soapy[r-1].maxelement > order[i])
            return false;

        if (soapy[r].s.size() == 0)
            soapy[r].maxelement = order[i];
        soapy[r].minelement = order[i];
        soapy[r].s.push(order[i]);

        if (r == first_stack) {
            while (pop_soapy(first_stack))
                first_stack++;
        }
    }

    return true;
}

int main(void)
{
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);

    scanf("%d", &n);
    order.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &order[i]);

    int l = 0;
    int r = n;
    while (r > l + 1) {
        int mid = (r + l) / 2;
        if (can_satisfy(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%d\n", l + 1);
    return 0;
}