#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define MAXK 1000

using namespace std;

multiset<int> berries_for_a_basket;
int n, k;

int find_element_at(int a)
{
    auto it = berries_for_a_basket.begin();
    int i = 0;
    while (i < a) {
        it++;
        i++;
    }

    return *it;
}

int main(void)
{
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        int curberries;
        scanf("%d", &curberries);
        berries_for_a_basket.insert(curberries);
    }

    while (berries_for_a_basket.size() > k)
        berries_for_a_basket.erase(berries_for_a_basket.begin());
    bool stop_method = false;  
    while (!stop_method) {
        int min_element = *(berries_for_a_basket.begin());
        auto it_max_element = berries_for_a_basket.end();
        int max_element = *--it_max_element;

        int mid = find_element_at(k / 2 - 1);
        if (min_element + mid < max_element) {
            berries_for_a_basket.erase(berries_for_a_basket.find(min_element));
            berries_for_a_basket.erase(berries_for_a_basket.find(max_element));

            berries_for_a_basket.insert(mid);
            berries_for_a_basket.insert(max_element - mid);
        }
        else 
            stop_method = true;
    }

    
    int cur_berries = 0;
    int i = 0;
    for (auto basket : berries_for_a_basket) {
        if (i == k / 2) break;
        i++;
        cur_berries += basket;
    }

    printf("%d\n", cur_berries);
    return 0;
}