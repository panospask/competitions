/*
ID: panos.p1
LANG: C++11
TASK: shopping
*/

#include <bits/stdc++.h>
#define MAXN 100
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

struct offer {
    int size;
    int price;

    ii items[5];

    void readoffer(void) {
        scanf("%d", &size);
        for (int i = 0; i < size; i++)
            scanf("%d %d", &items[i].first, &items[i].second);
        scanf("%d", &price);
    }
};
typedef struct offer Offer;

map<int, int> normprice;
map<int, int> remaining_objects;
int offnum;
Offer offers[MAXN];
bool goodoff[MAXN];
int ans = INT_MAX;
int b;

void dfs(int lastoffer, int curprice)
{
    int goodoffs = 0;
    Offer cur;
    vector<int> currej;
    for (int i = lastoffer; i < offnum; i++) {
        if (goodoff[i]) {
            bool isgood = true;
            cur = offers[i];
            for (int j = 0; j < cur.size && isgood; j++) {
                if (remaining_objects[cur.items[j].first] < cur.items[j].second)
                    isgood = false;
            }

            if (isgood) {
                goodoffs++;
                int newprice = curprice + cur.price;
                for (int j = 0; j < cur.size; j++) {
                    remaining_objects[cur.items[j].first] -= cur.items[j].second;
                }
                dfs(i, newprice);
                for (int j = 0; j < cur.size; j++) {
                    remaining_objects[cur.items[j].first] += cur.items[j].second;
                }
            }
            else {
                goodoff[i] = false;
                currej.pb(i);
            }
        }
    }

    if (goodoffs == 0) {
        int ttl_price = curprice;
        for (auto i : remaining_objects) {
            ttl_price += normprice[i.first] * i.second;
        }

        ans = min(ans, ttl_price);
    }

    for (auto r : currej)
        goodoff[r] = true;
}

int main(void)
{
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);

    scanf("%d", &offnum);
    for (int i = 0; i < offnum; i++) {
        offers[i].readoffer();
        goodoff[i] = true;
    }
    scanf("%d", &b);
    int c, k, p;
    for (int i = 0; i < b; i++) {
        scanf("%d %d %d", &c, &k, &p);
        remaining_objects[c] = k;
        normprice[c] = p;
    }

        dfs(0, 0);

    printf("%d\n", ans);
    return 0;
}