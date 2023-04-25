#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, k;
vector<int> a;
vector<int> init_a;
multiset<int> smaller_values;
multiset<int> larger_values;

void small_to_large(void)
{
    int rm = *smaller_values.rbegin();
    smaller_values.erase(smaller_values.find(rm));
    larger_values.insert(rm);

    return;
}
void large_to_small(void)
{
    int rm = *larger_values.begin();
    larger_values.erase(larger_values.begin());
    smaller_values.insert(rm);
}

int main(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i < k)
            init_a.push_back(a[i]);
    }
    sort(init_a.begin(), init_a.end());

    for (int i = 0; i < ((k+(k%2))/2); i++)
        smaller_values.insert(init_a[i]);
    for (int i = (k+k%2)/2; i < k; i++)
        larger_values.insert(init_a[i]);

    for (int i = 0; i <= n-k; i++) {
        int med = *smaller_values.rbegin();
        printf("%d ", med);

        // Remove a[i] and add a[i+k]
        if (a[i] <= med) {
            smaller_values.erase(smaller_values.find(a[i]));
            if (larger_values.size() > smaller_values.size()) {
                large_to_small();
            }
        }
        else {
            larger_values.erase(larger_values.find(a[i]));
            if (smaller_values.size() > larger_values.size() + 1) {
                small_to_large();
            }
        }

        if (smaller_values.empty() || a[i+k] <= *smaller_values.rbegin()) {
            smaller_values.insert(a[i+k]);
            if (smaller_values.size() > larger_values.size() + 1)
                small_to_large();
        }
        else {
            larger_values.insert(a[i+k]);
            if (larger_values.size() > smaller_values.size())
                large_to_small();
        }
    }
    printf("\n");
    return 0;
}