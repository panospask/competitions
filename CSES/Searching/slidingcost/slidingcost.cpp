#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll total_sum = 0;

int n, k;
vector<int> a;
multiset<int, greater<int>> small;
multiset<int> large;
int med;

void balance(void)
{
    if (small.size() > large.size() + 1) {
        small.erase(small.begin());
        large.insert(med);
        int newmed = *small.begin();

        int ch = abs(med - newmed);

        total_sum += (ll)large.size() * ch;
        total_sum -= (ll)small.size() * ch;

        med = newmed;
    }
    else if (large.size() > small.size()) {
        int newmed = *large.begin();
        int ch = abs(med - newmed);

        total_sum += (ll)small.size() * ch;
        total_sum -= (ll)large.size() * ch;

        large.erase(large.find(newmed));
        small.insert(newmed);

        med = newmed;
    }

    assert(*small.begin() == med);
}

void insert_element(int i)
{
    total_sum += abs(med - i);
    if (!small.empty() && *small.begin() >= i) {
        small.insert(i);
    }
    else
        large.insert(i);

    balance();
}

void erase_element(int i)
{
    total_sum -= abs(med - i);

    if (large.find(i) != large.end())
        large.erase(large.find(i));
    else {
        small.erase(small.find(i));
        int nmed = *small.begin();

        int ch  = abs(med - nmed);

        total_sum += (ll) large.size() * ch;
        total_sum -= (ll) small.size() * ch;

        med = nmed;
    }

    balance();
}

int main(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    med = 0;
    total_sum = 0;
    for (int i = 0; i < k; i++)
        insert_element(a[i]);

    for (int i = k; i < n; i++) {
        printf("%lld ", total_sum);
        insert_element(a[i]);
        erase_element(a[i - k]);
    }
    printf("%lld\n", total_sum);

    return 0;
}