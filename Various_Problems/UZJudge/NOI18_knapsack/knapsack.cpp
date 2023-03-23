#include <bits/stdc++.h>
#define MAXN 100000
#define MAXS 2000

using namespace std;

struct item {
    int copies;
    int value;
    int weight;
};
typedef struct item Item;

typedef pair<int, int> ii;


vector<ii> weight_category[MAXS + 2];
long long int bestval[MAXS + 2];
int n, s;
Item products[MAXN + 2];

int main(void)
{
    scanf("%d %d", &s, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &products[i].value, &products[i].weight, &products[i].copies);
        weight_category[products[i].weight].push_back(make_pair(products[i].value, products[i].copies));
    }

    for (int p = 0; p <= s; p++)
        sort(weight_category[p].rbegin(), weight_category[p].rend());

    bestval[0] = 0;
    int curplace;
    for (int prod = 1; prod <= s; prod++) {
        int optimal = s / prod;
        curplace = 0;
        int proccessed = 0;
        while (curplace < weight_category[prod].size() && proccessed < optimal) {
            if (weight_category[prod][curplace].second == 0) {
                curplace++;
                continue;
            }

            proccessed++;
            int curval = weight_category[prod][curplace].first;
            weight_category[prod][curplace].second--;

            for (int i = s; i >= prod; i--)
                bestval[i] = max(bestval[i], bestval[i - prod] + curval);
        }
    }

    printf("%lld\n", bestval[s]);
    return 0;
}